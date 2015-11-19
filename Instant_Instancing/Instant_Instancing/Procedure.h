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
		INSTANCE
	};

	struct procedureNode{
		transformType type;
		glm::mat4 transform;
		vector<pair<float, float>> xVals, yVals, zVals, degVals;
		Mesh *m;

		procedureNode(transformType t): type(t) {}
	};

	Procedure() : nonRandom(true) {}
	~Procedure() {}

	void addTranslate(float x, float y, float z);
	void addTranslate(vector<pair<float, float>> &x, vector<pair<float, float>> &y, vector<pair<float, float>> &z);

	void addRotate(float x, float y, float z, float deg);
	void addRotate(vector<pair<float, float>> &x, vector<pair<float, float>> &y, vector<pair<float, float>> &z, vector<pair<float, float>> &deg);

	void addScale(float x, float y, float z);
	void addScale(vector<pair<float, float>> &x, vector<pair<float, float>> &y, vector<pair<float, float>> &z);

	void addInstance(Mesh &m);
	void addProcedure(Procedure &p, int n);

	Mesh eval();

	vector<procedureNode> steps;
	bool nonRandom;
	Mesh nonRandomMesh;

private:
	void applyTransform(glm::mat4 &t);
	void applyRandomTransform(vector<pair<float, float>> *x, vector<pair<float, float>> *y, vector<pair<float, float>> *z, vector<pair<float, float>> *deg);
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