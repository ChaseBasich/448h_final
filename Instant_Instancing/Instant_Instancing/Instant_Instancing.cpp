// Instant_Instancing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <OpenMesh/Core/IO/Options.hh>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>

#include "Mesh.h"
#include "Cube.h"
#include "Transform.h"
#include "Procedure.h"


using namespace std;
using namespace OpenMesh;

typedef OpenMesh::PolyMesh_ArrayKernelT<OpenMesh::DefaultTraits> PolyMesh;



int _tmain(int argc, _TCHAR* argv[])
{
	
	Cube c;
	Procedure p1;
	p1.addInstance(c);
	p1.addTranslate(1, 0, 0);
	p1.addRotate(1, 0, 0, 30);
	Procedure p2;
	p2.addProcedure(p1, 12);
	Mesh output = p2.eval();
	output.Write("Test.off");
	
	/*
	Cube c;
	Cube c2;
	Transform t;
	t.RotateX(45);
	t.RotateY(45);
	c.ApplyMatrix(t);
	c.Insert(c2);
	Transform t2;
	t2.Translate(10, 0, 0);
	c.ApplyMatrix(t2);

	c.Write("output3.off");
	*/

	return 0;
}

