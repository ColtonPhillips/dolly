#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "GL/glu.h"

#include "math.h"

#include <iostream>


#define WIDTH	640
#define HEIGHT	480


float fov = 45;
float fov_accel = 45;

float y_offset = 0;
float y_offset_accel = 0;

float ang = 0;
float ang_accel =0;


void drawBox(float width, float height, float depth, float x, float y, float z)
{

	glBegin(GL_QUADS);
	//
	glColor3f(1,0,0);
	
	glVertex3f(x,			y,				z);
	glVertex3f(x,			y,				z + depth);
	glVertex3f(x,			y+height,		z + depth);
	glVertex3f(x,			y+height,		z);

	glColor3f(0,1,0);

	glVertex3f(x,			y,				z);
	glVertex3f(x,			y,				z + depth);
	glVertex3f(x + width,	y,				z + depth);
	glVertex3f(x + width,	y,				z);

	glColor3f(0,0,1);

	glVertex3f(x,			y,				z);
	glVertex3f(x,			y + height,		z);
	glVertex3f(x + width,	y + height,		z);
	glVertex3f(x + width,	y,				z);

	glColor3f(0,1,1);

	glVertex3f(x + width,	y,				z);
	glVertex3f(x + width,	y,				z + depth);
	glVertex3f(x + width,	y + height,		z + depth);
	glVertex3f(x + width,	y + height,		z);

	glColor3f(1,0,1);

	glVertex3f(x,			y + height,		z);
	glVertex3f(x,			y + height,		z + depth);
	glVertex3f(x + width,	y + height,		z + depth);
	glVertex3f(x + width,	y + height,		z);

	glColor3f(1,1,0);

	glVertex3f(x,			y,				z + depth);
	glVertex3f(x,			y + height,		z + depth);
	glVertex3f(x + width,	y + height,		z + depth);
	glVertex3f(x + width,	y,				z + depth);

	glEnd();

}

void changeFOV(float fovTarget)
{
	
	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();
	
	fov = fov * .99f + fovTarget * .01f;
	
	ang += ang_accel;
	y_offset += y_offset_accel;
	
	
	GLfloat zNear = 0.1f;
	GLfloat zFar = 2048.0f;
	GLfloat aspect = float(WIDTH)/float(HEIGHT);
	GLfloat fH = tan( float(fov / 360.0f * 3.14159f) ) * zNear;
	GLfloat fW = fH * aspect;
	glFrustum( -fW, fW, -fH, fH, zNear, zFar );

	//get the dolly zoom thing
	
	float dist = -13.95 / tan(((fov/2.f) / 360.0f )* 3.14159f);

	std::cout << "fov " << fov << " dist " << dist << "\n";
	
	glTranslatef(0, y_offset, dist);
	
	glRotatef(ang, 0, 1, 0);
	
	
	glMatrixMode(GL_MODELVIEW);

}

void endProgram(int code) {SDL_Quit();	exit(code);}
 
void handleKeys(SDL_keysym* keysym, bool state) {
	switch(keysym->sym) {
		case SDLK_ESCAPE:	endProgram(0); break;
		
		case SDLK_UP:
			if(state)
			{
				fov_accel = 150;
			}
			else
			{
				fov_accel = fov;
			}
			break;
		case SDLK_DOWN:	
			if(state)
			{
				fov_accel = 5;
 			}
 			else
 			{
 				fov_accel = fov;
 			}
 			break;	
 		case SDLK_d:
 			if(state)
 			{
 				ang_accel = 0.7f;
 			}
 			else
 			{
 				ang_accel = 0.f;
 			}
 			break;
 		case SDLK_a:
 			if(state)
 			{
 				ang_accel = -0.7f;
 			}
 			else
 			{
 				ang_accel = 0.f;
 			}
 			break;
 			
 			case SDLK_w:
 			if(state)
 			{
 				y_offset_accel = 1.f;
 			}
 			else
 			{
 				y_offset_accel = 0.f;
 			}
 			break;
 			
 			case SDLK_s:
 			if(state)
 			{
 				y_offset_accel = -1.f;
 			}
 			else
 			{
 				y_offset_accel = 0.f;
 			}
 			break;
 			
 			
	}
}


// Process SDL events
void processEvents() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_KEYDOWN:	handleKeys(&event.key.keysym, true );	break;
			case SDL_KEYUP  :	handleKeys(&event.key.keysym, false);	break;
			case SDL_QUIT   :	endProgram(0);	break;
		}
	}
}

void drawRegularBox(float x, float z)
{
	drawBox(4,4,4, x-2,-20, z);
}

 
void mainLoop() {
	
	
	changeFOV(fov);
	
	while(true) {
		processEvents();

 
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); // Clear color and depth buffer
		glLoadIdentity(); // Reset orientation
 
 		if(fov != fov_accel || ang_accel != 0.f || y_offset_accel != 0.f)
 		{
 			changeFOV(fov_accel);
		}
		
		drawRegularBox(0,0);
		
		for(int i = -16; i < 17; i++)
		{
			for( int j = -16; j < 17; j++)
			{
				if(i < 2 && i > -2 && j < 2 && j > -2)
				{
					break;
				}
			
				int thing = 	((i+16)*57 + (j+16)*109)%34 ;
				if(thing < 6 || thing > 22)
				{
					drawRegularBox(10*i, 10 * j);
				}
			}
		}
		
 
		SDL_GL_SwapBuffers(); // Update screen
 
	}
}
 
// Setup OpenGL perspective
void setupOpengl() {
	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_DEPTH_TEST);

	changeFOV(45);
	


	glMatrixMode(GL_MODELVIEW);
}
 
// Init everything
int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);



	SDL_WM_SetCaption( "Dolly", NULL );

	SDL_SetVideoMode(WIDTH, HEIGHT, 0, SDL_OPENGL | SDL_GL_DOUBLEBUFFER);
	setupOpengl();
	mainLoop();
	return 0;
}




