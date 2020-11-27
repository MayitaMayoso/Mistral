#pragma once

#include "Entity.h"
#include <iostream>
#include "GL/glut.h"
#include "Math.h"


#define Color(col) { glColor3f(col[0]/255., col[1]/255., col[2]/255.); };
#define Color3(r, g, b) { glColor3f(r/255., g/255., b/255.); };
#define GREY(val) { glColor3f(val/255., val/255., val/255.); };
#define PUSH glPushMatrix();
#define POP glPopMatrix();
#define PRINT(str) { std::cout << str << std::endl; };
#define REPEAT(n) for(int i=0 ; i<n ; i++)

class Character : public Entity {
public:
	Character(Mistral* g) : Entity(g) { Create(); };

	void Destroy();

	void Create();

	void Update();

	void DrawSelf();

	float hspd = 0;
	float vspd = 0;
	float maxspd = 0.1;
	float acceleration = 0.01;
	float gravity = 0.01;
	float jumpforce = 0.2;

	int bodyCol[3] = { 255, 69, 0 };
	int white[3] = { 255, 255, 255 };
	int black[3] = { 40, 3, 3 };
	int clothingCol[3] = { 186, 53, 0 };
	int clothingCol2[3] = { 160, 82, 45 };

	float animation = 0;
};

class Ground : public Entity {
public:

	Ground(Mistral* g) : Entity(g) { Create(); };

	void Update();

	void DrawSelf() {
		glPushMatrix();
			glColor3f(0., 150. / 255., 50. / 255.);
			glScalef(1., .3, 1.);
			glTranslatef(0.5, -0.5, 0.);
			glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
			glColor3f(102. / 255., 50. / 255., 0.);
			glTranslatef(0., -0.3, 0.);
			glScalef(1., .7, 1.);
			glTranslatef(0.5, -0.5, 0.);
			glutSolidCube(1);
		glPopMatrix();
	};
};

struct Cloud {
	float x, y, z;
	float xscale, yscale;
	float speed;

	Cloud(float posX, float posY, float posZ, float scaleX, float scaleY, float spd) {
		x = posX; y = posY; z = posZ; xscale = scaleX; yscale = scaleY; speed = spd;
	}
};

class Clouds : public Entity {
public:

	Clouds(Mistral* g) : Entity(g) { Create(); };

	void Create();

	void Draw();

	list<Cloud*> listOfClouds;
};

class Dust : public Entity {
public:
	Dust(Mistral* g) : Entity(g) { Create(); };

	void Update();

	void DrawSelf() {
		PUSH
			GREY(150);
			glutSolidCube(0.2);
		POP
	}

	int age = 0;
	int life = 40;
	float yspd = 0.01f;
	float xspd = 0.0f;
	float zspd = 0.0f;
};