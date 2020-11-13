#pragma once

#include "Entity.h"
#include <iostream>
#include "GL/glut.h"

class Character : public Entity {
	public:

		Character(Mistral* g) : Entity(g) { Create(); };

		void Create() { std::cout << "Create"; };

		void Update();

		void Draw() {
			// Use glTranslatef to move the camera back ten unit along the Z axis.
			//             X     Y     Z
			glTranslatef(ballPositionX, 0.0f, ballPositionY);

			// Set the sphere's color.
			glColor4fv(ballColor);
			glutSolidSphere(0.1, 20, 20);

			glRotatef(ballAngle, 0, 1, 0);
			glTranslatef(4, 0, 0);
			glColor3f(0, 1, 0);
			glutSolidSphere(1.0, 20, 20);

			glPushMatrix();

			glRotatef(ballAngle * 5, 0, 1, 0);
			glTranslatef(1.5, 0, 0);
			glColor3f(0.5, 0.5, 0.5);
			glutSolidSphere(0.05, 20, 20);

			glPopMatrix();

			glRotatef(ballAngle * 2, 0, 1, 0);
			glTranslatef(1.5, 1.0, 0);
			glColor3f(1.0, 0.3, 0.3);
			glutSolidSphere(0.03, 20, 20);
		};

		GLfloat ballColor[4] = { 0.0, 0.0, 1.0, 1.0 };
		GLfloat ballPositionX = 0.0;
		GLfloat ballPositionY = 0.0;
		GLfloat ballAngle = 0.0;
		float spd = 0.01;
};