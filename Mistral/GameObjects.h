#pragma once

#include "Entity.h"
#include <iostream>
#include "GL/glut.h"

class Character : public Entity {
	public:

		Character(Mistral* g) : Entity(g) { Create(); };

		void Create();

		void Update();

		void DrawSelf() {
			glPushMatrix();
				glScalef(1, 2, 1);
				glTranslatef(0, 0.1, 0);
				glutSolidCube(0.1);
			glPopMatrix();
			glPushMatrix();
				glScalef(0.5, 1, 0.5);
				glTranslatef(-0.1, 0.05, 0);
				glutSolidCube(0.1);
			glPopMatrix();
			glPushMatrix();
				glScalef(0.5, 1.3, 0.5);
				glTranslatef(0.1, 0.05, 0);
				glutSolidCube(0.1);
			glPopMatrix();
			glPushMatrix();
				glColor3f(1, 0, 0);
				glScalef(1.2, 1.2, 1.2);
				glTranslatef(0, 0.3, 0);
				glutSolidCube(0.1);
			glPopMatrix();
		};

		void Draw() {
			glPushMatrix();
			glColor3f(0.5, 0.1, 0.01);
			glTranslatef(0, -0.15, 0);
			glScalef(100, 1, 1);
			glutSolidCube(0.1);
			glPopMatrix();
			glColor3f(0, 1, 0.2);
			for (int i = 0; i < 50; i++) {
				glPushMatrix();
				glTranslatef(-50*0.1 + 0.1 * i * 2, (i%5)*0.1, -0.5 + (i % 3) * -0.3);
				glutSolidCube(0.1);
				glPopMatrix();
			}
		};

		float hspd = 0;
		float vspd = 0;
		float maxspd = 0.02;
		float acceleration = 0.001;
		float gravity = 0.002;
		float jumpforce = 0.06;
};

class Teapot : public Entity {
public:

	Teapot(Mistral* g) : Entity(g) { Create(); };

	void DrawSelf() {
		glutSolidTeapot(0.1);
	};

	void Update();
};