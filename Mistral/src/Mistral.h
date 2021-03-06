#pragma once

#include "Input.h"
#include "Camera.h"
#include "Scene.h"
#include "Entity.h"
#include "GameObjects.h"
#include "Audio.h"

class Input;

class Camera;

class Scene;

class Audio;

class Entity;

class Mistral {
	public:
		Mistral();

		int Run(int argc, char* args[], Mistral* s);
		void End();

		static void setSelf(Mistral* s) { self = s; };

		static Mistral* self;

		int width, height, fov, fps;
		float AspectRatio;

		list<Entity*> EntitiesList;
		list<int> EntitiesToDestroy;
		int idAccumulator = 0;

		Camera* camera;
		Input* input;
		Scene* scene;
		Audio* audio;
	private:
		int winId;
		// Main methods and callbacks of these methods
		void GeneralUpdate(int value);
		void GeneralDraw();

		static void UpdateCallback(int value) { self->GeneralUpdate(value); };
		static void DrawCallback() { self->GeneralDraw(); };

		// Gamepad methods and callbacks of these methods
		void GeneralPressKeyboard(unsigned char key, int x, int y);
		void GeneralPressSpecial(int key, int x, int y);
		void GeneralReleaseKeyboard(unsigned char key, int x, int y);
		void GeneralReleaseSpecial(int key, int x, int y);

		static void KeyboardPressCallback(unsigned char key, int x, int y) { self->GeneralPressKeyboard(key, x, y); };
		static void SpecialPressCallback(int key, int x, int y) { self->GeneralPressSpecial(key, x, y); };
		static void KeyboardReleaseCallback(unsigned char key, int x, int y) { self->GeneralReleaseKeyboard(key, x, y); };
		static void SpecialReleaseCallback(int key, int x, int y) { self->GeneralReleaseSpecial(key, x, y); };
};