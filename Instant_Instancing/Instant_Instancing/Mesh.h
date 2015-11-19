#pragma once

#include <string>

#define _USE_MATH_DEFINES
#include <OpenMesh/Core/IO/Options.hh>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include "Transform.h"
#include <unordered_set>

using namespace std;
using namespace OpenMesh;

typedef OpenMesh::TriMesh_ArrayKernelT<OpenMesh::DefaultTraits> TriMesh;

class Mesh
{
public:
	Mesh();
	~Mesh();
	void Write(string fileName);

	Mesh ApplyMatrix(Transform &t);

	Mesh Insert(Mesh &m);

protected:
	TriMesh mesh;
	
	unordered_set<Mesh *> subMeshes;
};

