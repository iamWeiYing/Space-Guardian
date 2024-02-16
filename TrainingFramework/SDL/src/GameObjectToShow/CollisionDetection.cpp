#include "CollisionDetection.h"

bool CollisionDetection::AABB(const SDL_Rect& recA, const SDL_Rect& recB) {
	if (
		recA.x + recA.w >= recB.x &&
		recB.x + recB.w >= recA.x &&
		recA.y + recA.h >= recB.y &&
		recB.y + recB.h >= recA.y
		) {
		return true;
	}

	return false;
}
bool CollisionDetection::AABB(const Object& colA, const Object& colB) {
	if (AABB(colA.Collider, colB.Collider)) {
		return true;
	}
	return false;
}