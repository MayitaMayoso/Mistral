#include "Scene.h"

Scene::Scene(Mistral* g) {
	game = g;
}

void Scene::Instantiate(string data[5]) {
	if (data[0] == "Character") {
		Entity* e = new Character(game);
		e->position = glm::vec3(std::stof(data[1]), std::stof(data[2]), std::stof(data[3]));
		e->scale = glm::vec3(std::stof(data[4]), std::stof(data[5]), 1);
	}

	if (data[0] == "Ground") {
		Entity* e = new Ground(game);
		e->position = glm::vec3(std::stof(data[1]), std::stof(data[2]),  std::stof(data[3]));
		e->scale = glm::vec3(std::stof(data[4]), std::stof(data[5]), 1);		
	}

	if (data[0] == "Grass") {
		Entity* e = new Grass(game);
		e->position = glm::vec3(std::stof(data[1]), std::stof(data[2]),  std::stof(data[3]));
		e->scale = glm::vec3(std::stof(data[4]), std::stof(data[5]), 1);		
	}

	if (data[0] == "GroundCornerRight") {
		Entity* e = new GroundCornerRight(game);
		e->position = glm::vec3(std::stof(data[1]), std::stof(data[2]),  std::stof(data[3]));
		e->scale = glm::vec3(std::stof(data[4]), std::stof(data[5]), 1);		
	}

	if (data[0] == "GroundCornerLeft") {
		Entity* e = new GroundCornerLeft(game);
		e->position = glm::vec3(std::stof(data[1]), std::stof(data[2]),  std::stof(data[3]));
		e->scale = glm::vec3(std::stof(data[4]), std::stof(data[5]), 1);		
	}

	if (data[0] == "GrassCornerRight") {
		Entity* e = new GrassCornerRight(game);
		e->position = glm::vec3(std::stof(data[1]), std::stof(data[2]),  std::stof(data[3]));
		e->scale = glm::vec3(std::stof(data[4]), std::stof(data[5]), 1);		
	}

	if (data[0] == "GrassCornerLeft") {
		Entity* e = new GrassCornerLeft(game);
		e->position = glm::vec3(std::stof(data[1]), std::stof(data[2]),  std::stof(data[3]));
		e->scale = glm::vec3(std::stof(data[4]), std::stof(data[5]), 1);		
	}

	if (data[0] == "BigBee") {
		Entity* e = new BigBee(game);
		e->position = glm::vec3(std::stof(data[1]), std::stof(data[2]),  std::stof(data[3]));
		e->scale = glm::vec3(std::stof(data[4]), std::stof(data[5]), 1);		
	}

	if (data[0] == "SmallBee") {
		Entity* e = new SmallBee(game);
		e->position = glm::vec3(std::stof(data[1]), std::stof(data[2]),  std::stof(data[3]));
		e->scale = glm::vec3(std::stof(data[4]), std::stof(data[5]), 1);		
	}

	if (data[0] == "Snail") {
		Entity* e = new Snail(game);
		e->position = glm::vec3(std::stof(data[1]), std::stof(data[2]),  std::stof(data[3]));
		e->scale = glm::vec3(std::stof(data[4]), std::stof(data[5]), 1);		
	}

	if (data[0] == "BigRedMushroom") {
		Entity* e = new BigRedMushroom(game);
		e->position = glm::vec3(std::stof(data[1]), std::stof(data[2]),  std::stof(data[3]));
		e->scale = glm::vec3(std::stof(data[4]), std::stof(data[5]), 1);		
	}

	if (data[0] == "SmallRedMushroom") {
		Entity* e = new SmallRedMushroom(game);
		e->position = glm::vec3(std::stof(data[1]), std::stof(data[2]),  std::stof(data[3]));
		e->scale = glm::vec3(std::stof(data[4]), std::stof(data[5]), 1);		
	}

	if (data[0] == "BigBlueMushroom") {
		Entity* e = new BigBlueMushroom(game);
		e->position = glm::vec3(std::stof(data[1]), std::stof(data[2]),  std::stof(data[3]));
		e->scale = glm::vec3(std::stof(data[4]), std::stof(data[5]), 1);
	}

	if (data[0] == "SmallBlueMushroom") {
		Entity* e = new SmallBlueMushroom(game);
		e->position = glm::vec3(std::stof(data[1]), std::stof(data[2]),  std::stof(data[3]));
		e->scale = glm::vec3(std::stof(data[4]), std::stof(data[5]), 1);
	}

	if (data[0] == "Hand") {
		Entity* e = new Hand(game);
		e->position = glm::vec3(std::stof(data[1]), std::stof(data[2]),  std::stof(data[3]));
		e->scale = glm::vec3(std::stof(data[4]), std::stof(data[5]), 1);		
	}

	if (data[0] == "Trunk") {
		Entity* e = new Trunk(game);
		e->position = glm::vec3(std::stof(data[1]), std::stof(data[2]),  std::stof(data[3]));
		e->scale = glm::vec3(std::stof(data[4]), std::stof(data[5]), 1);		
	}

	if (data[0] == "Branch") {
		Entity* e = new Branch(game);
		e->position = glm::vec3(std::stof(data[1]), std::stof(data[2]),  std::stof(data[3]));
		e->scale = glm::vec3(std::stof(data[4]), std::stof(data[5]), 1);		
	}

	if (data[0] == "Leaves") {
		Entity* e = new Leaves(game);
		e->position = glm::vec3(std::stof(data[1]), std::stof(data[2]),  std::stof(data[3]));
		e->scale = glm::vec3(std::stof(data[4]), std::stof(data[5]), 1);		
	}
}

void Scene::Load(std::string name) {
	string line;
	ifstream file;
	list<string> level;
	std::string path = std::filesystem::current_path().string() + "/resources/" + name + ".mistral";
	std::cout << path;
	file.open(path);
	if (file.is_open())	{
		while (getline(file, line))	level.push_front(line);
		file.close();
	}
	new Clouds(game);
	for( string line : level ) {
		string item = "";
		string data[6];
		for (char c : line ) {
			if (c == ',') {
				if (data[0] == "") data[0] = item;
				else if (data[1] == "") data[1] = item;
				else if (data[2] == "") data[2] = item;
				else if (data[3] == "") data[3] = item;
				else if (data[4] == "") data[4] = item;
				item = "";
			} else item += c;
		}
		data[5] = item;

		Instantiate(data);
	}
}

void Scene::SetLevels(std::list<std::string> levels) {
	levelsList = levels;
	Load(levelsList.front());
}

void Scene::NextLevel() {
	changeLevel = true;
}

void Scene::NextLevelCallback() {
	if (changeLevel) {
		for (Entity* e : game->EntitiesList) {
			delete e;
		}
		game->EntitiesList.clear();
		changeLevel = false;
		current++;
		int i = 0;
		bool endGame = true;
		for (std::string l : levelsList) {
			if (i == current) {
				endGame = false;
				Load(l);
			}
			i++;
		}
		if (endGame) {
			game->End();
		}
	}
}

void Scene::RestartLevel() {
	restartLevel = true;
}

void Scene::RestartLevelCallback() {
	if (restartLevel) {
		for (Entity* e : game->EntitiesList) {
			delete e;
		}
		game->EntitiesList.clear();
		restartLevel = false;
		int i = 0;
		for (std::string l : levelsList) {
			if (i == current) {
				Load(l);
			}
			i++;
		}
	}
}