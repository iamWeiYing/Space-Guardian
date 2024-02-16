#include "CMath.h"

struct BezierCurve {
	Vector2 p0;
	Vector2 p1;
	Vector2 p2;
	Vector2 p3;

	Vector2 CalculateCurvePoint(float t) {
		float tt = t * t;
		float ttt = tt * t;
		float u = 1.0f - t;
		float uu = u * u;
		float uuu = uu * u;

		Vector2 point = (p0 * uuu) + (p1 * 3 * uu * t) + (p2 * 3 * u * tt) + (p3 * ttt);
		point.x = round(point.x);
		point.y = round(point.y);
		return point;
	}
};
