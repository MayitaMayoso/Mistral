#include "Mistral.h"
#include "Input.h"
#include "Camera.h"
#include "GameObjects.h"
#include "math.h"

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
	alpha = 0.5;
};

void Character::Update() {
	int hdir = (int)game->input->InputCheck("RIGHT", InputState::HOLD) - (int)game->input->InputCheck("LEFT", InputState::HOLD);

	// Horizontal movement
	hspd = approach(hspd, maxspd * hdir, acceleration);

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
			x_scale = 0.7;
			y_scale = 1.3;
		}
	}

	if (game->input->InputCheck("EXIT", InputState::PRESSED)) game->End();

	game->camera->position = lerp(game->camera->position, glm::vec3(x, y + 0.7, z + 6), 0.1);
	game->camera->lookat = glm::vec3(x, y + 0.3, z);
	game->camera->up = glm::vec3(0., 1., 0.);

	x_scale = lerp(x_scale, 1, 0.1);
	y_scale = lerp(y_scale, 1, 0.1);
	y += vspd;
	x += hspd;
};

void Ground::Create() {
	x_scale = 100;
}

void Ground::Update() {
}