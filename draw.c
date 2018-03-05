#include "draw.h"

#include <GL/glut.h>
#include <SOIL/SOIL.h>

//typedef GLubyte Pixel[3];

//struct World {
//    int ground;
//    int tree;
//} World;



//void initializeTexture(struct World world) {
//    unsigned int i;
//    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//
////    char textureFilenames[][32] = {
////            "textures/grass.png",
////            "textures/trunk.png",
////            "textures/leaf.png"
////    };
////
////    for (i=0; i<3;i++){
////        textureNames[i] = loadTexture(textureFilenames[i], images[i]);
////    }
//    printf("its initTexture..");
//    world->ground = loadTexture("textures/grass.png");
//    world->tree.trunkTexture = loadTexture("textures/trunk.png");
//    world->tree.leafTexture = loadTexture("textures/leaf.png");
//
////    printf("World.grount %d", &world->ground);
//    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
//
//    glEnable(GL_TEXTURE_2D);
//}

void drawBlock(double x, double y, double z, int texture) {
//    printf("Its drawBlock");

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE);

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
//    printf("Its drawGround");
//    glBindTexture(GL_TEXTURE_2D, texture);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    double x, y;

    for (x=-50.0; x<50.0; x += 1.0){
        for (y=-50.0; y<50.0; y += 1.0){
            drawBlock(x, y, 0.0, texture);
        }
    }
}

void drawSkybox(int texture) {
    double theta, phi1, phi2;
    double x1, y1, z1;
    double x2, y2, z2;
    double u, v1, v2;

    int n_slices, n_stacks;
    double radius;
    int i, k;

    n_slices = 12;
    n_stacks = 6;
    radius = 50;

    glPushMatrix();

    glScaled(radius, radius, radius);

    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_TRIANGLE_STRIP);

    for (i = 0; i < n_stacks; ++i) {
        v1 = (double)i / n_stacks;
        v2 = (double)(i + 1) / n_stacks;
        phi1 = v1 * M_PI / 2.0;
        phi2 = v2 * M_PI / 2.0;
        for (k = 0; k <= n_slices; ++k) {
            u = (double)k / n_slices;
            theta = u * 2.0 * M_PI;
            x1 = cos(theta) * cos(phi1);
            y1 = sin(theta) * cos(phi1);
            z1 = sin(phi1);
            x2 = cos(theta) * cos(phi2);
            y2 = sin(theta) * cos(phi2);
            z2 = sin(phi2);
            glTexCoord2d(u, 1.0 - v1);
            glVertex3d(x1, y1, z1);
            glTexCoord2d(u, 1.0 - v2);
            glVertex3d(x2, y2, z2);
        }
    }

    glEnd();

    glPopMatrix();
}
