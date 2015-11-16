// Instant_Instancing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <OpenMesh/Core/IO/Options.hh>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>

#include <GL\freeglut.h>

#include "Mesh.h"
#include "Cube.h"


using namespace std;
using namespace OpenMesh;

typedef OpenMesh::TriMesh_ArrayKernelT<OpenMesh::DefaultTraits> TriMesh;



int _tmain(int argc, _TCHAR* argv[])
{
	Cube c;
	c.Write("output2.off");

	return 0;
}

