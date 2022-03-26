#pragma once

class Vector3
{
public:
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(const Vector3& vec3);

	float		dot(const Vector3& vec3);
	Vector3		cross(const Vector3& vec3);
	Vector3		normalize();
	float		length();

	Vector3		operator-(const Vector3& vec);
	Vector3		operator+(const Vector3& vec);
	Vector3		operator*(float v);
	Vector3		operator/(float v);

	static const Vector3 ZERO;
private:
	float m_fx;
	float m_fy;
	float m_fz;
};

