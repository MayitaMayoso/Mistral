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
	int black[3] = { 88, 54, 34 };
	int clothingCol[3] = { 255, 92, 0 };
	int clothingCol2[3] = { 255, 180, 10 };

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
	// BEES 
/* // BEE BODY
	PUSH
		COLOR3(255, 238, 0);
		TRANSLATE(0, 1.6, 0);
		SCALE(0.8, 0.6, 0.2);
		CUBE
	POP
	// BEE HEAD
	PUSH
		COLOR3(35, 26, 21);
		TRANSLATE(-0.5, 1.6, 0);
		SCALE(0.2, 0.5, 0.2);
		CUBE
	POP
	// WING EYE
	PUSH
		COLOR3(255, 255, 255);
		TRANSLATE(-0.5, 1.58, 0.09);
		SCALE(0.1, 0.15, 0.03);
		CUBE
	POP
	// BEE LINE
	PUSH
		COLOR3(45, 36, 31);
		TRANSLATE(0, 1.6, 0);
		SCALE(0.3, 0.7, 0.21);
		CUBE
	POP
	// BEE B
	PUSH
		COLOR3(45, 36, 31);
		TRANSLATE(0.45, 1.6, 0);
		SCALE(0.12, 0.4, 0.15);
		CUBE
	POP
	PUSH
		COLOR3(45, 36, 31);
		TRANSLATE(0.5, 1.6, 0);
		SCALE(0.2, 0.1, 0.03);
		CUBE
	POP
	PUSH
		COLOR3(255, 140, 26);
		TRANSLATE(0.63, 1.6, 0);
		SCALE(0.1, 0.1, 0.03);
		CUBE
	POP

	// PAWS
	PUSH
		COLOR3(45, 36, 31);
		TRANSLATE(-0.3, 1.25, -0.06);
		SCALE(0.1, 0.25, 0.04);
		CUBE
	POP
	PUSH
		COLOR3(35, 26, 21);
		TRANSLATE(-0.25, 1.25, 0.06);
		SCALE(0.1, 0.25, 0.04);
		CUBE
	POP
	// WING LEFT
	PUSH
		COLOR3(128, 255, 255); // BLUE
		TRANSLATE(-0.15, 2, 0.03);
		SCALE(0.2, 0.5, 0.12);
		CUBE
	POP
	// WING RIGHT
	PUSH
		COLOR3(128, 255, 255);
		TRANSLATE(0.13, 1.9, -0.03);
		SCALE(0.2, 0.5, 0.12);
		CUBE
	POP		
////////////// SMALL BEE 
	// BEE BODY 
	PUSH
		COLOR3(255, 238, 0);
		TRANSLATE(2, 0.7, 0);
		SCALE(0.4, 0.3, 0.1);
		CUBE
	POP
	// BEE HEAD
	PUSH
		COLOR3(35, 26, 21);
		TRANSLATE(1.745, 0.7, 0);
		SCALE(0.1, 0.25, 0.1);
		CUBE
	POP
	// WING EYE
	PUSH
		COLOR3(255, 255, 255);
		TRANSLATE(1.745, 0.654, 0.045);
		SCALE(0.05, 0.075, 0.015);
		CUBE
	POP
	// BEE LINE
	PUSH
		COLOR3(45, 36, 31);
		TRANSLATE(2, 0.7, 0);
		SCALE(0.18, 0.37, 0.11);
		CUBE
			POP
	// BEE B
	PUSH
		COLOR3(45, 36, 31);
		TRANSLATE(2.24, 0.7, 0);
		SCALE(0.06, 0.2, 0.075);
		CUBE
	POP
	PUSH
		COLOR3(45, 36, 31);
		TRANSLATE(2.28, 0.7, 0);
		SCALE(0.1, 0.05, 0.05);
		CUBE
	POP
	PUSH
		COLOR3(115, 230, 0);
		TRANSLATE(2.35, 0.7, 0);
		SCALE(0.04, 0.05, 0.05);
		CUBE
	POP
	// PAWS
	PUSH
		COLOR3(45, 36, 31);
		TRANSLATE(1.87, 0.525, -0.03);
		SCALE(0.06, 0.125, 0.02);
		CUBE
	POP
	PUSH
		COLOR3(35, 26, 21);
		TRANSLATE(1.85, 0.52, 0.03);
		SCALE(0.06, 0.125, 0.02);
		CUBE
	POP
	// WING LEFT
	PUSH
		COLOR3(128, 255, 255); // BLUE
		TRANSLATE(1.9, 0.85, -0.02);
		SCALE(0.1, 0.25, 0.05);
		CUBE
	POP
	// WING RIGHT
	PUSH
		COLOR3(128, 255, 255);
		TRANSLATE(2.05, 0.88, 0.02);
		SCALE(0.1, 0.25, 0.05);
		CUBE
	POP
	*/
	// MUSHROOMS 	
/* // NUMBER 1, LEG
	PUSH
		COLOR3(255, 255, 255);
		TRANSLATE(0, 0.4, 0);
		SCALE(0.2, 0.6, 0.08);
		CUBE
	POP
	/// HAT
	PUSH
		COLOR3(88, 54, 34);
		TRANSLATE(0, 0.8, 0);
		SCALE(0.5, 0.25, 0.2);
		CUBE
	POP
	PUSH
		COLOR3(88, 54, 34);
		TRANSLATE(0, 0.95, 0);
		SCALE(0.3, 0.2, 0.1);
		CUBE
	POP */
	// NUMBER 2
/* //LEG
	PUSH
		COLOR3(255, 255, 255);
		TRANSLATE(0, 0.5, 0);
		SCALE(0.35, 0.7, 0.08);
		CUBE
	POP
	/// HAT
	PUSH
		COLOR3(255, 10, 10);
		TRANSLATE(0, 1.07, 0);
		SCALE(1.2, 0.3, 0.2);
		CUBE
	POP
	PUSH
		COLOR3(255, 10, 10);
		TRANSLATE(0, 1.22, 0);
		SCALE(0.9, 0.35, 0.1);
		CUBE
	POP
	PUSH
		COLOR3(255, 10, 10);
		TRANSLATE(0, 1.37, 0);
		SCALE(0.6, 0.4, 0.1);
		CUBE
	POP
	PUSH
		COLOR3(255, 255, 255);
		TRANSLATE(0, 1, 0);
		SCALE(0.6, 0.4, 0.1);
		CUBE
	POP
	// DOTS
	PUSH
		COLOR3(255, 255, 255);
		TRANSLATE(0.06, 1.37, 0);
		SCALE(0.1, 0.1, 0.12);
		CUBE
	POP
	PUSH
		COLOR3(255, 255, 255);
		TRANSLATE(-0.3, 1.27, 0);
		SCALE(0.14, 0.12, 0.12);
		CUBE
	POP
	PUSH
		COLOR3(255, 255, 255);
		TRANSLATE(0.15, 1.1, 0);
		SCALE(0.18, 0.1, 0.22);
		CUBE
	POP */
	// SNAIL 
 /*
	PUSH
		COLOR3(222, 27, 58);
		TRANSLATE(-0.05, 0.5, 0);
		SCALE(0.8, 0.8, 0.1);
		CUBE
	POP 
	PUSH
		COLOR3(153, 0, 51);
		TRANSLATE(-0.05, 0.5, 0);
		SCALE(0.5, 0.5, 0.2);
		CUBE
	POP
	PUSH
		COLOR3(222, 27, 58);
		TRANSLATE(-0.05, 0.5, 0);
		SCALE(0.2, 0.2, 0.3);
		CUBE
	POP
	PUSH
		COLOR3(230, 153, 76);
		TRANSLATE(-0.6, 0.25, 0);
		SCALE(0.3, 0.3, 0.1);
		CUBE
	POP
	PUSH
		COLOR3(230, 153, 76);
		TRANSLATE(-0.8, 0.45, 0);
		SCALE(0.3, 0.7, 0.1);
		CUBE
	POP
	PUSH
		COLOR3(230, 153, 76);
		TRANSLATE(-0.8, 0.9, -0.02);
		SCALE(0.08, 0.2, 0.01);
		CUBE
	POP
	PUSH
		COLOR3(230, 153, 76);
		TRANSLATE(-0.8, 0.85, 0.02);
		SCALE(0.08, 0.15, 0.01);
		CUBE
	POP
	PUSH
		COLOR3(255, 255, 255);
		TRANSLATE(-0.8, 1, -0.02);
		SCALE(0.08, 0.15, 0.01);
		CUBE
	POP
		PUSH
		COLOR3(255, 255, 255);
		TRANSLATE(-0.8, 1, 0.02);
		SCALE(0.08, 0.15, 0.01);
		CUBE
	POP */
	// BOSS (?)
/* // EGG 
	PUSH
		COLOR3(255, 250, 250);
		TRANSLATE(0, 0.25, 0);
		SCALE(1.2, 0.4, 0.3);
		CUBE
	POP
	PUSH
		COLOR3(255, 250, 250);
		TRANSLATE(0, 0.6, 0);
		SCALE(1.6, 0.4, 0.3);
		CUBE
	POP
	PUSH
		COLOR3(255, 250, 250);
		TRANSLATE(-0.8, 0.9, 0);
		SCALE(0.4, 0.3, 0.3);
		CUBE
	POP
	PUSH
		COLOR3(255, 250, 250);
		TRANSLATE(0.7, 0.8, 0);
		SCALE(0.3, 0.3, 0.3);
		CUBE
	POP
	PUSH
		COLOR3(255, 250, 250);
		TRANSLATE(0, 0.9, 0);
		SCALE(0.2, 0.2, 0.3);
		CUBE
	POP
	PUSH
		COLOR3(255, 250, 250);
		TRANSLATE(0.7, 0.15, 0.2);
		SCALE(0.3, 0.2, 0.2);
		CUBE
	POP
// CHICKEN 
	PUSH
		COLOR3(255, 180, 0);
		TRANSLATE(0, 1, 0);
		SCALE(1.2, 0.8, 0.2);
		CUBE
	POP
	PUSH
		COLOR3(255, 180, 0);
		TRANSLATE(0, 1.5, 0);
		SCALE(0.9, 0.9, 0.2);
		CUBE
	POP
// MOUTH
	PUSH
		COLOR3(255, 80, 0);
		TRANSLATE(-0.14, 2, 0);
		SCALE(0.15, 0.3, 0.1);
		CUBE
	POP
	PUSH
		COLOR3(255, 80, 0);
		TRANSLATE(0.15, 2, 0);
		SCALE(0.15, 0.3, 0.1);
		CUBE
	POP
//  EYES
	PUSH
		COLOR3(255, 255, 255);
		TRANSLATE(-0.21, 1.8, 0);
		SCALE(0.1, 0.15, 0.22);
		CUBE
	POP
*/
	} 

	float vspd = 0;
	float hspd = 0;
	float gravity = 0.01;
};