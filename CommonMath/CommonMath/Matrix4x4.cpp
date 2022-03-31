#include "Matrix4x4.h"
#include <iostream>

//const
const float EPSILON = 0.00001f;
Matrix4x4::Matrix4x4()
{
	Identity();
}


Matrix4x4::Matrix4x4(const float src[16])
{
	Set(src);
}


Matrix4x4::Matrix4x4(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8, float m9, float m10, float m11, float m12, float m13, float m14, float m15)
{
	Set(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,m12,m13,m14,m15);
}

Matrix4x4::~Matrix4x4()
{
}

void Matrix4x4::Set(const float src[16])
{
	m[0] = src[0];
	m[1] = src[1];
	m[2] = src[2];
	m[3] = src[3];
	m[4] = src[4];
	m[5] = src[5];
	m[6] = src[6];
	m[7] = src[7];
	m[8] = src[8];
	m[9] = src[9];
	m[10] = src[10];
	m[11] = src[11];
	m[12] = src[12];
	m[13] = src[13];
	m[14] = src[14];
	m[15] = src[15];
}

void Matrix4x4::Set(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8, float m9, float m10, float m11, float m12, float m13, float m14, float m15)
{
	m[0] = m0;
	m[1] = m1;
	m[2] = m2;
	m[3] = m3;
	m[4] = m4;
	m[5] = m5;
	m[6] = m6;
	m[7] = m7;
	m[8] = m8;
	m[9] = m9;
	m[10] = m10;
	m[11] = m11;
	m[12] = m12;
	m[13] = m13;
	m[14] = m14;
	m[15] = m15;
}

void Matrix4x4::SetRow(int index, const float row[4])
{
	m[index * 4] = row[0];
	m[index * 4 + 1] = row[1];
	m[index * 4 + 2] = row[2];
	m[index * 4 + 3] = row[3];
}

//void Matrix4x4::SetRow(int index, const Vector4& vec)
//{
//	m[index] = vec.GetX();
//	m[index + 3] = vec.GetY();
//	m[index + 6] = vec.GetZ();
//}

void Matrix4x4::SetColumn(int index, const float column[4])
{
	m[index] = column[0];
	m[index + 4] = column[1];
	m[index + 8] = column[2];
	m[index + 12] = column[3];
}

//void Matrix4x4::SetColumn(int index, const Vector4& vec)
//{
//	m[index * 3] = vec.GetX();
//	m[index * 3 + 1] = vec.GetY();
//	m[index * 3 + 2] = vec.GetZ();
//}

const float* Matrix4x4::Get() const
{
	return m;
}


Matrix4x4& Matrix4x4::Identity()
{
	m[0] = m[5] = m[10] = m[15] = 1.0f;
	m[1] = m[2] = m[3] =m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.0f;
	return *this;
}

Matrix4x4& Matrix4x4::Transpose()
{
	std::swap(m[1], m[4]);
	std::swap(m[2], m[8]);
	std::swap(m[3], m[12]);
	std::swap(m[6], m[9]);
	std::swap(m[7], m[13]);
	std::swap(m[11], m[14]);
	return *this;
}
//
//Matrix4x4& Matrix4x4::Invert()
//{
//	float determinant, invDeterminant;
//	float tmp[9];
//	tmp[0] = m[4] * m[8] - m[5] * m[7];
//	tmp[1] = m[2] * m[7] - m[1] * m[8];
//	tmp[2] = m[1] * m[5] - m[2] * m[4];
//	tmp[3] = m[5] * m[6] - m[3] * m[8];
//	tmp[4] = m[0] * m[8] - m[2] * m[6];
//	tmp[5] = m[2] * m[3] - m[0] * m[5];
//	tmp[6] = m[3] * m[7] - m[4] * m[6];
//	tmp[7] = m[1] * m[6] - m[0] * m[7];
//	tmp[8] = m[0] * m[4] - m[1] * m[3];
//	determinant = m[0] * tmp[0] + m[1] * tmp[3] + m[2] * tmp[6];
//	if (fabs(determinant <= EPSILON))
//	{
//		return Identity();
//	}
//	invDeterminant = 1.0f / determinant;
//	m[0] = invDeterminant * tmp[0];
//	m[1] = invDeterminant * tmp[1];
//	m[2] = invDeterminant * tmp[2];
//	m[3] = invDeterminant * tmp[3];
//	m[4] = invDeterminant * tmp[4];
//	m[5] = invDeterminant * tmp[5];
//	m[6] = invDeterminant * tmp[6];
//	m[7] = invDeterminant * tmp[7];
//	m[8] = invDeterminant * tmp[8];
//
//	return *this;
//}
//
//Matrix4x4 Matrix4x4::operator+(const Matrix4x4& rhs) const
//{
//	return Matrix4x4(m[0] + rhs[0], m[1] + rhs[1], m[2] + rhs[2],
//		m[3] + rhs[3], m[4] + rhs[4], m[5] + rhs[5],
//		m[6] + rhs[6], m[7] + rhs[7], m[8] + rhs[8]);
//}
//
float Matrix4x4::operator[](int index) const
{
	return m[index];
}

float& Matrix4x4::operator[](int index)
{
	return m[index];
}
//
//Matrix4x4 Matrix4x4::operator-(const Matrix4x4& rhs) const
//{
//	return Matrix4x4(m[0] - rhs[0], m[1] - rhs[1], m[2] - rhs[2],
//		m[3] - rhs[3], m[4] - rhs[4], m[5] - rhs[5],
//		m[6] - rhs[6], m[7] - rhs[7], m[8] - rhs[8]);
//}
//
//Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& rhs)
//{
//	m[0] -= rhs[0];
//	m[1] -= rhs[1];
//	m[2] -= rhs[2];
//	m[3] -= rhs[3];
//	m[4] -= rhs[4];
//	m[5] -= rhs[5];
//	m[6] -= rhs[6];
//	m[7] -= rhs[7];
//	m[8] -= rhs[8];
//	return *this;
//}
//
//pfVector3 Matrix4x4::operator*(const pfVector3& rhs) const
//{
//	return pfVector3(m[0] * rhs.GetX() + m[1] * rhs.GetY() + m[2] * rhs.GetZ(),
//		m[3] * rhs.GetX() + m[4] * rhs.GetY() + m[5] * rhs.GetZ(),
//		m[6] * rhs.GetX() + m[7] * rhs.GetY() + m[8] * rhs.GetZ());
//}
//
Matrix4x4 Matrix4x4::operator*(const Matrix4x4& rhs) const
{
	return Matrix4x4(
		m[0] * rhs[0] + m[1] * rhs[4] + m[2] * rhs[8] + m[3] * rhs[12],
		m[0] * rhs[1] + m[1] * rhs[5] + m[2] * rhs[9] + m[3] * rhs[13],
		m[0] * rhs[2] + m[1] * rhs[6] + m[2] * rhs[10] + m[3] * rhs[14],
		m[0] * rhs[3] + m[1] * rhs[7] + m[2] * rhs[11] + m[3] * rhs[15],
		m[4] * rhs[0] + m[5] * rhs[4] + m[6] * rhs[8] + m[7] * rhs[12],
		m[4] * rhs[1] + m[5] * rhs[5] + m[6] * rhs[9] + m[7] * rhs[13],
		m[4] * rhs[2] + m[5] * rhs[6] + m[6] * rhs[10] + m[7] * rhs[14],
		m[4] * rhs[3] + m[5] * rhs[7] + m[6] * rhs[11] + m[7] * rhs[15],

		m[8] * rhs[0] + m[9] * rhs[4] + m[10] * rhs[8] + m[11] * rhs[12],
		m[8] * rhs[1] + m[9] * rhs[5] + m[10] * rhs[9] + m[11] * rhs[13],
		m[8] * rhs[2] + m[9] * rhs[6] + m[10] * rhs[10] + m[11] * rhs[14],
		m[8] * rhs[3] + m[9] * rhs[7] + m[10] * rhs[11] + m[11] * rhs[15],

		m[12] * rhs[0] + m[13] * rhs[4] + m[14] * rhs[8] + m[15] * rhs[12],
		m[12] * rhs[1] + m[13] * rhs[5] + m[14] * rhs[9] + m[15] * rhs[13],
		m[12] * rhs[2] + m[13] * rhs[6] + m[14] * rhs[10] + m[15] * rhs[14],
		m[12] * rhs[3] + m[13] * rhs[7] + m[14] * rhs[11] + m[15] * rhs[15]);
}

Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& rhs)
{
	*this = *this * rhs;
	return *this;
}

//bool Matrix4x4::operator!=(const Matrix4x4& rhs) const
//{
//	return m[0] != rhs[0] || m[1] != rhs[1] || m[2] != rhs[2] ||
//		m[3] != rhs[3] || m[4] != rhs[4] || m[5] != rhs[5] ||
//		m[6] != rhs[6] || m[7] != rhs[7] || m[8] != rhs[8];
//}
//
//bool Matrix4x4::operator==(const Matrix4x4& rhs) const
//{
//	return m[0] == rhs[0] && m[1] == rhs[1] && m[2] == rhs[2] &&
//		m[3] == rhs[3] && m[4] == rhs[4] && m[5] == rhs[5] &&
//		m[6] == rhs[6] && m[7] == rhs[7] && m[8] == rhs[8];
//}
//
//Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& rhs)
//{
//	m[0] += rhs[0];
//	m[1] += rhs[1];
//	m[2] += rhs[2];
//	m[3] += rhs[3];
//	m[4] += rhs[4];
//	m[5] += rhs[5];
//	m[6] += rhs[6];
//	m[7] += rhs[7];
//	m[8] += rhs[8];
//	return *this;
//}
//
//
//
//Matrix4x4 operator-(const Matrix4x4& rhs)
//{
//	return Matrix4x4(-rhs[0], -rhs[1], -rhs[2],
//		-rhs[3], -rhs[4], -rhs[5],
//		-rhs[6], -rhs[7], -rhs[8]);
//}
//
//Matrix4x4 operator*(float scale, const Matrix4x4& m)
//{
//	return Matrix4x4(scale*m[0], scale*m[1], scale*m[2],
//		scale*m[3], scale*m[4], scale*m[5],
//		scale*m[6], scale*m[7], scale*m[8]);
//}
//
//pfVector3 operator*(const pfVector3& vec, const Matrix4x4& m)
//{
//	return pfVector3(vec.GetX() * m[0] + vec.GetY() * m[3] + vec.GetZ() * m[6],
//		vec.GetX() * m[1] + vec.GetY() * m[4] + vec.GetZ() * m[7],
//		vec.GetX() * m[2] + vec.GetY() * m[5] + vec.GetZ() * m[8]);
//}
//
//std::ostream& operator<<(std::ostream& os, const Matrix4x4& m)
//{
//	os << std::fixed << std::setprecision(5);
//	os << "[" << std::setw(10) << m[0] << " " << std::setw(10) << m[1] << " " << std::setw(10) << m[2] << "]\n"
//		<< "[" << std::setw(10) << m[3] << " " << std::setw(10) << m[4] << " " << std::setw(10) << m[5] << "]\n"
//		<< "[" << std::setw(10) << m[6] << " " << std::setw(10) << m[7] << " " << std::setw(10) << m[8] << "]\n";
//	os << std::resetiosflags(std::ios_base::fixed || std::ios_base::floatfield);
//	return os;
//}