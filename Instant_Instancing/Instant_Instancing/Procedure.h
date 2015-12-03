#include <vector>
#include <glm\glm.hpp>
#include "Mesh.h"

using namespace std;

#pragma once
class Procedure{
public:
	enum transformType{
		TRANSFORM,
		RTRANSLATE,
		RROTATE,
		RSCALE,
		INSTANCE,
		PROCEDURE
	};

	struct procedureNode{
		transformType type;
		glm::mat4 transform;
		pair<float, float> xVals, yVals, zVals, degVals;
		Mesh *m;
		Procedure *p;
		int pnmin;
		int pnmax;

		procedureNode(transformType t): type(t), pnmin(-1), pnmax(-1) {}
	};

	Procedure() : nonRandom(true), firstTransformPos(-1), hasProcedureNodes(false) {}
	~Procedure() {}

	void addTranslate(pair<float, float> &x, pair<float, float> &y, pair<float, float> &z);
	void addRotate(pair<float, float> &x, pair<float, float> &y, pair<float, float> &z, pair<float, float> &deg);
	void addScale(pair<float, float> &x, pair<float, float> &y, pair<float, float> &z);

	void addInstance(Mesh &m);
	void addProcedure(Procedure &p, int n, int nmax, bool pre_eval = false);

	Mesh eval(glm::mat4 *result = nullptr);

	vector<procedureNode> steps;
	bool nonRandom;
	Mesh nonRandomMesh;

private:
	void applyTransform(glm::mat4 &t);
	void applyRandomTransform(pair<float, float> &x, pair<float, float> &y, pair<float, float> &z);
	void applyRandomTransform(pair<float, float> &x, pair<float, float> &y, pair<float, float> &z, pair<float, float> &deg);

	int firstTransformPos;
	bool hasProcedureNodes;
};

/*
class Procedure{
public:
	Procedure() {}
	~Procedure() {}

	void applyTransform(glm::mat4 t, int n = 1);

	void t(float x, float y, float z);
	void r(float x, float y, float z, float degrees);
	void s(float x, float y, float z);

	void instance(Mesh &m);

	void add(Procedure &p, int n = 1);

	glm::mat4 transform;
	Mesh mesh;
};
*/