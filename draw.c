#include "draw.h"

#include <GL/glut.h>
#include <SOIL/SOIL.h>

typedef GLubyte Pixel[3];

Pixel* images[3];
GLuint textureNames[3];

GLuint loadTexture(char* filename, Pixel* image) {
    GLuint textureName;
    int width;
    int height;

    glGenTextures(1, &textureName);

    image = (Pixel*)SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);

    glBindTexture(GL_TEXTURE_2D, textureName);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, (Pixel*)image);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    /*
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    */

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    return textureName;
}

void initializeTexture() {
    unsigned int i;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    char textureFilenames[][32] = {
            "textures/grass.png",
            "textures/trunk.png",
            "textures/leaf.png"
    };

    for (i=0; i<3;i++){
        textureNames[i] = loadTexture(textureFilenames[i], images[i]);
    }

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glEnable(GL_TEXTURE_2D);
}

void drawBlock(double x, double y, double z, int texture) {
    glBindTexture(GL_TEXTURE_2D, textureNames[texture]);

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

    //Second texture, to left
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

    //Third texture, to right
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

void drawTree(double positionX, double positionY, double trunkHeight){
    double z;
    for (z = 1.0; z <= trunkHeight; z+=1.0) {
        drawBlock(positionX, positionX, z, 1);
    }

    //leaf bottom
    drawBlock(positionX-2, positionY, z, 2);
    drawBlock(positionX-1, positionY+1, z, 2);
    drawBlock(positionX-1, positionY, z, 2);
    drawBlock(positionX-1, positionY-1, z, 2);
    drawBlock(positionX, positionY+2, z, 2);
    drawBlock(positionX, positionY+1, z, 2);
    drawBlock(positionX, positionY-1, z, 2);
    drawBlock(positionX, positionY-2, z, 2);
    drawBlock(positionX+1, positionY+1, z, 2);
    drawBlock(positionX+1, positionY, z, 2);
    drawBlock(positionX+1, positionY-1, z, 2);
    drawBlock(positionX+2, positionY, z, 2);


    //leaf middle
    drawBlock(positionX-1, positionY, z+1, 2);
    drawBlock(positionX, positionY+1, z+1, 2);
    drawBlock(positionX, positionY, z+1, 2);
    drawBlock(positionX, positionY-1, z+1, 2);
    drawBlock(positionX+1, positionY, z+1, 2);

    //leaf top
    drawBlock(positionX, positionY, z+2, 2);

}

void drawGround() {
    glBindTexture(GL_TEXTURE_2D, textureNames[0]);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    double x, y;

    for (x=-5.0; x<5.0; x += 1.0){
        for (y=-5.0; y<5.0; y += 1.0){
            drawBlock(x, y, 0.0, 0);
        }
    }
}