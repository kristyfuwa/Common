#include "EvildoerShader.h"

Maxtrix4x4  matrix;

TGAColor EvildoerShader::sample2D(const TGAImage& img, Vector2& uvf)
{
	return img.getColor(img.width()*uvf.m_fx, img.height()*uvf.m_fy);
}

void viewPort(const int x, const int y, const int w, const int h)
{

}

void projection(const double coeff /*= 0*/)
{

}

void lookat(const Vector3& eye, Vector3& target, Vector3 up)
{
	Vector3 look = (target - eye).normalize();
	Vector3 right = up.cross(look).normalize();
	Vector3 up = look.cross(right).normalize();
}
