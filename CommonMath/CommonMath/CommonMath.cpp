#include "CommonMath.h"

bool CommonMath::pointInTriangle(Vector3 a, Vector3 b, Vector3 c, Vector3 pt)
{
	return sameSide(a, b, c, pt) && sameSide(b, c, a, pt) && sameSide(c, a, b, pt);
}

// Determine whether two vectors v1 and v2 point to the same direction
// v1 = Cross(AB, AC)
// v2 = Cross(AB, AP)
bool CommonMath::sameSide(Vector3 a, Vector3 b, Vector3 c, Vector3 p)
{
	Vector3 ab = b - a;
	Vector3 ap = p - a;
	Vector3 ac = c - a;

	Vector3 v1 = ab.cross(ap);
	Vector3 v2 = ab.cross(ac);

	return v1.dot(v2) >= 0;
}
