#include "draw.h"

#include <GL/glut.h>
#include <SOIL/SOIL.h>

void drawBlock(double x, double y, double z, int texture) {

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE);

    //// BOTTOM
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,0.0);          // 0 0
    glVertex3d(x, y, z);

    glTexCoord2f(0.0, 1.0);         // 0 1
    glVertex3d(x,y+1,z);

    glTexCoord2f(1.0, 1.0);         // 1 1
    glVertex3d(x+1,y+1,z);

    glTexCoord2f(1.0,0.0);          // 1 0
    glVertex3d(x+1,y,z);
    glEnd();
    //end of first texture

    //// BACK
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);         // 0 0
    glVertex3d(x, y, z);

    glTexCoord2f(0.0, 1.0);         // 0 1
    glVertex3d(x, y, z+1);

    glTexCoord2f(1.0, 1.0);         // 1 1
    glVertex3d(x+1, y, z+1);

    glTexCoord2f(1.0, 0.0);         // 1 0
    glVertex3d(x+1, y, z);
    glEnd();
    //end of second texture

    //// LEFT
    glBegin(GL_QUADS);
    glTexCoord2s(0.0, 0.0);         // 0 0
    glVertex3d(x, y, z);

    glTexCoord2s(0.0, 1.0);         // 0 1
    glVertex3d(x, y, z+1);

    glTexCoord2s(1.0, 1.0);         // 1 1
    glVertex3d(x, y+1, z+1);

    glTexCoord2s(1.0, 0.0);         // 1 0
    glVertex3d(x, y+1, z);
    glEnd();
    //end of third texture

    //// RIGHT
    glBegin(GL_QUADS);
    glTexCoord2s(0.0, 0.0);         // 0 0
    glVertex3d(x+1, y, z);

    glTexCoord2s(0.0, 1.0);         // 0 1
    glVertex3d(x+1, y, z+1);

    glTexCoord2s(1.0, 1.0);         // 1 1
    glVertex3d(x+1, y+1, z+1);

    glTexCoord2s(1.0, 0.0);         // 1 0
    glVertex3d(x+1, y+1, z);
    glEnd();

    //// FRONT
    glBegin(GL_QUADS);
    glTexCoord2s(0.0, 0.0);         // 0 0
    glVertex3d(x, y+1, z);

    glTexCoord2s(0.0, 1.0);         // 0 1
    glVertex3d(x, y+1, z+1);

    glTexCoord2s(1.0, 1.0);         // 1 1
    glVertex3d(x+1, y+1, z+1);

    glTexCoord2s(1.0, 0.0);         // 1 0
    glVertex3d(x+1, y+1, z);
    glEnd();
//
//  6th, to the top
    glBegin(GL_QUADS);
    glTexCoord2s(0.0, 0.0);         // 0 0
    glVertex3d(x, y, z+1);

    glTexCoord2s(0.0, 1.0);         // 0 1
    glVertex3d(x, y+1, z+1);

    glTexCoord2s(1.0, 1.0);         // 1 1
    glVertex3d(x+1, y+1, z+1);

    glTexCoord2s(1.0, 0.0);         // 1 0
    glVertex3d(x+1, y, z+1);
    glEnd();
}

void drawTree(double positionX, double positionY, double trunkHeight, Tree tree){
    double z;

    //leaf bottom
    drawBlock(positionX-2, positionY, trunkHeight, tree.leafTexture);
    drawBlock(positionX-1, positionY+1, trunkHeight, tree.leafTexture);
    drawBlock(positionX-1, positionY, trunkHeight, tree.leafTexture);
    drawBlock(positionX-1, positionY-1, trunkHeight, tree.leafTexture);
    drawBlock(positionX, positionY+2, trunkHeight, tree.leafTexture);
    drawBlock(positionX, positionY+1, trunkHeight, tree.leafTexture);
    drawBlock(positionX, positionY-1, trunkHeight, tree.leafTexture);
    drawBlock(positionX, positionY-2, trunkHeight, tree.leafTexture);
    drawBlock(positionX+1, positionY+1, trunkHeight, tree.leafTexture);
    drawBlock(positionX+1, positionY, trunkHeight, tree.leafTexture);
    drawBlock(positionX+1, positionY-1, trunkHeight, tree.leafTexture);
    drawBlock(positionX+2, positionY, trunkHeight, tree.leafTexture);

    //leaf middle
    drawBlock(positionX-1, positionY, trunkHeight+1, tree.leafTexture);
    drawBlock(positionX, positionY+1, trunkHeight+1, tree.leafTexture);
    drawBlock(positionX, positionY, trunkHeight+1, tree.leafTexture);
    drawBlock(positionX, positionY-1, trunkHeight+1, tree.leafTexture);
    drawBlock(positionX+1, positionY, trunkHeight+1, tree.leafTexture);

    //leaf top
    drawBlock(positionX, positionY, trunkHeight+2, tree.leafTexture);


    for (z = 1.0; z <= trunkHeight; z+=1.0) {
        drawBlock(positionX, positionY, z, tree.trunkTexture);
    }
}

void drawGround(int texture) {

    double x, y, z;

        for (x = -SKYBOX_WIDHT; x < SKYBOX_WIDHT; x++) {
            for (y = -SKYBOX_WIDHT; y < SKYBOX_WIDHT; y++) {
                drawBlock(x, y, 0.0, texture);
            }
        }
}

void drawSkyboxBack(int texture) {

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);         // 0 0
    glVertex3d(-SKYBOX_WIDHT, -SKYBOX_WIDHT, GROUND_LEVEL);

    glTexCoord2f(0.0, 1.0);         // 0 1
    glVertex3d(-SKYBOX_WIDHT, -SKYBOX_WIDHT, SKYBOX_HEIGHT);

    glTexCoord2f(1.0, 1.0);         // 1 1
    glVertex3d(SKYBOX_WIDHT, -SKYBOX_WIDHT, SKYBOX_HEIGHT);

    glTexCoord2f(1.0, 0.0);         // 1 0
    glVertex3d(SKYBOX_WIDHT, -SKYBOX_WIDHT, GROUND_LEVEL);
    glEnd();
}

void drawSkyboxFront(int texture) {
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE);

    glBegin(GL_QUADS);
    glTexCoord2s(0.0, 0.0);         // 0 0
    glVertex3d(-SKYBOX_WIDHT, SKYBOX_WIDHT, GROUND_LEVEL);

    glTexCoord2s(0.0, 1.0);         // 0 1
    glVertex3d(-SKYBOX_WIDHT, SKYBOX_WIDHT, SKYBOX_HEIGHT);

    glTexCoord2s(1.0, 1.0);         // 1 1
    glVertex3d(SKYBOX_WIDHT, SKYBOX_WIDHT, SKYBOX_HEIGHT);

    glTexCoord2s(1.0, 0.0);         // 1 0
    glVertex3d(SKYBOX_WIDHT, SKYBOX_WIDHT, GROUND_LEVEL);
    glEnd();
}

void drawSkyboxLeft(int texture) {
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE);

    glBegin(GL_QUADS);
    glTexCoord2s(0.0, 0.0);         // 0 0
    glVertex3d(-SKYBOX_WIDHT, -SKYBOX_WIDHT, GROUND_LEVEL);

    glTexCoord2s(0.0, 1.0);         // 0 1
    glVertex3d(-SKYBOX_WIDHT, -SKYBOX_WIDHT, SKYBOX_HEIGHT);

    glTexCoord2s(1.0, 1.0);         // 1 1
    glVertex3d(-SKYBOX_WIDHT, SKYBOX_WIDHT, SKYBOX_HEIGHT);

    glTexCoord2s(1.0, 0.0);         // 1 0
    glVertex3d(-SKYBOX_WIDHT, SKYBOX_WIDHT, GROUND_LEVEL);
    glEnd();
}

void drawSkyboxRight(int texture) {

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE);

    //Second texture, to left
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);         // 0 0
    glVertex3d(SKYBOX_WIDHT, -SKYBOX_WIDHT, GROUND_LEVEL);

    glTexCoord2f(0.0, 1.0);         // 0 1
    glVertex3d(SKYBOX_WIDHT, -SKYBOX_WIDHT, SKYBOX_HEIGHT);

    glTexCoord2f(1.0, 1.0);         // 1 1
    glVertex3d(SKYBOX_WIDHT, SKYBOX_WIDHT, SKYBOX_HEIGHT);

    glTexCoord2f(1.0, 0.0);         // 1 0
    glVertex3d(SKYBOX_WIDHT, SKYBOX_WIDHT, GROUND_LEVEL);
    glEnd();
}

void drawSkyboxTop(int texture) {
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE);

    glBegin(GL_QUADS);
    glTexCoord2s(0.0, 0.0);         // 0 0
    glVertex3d(-SKYBOX_WIDHT, -SKYBOX_WIDHT, SKYBOX_HEIGHT);

    glTexCoord2s(0.0, 1.0);         // 0 1
    glVertex3d(-SKYBOX_WIDHT, SKYBOX_WIDHT, SKYBOX_HEIGHT);

    glTexCoord2s(1.0, 1.0);         // 1 1
    glVertex3d(SKYBOX_WIDHT, SKYBOX_WIDHT, SKYBOX_HEIGHT);

    glTexCoord2s(1.0, 0.0);         // 1 0
    glVertex3d(SKYBOX_WIDHT, -SKYBOX_WIDHT, SKYBOX_HEIGHT);
    glEnd();
}

void drawSkybox(Skybox skybox) {

    drawSkyboxBack(skybox.back);
    drawSkyboxFront(skybox.front);

    drawSkyboxLeft(skybox.left);
    drawSkyboxRight(skybox.right);

    drawSkyboxTop(skybox.top);
}
