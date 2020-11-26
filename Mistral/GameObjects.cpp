#include "Mistral.h"
#include "Input.h"
#include "Camera.h"
#include "GameObjects.h"
#include "Math.h"

#define PI 3.14159265358979323

#define Color(col) { glColor3f(col[0]/255., col[1]/255., col[2]/255.); };

float Wave(float from, float to, float duration, float offset, float W) {
	float A = float((to - from) * 0.5);

	return float(from + A + A * sin((2 * PI * W) / duration + offset));
}

float approach(float a, float b, float amount) {
	if (a < b) {
		float shift = a + amount;
		return (shift > b) ? b : shift;
	} else {
		float shift = a - amount;
		return (shift < b) ? b : shift;
	}
}

float lerp(float a, float b, float amount) {
	return a + (b - a) * amount;
}

glm::vec3 lerp(glm::vec3 a, glm::vec3 b, float amount) {
	return a + (b - a) * amount;
}

void Character::Create() {
	y_angle = -30;
};

void Character::Update() {
	animation++;
	int hdir = (int)game->input->InputCheck("RIGHT", InputState::HOLD) - (int)game->input->InputCheck("LEFT", InputState::HOLD);

	// Horizontal movement
	hspd = approach(hspd, maxspd * hdir, acceleration);

	if (hspd > 0)	y_angle = lerp(y_angle, -30, .3);
	if (hspd < 0)	y_angle = lerp(y_angle, -150, .3);

	// Vertical movement
	if (y - gravity > 0) {
		vspd -= gravity;
	}
	else {
		if (abs(vspd) > 0) {
			y_scale = 0.2;
			x_scale = 1.8;
		}
		vspd = 0;
		y = 0;
		if (game->input->InputCheck("UP", InputState::PRESSED)) {
			vspd = jumpforce;
			x_scale = 0.2;
			y_scale = 1.8;
		}
	}

	if (game->input->InputCheck("EXIT", InputState::PRESSED)) game->End();

	game->camera->position = lerp(game->camera->position, glm::vec3(x, y + 1, z + 5), 0.1);
	game->camera->lookat = lerp(game->camera->lookat, glm::vec3(x + (2*(y_angle>-50)-1)*0.5, y + 1, z), 0.1);
	game->camera->up = glm::vec3(0., 1., 0.);

	x_scale = lerp(x_scale, 1, 0.1);
	y_scale = lerp(y_scale, 1, 0.1);
	y += vspd;
	x += hspd;
};

void Character::DrawSelf() {
	glPushMatrix();

	// Body Upper
	glPushMatrix();
	Color(bodyCol);
	glTranslatef(0., .15, 0.);
	glScalef(.5, .7, .55);
	glTranslatef(0., .5, 0.);
	glutSolidCube(1.);
	glPopMatrix();

	// Clothes Base
	glPushMatrix();
	Color(clothingCol);
	glTranslatef(0., .15, 0.);
	glScalef(.55, .5, .6);
	glTranslatef(0., .5, 0.);
	glutSolidCube(1.);
	glPopMatrix();

	// Clothes Right
	glPushMatrix();
	Color(clothingCol);
	glTranslatef(0., .5, .15);
	glScalef(.525, .25, .15);
	glTranslatef(0., 1., 0.);
	glutSolidCube(1.);
	glPopMatrix();

	// Clothes Left
	glPushMatrix();
	Color(clothingCol);
	glTranslatef(0., .5, -.15);
	glScalef(.525, .25, .15);
	glTranslatef(0., 1., 0.);
	glutSolidCube(1.);
	glPopMatrix();

	// Button Right
	glPushMatrix();
	Color(clothingCol2);
	glTranslatef(.3, .45, .15);
	glScalef(.05, .1, .1);
	glTranslatef(0., 1., 0.);
	glutSolidCube(1.);
	glPopMatrix();

	// Button Left
	glPushMatrix();
	Color(clothingCol2);
	glTranslatef(.3, .45, -.15);
	glScalef(.05, .1, .1);
	glTranslatef(0., 1., 0.);
	glutSolidCube(1.);
	glPopMatrix();

	// Head
	glPushMatrix();
	Color(bodyCol);
	glTranslatef(0., .7, 0.);
	glScalef(.4, .45, .47);
	glTranslatef(0., .5, 0.);
	glutSolidCube(1.);
	glPopMatrix();

	// Ear Right
	glPushMatrix();
	Color(bodyCol);
	glTranslatef(0., 1.05, .25);
	glScalef(.1, .2, .2);
	glTranslatef(0., .5, 0.);
	glutSolidCube(1.);
	glPopMatrix();

	// Ear Left
	glPushMatrix();
	Color(bodyCol);
	glTranslatef(0., 1.05, -.25);
	glScalef(.1, .2, .2);
	glTranslatef(0., .5, 0.);
	glutSolidCube(1.);
	glPopMatrix();

	// Eye Right
	glPushMatrix();
	Color(white);
	glTranslatef(0.22, 1., .1);
	glScalef(.05, ( ((int)animation + 20) % 120 < 10) ? .015 : .1, .1);
	glTranslatef(0., .5, 0.);
	glutSolidCube(1.);
	glPopMatrix();

	// Eye Left
	glPushMatrix();
	Color(white);
	glTranslatef(0.22, 1., -.1);
	glScalef(.05, ( ((int)animation + 20 )%120 < 10 )?.01:.15, .1);
	glTranslatef(0., .5, 0.);
	glutSolidCube(1.);
	glPopMatrix();

	// Nose
	glPushMatrix();
	Color(black);
	glTranslatef(0.22, .9, 0.);
	glScalef(.05, .09, .09);
	glTranslatef(0., .5, 0.);
	glutSolidCube(1.);
	glPopMatrix();

	// Right Arm
	glPushMatrix();
	Color(bodyCol);
	glTranslatef(0., .8, 0.4);
	if (y == 0) {
		if (abs(hspd) > 0)	glRotatef(Wave(-120, 120, 60, 0, animation), 0, 0, 1);
	} else {
		glRotatef((y_angle > -50) ? 140 : 0, 0, 0, 1);
	}
	glScalef(.2, .4, .2);
	glTranslatef(0., -.5, 0.);
	glutSolidCube(1.);
	glPopMatrix();

	// Left Arm
	glPushMatrix();
	Color(bodyCol);
	glTranslatef(0., .8, -0.4);
	if (y == 0) {
		if (abs(hspd) > 0)	glRotatef(Wave(-120, 120, 60, 0, -animation), 0, 0, 1);
	} else {
		glRotatef((y_angle > -50) ? 0 : 140, 0, 0, 1);
	}
	glScalef(.2, .4, .2);
	glTranslatef(0., -.5, 0.);
	glutSolidCube(1.);
	glPopMatrix();

	// Right Foot
	glPushMatrix();
	Color(bodyCol);
	glTranslatef(0., .4, 0.15);
	if (y == 0) {
		if (abs(hspd) > 0)	glRotatef(Wave(-30, 30, 60, 0, -animation), 0, 0, 1);
	} else {
		glRotatef((y_angle > -50) ? -30 : 30, 0, 0, 1);
	}
	glScalef(.2, .4, .2);
	glTranslatef(0., -.5, 0.);
	glutSolidCube(1.);
	glPopMatrix();

	// Left Foot
	glPushMatrix();
	Color(bodyCol);
	glTranslatef(0., .4, -0.15);
	if (y == 0) {
		if (abs(hspd) > 0)	glRotatef(Wave(-30, 30, 60, 0, animation), 0, 0, 1);
	} else {
		glRotatef((y_angle > -50)?30:-30, 0, 0, 1);
	}
	glScalef(.2, .4, .2);
	glTranslatef(0., -.5, 0.);
	glutSolidCube(1.);
	glPopMatrix();
	glPopMatrix();
};

void Ground::Create() {
	x_scale = 100;
}

void Ground::Update() {
}