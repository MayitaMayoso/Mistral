#pragma once

#include <iostream>
#include <string>
#include <typeinfo>
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"

class Mistral;

class Entity {
	public:
		Entity( Mistral* g ); // Class constructor. Initializes all the Entities built-in variables.
		~Entity();

		void DrawSelfCallback();
		bool CheckCollision(std::string object, float x, float y);
		bool CheckCollision(std::string object, glm::vec3 pos);

		virtual void Create() {};
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
		glm::vec4 margin = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

		Mistral* game;
};