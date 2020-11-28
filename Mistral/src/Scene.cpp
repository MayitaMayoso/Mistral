#include "Scene.h"

Scene::Scene(Mistral* g) {
	game = g;
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

	int y = 0;
	for( string line : level ) {
		int x = -1;
		for (char c : line ) {
			if ( c == ',') x++;
			else {
				if ( c == 'G') {
					Entity* e = new Ground(game);
					e->position = glm::vec3(x, y, 0);
				}
				if ( c == 'C') {
					Entity* e = new Character(game);
					e->position = glm::vec3(x, y, 0);
				}
				if (c == 'E') {
					Entity* e = new Enemy(game);
					e->position = glm::vec3(x, y, 0);
				}
			}
		}
		y++;
	}
}