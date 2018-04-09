#ifndef BEADANDO_DRAW_H
#define BEADANDO_DRAW_H

#include "model.h"

#include <GL/glut.h>
#include <math.h>

#define SKYBOX_WIDHT 50.0       // used to world width like: [-x, x]
#define SKYBOX_HEIGHT 50.0      // used to world height like: [GROUND_LEVEL, x]
#define GROUND_LEVEL 0.0

#ifndef GL_EXT_texture_edge_clamp
#define GL_EXT_CLAMP_TO_EDGE                 0x812F
#endif

/**
 * FUNCTIONS
 */
//// Load all texture
void initializeTexture();

////Draw block based on x,y,z coords and texture
void drawBlock(double x, double y, double z, int texture);

////Draw tree to x,y position with given height
void drawTree(double positionX, double positionY, double trunkHeight, Tree tree);

//// Draw a big tree to x,y position with given height
void drawBigTree(double positionX, double positionY, double trunkHeight, Tree tree, double cords[40][3]);

////Draw the ground
void drawGround(int groundTexture, int gardenTexture);

//// Draw the back of the skybox
void drawSkyboxBack(int texture);

//// Draw the front of the skybox
void drawSkyboxFront(int texture);

//// Draw the left of the skybox
void drawSkyboxLeft(int texture);

//// Draw the right of the skybox
void drawSkyboxRight(int texture);

//// Draw the top of the skybox
void drawSkyboxTop(int texture);

//// Draw all the skybox elements
void drawSkybox(Skybox skybox);

//// Draw house model
void drawHouse(World world);

//// Draw a given model
void drawModel(const struct Model* model);

//// Draw all the world elements and models
void drawWorld(struct World world);

//// Initialize all the tree coords
void initializeAllTreeCoords();
#endif
