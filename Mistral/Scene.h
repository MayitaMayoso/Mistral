#pragma once

#include "Mistral.h"
#include "Entity.h"
#include "GameObjects.h"

#include <iostream>
#include <fstream>
#include <string>

class Mistral;

class Entity;

class Scene {
public:
	Scene(Mistral* g);

	void Load(std::string path);

	Mistral* game;
};

