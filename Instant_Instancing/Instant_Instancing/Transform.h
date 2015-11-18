#pragma once

#include <glm\glm.hpp>
using namespace glm;
class Transform
{
public:
	Transform();
	~Transform();

	void RotateX(double angle);
	void RotateY(double angle);
	void RotateZ(double angle);

	void Scale(double x, double y, double z);

	void Translate(double x, double y, double z);

	vec4 Apply(vec4 &v);

private:
	dmat4 m;
};

