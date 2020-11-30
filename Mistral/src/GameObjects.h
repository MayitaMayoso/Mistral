#pragma once

#include "Entity.h"
#include <iostream>
#include "glut.h"
#include "Math.h"


#define COLOR(col) { glColor3f(col[0]/255., col[1]/255., col[2]/255.); };
#define COLOR3(r, g, b) { glColor3f(r/255., g/255., b/255.); };
#define GREY(val) { glColor3f(val/255., val/255., val/255.); };
#define PUSH glPushMatrix();
#define POP glPopMatrix();
#define PRINT(str) { std::cout << str << std::endl; };
#define REPEAT(n) for(int i=0 ; i<n ; i++)
#define CUBE glutSolidCube(1.0f);
#define TRANSLATE(x, y, z) glTranslatef(x, y, z);
#define SCALE(x, y, z) glScalef(x, y, z);
#define ROTATE(angle, x, y, z) glRotatef(angle, x, y, z);
#define BEGIN glBegin(GL_QUADS);
#define VERTEX(x, y, z) glVertex3f(x, y, z);
#define END glEnd();

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

	int bodyCol[3] = { 255, 150, 0 };
	int white[3] = { 255, 255, 255 };
	int black[3] = { 0, 0, 0 };
	int clothingCol[3] = { 255, 82, 0 };
	int clothingCol2[3] = { 160, 82, 45 };

	float animation = 0;
};

class Ground : public Entity {
public:
	Ground(Mistral* g) : Entity(g) { Create(); };

	void Update();

	void DrawSelf() {
		PUSH
			BEGIN
			COLOR3(102, 50, 0)

			VERTEX(0, 0, .5)
			VERTEX(1, 0, .5)
			VERTEX(1, -1, .5)
			VERTEX(0, -1, .5)


			VERTEX(0, -1, .5)
			VERTEX(1, -1, .5)
			VERTEX(1, -1, -.5)
			VERTEX(0, -1, -.5)
			END
		POP
	};
};

class Grass : public Ground {
public:
	Grass(Mistral* g) : Ground(g) { Create(); };

	void DrawSelf() {
		PUSH
		BEGIN
		COLOR3(0, 150, 50)

		VERTEX(0, 0, -.5)
		VERTEX(1, 0, -.5)
		VERTEX(1, 0, .5)
		VERTEX(0, 0, .5)

		VERTEX(0, 0, .5)
		VERTEX(1, 0, .5)
		VERTEX(1, -.4, .5)
		VERTEX(0, -.4, .5)

		COLOR3(102, 50, 0)

		VERTEX(0, -.4, .5)
		VERTEX(1, -.4, .5)
		VERTEX(1, -1, .5)
		VERTEX(0, -1, .5)

		VERTEX(0, -1, .5)
		VERTEX(1, -1, .5)
		VERTEX(1, -1, -.5)
		VERTEX(0, -1, -.5)
		END
		POP
	};
};


class GroundCorner : public Ground {
public:
	GroundCorner(Mistral* g) : Ground(g) { Create(); };

	void DrawSelf() {
		PUSH
			BEGIN
			COLOR3(102, 50, 0)

			// Top grass
			VERTEX(0, 0, -.5)
			VERTEX(1, 0, -.5)
			VERTEX(1, 0, .5)
			VERTEX(0, 0, .5)

			// Bottom grass
			VERTEX(0, -.4, -.5)
			VERTEX(1, -.4, -.5)
			VERTEX(1, -.4, .5)
			VERTEX(0, -.4, .5)

			// Front grass
			VERTEX(0, 0, .5)
			VERTEX(1, 0, .5)
			VERTEX(1, -.4, .5)
			VERTEX(0, -.4, .5)

			// Side Grass
			VERTEX(1, 0, -.5)
			VERTEX(1, -.4, -.5)
			VERTEX(1, -.4, .5)
			VERTEX(1, 0, .5)

			// Front ground
			VERTEX(0, -.4, .5)
			VERTEX(.5, -.4, .5)
			VERTEX(.5, -1, .5)
			VERTEX(0, -1, .5)

			// Right ground
			VERTEX(.5, -.4, .5)
			VERTEX(.5, -.4, -.5)
			VERTEX(.5, -1, -.5)
			VERTEX(.5, -1, .5)

			// Left ground
			VERTEX(0, 0, .5)
			VERTEX(0, 0, -.5)
			VERTEX(0, -1, -.5)
			VERTEX(0, -1, .5)

			// Bottom ground
			VERTEX(0, -1, .5)
			VERTEX(.5, -1, .5)
			VERTEX(.5, -1, -.5)
			VERTEX(0, -1, -.5)

			END
			POP
	};
};


class GrassCorner : public Ground {
public:
	GrassCorner(Mistral* g) : Ground(g) { Create(); };

	void DrawSelf() {
		PUSH
			BEGIN
			COLOR3(0, 150, 50)

			// Top grass
			VERTEX(0, 0, -.5)
			VERTEX(1, 0, -.5)
			VERTEX(1, 0, .5)
			VERTEX(0, 0, .5)

			// Bottom grass
			VERTEX(0, -.4, -.5)
			VERTEX(1, -.4, -.5)
			VERTEX(1, -.4, .5)
			VERTEX(0, -.4, .5)

			// Front grass
			VERTEX(0, 0, .5)
			VERTEX(1, 0, .5)
			VERTEX(1, -.4, .5)
			VERTEX(0, -.4, .5)

			// Side Grass
			VERTEX(1, 0, -.5)
			VERTEX(1, -.4, -.5)
			VERTEX(1, -.4, .5)
			VERTEX(1, 0, .5)

			COLOR3(102, 50, 0)

			// Front ground
			VERTEX(0, -.4, .5)
			VERTEX(.5, -.4, .5)
			VERTEX(.5, -1, .5)
			VERTEX(0, -1, .5)

			// Side ground
			VERTEX(.5, -.4, .5)
			VERTEX(.5, -.4, -.5)
			VERTEX(.5, -1, -.5)
			VERTEX(.5, -1, .5)

			// Bottom ground
			VERTEX(0, -1, .5)
			VERTEX(.5, -1, .5)
			VERTEX(.5, -1, -.5)
			VERTEX(0, -1, -.5)

			END
			POP
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

class Enemy1 : public Entity {
public:
	Enemy1(Mistral* g) : Entity(g) { Create(); };

	void Create();

	void Update();

	void DrawSelf() {
		PUSH
			COLOR3(200, 100, 0)
			SCALE(0.7, 0.7, 0.5)
			TRANSLATE(0, 0.5, 0)
			CUBE
		POP
	}

	float vspd = 0;
	float hspd = 0;
	float gravity = 0.01;
};