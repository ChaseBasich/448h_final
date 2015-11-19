// Instant_Instancing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <OpenMesh/Core/IO/Options.hh>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>

#include "Mesh.h"
#include "Cube.h"
#include "Transform.h"


using namespace std;
using namespace OpenMesh;

typedef OpenMesh::TriMesh_ArrayKernelT<OpenMesh::DefaultTraits> TriMesh;



int _tmain(int argc, _TCHAR* argv[])
{
	Cube c;
	Cube c2;
	Transform t;
	t.RotateX(45);
	t.RotateY(45);
	c.ApplyMatrix(t);
	c.Write("output2.off");

	c.Insert(c2);
	Transform t2;
	t2.Translate(10, 0, 0);
	c.ApplyMatrix(t2);

	c.Write("output3.off");

	return 0;
}

