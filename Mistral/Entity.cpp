#include "Mistral.h"
#include "Entity.h"
#include "Camera.h"


using namespace std;

// ==================================================================
//    THESE METHODS SHOULD NOT BE OVERWRITTED ON AN INHERITED CLASS
// ==================================================================
Entity::Entity(Mistral* g) {
	game = g;
	id = game->EntitiesList.size();
	g->EntitiesList.push_back(this);
}

Entity::~Entity() {}

void Entity::DrawSelfCallback() {
	if (visible) {
		glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glScalef(scale.x, scale.y, scale.z);
		glRotatef(rotation.x, 1, 0, 0);
		glRotatef(rotation.y, 0, 1, 0);
		glRotatef(rotation.z, 0, 0, 1);
		DrawSelf();
		glPopMatrix();
	}
}

string Entity::GetName() {
	string ctype = typeid(*this).name();
	int len = ctype.length();
	return ctype.substr(6, len);
}

struct BoundingBox {
	float right;
	float up;
	float left;
	float down;
};

bool IsBetween(float val, float min, float max) {
	return ( val >= min && val <= max );
}

bool Entity::CheckCollision(std::string object, float x, float y) {
	bool isColliding = false;
	BoundingBox bbox;

	bbox.right	= x + margin[0];
	bbox.up		= y + margin[1];
	bbox.left	= x - margin[2];
	bbox.down	= y - margin[3];

	BoundingBox bboxOther;
	for (Entity* e : game->EntitiesList) {
		if (e->GetName() == object && e->id != id) {
			bboxOther.right = e->position.x + e->margin[0];
			bboxOther.up	= e->position.y + e->margin[1];
			bboxOther.left	= e->position.x - e->margin[2];
			bboxOther.down	= e->position.y - e->margin[3];

			bool xColl = IsBetween(bbox.right, bboxOther.left, bboxOther.right)
				|| IsBetween(bbox.left, bboxOther.left, bboxOther.right);
			bool yColl = IsBetween(bbox.up, bboxOther.down, bboxOther.up) ||
				IsBetween(bbox.down, bboxOther.down, bboxOther.up);

			if (xColl && yColl) {
				isColliding = true;
				break;
			}
		}
	}

	return isColliding;
}

bool Entity::CheckCollision(std::string object, glm::vec3 pos) {
	bool isColliding = false;
	BoundingBox bbox;

	bbox.right	= pos.x + margin[0];
	bbox.up		= pos.y + margin[1];
	bbox.left	= pos.x - margin[2];
	bbox.down	= pos.y - margin[3];

	BoundingBox bboxOther;
	for (Entity* e : game->EntitiesList) {
		if ( e->GetName() == object && e->id != id) {
			bboxOther.right = e->position.x + e->margin[0];
			bboxOther.up	= e->position.y + e->margin[1];
			bboxOther.left	= e->position.x - e->margin[2];
			bboxOther.down	= e->position.y - e->margin[3];

			bool xColl = IsBetween(bbox.right, bboxOther.left, bboxOther.right)
				|| IsBetween(bbox.left, bboxOther.left, bboxOther.right);
			bool yColl = IsBetween(bbox.up, bboxOther.down, bboxOther.up) ||
				IsBetween(bbox.down, bboxOther.down, bboxOther.up);

			if ( xColl && yColl ) {
				isColliding = true;
				break;
			}
		}
	}

	return isColliding;
}