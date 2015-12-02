#include "stdafx.h"
#include "Procedure.h"
#include <glm/gtc/matrix_transform.hpp>

#define DEGREES_TO_RADIANS 0.01745329251994329576923690768489

void Procedure::applyTransform(glm::mat4 &t)
{
	if (steps.size() > 0 && steps.back().type == TRANSFORM)
		steps.back().transform = t * steps.back().transform;
	else {
		steps.push_back(procedureNode(TRANSFORM));
		steps.back().transform = t;
	}
}

void Procedure::applyRandomTransform(pair<float, float> &x, pair<float, float> &y, pair<float, float> &z)
{
	steps.back().xVals = x;
	steps.back().yVals = y;
	steps.back().zVals = z;
}

void Procedure::applyRandomTransform(pair<float, float> &x, pair<float, float> &y, pair<float, float> &z, pair<float, float> &deg)
{
	applyRandomTransform(x, y, z);
	steps.back().degVals = deg;
}

void Procedure::addTranslate(pair<float, float> &x, pair<float, float> &y, pair<float, float> &z)
{
	if (x.first == x.second &&
		y.first == y.second &&
		z.first == z.second){
		applyTransform(glm::translate(glm::mat4(1.0f), glm::vec3(x.first, y.first, z.first)));
	}
	else {
		nonRandom = false;
		steps.push_back(procedureNode(RTRANSLATE));
		applyRandomTransform(x, y, z);
	}
}

void Procedure::addRotate(pair<float, float> &x, pair<float, float> &y, pair<float, float> &z, pair<float, float> &deg)
{
	deg.first *= DEGREES_TO_RADIANS;
	deg.second *= DEGREES_TO_RADIANS;

	if (x.first == x.second &&
		y.first == y.second &&
		z.first == z.second &&
		deg.first == deg.second){
		applyTransform(glm::rotate(glm::mat4(1.0f), deg.first, glm::vec3(x.first, y.first, z.first)));
	}
	else {
		nonRandom = false;
		steps.push_back(procedureNode(RROTATE));
		applyRandomTransform(x, y, z, deg);
	}
}

void Procedure::addScale(pair<float, float> &x, pair<float, float> &y, pair<float, float> &z)
{
	if (x.first == x.second &&
		y.first == y.second &&
		z.first == z.second){
		applyTransform(glm::scale(glm::mat4(1.0f), glm::vec3(x.first, y.first, z.first)));
	}
	else {
		nonRandom = false;
		steps.push_back(procedureNode(RSCALE));
		applyRandomTransform(x, y, z);
	}
}

void Procedure::addInstance(Mesh &m)
{
	if (nonRandom){
		if (steps.size() == 0)
			nonRandomMesh.Insert(m);
		else {
			Mesh m2(m);
			m2.ApplyMatrix(steps[0].transform);
			nonRandomMesh.Insert(m2);
		}
	}
	else {
		steps.push_back(procedureNode(INSTANCE));
		steps.back().m = &m;
	}
}

void Procedure::addProcedure(Procedure &p, int n = 1)
{
	nonRandom = nonRandom && p.nonRandom;
	steps.reserve(steps.size() + n * p.steps.size());
	for (int i = 0; i < n; i++) {
		addInstance(p.nonRandomMesh);
		
		if (nonRandom &&steps.size() != 0 && p.steps.size() != 0)
			steps[0].transform *= p.steps[0].transform;
		else
			steps.insert(steps.end(), p.steps.begin(), p.steps.end());
	}
}

Mesh Procedure::eval()
{
	if (nonRandom) {
		//if there is no randomness, mesh is already up to date
		return nonRandomMesh;
	}


	Mesh outMesh;
	outMesh.Insert(nonRandomMesh);
	glm::mat4 currTransform = glm::mat4();

	for (size_t i = 0; i < steps.size(); i++) {
		switch (steps[i].type) {
			case TRANSFORM:
				currTransform = steps[i].transform * currTransform;
				break;
			case INSTANCE:
			{
				Mesh m2(*steps[i].m);
				m2.ApplyMatrix(currTransform);
				outMesh.Insert(m2);
				break;
			}
			default:
			{
				float x = (float)rand() / RAND_MAX * (steps[i].xVals.second - steps[i].xVals.first) + steps[i].xVals.first;
				float y = (float)rand() / RAND_MAX * (steps[i].yVals.second - steps[i].yVals.first) + steps[i].yVals.first;
				float z = (float)rand() / RAND_MAX * (steps[i].zVals.second - steps[i].zVals.first) + steps[i].zVals.first;
			
				switch (steps[i].type) {
					case RTRANSLATE:
						currTransform = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z)) * currTransform;
						break;
					case RROTATE:
					{
						float deg = (float)rand() / RAND_MAX * (steps[i].degVals.second - steps[i].degVals.first) + steps[i].degVals.first;
						currTransform = glm::rotate(glm::mat4(1.0f), deg, glm::vec3(x, y, z)) * currTransform;
						break;
					}
					case RSCALE:
						currTransform = glm::scale(glm::mat4(1.0f), glm::vec3(x, y, z)) * currTransform;
						break;
				}
				break;
			}
		}
	}

	return outMesh;
}