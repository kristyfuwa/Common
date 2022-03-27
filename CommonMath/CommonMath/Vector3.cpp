#include "Vector3.h"
#include <cmath>

const Vector3 Vector3::ZERO(0, 0, 0);

Vector3::Vector3():Vector3(ZERO)
{

}

Vector3::Vector3(float x, float y, float z): m_fx(x), m_fy(y), m_fz(z)
{

}

Vector3::Vector3(const Vector3& vec3): m_fx(vec3.m_fx), m_fy(vec3.m_fy), m_fz(vec3.m_fz)
{
	
}

float Vector3::dot(const Vector3& vec3)
{
	return m_fx * vec3.m_fx + m_fy * vec3.m_fy + m_fz * vec3.m_fz;
}

Vector3 Vector3::cross(const Vector3& vec3)
{
	return Vector3(m_fy*vec3.m_fz - m_fz * vec3.m_fy, m_fx*vec3.m_fz - m_fz * vec3.m_fx, m_fx*vec3.m_fy - m_fz * vec3.m_fx);
}

Vector3 Vector3::normalize()
{
	float len = std::sqrt(length());
	return (*this) / len;
}

float Vector3::length()
{
	return m_fx * m_fx + m_fy * m_fy + m_fz * m_fz;
}

Vector3 Vector3::operator-(const Vector3& vec)
{
	return Vector3(m_fx - vec.m_fx, m_fy - vec.m_fy, m_fz - vec.m_fz);
}

Vector3 Vector3::operator+(const Vector3& vec)
{
	return Vector3(m_fx + vec.m_fx, m_fy + vec.m_fy, m_fz + vec.m_fz);
}

Vector3 Vector3::operator*(float v)
{
	return Vector3(m_fx*v, m_fy*v, m_fz*v);
}

Vector3 Vector3::operator/(float v)
{
	return Vector3(m_fx / v, m_fy / v, m_fz / v);
}
