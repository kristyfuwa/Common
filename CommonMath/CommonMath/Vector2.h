#pragma once
class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	Vector2(const Vector2& vec);

	Vector2		normalize();
	float		length();

	Vector2		operator-(const Vector2& vec);
	Vector2		operator+(const Vector2& vec);
	Vector2		operator*(float v);
	Vector2		operator/(float v);

	static const Vector2 ZERO;
private:
	float m_fx;
	float m_fy;
};

