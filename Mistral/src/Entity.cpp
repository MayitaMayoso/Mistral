#include "Mistral.h"
#include "Entity.h"
#include "Camera.h"

template<typename T>
bool IsIn(T value, list<T> values) {
	for (T v : values)
		if (v == value) return true;
	return false;
}



using namespace std;

// ==================================================================
//    THESE METHODS SHOULD NOT BE OVERWRITTED ON AN INHERITED CLASS
// ==================================================================
Entity::Entity(Mistral* g) {
	game = g;
	id = game->idAccumulator;
	game->idAccumulator++;
	game->EntitiesList.push_back(this);
}

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

void Entity::EntityDestroy(int entityId) {
	game->EntitiesToDestroy.push_back(entityId);
}

struct BoundingBox {
	float right;
	float up;
	float left;
	float down;
};

bool IsBetween(float val, float min, float max) {
	if (min<max)
		return ( val >= min && val <= max );
	else
		return (val <= min && val >= max);
}

bool Entity::CheckCollision(std::string object, float x, float y) {
	BoundingBox bbox;

	for (glm::vec4 mar : margin) {
		bbox.right = x + mar[0];
		bbox.up = y + mar[1];
		bbox.left = x - mar[2];
		bbox.down = y - mar[3];

		BoundingBox bboxOther;
		for (Entity* e : game->EntitiesList) {
			if (e->position.z == position.z && e->GetName() == object && e->id != id && (abs(position.x - e->position.x) < 10.0f)) {
				for (glm::vec4 mar2 : e->margin) {
					bboxOther.right = e->position.x + mar2[0];
					bboxOther.up = e->position.y + mar2[1];
					bboxOther.left = e->position.x - mar2[2];
					bboxOther.down = e->position.y - mar2[3];

					bool xColl = IsBetween(bbox.right, bboxOther.left, bboxOther.right)
						|| IsBetween(bbox.left, bboxOther.left, bboxOther.right);
					bool yColl = IsBetween(bbox.up, bboxOther.down, bboxOther.up) ||
						IsBetween(bbox.down, bboxOther.down, bboxOther.up);

					bool xColl2 = IsBetween(bboxOther.right, bbox.left, bbox.right)
						|| IsBetween(bboxOther.left, bbox.left, bbox.right);
					bool yColl2 = IsBetween(bboxOther.up, bbox.down, bbox.up) ||
						IsBetween(bboxOther.down, bbox.down, bbox.up);

					if (xColl && yColl || xColl2 && yColl2) {
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool Entity::CheckCollision(std::string object, glm::vec3 pos) {
	return CheckCollision(object, pos.x, pos.y);
}

bool Entity::CheckCollision(std::list<std::string> objects, float x, float y) {
	BoundingBox bbox;

	for (glm::vec4 mar : margin) {
		bbox.right = x + mar[0];
		bbox.up = y + mar[1];
		bbox.left = x - mar[2];
		bbox.down = y - mar[3];

		BoundingBox bboxOther;
		for (Entity* e : game->EntitiesList) {
			if (e->position.z == position.z && IsIn(e->GetName(), objects) && e->id != id && (abs(position.x - e->position.x) < 10.0f)) {
				for (glm::vec4 mar2 : e->margin) {
					bboxOther.right = e->position.x + mar2[0];
					bboxOther.up = e->position.y + mar2[1];
					bboxOther.left = e->position.x - mar2[2];
					bboxOther.down = e->position.y - mar2[3];

					bool xColl = IsBetween(bbox.right, bboxOther.left, bboxOther.right)
						|| IsBetween(bbox.left, bboxOther.left, bboxOther.right);
					bool yColl = IsBetween(bbox.up, bboxOther.down, bboxOther.up) ||
						IsBetween(bbox.down, bboxOther.down, bboxOther.up);

					bool xColl2 = IsBetween(bboxOther.right, bbox.left, bbox.right)
						|| IsBetween(bboxOther.left, bbox.left, bbox.right);
					bool yColl2 = IsBetween(bboxOther.up, bbox.down, bbox.up) ||
						IsBetween(bboxOther.down, bbox.down, bbox.up);

					if (xColl && yColl || xColl2 && yColl2) {
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool Entity::CheckCollision(std::list<std::string> objects, glm::vec3 pos) {
	return CheckCollision(objects, pos.x, pos.y);
}