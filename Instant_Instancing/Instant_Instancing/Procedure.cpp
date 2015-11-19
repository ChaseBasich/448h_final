#include "stdafx.h"
#include "Procedure.h"
#include <glm/gtc/matrix_transform.hpp>

void Procedure::applyTransform(glm::mat4 &t)
{
	if (steps.size() > 0 && steps[steps.size() - 1].type == TRANSFORM)
		steps[steps.size() - 1].transform *= t;
	else {
		steps.push_back(procedureNode(TRANSFORM));
		steps[steps.size() - 1].transform = t;
	}
}

void Procedure::applyRandomTransform(vector<pair<float, float>> *x, vector<pair<float, float>> *y, vector<pair<float, float>> *z, vector<pair<float, float>> *deg)
{
	steps[steps.size() - 1].xVals.swap(*x);
	steps[steps.size() - 1].yVals.swap(*y);
	steps[steps.size() - 1].zVals.swap(*z);
	if (deg != nullptr)
		steps[steps.size() - 1].degVals.swap(*deg);
}

void Procedure::addTranslate(float x, float y, float z)
{
	applyTransform(glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z)));	
}

void Procedure::addTranslate(vector<pair<float, float>> &x, vector<pair<float, float>> &y, vector<pair<float, float>> &z)
{
	nonRandom = false;
	steps.push_back(procedureNode(RTRANSLATE));
	applyRandomTransform(&x, &y, &z, nullptr);
}

void Procedure::addRotate(float x, float y, float z, float deg)
{
	applyTransform(glm::rotate(glm::mat4(1.0f), deg, glm::vec3(x, y, z)));
}

void Procedure::addRotate(vector<pair<float, float>> &x, vector<pair<float, float>> &y, vector<pair<float, float>> &z, vector<pair<float, float>> &deg)
{
	nonRandom = false;
	steps.push_back(procedureNode(RROTATE));
	applyRandomTransform(&x, &y, &z, &deg);
}

void Procedure::addScale(float x, float y, float z)
{
	applyTransform(glm::scale(glm::mat4(1.0f), glm::vec3(x, y, z)));
}

void Procedure::addScale(vector<pair<float, float>> &x, vector<pair<float, float>> &y, vector<pair<float, float>> &z)
{
	nonRandom = false;
	steps.push_back(procedureNode(RSCALE));
	applyRandomTransform(&x, &y, &z, nullptr);
}

void Procedure::addInstance(Mesh &m)
{
	if (nonRandom){
		if (steps.size() == 0)
			nonRandomMesh.Insert(m);
		else {
			m.ApplyMatrix(steps[0].transform);
			nonRandomMesh.Insert(m);
		}
	}
	else {
		steps.push_back(procedureNode(INSTANCE));
		steps[steps.size() - 1].m = &m;
	}
}

void Procedure::addProcedure(Procedure &p, int n = 1)
{
	nonRandom = nonRandom && p.nonRandom;
	steps.reserve(steps.size() + n * p.steps.size());
	for (int i = 0; i < n; i++) {
		addInstance(p.nonRandomMesh);
		steps.insert(steps.end(), p.steps.begin(), p.steps.end());
	}
}

Mesh Procedure::eval()
{
	Mesh outMesh;
	outMesh.Insert(nonRandomMesh);
	glm::mat4 currTransform = glm::mat4();

	for (size_t i = 0; i < steps.size(); i++) {
		switch (steps[i].type) {
		case TRANSFORM:
			currTransform *= steps[i].transform;
			break;
		case INSTANCE:
			(*steps[i].m).ApplyMatrix(currTransform);
			outMesh.Insert(*steps[i].m);
			break;
		default:
			/*
			size_t index = rand() % steps[i].xVals.size();
			pair<float, float> vals = steps[i].xVals;
			float x = (float)rand() / RAND_MAX * (vals.second - vals.first) + vals.first;
			
			index = rand() % steps[i].yVals.size();
			vals = steps[i].yVals;
			float y = (float)rand() / RAND_MAX * (vals.second - vals.first) + vals.first;
			
			index = rand() % steps[i].zVals.size();
			vals = steps[i].zVals;
			float z = (float)rand() / RAND_MAX * (vals.second - vals.first) + vals.first;
			
			switch (steps[i].type) {
			case RTRANSLATE:
				currTransform *= glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
				break;
			case RROTATE:
				break;
			case RSCALE:
				break;
			}
			*/
			break;
		}
	}

	return outMesh;
}