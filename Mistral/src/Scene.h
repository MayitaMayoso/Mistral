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

	void SetLevels(std::list<std::string> levels);
	void Load(std::string name);
	void Instantiate(std::string data[5]);
	void NextLevel();
	void NextLevelCallback();
	void RestartLevel();
	void RestartLevelCallback();

	std::list<std::string> levelsList;
	int current = 0;
	bool changeLevel = false;
	bool restartLevel = false;
	Mistral* game;
};

