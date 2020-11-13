#include "Mistral.h"
#include "Input.h"
#include "Camera.h"
#include "GameObjects.h"

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

void Character::Update() {
	if (game->input->InputCheck("FORWARD", InputState::HOLD)) {
		ballPositionY -= spd;
	}

	if (game->input->InputCheck("BACKWARD", InputState::HOLD)) {
		ballPositionY += spd;
	}

	if (game->input->InputCheck("LEFT", InputState::HOLD)) {
		ballPositionX += spd;
	}

	if (game->input->InputCheck("RIGHT", InputState::HOLD)) {
		ballPositionX -= spd;
	}
};