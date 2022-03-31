#include "EvildoerShader.h"
#include "Matrix4x4.h"

Matrix4x4  view;

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

void lookat(const Vector3& eye, Vector3& target, Vector3 u)
{
	Vector3 look = (target - eye).normalize();
	Vector3 right = u.cross(look).normalize();
	Vector3 up = look.cross(right).normalize();

	float x = -right.dot(eye);
	float y = -up.dot(eye);
	float z = -look.dot(eye);

	//Matrix4x4 matT;
	//Matrix4x4 matR;

	//matT.Identity();
	//matT.m[12] = -eye.m_fx;
	//matT.m[13] = -eye.m_fy;
	//matT.m[14] = -eye.m_fz;

	//matR.Identity();

	//float col[4] = { right.m_fx,right.m_fy,right.m_fz,0 };
	//matR.SetColumn(0, col);
	//float col2[4] = { up.m_fx,up.m_fy,up.m_fz,0 };
	//matR.SetColumn(1, col2);
	//float col3[4] = { look.m_fx,look.m_fy,look.m_fz,0 };
	//matR.SetColumn(2, col3);

	//view = matT * matR;

	view.m[0] = right.m_fx;
	view.m[4] = right.m_fy;
	view.m[8] = right.m_fz;
	view.m[12] = x;

	view.m[1] = up.m_fx;
	view.m[5] = up.m_fy;
	view.m[9] = up.m_fz;
	view.m[13] = y;

	view.m[2] = look.m_fx;
	view.m[6] = look.m_fy;
	view.m[10] = look.m_fz;
	view.m[14] = z;

	view.m[3] = 0;
	view.m[7] = 0;
	view.m[11] = 0;
	view.m[15] = 1;
}
