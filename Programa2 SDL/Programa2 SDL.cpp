// ConsoleApplication1.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

GLdouble angle = 0.0F;
int refreshmill = 1;
int red = 1, green = 0, blue = 0;
float angulo = 0.0;
float camX = 0.0f, camY = 0.0f, objX;
static int rotarobj = 0, rotarobjy = 0;
int colores;
int radio;
float z = cos(camY) * radio;
float x = sin(camY) * radio;
float i = 0;
//y esta para el tono (hue) del color
float h = 0;

SDL_Window *window;

void endfunc(int codeExit) {
	SDL_Quit();
	exit(codeExit);
}

void cubo() {
	static GLfloat v0[] = { -1.0f, -1.0f,  1.0f };
	static GLfloat v1[] = { 1.0f, -1.0f,  1.0f };
	static GLfloat v2[] = { 1.0f,  1.0f,  1.0f };
	static GLfloat v3[] = { -1.0f,  1.0f,  1.0f };
	static GLfloat v4[] = { -1.0f, -1.0f, -1.0f };
	static GLfloat v5[] = { 1.0f, -1.0f, -1.0f };
	static GLfloat v6[] = { 1.0f,  1.0f, -1.0f };
	static GLfloat v7[] = { -1.0f,  1.0f, -1.0f };
	static GLubyte red[] = { 255,   0,   0, 255 };
	static GLubyte green[] = { 0, 255,   0, 255 };
	static GLubyte blue[] = { 0,   0, 255, 255 };
	static GLubyte white[] = { 255, 255, 255, 255 };
	static GLubyte yellow[] = { 0, 255, 255, 255 };
	static GLubyte black[] = { 0,   0,   0, 255 };
	static GLubyte orange[] = { 255, 255,   0, 255 };
	static GLubyte purple[] = { 255,   0, 255,   0 };

	glBegin(GL_TRIANGLES);

	glColor4ubv(red);
	glVertex3fv(v0);
	glColor4ubv(green);
	glVertex3fv(v1);
	glColor4ubv(blue);
	glVertex3fv(v2);

	glColor4ubv(red);
	glVertex3fv(v0);
	glColor4ubv(blue);
	glVertex3fv(v2);
	glColor4ubv(white);
	glVertex3fv(v3);

	glColor4ubv(green);
	glVertex3fv(v1);
	glColor4ubv(black);
	glVertex3fv(v5);
	glColor4ubv(orange);
	glVertex3fv(v6);

	glColor4ubv(green);
	glVertex3fv(v1);
	glColor4ubv(orange);
	glVertex3fv(v6);
	glColor4ubv(blue);
	glVertex3fv(v2);

	glColor4ubv(black);
	glVertex3fv(v5);
	glColor4ubv(yellow);
	glVertex3fv(v4);
	glColor4ubv(purple);
	glVertex3fv(v7);

	glColor4ubv(black);
	glVertex3fv(v5);
	glColor4ubv(purple);
	glVertex3fv(v7);
	glColor4ubv(orange);
	glVertex3fv(v6);

	glColor4ubv(yellow);
	glVertex3fv(v4);
	glColor4ubv(red);
	glVertex3fv(v0);
	glColor4ubv(white);
	glVertex3fv(v3);

	glColor4ubv(yellow);
	glVertex3fv(v4);
	glColor4ubv(white);
	glVertex3fv(v3);
	glColor4ubv(purple);
	glVertex3fv(v7);

	glColor4ubv(white);
	glVertex3fv(v3);
	glColor4ubv(blue);
	glVertex3fv(v2);
	glColor4ubv(orange);
	glVertex3fv(v6);

	glColor4ubv(white);
	glVertex3fv(v3);
	glColor4ubv(orange);
	glVertex3fv(v6);
	glColor4ubv(purple);
	glVertex3fv(v7);

	glColor4ubv(green);
	glVertex3fv(v1);
	glColor4ubv(red);
	glVertex3fv(v0);
	glColor4ubv(yellow);
	glVertex3fv(v4);

	glColor4ubv(green);
	glVertex3fv(v1);
	glColor4ubv(yellow);
	glVertex3fv(v4);
	glColor4ubv(black);
	glVertex3fv(v5);

	glEnd();
}

void draw_screen() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* We don't want to modify the projection matrix. */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(8.0, 8.0f+angle, 8.0f+angle, 0, 0+angle, 0+angle, 0.f, 1.f,1.f);
	glColor3f(red, blue, green);
	glPushMatrix();
	glRotatef(angulo, 0.0, 1.0, rotarobjy);
	cubo();
	glPopMatrix();
	rotarobj = (rotarobj + 1) % 360;
	SDL_GL_SwapWindow(window);
	angulo++;
	//glFlush();
}

static void setup_opengl(int width, int height)
{
	float ratio = (float)width / (float)height;

	/* Our shading model--Gouraud (smooth). */
	glShadeModel(GL_SMOOTH);

	/* Culling. */
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	/* Set the clear color. */
	glClearColor(0, 0, 0, 0);

	/* Setup our viewport. */
	glViewport(0, 0, width, height);

	/*
	* Change to the projection matrix and set
	* our viewing volume.
	*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/*
	* EXERCISE:
	* Replace this with a call to glFrustum.
	*/
	gluPerspective(60.0, ratio, 1.0, 1024.0);
}

void handle_key_down(SDL_Keysym *keysym) {
	switch (keysym->sym) {
	case SDLK_ESCAPE:
		endfunc(0);
		break;
	case SDLK_x:
		rotarobjy = (rotarobjy - 60) % 360;
		//glutPostRedisplay();
		break;
	case SDLK_c:
		red = rand() % 2;
		blue = rand() % 2;
		green = rand() % 2;
		break;
	case SDLK_s:
		angle = angle + 1;
		//glutPostRedisplay();
		break;
	case SDLK_a:
		angle = angle - 1;
		//glutPostRedisplay();
		break;
	case SDLK_F7:
		rotarobjy = (rotarobjy - 60) % 360;
		//glutPostRedisplay();
		break;
	case SDLK_F4:
		red = rand() % 2;;
		blue = rand() % 2;
		green = rand() % 2;
		//glutPostRedisplay();
		break;
	case SDLK_F3:
		angle = angle + 1;
		//glutPostRedisplay();
		break;
	}
	//if (SDLK_LCTRL || SDLK_RCTRL) {
	//	printf("CTRL  key %d\n");
	//	angle = angle - 1;
	//	//glutPostRedisplay();
	//}
}

static void process_events(void)
{
	/* Our SDL event placeholder. */
	SDL_Event event;

	/* Grab all the events off the queue. */
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			/* Handle key presses. */
			handle_key_down(&event.key.keysym);
			break;
		case SDL_QUIT:
			/* Handle quit requests (like Ctrl-c). */
			endfunc(0);
			break;
		}

	}

}

int main(int argc, char *argv[])
{

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL no pudo ser inicializado Error: " << SDL_GetError() << std::endl;
		endfunc(1);
		return EXIT_FAILURE;
	}

	window = SDL_CreateWindow("Programa 2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

	//SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	//SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	//SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	//SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	setup_opengl(SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_RenderPresent(renderer);


	while (1) {
		/* Process incoming events. */
		process_events();
		/* Draw the screen. */
		draw_screen();
	}


	return EXIT_SUCCESS;
}
