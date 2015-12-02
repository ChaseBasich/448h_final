#include "stdafx.h"
#include "Sphere.h"


void Sphere::UVSphere() {
	int rings = 10;

	double deltaTheta = (M_PI) / (rings + 2);
	double deltaPhi = (2 * M_PI) / rings;

	PolyMesh::VertexHandle northCap = mesh.add_vertex(PolyMesh::Point(0, 0, 1));
	PolyMesh::VertexHandle southCap = mesh.add_vertex(PolyMesh::Point(0, 0, -1));
	vector<VertexHandle> vertices;

	for (int i = 0; i < rings + 1; i++){
		for (int n = 0; n < rings; n++){
			double theta = (i + 1) * deltaTheta;
			double phi = n * deltaPhi;
			double x = sin(theta) * cos(phi);
			double y = sin(theta) * sin(phi);
			double z = cos(theta);
			vertices.push_back(mesh.add_vertex(PolyMesh::Point(x, y, z)));
		}
	}

	std::vector<PolyMesh::VertexHandle>  face_vhandles;


	for (int i = 0; i < rings; i++){
		face_vhandles.clear();
		face_vhandles.push_back(vertices[i]);
		face_vhandles.push_back(vertices[(i + 1) % rings]);
		face_vhandles.push_back(northCap);

		mesh.add_face(face_vhandles);
	}

	for (int i = 0; i < rings; i++){
		face_vhandles.clear();
		face_vhandles.push_back(vertices[rings * rings + (i + 1) % rings]);
		face_vhandles.push_back(vertices[rings * rings + i]);
		face_vhandles.push_back(southCap);
		mesh.add_face(face_vhandles);
	}


	for (int i = 0; i < rings; i++){
		for (int n = 0; n < rings; n++){
			face_vhandles.clear();



			face_vhandles.push_back(vertices[(i + 1) * rings + (n + 1) % rings]);
			face_vhandles.push_back(vertices[i * rings + (n + 1) % rings]);
			face_vhandles.push_back(vertices[i * rings + n]);
			face_vhandles.push_back(vertices[(i + 1) * rings + n]);

			mesh.add_face(face_vhandles);
		}
	}
}

void Sphere::IcoSphere() {
	vector<VertexHandle> vertices;
	double t = (1.0 + sqrt(5.0)) / 2.0;

	vertices.push_back(mesh.add_vertex(PolyMesh::Point(-1, t, 0).normalize()));
	vertices.push_back(mesh.add_vertex(PolyMesh::Point(1, t, 0).normalize()));
	vertices.push_back(mesh.add_vertex(PolyMesh::Point(-1, -t, 0).normalize()));
	vertices.push_back(mesh.add_vertex(PolyMesh::Point(1, -t, 0).normalize()));

	vertices.push_back(mesh.add_vertex(PolyMesh::Point(0, -1, t).normalize()));
	vertices.push_back(mesh.add_vertex(PolyMesh::Point(0, 1, t).normalize()));
	vertices.push_back(mesh.add_vertex(PolyMesh::Point(0, -1, -t).normalize()));
	vertices.push_back(mesh.add_vertex(PolyMesh::Point(0, 1, -t).normalize()));

	vertices.push_back(mesh.add_vertex(PolyMesh::Point(t, 0, -1).normalize()));
	vertices.push_back(mesh.add_vertex(PolyMesh::Point(t, 0, 1).normalize()));
	vertices.push_back(mesh.add_vertex(PolyMesh::Point(-t, 0, -1).normalize()));
	vertices.push_back(mesh.add_vertex(PolyMesh::Point(-t, 0, 1).normalize()));


	std::vector<PolyMesh::VertexHandle>  face_vhandles;

	face_vhandles.clear();
	face_vhandles.push_back(vertices[0]);
	face_vhandles.push_back(vertices[11]);
	face_vhandles.push_back(vertices[5]);
	mesh.add_face(face_vhandles);

	face_vhandles.clear();
	face_vhandles.push_back(vertices[0]);
	face_vhandles.push_back(vertices[5]);
	face_vhandles.push_back(vertices[1]);
	mesh.add_face(face_vhandles);

	face_vhandles.clear();
	face_vhandles.push_back(vertices[0]);
	face_vhandles.push_back(vertices[1]);
	face_vhandles.push_back(vertices[7]);
	mesh.add_face(face_vhandles);

	face_vhandles.clear();
	face_vhandles.push_back(vertices[0]);
	face_vhandles.push_back(vertices[7]);
	face_vhandles.push_back(vertices[10]);
	mesh.add_face(face_vhandles);

	face_vhandles.clear();
	face_vhandles.push_back(vertices[0]);
	face_vhandles.push_back(vertices[10]);
	face_vhandles.push_back(vertices[11]);
	mesh.add_face(face_vhandles);


	//next set of faces
	face_vhandles.clear();
	face_vhandles.push_back(vertices[1]);
	face_vhandles.push_back(vertices[5]);
	face_vhandles.push_back(vertices[9]);
	mesh.add_face(face_vhandles);

	face_vhandles.clear();
	face_vhandles.push_back(vertices[5]);
	face_vhandles.push_back(vertices[11]);
	face_vhandles.push_back(vertices[4]);
	mesh.add_face(face_vhandles);

	face_vhandles.clear();
	face_vhandles.push_back(vertices[11]);
	face_vhandles.push_back(vertices[10]);
	face_vhandles.push_back(vertices[2]);
	mesh.add_face(face_vhandles);

	face_vhandles.clear();
	face_vhandles.push_back(vertices[10]);
	face_vhandles.push_back(vertices[7]);
	face_vhandles.push_back(vertices[6]);
	mesh.add_face(face_vhandles);

	face_vhandles.clear();
	face_vhandles.push_back(vertices[7]);
	face_vhandles.push_back(vertices[1]);
	face_vhandles.push_back(vertices[8]);
	mesh.add_face(face_vhandles);

	//next set of faces
	face_vhandles.clear();
	face_vhandles.push_back(vertices[3]);
	face_vhandles.push_back(vertices[9]);
	face_vhandles.push_back(vertices[4]);
	mesh.add_face(face_vhandles);

	face_vhandles.clear();
	face_vhandles.push_back(vertices[3]);
	face_vhandles.push_back(vertices[4]);
	face_vhandles.push_back(vertices[2]);
	mesh.add_face(face_vhandles);

	face_vhandles.clear();
	face_vhandles.push_back(vertices[3]);
	face_vhandles.push_back(vertices[2]);
	face_vhandles.push_back(vertices[6]);
	mesh.add_face(face_vhandles);

	face_vhandles.clear();
	face_vhandles.push_back(vertices[3]);
	face_vhandles.push_back(vertices[6]);
	face_vhandles.push_back(vertices[8]);
	mesh.add_face(face_vhandles);

	face_vhandles.clear();
	face_vhandles.push_back(vertices[3]);
	face_vhandles.push_back(vertices[8]);
	face_vhandles.push_back(vertices[9]);
	mesh.add_face(face_vhandles);

	//last set of faces
	face_vhandles.clear();
	face_vhandles.push_back(vertices[4]);
	face_vhandles.push_back(vertices[9]);
	face_vhandles.push_back(vertices[5]);
	mesh.add_face(face_vhandles);

	face_vhandles.clear();
	face_vhandles.push_back(vertices[2]);
	face_vhandles.push_back(vertices[4]);
	face_vhandles.push_back(vertices[11]);
	mesh.add_face(face_vhandles);

	face_vhandles.clear();
	face_vhandles.push_back(vertices[6]);
	face_vhandles.push_back(vertices[2]);
	face_vhandles.push_back(vertices[10]);
	mesh.add_face(face_vhandles);

	face_vhandles.clear();
	face_vhandles.push_back(vertices[8]);
	face_vhandles.push_back(vertices[6]);
	face_vhandles.push_back(vertices[7]);
	mesh.add_face(face_vhandles);

	face_vhandles.clear();
	face_vhandles.push_back(vertices[9]);
	face_vhandles.push_back(vertices[8]);
	face_vhandles.push_back(vertices[1]);
	mesh.add_face(face_vhandles);	
}

Sphere::Sphere(bool UV)
{
	if (UV) {
		UVSphere();
	}
	else {
		IcoSphere();
	}
		
}




Sphere::~Sphere()
{
}
