#pragma once

#include "Input.h"
#include "Camera.h"
#include "Entity.h"
#include "GameObjects.h"

class Input;

class Camera;

class Entity;

class Mistral {
	public:
		Mistral();
		~Mistral();

		int Run(int argc, char* args[], Mistral* s);
		void End();

		static void setSelf(Mistral* s) { self = s; };

		static Mistral* self;

		int width, height, fov, fps;
		float AspectRatio;

		list<Entity*> EntitiesList;

		Camera* camera;
		Input* input;
	private:
		int winId;
		// Main methods and callbacks of these methods
		virtual void GeneralUpdate(int value);
		virtual void GeneralDraw();

		static void UpdateCallback(int value) { self->GeneralUpdate(value); };
		static void DrawCallback() { self->GeneralDraw(); };

		// Gamepad methods and callbacks of these methods
		virtual void GeneralPressKeyboard(unsigned char key, int x, int y);
		virtual void GeneralPressSpecial(int key, int x, int y);
		virtual void GeneralReleaseKeyboard(unsigned char key, int x, int y);
		virtual void GeneralReleaseSpecial(int key, int x, int y);

		static void KeyboardPressCallback(unsigned char key, int x, int y) { self->GeneralPressKeyboard(key, x, y); };
		static void SpecialPressCallback(int key, int x, int y) { self->GeneralPressSpecial(key, x, y); };
		static void KeyboardReleaseCallback(unsigned char key, int x, int y) { self->GeneralReleaseKeyboard(key, x, y); };
		static void SpecialReleaseCallback(int key, int x, int y) { self->GeneralReleaseSpecial(key, x, y); };
};