#include "../includes/draw.h"
#include "../includes/model.h"

#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <time.h>

//// Normal trees coords
double treeCords[200][3];

//// Normal trees piece number
const int TREE_PIECE = 200;

//// The only big tree coords
double bigTreeX = -5.0;
double bigTreeY = -5.0;
double bigTreeHeight = 10.0;
double bigTreeLeafCords[52][3];


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

//// START tree func
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

void drawBigTree(double positionX, double positionY, double trunkHeight, Tree tree, double cords[52][3]){
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
//// END tree func

//// Draw ground
void drawGround(int groundTexture, int gardenTexture) {

    double x, y, z = 0.0;

        for (x = -SKYBOX_WIDHT; x < SKYBOX_WIDHT; x++) {
            for (y = -SKYBOX_WIDHT; y < SKYBOX_WIDHT; y++) {
                if( (fabs(x) < 10 && fabs(y) < 10) ) {
                    drawBlock(x, y, z, gardenTexture);
                } else {
                    drawBlock(x, y, z, groundTexture);
                }
            }
        }
}

// Deprecated
void drawPlatform(int texture) {
    double i, j;
    for (i = -10.0; i < 10.0; i++) {
        for (j = -10.0; j < 10.0; j++) {
            drawBlock(i, j, 0.5, texture);
        }
    }
}


//// START skybox func
void drawSkyboxBack(int texture) {
    glPushMatrix();

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

    GLfloat materialAmbient[] = {0.5, 0.5, 0.5, 1};
    GLfloat materialDiffuse[] = {0, 0, 0, 1};
    GLfloat materialSpecular[] = {0, 0, 0, 1};
    GLfloat materialShininess[] = {50.0};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, materialShininess);

    drawSkyboxBack(skybox.back);
    drawSkyboxFront(skybox.front);

    drawSkyboxLeft(skybox.left);
    drawSkyboxRight(skybox.right);

    drawSkyboxTop(skybox.top);
}
//// END skybox func


//// START model func
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

void drawHouse() {
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
//// END model func


//// World
void drawWorld() {
    int i;

    drawGround(world.ground, world.garden);
    for (i = 0; i < TREE_PIECE; i++) {
        drawTree(world.tree.cords[i][0], world.tree.cords[i][1], world.tree.cords[i][2], world.tree);
    }
    drawBigTree(world.bigTree.positionX, world.bigTree.positionY, world.bigTree.height, world.tree, world.bigTree.leafCords);
    drawHouse();
    drawSkybox(world.skybox);
}

//// Initalize tree x,y,z coords
void initTreeCoords(){
    printf("Initialize normal tree coords...\n");
    int i, good, wrong;
    int range = SKYBOX_WIDHT-3;
    int doubleRange = 2*SKYBOX_WIDHT-6;
    time_t t;

    srand((unsigned) time(&t));

    world.tree.cords[0][0] = (double)(rand() % doubleRange) - range;
    world.tree.cords[0][1] = (double)(rand() % doubleRange) - range;
    world.tree.cords[0][2] = (double)(rand() % 4) + 3;

    for( i = 1 ; i < TREE_PIECE; i++ ) {
        good = 0;
        while (good != 1) {
            wrong = 0;
            int j = 0;

            world.tree.cords[i][0] = (double)(rand() % doubleRange) - range;
            world.tree.cords[i][1] = (double)(rand() % doubleRange) - range;

            if( (fabs(world.tree.cords[i][0]) >= 10 || fabs(world.tree.cords[i][1]) >= 10) ) {
                while (j < i && wrong != 1) {
                    if ((fabs(world.tree.cords[j][0] - world.tree.cords[i][0]) < 4) && (fabs(world.tree.cords[j][1] - world.tree.cords[i][1]) < 4)) {
                        wrong = 1;
                    } else {
                        j++;
                    }
                }
                if (j == i) {
                    good = 1;
                }
            }
        };
        world.tree.cords[i][2] = (double) (rand() % 4) + 3;
    }
}

void calcBigTreeLeafCords(double width, double height, int* index) {
    double x, y, yMax, yMin;
    int step = 0, i = *index;

    x = world.bigTree.positionX;
    yMax = world.bigTree.positionY+width;
    yMin = world.bigTree.positionY-width;

    for (y = yMax; y > yMin; y -= 1.0) {
        if(y > world.bigTree.positionY) {
            x++;
            step += 2;
        } else if ( y < world.bigTree.positionY ) {
            x--;
            step -= 2;
        }
        world.bigTree.leafCords[i][0] = x-1;
        world.bigTree.leafCords[i][1] = y;
        world.bigTree.leafCords[i][2] = height;

        world.bigTree.leafCords[i-1][0] = x-step;
        world.bigTree.leafCords[i-1][1] = y;
        world.bigTree.leafCords[i-1][2] = height;

        i += 2;
        *index += 2;
    }
}

void initBigTreeLeafCords() {
    printf("Initialize big tree coords...\n");
    int index = 1;
    double height = world.bigTree.height;

    //// Level 0 (bottom)
    calcBigTreeLeafCords(3.0, height, &index);

    //// Level 1
    calcBigTreeLeafCords(4.0, height+1, &index);

    //// Level 2
    calcBigTreeLeafCords(3.0, height+2, &index);

    //// Level 3
    calcBigTreeLeafCords(2.0, height+3, &index);

    //// Level 4 top
    calcBigTreeLeafCords(1.0, height+4, &index);

}

void initTreeSize() {
    world.bigTree.positionX = -5.0;
    world.bigTree.positionY = -5.0;
    world.bigTree.height = 10.0;
}

void initializeAllTreeCoords() {
    initTreeSize();

    initTreeCoords();
    initBigTreeLeafCords();
}

GLuint loadTexture(const char* filename) {
    int width;
    int height;

    GLuint textureName;
    Pixel* image;
    glGenTextures(1, &textureName);

    image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGBA);

    glBindTexture(GL_TEXTURE_2D, textureName);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return textureName;
}

void initializeTexture() {
    time_t t;
    int dayTime;
    srand((unsigned) time(&t));

    dayTime = (rand() % 3);
    printf("Daytime number: %d\n", dayTime);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    printf("Loading textures...\n");
    world.ground = loadTexture("src/textures/ground_summer.png");
    world.garden = loadTexture("src/textures/garden.png");
    world.helpMenu = loadTexture("src/textures/helpMenu.png");
    world.tree.trunkTexture = loadTexture("src/textures/trunk.png");
    world.tree.leafTexture = loadTexture("src/textures/leaf_summer.png");

    switch(dayTime) {
        case 0:
            world.skybox.back = loadTexture("src/textures/skybox/nightbox3_back.png");
            world.skybox.front = loadTexture("src/textures/skybox/nightbox3_front.png");
            world.skybox.left = loadTexture("src/textures/skybox/nightbox3_left.png");
            world.skybox.right = loadTexture("src/textures/skybox/nightbox3_right.png");
            world.skybox.top = loadTexture("src/textures/skybox/nightbox3_top.png");

            world.globalAmbient[0] = 0.3;
            world.globalAmbient[1] = 0.3;
            world.globalAmbient[2] = 0.3;
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, world.globalAmbient);
            break;
        case 1:
            world.skybox.back = loadTexture("src/textures/skybox/skybox1_back.png");
            world.skybox.front = loadTexture("src/textures/skybox/skybox1_front.png");
            world.skybox.left = loadTexture("src/textures/skybox/skybox1_left.png");
            world.skybox.right = loadTexture("src/textures/skybox/skybox1_right.png");
            world.skybox.top = loadTexture("src/textures/skybox/skybox1_top.png");

            world.globalAmbient[0] = 0.6;
            world.globalAmbient[1] = 0.6;
            world.globalAmbient[2] = 0.6;
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, world.globalAmbient);
            break;
        case 2:
            world.skybox.back = loadTexture("src/textures/skybox/skybox2_back.png");
            world.skybox.front = loadTexture("src/textures/skybox/skybox2_front.png");
            world.skybox.left = loadTexture("src/textures/skybox/skybox2_left.png");
            world.skybox.right = loadTexture("src/textures/skybox/skybox2_right.png");
            world.skybox.top = loadTexture("src/textures/skybox/skybox2_top.png");

            world.globalAmbient[0] = 1.0;
            world.globalAmbient[1] = 1.0;
            world.globalAmbient[2] = 1.0;
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, world.globalAmbient);
            break;
        default:
            world.skybox.back = loadTexture("src/textures/skybox/skybox2_back.png");
            world.skybox.front = loadTexture("src/textures/skybox/skybox2_front.png");
            world.skybox.left = loadTexture("src/textures/skybox/skybox2_left.png");
            world.skybox.right = loadTexture("src/textures/skybox/skybox2_right.png");
            world.skybox.top = loadTexture("src/textures/skybox/skybox2_top.png");
            break;
    }
    world.house.texture = loadTexture("src/textures/house.png");

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}