#include "Vector2.h"
#include <cmath>


const Vector2 Vector2::ZERO = Vector2(0.0f,0.0f);
Vector2::Vector2():Vector2(ZERO)
{

}

Vector2::Vector2(float x, float y):m_fx(x),m_fy(y)
{

}

Vector2::Vector2(const Vector2& vec):m_fx(vec.m_fx),m_fy(vec.m_fy)
{

}

Vector2 Vector2::normalize()
{
	return (*this) / length();
}

float Vector2::length()
{
	return std::sqrt(m_fx*m_fx + m_fy * m_fy);
}

Vector2 Vector2::operator-(const Vector2& vec)
{
	return Vector2(m_fx - vec.m_fx, m_fy - vec.m_fy);
}

Vector2 Vector2::operator+(const Vector2& vec)
{
	return Vector2(m_fx + vec.m_fx, m_fy + vec.m_fy);
}

Vector2 Vector2::operator*(float v)
{
	return Vector2(m_fx*v, m_fy*v);
}

Vector2 Vector2::operator/(float v)
{
	return Vector2(m_fx / v, m_fy / v);
}

