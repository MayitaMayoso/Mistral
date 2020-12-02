#pragma once

#include "Mistral.h"
#include "Entity.h"
#include "GameObjects.h"

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

class Mistral;

class Entity;

class Scene {
public:
	Scene(Mistral* g);

	void Load(std::string name, float z);
	void Instantiate(std::string data[5], float z);

	Mistral* game;
};

