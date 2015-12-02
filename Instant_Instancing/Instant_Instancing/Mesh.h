#pragma once

#include <string>

#define _USE_MATH_DEFINES
#include <OpenMesh/Core/IO/Options.hh>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#include "Transform.h"
#include <unordered_set>

using namespace std;
using namespace OpenMesh;

typedef OpenMesh::PolyMesh_ArrayKernelT <OpenMesh::DefaultTraits> PolyMesh;

class Mesh
{
public:
	Mesh();
	Mesh(string filename);
	~Mesh();

	void Write(string fileName);
	void Read(string filename);

	Mesh ApplyMatrix(Transform &t);
	Mesh ApplyMatrix(mat4 &m);

	Mesh Insert(Mesh &m);

protected:
	PolyMesh mesh;
};

