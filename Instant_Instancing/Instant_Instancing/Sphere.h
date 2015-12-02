#pragma once
#include "Mesh.h"
class Sphere : public Mesh
{
public:
	Sphere(bool UV = true);
	~Sphere();
private:
	void UVSphere();
	void IcoSphere();
};

