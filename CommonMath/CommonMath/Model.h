#pragma once
#include "Vector3.h"
#include "Vector2.h"
#include<vector>
#include "TGAImage.h"

class Model
{
public:
	Model(const std::string filename);
	~Model();

	void loadModel(const char* path);

	void load_texture(const std::string& name, const std::string& suffix, TGAImage& img);

private:

	int nverts() const;
	int nfaces() const;

	Vector3 normal(const Vector2& uv)const;//fetch the normal vector from the normal map texture
	Vector3 normal(const int face, const int nthvert)const;// per triangle corner normal vertex

	Vector3 vert(const int i)const;
	Vector3 vert(const int iface, const int nthvert)const;

	Vector2 uv(const int iface, const int nthvert)const;

	const TGAImage& diffuse()const { return m_diffuseMap; }
	const TGAImage& specular()const { return m_specularMap; }
private:
	std::vector<Vector3>		m_vecVertices;
	std::vector<Vector3>		m_vecNormals;
	std::vector<Vector3>		m_vecTexcoord;

	std::vector<int>			m_vecFace;

	std::vector<Vector3>		verts{};     // array of vertices
	std::vector<Vector2>		tex_coord{}; // per-vertex array of tex coords
	std::vector<Vector3>		norms{};     // per-vertex array of normal vectors
	std::vector<int>			facet_vrt{};
	std::vector<int>			facet_tex{};  // per-triangle indices in the above arrays
	std::vector<int>			facet_nrm{};

	TGAImage					m_diffuseMap;
	TGAImage					m_normalMap;
	TGAImage					m_specularMap;
};

