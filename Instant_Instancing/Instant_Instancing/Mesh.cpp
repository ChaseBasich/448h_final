#include "stdafx.h"
#include "Mesh.h"

#include <glm\glm.hpp>
#include <unordered_map>

glm::vec4 toGLM(PolyMesh::Point &p) {
	return glm::vec4(p[0], p[1], p[2], 1);
}

PolyMesh::Point toOpenMesh(glm::vec4 v) {
	return PolyMesh::Point(v[0], v[1], v[2]);
}


Mesh Mesh::ApplyMatrix(Transform &t){
	for (PolyMesh::VertexIter v_it = mesh.vertices_begin(); v_it != mesh.vertices_end(); ++v_it) {
		const PolyMesh::VertexHandle vh = (*v_it);
		glm::vec4 v(toGLM(mesh.point(vh)));
		v = t.Apply(v);

		mesh.point(vh) = toOpenMesh(v);
	}
	return *this;
}

Mesh Mesh::ApplyMatrix(mat4 &m) {
	for (PolyMesh::VertexIter v_it = mesh.vertices_begin(); v_it != mesh.vertices_end(); ++v_it) {
		const PolyMesh::VertexHandle vh = (*v_it);
		glm::vec4 v(toGLM(mesh.point(vh)));
		v = m * v;

		mesh.point(vh) = toOpenMesh(v);
	}

	return *this;
}

namespace std
{
	template <>
	struct hash<PolyMesh::Point>
	{
		size_t operator()(PolyMesh::Point const &p) const
		{
			return (
			(51 + std::hash<int>()(p[0])) * 51
			+ std::hash<int>()(p[1]) * 53 + std::hash<int>()(p[2])
			);
		}
	};
}

Mesh Mesh::Insert(Mesh &m) {
	unordered_map<PolyMesh::Point, PolyMesh::VertexHandle> vertexMap;

	for (PolyMesh::VertexIter v_it = m.mesh.vertices_begin(); v_it != m.mesh.vertices_end(); ++v_it) {
		PolyMesh::VertexHandle vh = *v_it;
		PolyMesh::Point p = m.mesh.point(vh);
		vh = mesh.add_vertex(p);
		vertexMap.insert({ p, vh });
	}

	std::vector<PolyMesh::VertexHandle>  face_vhandles;

	for (PolyMesh::FaceIter f_it = m.mesh.faces_begin(); f_it != m.mesh.faces_end(); ++f_it) {
		PolyMesh::FaceHandle fh = *f_it;
		face_vhandles.clear();
		PolyMesh::FaceVertexIter fv_it = m.mesh.fv_begin(fh);
		while (fv_it != m.mesh.fv_end(fh)){
			PolyMesh::Point p = m.mesh.point(*fv_it);
			face_vhandles.push_back(vertexMap.at(p));
			fv_it++;
		}
		mesh.add_face(face_vhandles);
	}
	return *this;
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

void Mesh::Read(string filename) {
	try
	{
		if (!OpenMesh::IO::read_mesh(mesh, filename))
		{
			std::cerr << "Error loading mesh from file " << filename << std::endl;
		}
	} 
	catch (std::exception& x)
	{
		std::cerr << x.what() << std::endl;
	}
}

Mesh::Mesh(string filename) {
	Read(filename);
}

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}
