#include "Mistral.h"
#include "Entity.h"
#include "Camera.h"


using namespace std;

// ==================================================================
//    THESE METHODS SHOULD NOT BE OVERWRITTED ON AN INHERITED CLASS
// ==================================================================
Entity::Entity(Mistral* g) {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	x_scale = 1.0;
	y_scale = 1.0;
	z_scale = 1.0;
	x_angle = 0.0;
	y_angle = 0.0;
	z_angle = 0.0;
	red = 1.0;
	green = 1.0;
	blue = 1.0;
	alpha = 1.0;

	game = g;


	id = game->EntitiesList.size();
	game->EntitiesCount();

	g->EntitiesList.push_back(this);
}

Entity::~Entity() {}

void Entity::DrawSelfCallback() {
	if (visible) {
		glPushMatrix();
		glColor4f(red, green, blue, alpha);
		glTranslatef(x, y, z);
		glScalef(x_scale, y_scale, z_scale);
		glRotatef(x_angle, 1, 0, 0);
		glRotatef(y_angle, 0, 1, 0);
		glRotatef(z_angle, 0, 0, 1);
		DrawSelf();
		glPopMatrix();
	}
}

// ==================================================================
//    THESE ARE THE GETTERS AND SETTERS OF THE ENTITY CLASS
// ==================================================================

// GETTERS

unsigned int Entity::get_id() { return id; }

string Entity::get_name() {
	string ctype = typeid(*this).name();
	int len = ctype.length();
	return ctype.substr(6, len);
}

float Entity::get_x() { return x; }

float Entity::get_y() { return y; }

float Entity::get_z() { return z; }


float Entity::get_x_scale() { return x_scale; }

float Entity::get_y_scale() { return y_scale; }

float Entity::get_z_scale() { return z_scale; }


float Entity::get_x_angle() { return x_angle; }

float Entity::get_y_angle() { return y_angle; }

float Entity::get_z_angle() { return z_angle; }


float Entity::get_red() { return red; }

float Entity::get_green() { return green; }

float Entity::get_blue() { return blue; }

float Entity::get_alpha() { return alpha; }


// SETTERS

void Entity::set_position(float x_value, float y_value, float z_value) { x = x_value; y = y_value; z = z_value; }

void Entity::set_x( float value ) { x = value; }

void Entity::set_y( float value ) { y = value; }

void Entity::set_z( float value) { z = value; }


void Entity::set_scale(float x_value, float y_value, float z_value) { x_scale = x_value; y_scale = y_value; z_scale = z_value; }

void Entity::set_x_scale( float value ) { x_scale = value; }

void Entity::set_y_scale( float value ) { y_scale = value; }

void Entity::set_z_scale( float value ) { z_scale = value; }


void Entity::set_angle(float x_value, float y_value, float z_value) { x_angle = x_value; y_angle = y_value; z_angle = z_value; }

void Entity::set_x_angle( float value ) { x_angle = value; }

void Entity::set_y_angle( float value ) { y_angle = value; }

void Entity::set_z_angle( float value ) { z_angle = value; }


void Entity::set_rgba(float r_value, float g_value, float b_value, float a_value) { red = r_value; green = g_value; blue = b_value; alpha = a_value;  }

void Entity::set_red( float value ) { red = value; }

void Entity::set_green( float value ) { green = value; }

void Entity::set_blue( float value ) { blue = value; }

void Entity::set_alpha(float value) { alpha = value; }