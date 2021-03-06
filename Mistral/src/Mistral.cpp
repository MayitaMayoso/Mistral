#include "Mistral.h"

#include "iostream"
#include <stdlib.h>
#include "glut.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"


Mistral* Mistral::self = 0;

void init(void) {
	// Light properties for the diffuse light, specular light, and light position.
	float diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	float specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float LightPosition[] = { 8.0f, 8.0f, 8.0f, 1.0f };
	float LightPosition2[] = { -8.0f, 8.0f, 8.0f, 1.0f };

	glClearColor(0.0f, 0.7f, 0.8f, 1.0f);  // Clear the screen to black.
	glShadeModel(GL_SMOOTH);               // Smooth shading in our scenes.
	glEnable(GL_DEPTH_TEST);               // Enable desth testing.
	glEnable(GL_LIGHTING);                 // Enable lighting.


	// Here we will set up a spotlight light source in our scene.  This light will shine on
	// the objects giving them a nicer look than a plain dull color.  This stuff has nothing
	// to do with the demo it self but only to make things look better.
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

	// Enable our light.
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_AUTO_NORMAL);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition2);

	// Enable our light.
	glEnable(GL_LIGHT1);

	// Set up the material information for our objects.  Again this is just for show.
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_RIGHT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT_RIGHT, GL_SPECULAR, specularLight);
	glMateriali(GL_FRONT_RIGHT, GL_SHININESS, 80);
}

// ------------- INITIALIZING THE ENGINE VARIABLES ---------------
Mistral::Mistral() {
	// VIEW VARIABLES
	width = 1280;
	height = 720;
	AspectRatio = float(width) / float(height);
	fov = 90.0f;
	fps = 60;
	winId = 0;

	input = new Input();
	camera = new Camera(this);
	scene = new Scene(this);

	audio = new Audio();
	int buf = audio->loadSound("resources/GameMusic.wav");
	auto music = new AudioSource();
	music->playSound(buf);
}

void Mistral::GeneralDraw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(fov, AspectRatio, 0.01, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camera->position.x,	camera->position.y, camera->position.z
			 ,camera->lookat.x,		camera->lookat.y,	camera->lookat.z
			 ,camera->up.x,			camera->up.y,		camera->up.z	);

	// Draw all the entities
	for (Entity* e : EntitiesList) {
		e->DrawSelfCallback();
	}

	// Draw all the entities
	for (Entity* e : EntitiesList) {
		e->Draw();
	}
	glutSwapBuffers();
}

void Mistral::GeneralUpdate(int value) {
	static int delta = glutGet(GLUT_ELAPSED_TIME);

	input->UpdateInputs();
	camera->UpdateCamera();

	// Draw all the entities
	for (int id : EntitiesToDestroy) {
		for (Entity* e : EntitiesList) {
			if (e->id == id) {
				e->Destroy();
				EntitiesList.remove(e);
				delete e;
				break;
			}
		}
	}
	EntitiesToDestroy.clear();

	scene->NextLevelCallback();
	scene->RestartLevelCallback();

	for (Entity* e : EntitiesList) {
		e->Update();
	}

	if (input->InputCheck("EXIT", InputState::PRESSED)) End();
	if (input->InputCheck("RESTART", InputState::PRESSED)) scene->RestartLevel();

	glutTimerFunc(1000 / fps, UpdateCallback, 0);
	glutPostRedisplay();
}

void Mistral::GeneralPressKeyboard(unsigned char key, int x, int y) {
	input->KeyboardPressHandle(toupper(key));
}

void Mistral::GeneralPressSpecial(int key, int x, int y) {
	input->KeyboardPressHandle(key);
}

void Mistral::GeneralReleaseKeyboard(unsigned char key, int x, int y) {
	input->KeyboardReleaseHandle(toupper(key));
}

void Mistral::GeneralReleaseSpecial(int key, int x, int y) {
	input->KeyboardReleaseHandle(key);
}

void Mistral::End() {
	glutDestroyWindow(winId);
}

int Mistral::Run(int argc, char* args[], Mistral* s) {
	glutInit(&argc, args);
	setSelf(s);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(1920 / 2 - width / 2, 1080 / 2 - height / 2);
	winId = glutCreateWindow("Mistral");
	init();

	scene->SetLevels({ "world1", "world2", "world3", "world4", "world5" });

	glutDisplayFunc(DrawCallback);
	glutTimerFunc(int(1000 / fps), UpdateCallback, 0);

	glutKeyboardFunc(KeyboardPressCallback);
	glutSpecialFunc(SpecialPressCallback);
	glutKeyboardUpFunc(KeyboardReleaseCallback);
	glutSpecialUpFunc(SpecialReleaseCallback);
	glutIgnoreKeyRepeat(1);
	glutMainLoop();
	return 0;
}

int main(int argc, char* args[]) {
	Mistral* game = new Mistral();

	game->Run(argc, args, game);

	return 0;
}