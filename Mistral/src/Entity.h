#pragma once

#include <iostream>
#include <string>
#include <typeinfo>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

class Mistral;

class Entity {
	public:
		Entity(Mistral* g); // Class constructor. Initializes all the Entities built-in variables.

		void DrawSelfCallback();

		bool CheckCollision(std::string object, float x, float y);
		bool CheckCollision(std::string object, glm::vec3 pos);
		bool CheckCollision(std::list<std::string> objects, float x, float y);
		bool CheckCollision(std::list<std::string> objects, glm::vec3 pos);
		void EntityDestroy(int id);

		virtual void Create() {};
		virtual void Destroy() {};
		virtual void Update() {}; // This method is called in the Timer Function of the main loop.
		virtual void Draw() {}; // Draws the Entitys body. Position, scale and angle affects how the bodys is drawn.
		virtual void DrawSelf() {}; // Same as the draw event but is affected by the transformations
									// of position, scale and rotation

		// ------------------- Getters and Setters -----------------------
		bool visible = true;
		string GetName();
		unsigned int id;
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		std::list<glm::vec4> margin;

		Mistral* game;
};