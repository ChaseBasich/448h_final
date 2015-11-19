#include "stdafx.h"
#include "Transform.h"

#include <glm\gtc\matrix_transform.hpp>


Transform::Transform()
{
	m = dmat4();
}

void Transform::RotateX(double angle) {
	m = rotate(m, angle, dvec3(1, 0, 0));
}

void Transform::RotateY(double angle) {
	m = rotate(m, angle, dvec3(0, 1, 0));
}

void Transform::RotateZ(double angle) {
	m = rotate(m, angle, dvec3(0, 0, 1));
}

void Transform::Rotate(double angle, dvec3 &axis) {
	m = rotate(m, angle, axis);
}

void Transform::Scale(double x, double y, double z) {
	m = scale(m, dvec3(x, y, z));
}

void Transform::Translate(double x, double y, double z) {
	m = translate(m, dvec3(x, y, z));
}



Transform::~Transform()
{
}

vec4 Transform::Apply(vec4 &v) {
	return m * v;
}