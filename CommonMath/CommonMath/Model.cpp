#include "Model.h"
#include "assimp/scene.h"
#include "assimp/cimport.h"
#include "assimp/postprocess.h"
#include <iostream>
#include <sstream>

Model::Model(const std::string filename)
{
	std::ifstream in;
	in.open(filename, std::ifstream::in);
	if (in.fail()) return;
	std::string line;
	while (!in.eof()) {
		std::getline(in, line);
		std::istringstream iss(line.c_str());
		char trash;
		if (!line.compare(0, 2, "v ")) {
			iss >> trash;
			Vector3 v;
			for (int i = 0; i < 3; i++)
				iss >> v[i];
			verts.push_back(v);
		}
		else if (!line.compare(0, 3, "vn ")) {
			iss >> trash >> trash;
			Vector3 n;
			for (int i = 0; i < 3; i++) iss >> n[i];
			norms.push_back(n.normalize());
		}
		else if (!line.compare(0, 3, "vt ")) {
			iss >> trash >> trash;
			Vector2 uv;
			for (int i = 0; i < 2; i++) iss >> uv[i];
			tex_coord.push_back({ uv.m_fx, 1 - uv.m_fy });
		}
		else if (!line.compare(0, 2, "f ")) {
			int f, t, n;
			iss >> trash;
			int cnt = 0;
			while (iss >> f >> trash >> t >> trash >> n) {
				facet_vrt.push_back(--f);
				facet_tex.push_back(--t);
				facet_nrm.push_back(--n);
				cnt++;
			}
			if (3 != cnt) {
				std::cerr << "Error: the obj file is supposed to be triangulated" << std::endl;
				in.close();
				return;
			}
		}
	}
	in.close();
	std::cerr << "# v# " << nverts() << " f# " << nfaces() << " vt# " << tex_coord.size() << " vn# " << norms.size() << std::endl;
	load_texture(filename, "_diffuse.tga", m_diffuseMap);
	load_texture(filename, "_nm_tangent.tga", m_normalMap);
	load_texture(filename, "_spec.tga", m_specularMap);
}

Model::~Model()
{

}

void Model::loadModel(const char* path)
{
	const aiScene* scene = aiImportFile(path, aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices |
		aiProcess_MakeLeftHanded | aiProcess_Triangulate | aiProcess_SortByPType);
	if (scene && scene->mNumMeshes > 0)
	{
		for (size_t i = 0; i < scene->mNumMeshes; ++i)//use one mesh
		{
			aiMesh* mesh = scene->mMeshes[i];
			for (size_t j = 0; j < mesh->mNumVertices; ++j)
			{
				Vector3 vert = *(Vector3*)(&mesh->mVertices[j]);
				m_vecVertices.push_back(vert);
				Vector3 normal = *(Vector3*)(&mesh->mNormals[j]);
				m_vecNormals.push_back(normal);
				Vector3 tex_coord = *(Vector3*)(&mesh->mTextureCoords[0][j]);
				m_vecTexcoord.push_back(tex_coord);
			}
			for (size_t j = 0; j < mesh->mNumFaces; ++j)
			{
				aiFace face = mesh->mFaces[j];
				for (size_t k = 0; k < face.mNumIndices; ++k)
					m_vecFace.push_back(face.mIndices[k]);
			}
			break;
		}
	}
	load_texture(path, "_diffuse.tga",		m_diffuseMap);
	load_texture(path, "_nm_tangent.tga" ,	m_normalMap);
	load_texture(path, "_spec.tga",			m_specularMap);
}


void Model::load_texture(const std::string& name, const std::string& suffix, TGAImage& img)
{
	size_t dot = name.find_last_of(".");
	if (dot == std::string::npos) return;
	std::string filename = filename.substr(0, dot) + suffix;
	img.read_tga_data(filename.data());
}

int Model::nverts() const
{
	return verts.size();
}

int Model::nfaces() const
{
	return facet_vrt.size();
}

Vector3 Model::normal(const Vector2& uv)const
{
	TGAColor color = m_normalMap.getColor(uv.m_fx*m_normalMap.width(), uv.m_fy*m_normalMap.height());
	return Vector3(Vector3(color.bgra[2],color.bgra[1],color[0])/255.0f * 2) - Vector3(1, 1, 1);
}

Vector3 Model::normal(const int iface, const int nthvert) const
{
	return norms[facet_nrm[iface * 3 + nthvert]];
}

Vector3 Model::vert(const int i) const
{
	return verts[i];
}

Vector3 Model::vert(const int iface, const int nthvert) const
{
	return verts[facet_vrt[iface * 3 + nthvert]];
}

Vector2 Model::uv(const int iface, const int nthvert) const
{
	return tex_coord[facet_tex[iface * 3 + nthvert]];
}

