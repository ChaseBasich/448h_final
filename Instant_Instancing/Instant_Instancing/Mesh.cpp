#include "stdafx.h"
#include "Mesh.h"

#include <glm\glm.hpp>

glm::vec4 toGLM(TriMesh::Point &p) {
	return glm::vec4(p[0], p[1], p[2], 1);
}

TriMesh::Point toOpenMesh(glm::vec4 v) {
	return TriMesh::Point(v[0], v[1], v[2]);
}


Mesh Mesh::ApplyMatrix(Transform &t){
	for (TriMesh::VertexIter v_it = mesh.vertices_begin(); v_it != mesh.vertices_end(); ++v_it) {
		const TriMesh::VertexHandle vh = (*v_it);
		glm::vec4 v(toGLM(mesh.point(vh)));
		v = t.Apply(v);

		mesh.point(vh) = toOpenMesh(v);
	}
	return *this;
}

Mesh::Mesh()
{
}

void Mesh::Write(string fileName) {
	// write mesh to fileName
	try
	{
		if (!OpenMesh::IO::write_mesh(mesh, fileName))
		{
			std::cerr << "Cannot write mesh to file "<< fileName << std::endl;
		}
	}
	catch (std::exception& x)
	{
		std::cerr << x.what() << std::endl;
	}
}

Mesh::~Mesh()
{
}
