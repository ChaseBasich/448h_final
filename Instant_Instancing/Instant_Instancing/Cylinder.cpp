#include "stdafx.h"
#include "Cylinder.h"

#define DEFAULT_LENGTH 1.0


Cylinder::Cylinder(int sides)
{
	int points = sides + 1;
	vector<VertexHandle> topVertices;
	vector<VertexHandle> botVertices;


	//construct two circles with a center at 0, 0, -.5 and 0, 0, .5
	VertexHandle topCenter = mesh.add_vertex(PolyMesh::Point(0, 0, DEFAULT_LENGTH / 2));
	VertexHandle botCenter = mesh.add_vertex(PolyMesh::Point(0, 0, -DEFAULT_LENGTH / 2));

	//add points around the circle
	double deltaTheta = (2 * M_PI) / (float)points;
	for (int i = 0; i < points; i++) {
		double x = cos(i * deltaTheta);
		double y = sin(i * deltaTheta);

		topVertices.push_back(mesh.add_vertex(PolyMesh::Point(x, y, DEFAULT_LENGTH / 2)));
		botVertices.push_back(mesh.add_vertex(PolyMesh::Point(x, y, -DEFAULT_LENGTH / 2)));
	}

	//construct faces on circles
	std::vector<PolyMesh::VertexHandle>  face_vhandles;
	for (int i = 0; i < points; i++) {
		//top
		face_vhandles.clear();
		face_vhandles.push_back(topVertices[i]);
		face_vhandles.push_back(topVertices[(i + 1) % points]);
		face_vhandles.push_back(topCenter);
		mesh.add_face(face_vhandles);

		//bot
		face_vhandles.clear();
		face_vhandles.push_back(botVertices[i]);
		face_vhandles.push_back(botCenter);
		face_vhandles.push_back(botVertices[(i + 1) % points]);
		mesh.add_face(face_vhandles);
	}


	//add faces along the side

	for (int i = 0; i < points; i++) {
		face_vhandles.clear();
		face_vhandles.push_back(botVertices[(i + 1) % points]);
		face_vhandles.push_back(topVertices[(i + 1) % points]);		
		face_vhandles.push_back(topVertices[i]);
		face_vhandles.push_back(botVertices[i]);
		mesh.add_face(face_vhandles);
	}
}


Cylinder::~Cylinder()
{
}
