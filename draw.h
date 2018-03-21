#ifndef BEADANDO_DRAW_H
#define BEADANDO_DRAW_H

#include "model.h"

#include <GL/glut.h>
#include <math.h>

#define SKYBOX_WIDHT 50.0       // [-x, x]
#define SKYBOX_HEIGHT 50.0      // [GROUND_LEVEL, x]
#define GROUND_LEVEL 0.0

#ifndef GL_EXT_texture_edge_clamp
#define GL_EXT_CLAMP_TO_EDGE                 0x812F
#endif

void initializeTexture();

////Draw block based on coords and texture
void drawBlock(double x, double y, double z, int texture);

////Draw tree to x,y position width given height
void drawTree(double positionX, double positionY, double trunkHeight, Tree tree);

void drawBigTree(double positionX, double positionY, double trunkHeight, Tree tree, double cords[40][3]);

////Draw ground
void drawGround(int groundTexture, int gardenTexture);

void drawSkyboxBack(int texture);

void drawSkyboxFront(int texture);

void drawSkyboxLeft(int texture);

void drawSkyboxRight(int texture);

void drawSkyboxTop(int texture);

void drawSkybox(Skybox skybox);

void drawHouse(World world);

void drawModel(const struct Model* model);

#endif
