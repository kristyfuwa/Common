#pragma once
#include "Vector3.h"

class CommonMath
{
public:
	static bool pointInTriangle(Vector3 a, Vector3 b, Vector3 c, Vector3 pt);

private:
	static bool sameSide(Vector3 a, Vector3 b, Vector3 c, Vector3 p);
};

