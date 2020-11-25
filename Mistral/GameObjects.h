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
				// Body
				glPushMatrix();
					glColor3f(204. / 255., 51. / 255, 153. / 255.);
					glTranslatef(0., .1, 0.);
					glScalef(.5, .7, .5);
					glTranslatef(0., .5, 0.);
					glutSolidCube(1.);
				glPopMatrix();

				// Head
				glPushMatrix();
					glColor3f(204. / 255., 51. / 255, 153. / 255.);
					glTranslatef(0.1, .7, 0.);
					glScalef(.5, .5, .5);
					glTranslatef(0., .5, 0.);
					glRotatef(-45., 0., 0., 1.);
					glRotatef(-45., 0., 1., 0.);
					glutSolidCube(1.);
				glPopMatrix();

				// Right Arm
				glPushMatrix();
					glColor3f(163 / 255., 41 / 255, 122 / 255.);
					glTranslatef(0.05, .5, 0.3);
					glScalef(.2, .2, .2);
					glTranslatef(0., .5, 0.);
					glutSolidCube(1.);
				glPopMatrix();

				// Left Arm
				glPushMatrix();
					glColor3f(163 / 255., 41 / 255, 122 / 255.);
					glTranslatef(0.05, .5, -0.3);
					glScalef(.2, .2, .2);
					glTranslatef(0., .5, 0.);
					glutSolidCube(1.);
				glPopMatrix();

				// Right Foot
				glPushMatrix();
				glColor3f(163 / 255., 41 / 255, 122 / 255.);
				glTranslatef(0., .0, 0.3);
				glScalef(.2, .2, .2);
				glTranslatef(0., .5, 0.);
				glutSolidCube(1.);
				glPopMatrix();

				// Left Foot
				glPushMatrix();
				glColor3f(163 / 255., 41 / 255, 122 / 255.);
				glTranslatef(0., .0, -0.3);
				glScalef(.3, .3, .3);
				glTranslatef(0., .5, 0.);
				glutSolidCube(1.);
				glPopMatrix();
			glPopMatrix();
		};

		float hspd = 0;
		float vspd = 0;
		float maxspd = 0.1;
		float acceleration = 0.01;
		float gravity = 0.01;
		float jumpforce = 0.2;
};

class Ground : public Entity {
public:

	Ground(Mistral* g) : Entity(g) { Create(); };

	void Create();

	void Update();

	void DrawSelf() {
		glPushMatrix();
			glColor3f(0., 150. / 255., 50. / 255.);
			glScalef(1., .3, 1.);
			glTranslatef(0., -0.5, 0.);
			glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
			glColor3f(102. / 255., 50. / 255., 0.);
			glTranslatef(0., -0.3, 0.);
			glScalef(1., .7, 1.);
			glTranslatef(0., -0.5, 0.);
			glutSolidCube(1);
		glPopMatrix();
	};
};