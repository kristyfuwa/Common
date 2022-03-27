#include "Model.h"
#include "assimp/scene.h"
#include "assimp/cimport.h"
#include "assimp/postprocess.h"

Model::Model()
{

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
}
 