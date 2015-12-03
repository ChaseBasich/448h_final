// Instant_Instancing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <OpenMesh/Core/IO/Options.hh>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>

#include <time.h>

#include "Mesh.h"
#include "Cube.h"
#include "Transform.h"
#include "Procedure.h"
#include "Parser.h"


using namespace std;
using namespace OpenMesh;

typedef OpenMesh::PolyMesh_ArrayKernelT<OpenMesh::DefaultTraits> PolyMesh;



int _tmain(int argc, _TCHAR* argv[])
{
	/*
	pair<float, float> zero(0, 0);
	pair<float, float> one(1, 1);
	pair<float, float> thirty(30, 30);

	Cube c;
	Procedure p1;
	p1.addInstance(c);
	p1.addTranslate(one, zero, zero);
	p1.addRotate(one, zero, zero, thirty);
	Procedure p2;
	p2.addProcedure(p1, 12);
	Mesh output = p2.eval();
	output.Write("Test.off");
	*/
	
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
	clock_t t;
	t = clock();
	Parser parser;
	string file = "helix.txt";
	parser.parseFile(file);
	t = clock() - t;
	printf("It took me %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);

	system("pause");
	return 0;
}

