#include "Box.h"
#include <iostream>

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "GL/glu.h"

Box::Box()
{

}

Box::~Box()
{

}

void Box::drawBox()
{
/* 	glBegin(GL_QUADS);

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

*/
}
