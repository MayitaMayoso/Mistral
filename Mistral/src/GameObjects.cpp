#include "Mistral.h"
#include "Input.h"
#include "Camera.h"
#include "GameObjects.h"
#include "random"

#define PI 3.14159265358979323


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

int sign(float val) {
	return (val == 0) ? 0 : ( ( val > 0 ) ? 1 : -1);
}

float radians(float degree) {
	return degree * (PI / 180);
}

float degrees(float radian) {
	return radian * (180 / PI);
}

float random() { return (float)rand() / (float)RAND_MAX; }

void Character::Create() {
	rotation.y = -30;
	margin = glm::vec4(0.25f, 0.9f, 0.25f, 0.0f);
	position.y = 1.0f;
};

void Character::Destroy() {
	new Character(game);
}

void Character::Update() {
	int hdir = (int)game->input->InputCheck("RIGHT", InputState::HOLD) - (int)game->input->InputCheck("LEFT", InputState::HOLD);

	int vdir = - (int)game->input->InputCheck("DOWN", InputState::HOLD);

	// Horizontal movement
	hspd = approach(hspd, maxspd * hdir, acceleration);

	if (hspd > 0)	rotation.y = lerp(rotation.y, -30, .3);
	if (hspd < 0)	rotation.y = lerp(rotation.y, -150, .3);

	if (hspd == 0) animation = 0;
	else animation -= 1 - 2 * (hspd > 0);


	// Vertical movement
	if (!CheckCollision("Ground", position.x, position.y - gravity)) {
		vspd = max(vspd - gravity, -.3f);
	} else {
		if (game->input->InputCheck("JUMP", InputState::PRESSED)) {
			int buf = game->audio->loadSound("resources/jump.wav");
			auto jump = new AudioSource();
			jump->playSound(buf);
			vspd = jumpforce;
			scale = glm::vec3(0.2f, 1.8f, 1.0f);
		}
		if ( abs(hspd) > 0 && random() < 0.1f) {
			Dust* e = new Dust(game);
			e->position = position;
			e->yspd = random() * 0.0095 + 0.0005;
		}
	}

	if (position.y < -10.0f) {
		EntityDestroy(id);
	}

	// Check collisions
	if (CheckCollision("Ground", position.x + hspd, position.y)) {
		while (!CheckCollision("Ground", position.x + sign(hspd) * 0.01, position.y)) {
			position.x += sign(hspd) * 0.01;
		}
		hspd = 0;
	}

	if (CheckCollision("Ground", position.x, position.y + vspd)) {
		while (!CheckCollision("Ground", position.x, position.y + sign(vspd) * 0.01)) {
			position.y += sign(vspd) * 0.01;
		}
		float squash = abs(vspd) / 0.3f;
		scale = glm::vec3(1.0f + squash, 1.0f - min(squash, 0.9f), 1.0f);

		if (vspd < -0.22) {
			REPEAT(20) {
				Dust* e = new Dust(game);
				e->position = position;
				float dir = random() * 1.0f - 0.5f;
				e->position.x += dir;
				e->xspd = dir * 0.01;
				e->yspd = random() * 0.005 + 0.005;
				e->zspd = random() * 0.005 + 0.005;
			}
		}
		vspd = 0;
	}

	if (CheckCollision("Ground", position.x, position.y)) {
		int count = 0;
		float dist = 0.2;
		float prec = 90;
		float jump = 0.2;

		glm::vec3 origin = position;
		while (CheckCollision("Ground", position)) {
			position.x = origin.x + dist * cos(radians(count * prec));
			position.y = origin.y + dist * sin(radians(count * prec));
			count++;
			if (count == 4) {
				count = 0;
				dist += jump;
			}
		}
	}

	if (game->input->InputCheck("EXIT", InputState::PRESSED)) game->End();

	game->camera->position = lerp(game->camera->position, position + glm::vec3(0.0f, 1.0f, 5.0f), 0.1f);
	game->camera->lookat = lerp(game->camera->lookat, position + glm::vec3(0.0f, 1.0f, 0.0f), 0.1);
	game->camera->up = glm::vec3(0.0f, 1.0f, 0.0f);


	scale = lerp(scale, glm::vec3(1.0f, 1.0f, 1.0f), 0.1f);
	position += glm::vec3(hspd, vspd, 0);
};

void Character::DrawSelf() {
	glPushMatrix();

	// Body Upper
	glPushMatrix();
	COLOR(bodyCol);
	glTranslatef(0., .15, 0.);
	glScalef(.5, .7, .55);
	glTranslatef(0., .5, 0.);
	glutSolidCube(1.);
	glPopMatrix();

	// Clothes Base
	glPushMatrix();
	COLOR(clothingCol);
	glTranslatef(0., .15, 0.);
	glScalef(.55, .5, .6);
	glTranslatef(0., .5, 0.);
	glutSolidCube(1.);
	glPopMatrix();

	// Clothes Right
	glPushMatrix();
	COLOR(clothingCol);
	glTranslatef(0., .5, .15);
	glScalef(.525, .25, .15);
	glTranslatef(0., 1., 0.);
	glutSolidCube(1.);
	glPopMatrix();

	// Clothes Left
	glPushMatrix();
	COLOR(clothingCol);
	glTranslatef(0., .5, -.15);
	glScalef(.525, .25, .15);
	glTranslatef(0., 1., 0.);
	glutSolidCube(1.);
	glPopMatrix();

	// Button Right
	glPushMatrix();
	COLOR(clothingCol2);
	glTranslatef(.3, .5, .15);
	glScalef(.025, .1, .1);
	glTranslatef(0., 1., 0.);
	glutSolidCube(1.);
	glPopMatrix();

	// Button Left
	glPushMatrix();
	(clothingCol2);
	glTranslatef(.3, .5, -.15);
	glScalef(.05, .08, .1);
	glTranslatef(0., 1., 0.);
	glutSolidCube(1.);
	glPopMatrix();

	//Pocket
	glPushMatrix();
	COLOR(bodyCol);
	glTranslatef(.3, .4, .0);
	glScalef(.04, .05, .35);
	glTranslatef(0., 1., 0.);
	glutSolidCube(1.);
	glPopMatrix();

	glPushMatrix();
	COLOR(clothingCol2);
	glTranslatef(.3, .15, .0);
	glScalef(.03, .2, .3);
	glTranslatef(0., 1., 0.);
	glutSolidCube(1.);
	glPopMatrix();

	// Head
	glPushMatrix();
	COLOR(bodyCol);
	glTranslatef(0., .7, 0.);
	glScalef(.4, .45, .47);
	glTranslatef(0., .5, 0.);
	glutSolidCube(1.);
	glPopMatrix();

	// Ear Right
	glPushMatrix();
	COLOR(bodyCol);
	glTranslatef(0., 1.05, .2);
	glScalef(.1, .2, .2);
	glTranslatef(0., .5, 0.);
	glutSolidCube(1.);
	glPopMatrix();

	// Ear Left
	glPushMatrix();
	COLOR(bodyCol);
	glTranslatef(0., 1.05, -.2);
	glScalef(.1, .2, .2);
	glTranslatef(0., .5, 0.);
	glutSolidCube(1.);
	glPopMatrix();

	// Eye Right
	glPushMatrix();
	COLOR(white);
	glTranslatef(0.22, 1., .1);
	glScalef(.05, ( ((int)abs(animation) + 20) % 120 < 10) ? .015 : .1, .1);
	glTranslatef(0., .5, 0.);
	glutSolidCube(1.);
	glPopMatrix();

	// Eye Left
	glPushMatrix();
	COLOR(white);
	glTranslatef(0.22, 1., -.1);
	glScalef(.05, ( ((int)abs(animation) + 20 )%120 < 10 )?.01:.15, .1);
	glTranslatef(0., .5, 0.);
	glutSolidCube(1.);
	glPopMatrix();

	// Nose
	glPushMatrix();
	COLOR(black);
	glTranslatef(0.3, .9, 0.);
	glScalef(.05, .09, .09);
	glTranslatef(0., .5, 0.);
	glutSolidCube(1.);
	glPopMatrix();

	glPushMatrix();
	COLOR(bodyCol);
	glTranslatef(0.22, .85, 0.);
	glScalef(.15, .15, .3);
	glTranslatef(0., .5, 0.);
	glutSolidCube(1.);
	glPopMatrix();

	// Right Arm
	glPushMatrix();
	COLOR(bodyCol);
	glTranslatef(.1, .8, 0.4);
	if (vspd == 0) {
		if (abs(hspd) > 0)	glRotatef(Wave(-120, 120, 60, 0, animation), 0, 0, 1);
	} else {
		glRotatef((rotation.y > -50) ? 140 : 0, 0, 0, 1);
	}
	glScalef(.2, .4, .15);
	glTranslatef(0., -.5, 0.);
	glutSolidCube(1.);
	glPopMatrix();

	// Left Arm
	glPushMatrix();
	COLOR(bodyCol);
	glTranslatef(.1, .8, -0.4);
	if (vspd == 0) {
		if (abs(hspd) > 0)	glRotatef(Wave(-120, 120, 60, 0, -animation), 0, 0, 1);
	} else {
		glRotatef((rotation.y > -50) ? 0 : 140, 0, 0, 1);
	}
	glScalef(.2, .4, .15);
	glTranslatef(0., -.5, 0.);
	glutSolidCube(1.);
	glPopMatrix();

	// Right Foot
	glPushMatrix();
	COLOR(bodyCol);
	glTranslatef(0., .4, 0.15);
	if (vspd == 0) {
		if (abs(hspd) > 0)	glRotatef(Wave(-30, 30, 60, 0, -animation), 0, 0, 1);
	} else {
		glRotatef((rotation.y > -50) ? -30 : 30, 0, 0, 1);
	}
	glScalef(.3, .4, .27);
	glTranslatef(0., -.5, 0.);
	glutSolidCube(1.);
	glPopMatrix();

	// Left Foot
	glPushMatrix();
	COLOR(bodyCol);
	glTranslatef(0., .4, -0.15);
	if (vspd == 0) {
		if (abs(hspd) > 0)	glRotatef(Wave(-30, 30, 60, 0, animation), 0, 0, 1);
	} else {
		glRotatef((rotation.y > -50)?30:-30, 0, 0, 1);
	}
	glScalef(.3, .4, .27);
	glTranslatef(0., -.5, 0.);
	glutSolidCube(1.);
	glPopMatrix();
	glPopMatrix();

};

void Ground::Update() {
	margin = glm::vec4(scale.x, 0.0f, 0.0f, scale.y);
}

void Clouds::Create() {
	for (int i = 0; i < 100; i++) {
		Cloud* c = new Cloud(rand() % 100 - 50, rand() % 50, -(rand() % 10) -5.0f, 5, 2, 0.1f + 0.2f*(rand() % 100) / 100.f);
		listOfClouds.push_back(c);
	}
}

void Clouds::Draw() {
	for (Cloud* c : listOfClouds) {
		glPushMatrix();
		COLOR3(200, 200, 200);
		glTranslatef(c->x, c->y, c->z);
		glScalef(c->xscale, c->yscale, .01f);
		glutSolidCube(1);
		glPopMatrix();
		c->x += c->speed;
		if (c->x > 60.0f) c->x = -60.0f;
	};
}

void Dust::Update() {
	position.y += yspd;
	position.x += xspd;
	position.z += zspd;
	scale = glm::vec3(0.3 + (float)age / (float)life);
	age++;
	if (age >= life) {
		EntityDestroy(id);
	}
}
