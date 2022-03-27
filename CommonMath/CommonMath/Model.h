#pragma once
#include "Vector3.h"
#include "Vector2.h"
#include<vector>

class Model
{
public:
	Model();
	~Model();

	void loadModel(const char* path);


private:
	std::vector<Vector3>		m_vecVertices;
	std::vector<Vector3>		m_vecNormals;
	std::vector<Vector3>		m_vecTexcoord;

	std::vector<int>			m_vecFace;
};

