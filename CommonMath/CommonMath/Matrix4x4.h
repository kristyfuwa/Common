#pragma once
#include "Vector3.h"
class  Matrix4x4
{
public:
	Matrix4x4();
	Matrix4x4(const float src[16]);
	Matrix4x4(float m0, float m1, float m2,float m3,
		float m4, float m5,float m6, float m7,
		float m8, float m9, float m10, float m11,
		float m12, float m13, float m14, float m15);
	~Matrix4x4();

	void Set(const float src[16]);
	void Set(float m0, float m1, float m2, float m3,
		float m4, float m5, float m6, float m7,
		float m8, float m9, float m10, float m11,
		float m12, float m13, float m14, float m15);
	void SetRow(int index, const float row[4]);
	//void SetRow(int index, const Vector4& vec);
	void SetColumn(int index, const float column[4]);
	//void SetColumn(int index, const Vector4& vec);

	const float* Get() const;

	Matrix4x4& Identity();
	Matrix4x4& Transpose();
	//Matrix4x4& Invert();

	//Matrix4x4 operator+(const Matrix4x4& rhs) const;
	//Matrix4x4 operator-(const Matrix4x4& rhs) const;
	//Matrix4x4& operator+=(const Matrix4x4& rhs);
	//Matrix4x4& operator-=(const Matrix4x4& rhs);
	//Vector3  operator*(const Vector3& rhs) const;
	Matrix4x4 operator*(const Matrix4x4& rhs) const;
	Matrix4x4& operator*=(const Matrix4x4& rhs);

	//bool	operator==(const Matrix4x4& rhs) const;
	//bool	operator!=(const Matrix4x4& rhs) const;
	float   operator[](int index) const;
	float&  operator[](int index);

	//friend Matrix4x4 operator-(const Matrix4x4& m);
	//friend Matrix4x4 operator*(float scale, const Matrix4x4& m);
	//friend Vector3 operator*(const Vector3& vec, const Matrix4x4& m);
	//friend std::ostream& operator<<(std::ostream& os, const Matrix4x4& m);
public:
	float m[16];
};

