#ifndef BEADANDO_DRAW_H
#define BEADANDO_DRAW_H

#include <GL/glut.h>

typedef GLubyte Pixel[3];

GLuint loadTexture(char* filename, Pixel* image);

void initializeTexture();

////Draw block based on coords and texture
void drawBlock(double x, double y, double z, int texture);

////Draw tree to x,y position width given height
void drawTree(double positionX, double positionY, double trunkHeight);

////Draw ground
void drawGround();

#endif
