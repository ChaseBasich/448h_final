// Instant_Instancing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>

#define _USE_MATH_DEFINES
#include <OpenMesh/Core/IO/Options.hh>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>

#include "Mesh.h"
#include "Cube.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Transform.h"
#include "Procedure.h"
#include "SymbolicMatrix.h"
#include <glm\gtc\matrix_transform.hpp>


using namespace std;
using namespace OpenMesh;

typedef OpenMesh::PolyMesh_ArrayKernelT<OpenMesh::DefaultTraits> PolyMesh;



int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));

	SymbolicMatrix sm;
	sm = sm.RotateZ(60, 60);
	sm = sm.Translate(5, 5, 5, 5, 5, 5);
	sm = sm.Scale(2, 2, 1, 1, 1, 1);

	dmat4 m = sm.Eval();

	for (int i = 0; i < 4; i++) {
		for (int n = 0; n < 4; n++) {
			cout << m[n][i] << endl;
		}
	}

	cout << endl << endl;

	m = dmat4();
	m = glm::rotate(m, 1.0472, dvec3(0.0, 0.0, 1.0));
	m = glm::translate(m, dvec3(5, 5, 5));
	m = glm::scale(m, dvec3(2, 1, 1));

	for (int i = 0; i < 4; i++) {
		for (int n = 0; n < 4; n++) {
			cout << m[n][i] << endl;
		}
	}

	
	int unused;
	cin >> unused;

	/*
	Cube c;
	Procedure p1;
	p1.addInstance(c);
	p1.addTranslate(2, 0, 0);
	p1.addRotate(1, 0, 0, 30);
	Procedure p2;
	p2.addProcedure(p1, 12);
	Mesh output = p2.eval();
	output.Write("Test.off");
	
	
	Sphere s; 
	Sphere is(false);
	Transform t;
	t.Translate(5, 0, 0);
	is.ApplyMatrix(t);
	s.Insert(is);
	s.Write("spheres.off");


	
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

