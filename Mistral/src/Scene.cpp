#include "Scene.h"

Scene::Scene(Mistral* g) {
	game = g;
}

void Scene::Instantiate(string data[5]) {
	if (data[0] == "CHARACTER") {
		Entity* e = new Character(game);
		e->position = glm::vec3(std::stof(data[1]), std::stof(data[2]), 0);
		e->scale = glm::vec3(std::stof(data[3]), std::stof(data[4]), 1);
	}

	if (data[0] == "ENEMY_1") {
		Entity* e = new Enemy1(game);
		e->position = glm::vec3(std::stof(data[1]), std::stof(data[2]), 0);
		e->scale = glm::vec3(std::stof(data[3]), std::stof(data[4]), 1);
	}

	if (data[0] == "GROUND") {
		Entity* e = new Ground(game);
		e->position = glm::vec3(std::stof(data[1]), std::stof(data[2]), 0);
		e->scale = glm::vec3(std::stof(data[3]), std::stof(data[4]), 1);
	}

	if (data[0] == "GRASS") {
		Entity* e = new Grass(game);
		e->position = glm::vec3(std::stof(data[1]), std::stof(data[2]), 0);
		e->scale = glm::vec3(std::stof(data[3]), std::stof(data[4]), 1);
	}

	if (data[0] == "GROUND_CORNER") {
		Entity* e = new GroundCorner(game);
		e->position = glm::vec3(std::stof(data[1]), std::stof(data[2]), 0);
		e->scale = glm::vec3(std::stof(data[3]), std::stof(data[4]), 1);
	}

	if (data[0] == "GRASS_CORNER") {
		Entity* e = new GrassCorner(game);
		e->position = glm::vec3(std::stof(data[1]), std::stof(data[2]), 0);
		e->scale = glm::vec3(std::stof(data[3]), std::stof(data[4]), 1);
	}
}


void Scene::Load(std::string name) {

	string line;
	ifstream file;
	list<string> level;
	std::string path = std::filesystem::current_path().string() + "/resources/" + name;
	std::cout << path;
	file.open(path);
	if (file.is_open())	{
		while (getline(file, line))	level.push_front(line);
		file.close();
	}

	for( string line : level ) {
		string item = "";
		string data[5];
		for (char c : line ) {
			if (c == ',') {
				if (data[0] == "") data[0] = item;
				else if (data[1] == "") data[1] = item;
				else if (data[2] == "") data[2] = item;
				else if (data[3] == "") data[3] = item;
				item = "";
			} else item += c;
		}
		data[4] = item;

		Instantiate(data);
	}
}