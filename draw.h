#ifndef BEADANDO_DRAW_H
#define BEADANDO_DRAW_H

#include "model.h"

#include <GL/glut.h>
#include <math.h>

#ifndef GL_EXT_texture_edge_clamp
#define GL_EXT_CLAMP_TO_EDGE                 0x812F
#endif
//typedef GLubyte Pixel[3];

//GLuint loadTexture(char* filename, Pixel* image);

void initializeTexture();

////Draw block based on coords and texture
void drawBlock(double x, double y, double z, int texture);

////Draw tree to x,y position width given height
void drawTree(double positionX, double positionY, double trunkHeight, Tree tree);

////Draw ground
void drawGround(int texture);

void drawSkybox(int texture);

#endif
