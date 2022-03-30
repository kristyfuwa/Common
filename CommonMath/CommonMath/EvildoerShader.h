#pragma once

#include "Vector3.h"
#include "TGAImage.h"
#include "Vector2.h"

void viewPort(const int x, const int y, const int w, const int h);

void projection(const double coeff = 0);//coeff = -1/c

void lookat(const Vector3& eye, const Vector3& target, Vector3 up);

class EvildoerShader
{
public:
	static TGAColor sample2D(const TGAImage& img, Vector2& uvf);

	virtual bool fragment(const Vector3* bar, TGAColor & color) = 0;
};


