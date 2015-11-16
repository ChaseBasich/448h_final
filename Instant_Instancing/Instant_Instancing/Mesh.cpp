#include "stdafx.h"
#include "Mesh.h"


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
