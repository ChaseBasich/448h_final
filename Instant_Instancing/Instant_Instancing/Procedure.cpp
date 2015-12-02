#include "stdafx.h"
#include "Procedure.h"
#include <glm/gtc/matrix_transform.hpp>

#define DEGREES_TO_RADIANS 0.01745329251994329576923690768489

void Procedure::applyTransform(glm::mat4 &t)
{
	bool added = false;

	if (steps.size() > 0) {
		if (steps.back().type == SYMBOLIC) {
			steps.back().smat = SymbolicMatrix(t) * steps.back().smat;
			added = true;
		}
		else if (steps.back().type == TRANSFORM) {
			steps.back().transform = t * steps.back().transform;
			added = true;
		}
	}

	if (!added) {
		steps.push_back(procedureNode(TRANSFORM));
		steps.back().transform = t;
	}
}

void Procedure::applyRandomTransform(SymbolicMatrix &smat)
{
	nonRandom = false;
	bool added = false;

	if (steps.size() > 0) {
		if (steps.back().type == SYMBOLIC) {
			steps.back().smat = smat * steps.back().smat;
			added = true;
		}
		else if (steps.back().type == TRANSFORM) {
			steps.back().type = SYMBOLIC;
			steps.back().smat = smat * SymbolicMatrix(steps.back().transform);
			added = true;
		}
	}

	if (!added) {
		steps.push_back(procedureNode(SYMBOLIC));
		steps.back().smat = smat;
	}	
}

void Procedure::addTranslate(pair<float, float> &x, pair<float, float> &y, pair<float, float> &z)
{
	if (x.first == x.second &&
		y.first == y.second &&
		z.first == z.second){
		applyTransform(glm::translate(glm::mat4(1.0f), glm::vec3(x.first, y.first, z.first)));
	}
	else {
		SymbolicMatrix smat;
		smat = smat.Translate(x.first, x.second, y.first, y.second, z.first, z.second);
		applyRandomTransform(smat);
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
		SymbolicMatrix smat;
		if (x.first != 0 && x.second != 0 &&
			y.first == 0 && y.second == 0 &&
			z.first == 0 && z.second == 0) {
			smat = smat.RotateX(deg.first, deg.second);
		}
		else if (x.first == 0 && x.second == 0 &&
				 y.first != 0 && y.second != 0 &&
				 z.first == 0 && z.second == 0) {
			SymbolicMatrix smat;
			smat = smat.RotateY(deg.first, deg.second);
		}
		else if (x.first == 0 && x.second == 0 &&
				 y.first == 0 && y.second == 0 &&
				 z.first != 0 && z.second != 0) {
			SymbolicMatrix smat;
			smat = smat.RotateZ(deg.first, deg.second);
		}

		applyRandomTransform(smat);
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
		SymbolicMatrix smat;
		smat = smat.Scale(x.first, x.second, y.first, y.second, z.first, z.second);
		applyRandomTransform(smat);
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
			case SYMBOLIC:
			{
				currTransform = steps[i].smat.Eval() * currTransform;
			}
		}
	}

	return outMesh;
}