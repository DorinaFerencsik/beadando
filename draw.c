#include "draw.h"

#include <GL/glut.h>
#include <SOIL/SOIL.h>

void drawBlock(double x, double y, double z, int texture) {

    glPushMatrix();

    GLfloat materialAmbient[] = {0.5, 0.5, 0.5, 1};
    GLfloat materialDiffuse[] = {0.7, 0.7, 0.7, 1};
    GLfloat materialSpecular[] = {1, 1, 1, 1};
    GLfloat materialShininess[] = {50.0};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, materialShininess);

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

    //// TOP
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

    glPopMatrix();
}

//// Start tree func
void drawTree(double positionX, double positionY, double trunkHeight, Tree tree){
    double z;

    //// leaf bottom
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

    //// leaf middle
    drawBlock(positionX-1, positionY, trunkHeight+1, tree.leafTexture);
    drawBlock(positionX, positionY+1, trunkHeight+1, tree.leafTexture);
    drawBlock(positionX, positionY, trunkHeight+1, tree.leafTexture);
    drawBlock(positionX, positionY-1, trunkHeight+1, tree.leafTexture);
    drawBlock(positionX+1, positionY, trunkHeight+1, tree.leafTexture);

    //// leaf top
    drawBlock(positionX, positionY, trunkHeight+2, tree.leafTexture);

    //// trunk
    for (z = 1.0; z <= trunkHeight; z+=1.0) {
        drawBlock(positionX, positionY, z, tree.trunkTexture);
    }
}

void drawBigTree(double positionX, double positionY, double trunkHeight, Tree tree, double cords[40][3]){
    double z;
    int i;

    //// leaf
    for (i = 0; i < 52; i++) {
        drawBlock(cords[i][0], cords[i][1], cords[i][2], tree.leafTexture);
    }

    //// trunk
    for (z = 1.0; z <= trunkHeight; z+=1.0) {
        drawBlock(positionX, positionY, z, tree.trunkTexture);
        drawBlock(positionX, positionY+1, z, tree.trunkTexture);
        drawBlock(positionX-1, positionY, z, tree.trunkTexture);
        drawBlock(positionX-1, positionY+1, z, tree.trunkTexture);
    }
    drawBlock(positionX-2, positionY, trunkHeight, tree.trunkTexture);
    drawBlock(positionX-2, positionY+1, trunkHeight, tree.trunkTexture);
    drawBlock(positionX-1, positionX+2, trunkHeight, tree.trunkTexture);
    drawBlock(positionX, positionY+2, trunkHeight, tree.trunkTexture);
    drawBlock(positionX+1, positionY+1, trunkHeight, tree.trunkTexture);
    drawBlock(positionX+1, positionY, trunkHeight, tree.trunkTexture);
    drawBlock(positionX, positionY-1, trunkHeight, tree.trunkTexture);
    drawBlock(positionX-1, positionY-1, trunkHeight, tree.trunkTexture);
}
//// End tree func

//// Draw ground
void drawGround(int groundTexture, int gardenTexture) {

    double x, y, z;

        for (x = -SKYBOX_WIDHT; x < SKYBOX_WIDHT; x++) {
            for (y = -SKYBOX_WIDHT; y < SKYBOX_WIDHT; y++) {
                if( (fabs(x) <10 && fabs(y) < 10) ) {
                    drawBlock(x, y, 0.0, gardenTexture);
                } else {
                    drawBlock(x, y, 0.0, groundTexture);
                }
//                drawBlock(x, y, 0.0, texture);
            }
        }
}

void drawPlatform(int texture) {
    double i, j;
    for (i = -10.0; i < 10.0; i++) {
        for (j = -10.0; j < 10.0; j++) {
            drawBlock(i, j, 0.5, texture);
        }
    }
}


//// Start skybox func
void drawSkyboxBack(int texture) {
    glPushMatrix();

    GLfloat materialAmbient[] = {0.5, 0.5, 0.5, 1};
    GLfloat materialDiffuse[] = {0.7, 0.7, 0.7, 1};
    GLfloat materialSpecular[] = {1, 1, 1, 1};
    GLfloat materialShininess[] = {50.0};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, materialShininess);

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

    glPopMatrix();
}

void drawSkyboxFront(int texture) {
    glPushMatrix();

    GLfloat materialAmbient[] = {0.5, 0.5, 0.5, 1};
    GLfloat materialDiffuse[] = {0.7, 0.7, 0.7, 1};
    GLfloat materialSpecular[] = {1, 1, 1, 1};
    GLfloat materialShininess[] = {50.0};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, materialShininess);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE);

    glBegin(GL_QUADS);
    glTexCoord2s(0.0, 0.0);         // 0 0
    glVertex3d(-SKYBOX_WIDHT, SKYBOX_WIDHT, GROUND_LEVEL-1);

    glTexCoord2s(0.0, 1.0);         // 0 1
    glVertex3d(-SKYBOX_WIDHT, SKYBOX_WIDHT, SKYBOX_HEIGHT);

    glTexCoord2s(1.0, 1.0);         // 1 1
    glVertex3d(SKYBOX_WIDHT, SKYBOX_WIDHT, SKYBOX_HEIGHT);

    glTexCoord2s(1.0, 0.0);         // 1 0
    glVertex3d(SKYBOX_WIDHT, SKYBOX_WIDHT, GROUND_LEVEL-1);
    glEnd();

    glPopMatrix();
}

void drawSkyboxLeft(int texture) {
    glPushMatrix();

    GLfloat materialAmbient[] = {0.5, 0.5, 0.5, 1};
    GLfloat materialDiffuse[] = {0.7, 0.7, 0.7, 1};
    GLfloat materialSpecular[] = {1, 1, 1, 1};
    GLfloat materialShininess[] = {50.0};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, materialShininess);

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

    glPopMatrix();
}

void drawSkyboxRight(int texture) {
    glPushMatrix();

    GLfloat materialAmbient[] = {0.5, 0.5, 0.5, 1};
    GLfloat materialDiffuse[] = {0.7, 0.7, 0.7, 1};
    GLfloat materialSpecular[] = {1, 1, 1, 1};
    GLfloat materialShininess[] = {50.0};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, materialShininess);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE);

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

    glPopMatrix();
}

void drawSkyboxTop(int texture) {
    glPushMatrix();

    GLfloat materialAmbient[] = {0.5, 0.5, 0.5, 1};
    GLfloat materialDiffuse[] = {0.7, 0.7, 0.7, 1};
    GLfloat materialSpecular[] = {1, 1, 1, 1};
    GLfloat materialShininess[] = {50.0};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, materialShininess);

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

    glPopMatrix();
}

void drawSkybox(Skybox skybox) {

    drawSkyboxBack(skybox.back);
    drawSkyboxFront(skybox.front);

    drawSkyboxLeft(skybox.left);
    drawSkyboxRight(skybox.right);

    drawSkyboxTop(skybox.top);
}
//// End skybox func


//// Start model func
void drawTriangles(const struct Model* model) {
    int i, k;
    int vertexIndex, textureIndex;
    double x, y, z, u, v;

    glBegin(GL_TRIANGLES);

    for (i = 0; i < model->nTriangles; i++) {
        for (k = 0; k < 3; k++) {

            textureIndex = model->triangles[i].points[k].textureIndex;
            u = model->textureVertices[textureIndex].u;
            v = model->textureVertices[textureIndex].v;
            // NOTE: The 1-v is model file specific!
            glTexCoord2f(u, 1-v);

            vertexIndex = model->triangles[i].points[k].vertexIndex;
            x = model->vertices[vertexIndex].x;
            y = model->vertices[vertexIndex].y;
            z = model->vertices[vertexIndex].z;
            glVertex3d(x, y, z);
        }
    }

    glEnd();
}

void drawQuads(const struct Model* model) {
    int i, k;
    int vertexIndex, textureIndex;
    double x, y, z, u, v;

    glBegin(GL_QUADS);

    for (i = 0; i < model->nQuads; i++) {
        for (k = 0; k < 4; k++) {

            textureIndex = model->quads[i].points[k].textureIndex;
            u = model->textureVertices[textureIndex].u;
            v = model->textureVertices[textureIndex].v;
            // NOTE: The 1-v is model file specific!
            glTexCoord2f(u, 1-v);

            vertexIndex = model->quads[i].points[k].vertexIndex;
            x = model->vertices[vertexIndex].x;
            y = model->vertices[vertexIndex].y;
            z = model->vertices[vertexIndex].z;
            glVertex3d(x, y, z);
        }
    }

    glEnd();
}

void drawModel(const struct Model* model) {
    drawTriangles(model);
    drawQuads(model);
}

void drawHouse(World world) {
//    glScalef(16, 16, 16);
    glPushMatrix();

    GLfloat materialAmbient[] = {0.5, 0.5, 0.5, 1};
    GLfloat materialDiffuse[] = {0.7, 0.7, 0.7, 1};
    GLfloat materialSpecular[] = {1, 1, 1, 1};
    GLfloat materialShininess[] = {50.0};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, materialShininess);

    glBindTexture(GL_TEXTURE_2D, world.house.texture);
    drawModel(&world.house.model);

    glPopMatrix();
}
//// End model func