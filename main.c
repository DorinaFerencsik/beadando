#include "camera.h"
#include "draw.h"
#include "model.h"

#include "math.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <time.h>

#define VIEWPORT_RATIO (4.0 / 3.0)

double CAMERA_SPEED = 2.0;

int mouseX, mouseY;

double treeCords[100][3];
const int TREE_PIECE = 100;

double bigTreeX = -5.0;
double bigTreeY = -5.0;
double bigTreeHeight = 10.0;
double bigTreeLeafCords[52][3];

struct Camera camera;

struct Action {
    int moveForward;
    int moveBackward;
    int moveLeft;
    int moveRight;
    int moveUp;
    int moveDown;
    int speedUp;
    int increaseLight;
    int decreaseLight;
    int lightOn;
};

struct Action action;
int times;

World world;

typedef GLubyte Pixel;

GLuint loadTexture(const char* filename) {

    GLuint textureName;
    Pixel* image;
    glGenTextures(1, &textureName);

    int width;
    int height;


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

    world.cube = loadTexture("textures/cube.png");
    world.ground = loadTexture("textures/ground_summer.png");
    world.garden = loadTexture("textures/garden.png");
    world.tree.trunkTexture = loadTexture("textures/trunk.png");
    world.tree.leafTexture = loadTexture("textures/leaf_summer.png");

    switch(dayTime) {
        case 0:
            world.skybox.back = loadTexture("textures/skybox/nightbox3_back.png");
            world.skybox.front = loadTexture("textures/skybox/nightbox3_front.png");
            world.skybox.left = loadTexture("textures/skybox/nightbox3_left.png");
            world.skybox.right = loadTexture("textures/skybox/nightbox3_right.png");
            world.skybox.top = loadTexture("textures/skybox/nightbox3_top.png");
            break;
        case 1:
            world.skybox.back = loadTexture("textures/skybox/skybox1_back.png");
            world.skybox.front = loadTexture("textures/skybox/skybox1_front.png");
            world.skybox.left = loadTexture("textures/skybox/skybox1_left.png");
            world.skybox.right = loadTexture("textures/skybox/skybox1_right.png");
            world.skybox.top = loadTexture("textures/skybox/skybox1_top.png");
            break;
        case 2:
            world.skybox.back = loadTexture("textures/skybox/skybox2_back.png");
            world.skybox.front = loadTexture("textures/skybox/skybox2_front.png");
            world.skybox.left = loadTexture("textures/skybox/skybox2_left.png");
            world.skybox.right = loadTexture("textures/skybox/skybox2_right.png");
            world.skybox.top = loadTexture("textures/skybox/skybox2_top.png");
            break;
        default:
            world.skybox.back = loadTexture("textures/skybox/skybox2_back.png");
            world.skybox.front = loadTexture("textures/skybox/skybox2_front.png");
            world.skybox.left = loadTexture("textures/skybox/skybox2_left.png");
            world.skybox.right = loadTexture("textures/skybox/skybox2_right.png");
            world.skybox.top = loadTexture("textures/skybox/skybox2_top.png");
            break;
    }
    world.house.texture = loadTexture("textures/house.png");

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}

double calcElapsedTime(){
    int currentTime;
    double elapsedTime;

    currentTime = glutGet(GLUT_ELAPSED_TIME);
    elapsedTime = (double)(currentTime - times) / 1000.0;
    times = currentTime;

    return elapsedTime;
}

void updateCameraPosition(struct Camera* camera, double elapsedTime){
    double distance;

    distance = elapsedTime * CAMERA_SPEED;

    if (action.moveForward == TRUE) {
        moveForward(camera, distance);
    }

    if (action.moveBackward == TRUE) {
        moveBackward(camera, distance);
    }

    if (action.moveLeft == TRUE) {
        moveLeft(camera, distance);
    }

    if (action.moveRight == TRUE) {
       moveRight(camera, distance);
    }

    if(action.moveUp == TRUE) {
        moveUp(camera, distance);
    }

    if (action.moveDown == TRUE) {
        moveDown(camera, distance);
    }

    if(action.speedUp == TRUE) {
        CAMERA_SPEED = 6.0;
    } else {
        CAMERA_SPEED = 2.0;
    }

    if (action.increaseLight == TRUE) {
        if (world.globalAmbient[0] < 1) {
            world.globalAmbient[0] = world.globalAmbient[1] = world.globalAmbient[2] += 0.1;
        }
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, world.globalAmbient);
    }

    if (action.decreaseLight == TRUE) {
        if (world.globalAmbient[0] > 0) {
            world.globalAmbient[0] = world.globalAmbient[1] = world.globalAmbient[2] -= 0.1;
        }
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, world.globalAmbient);
    }

    if (action.lightOn) {
        glEnable(GL_LIGHT2);
    } else {
        glDisable(GL_LIGHT2);
    }
}

void display(){
    double elapsedTime;
    int i;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLfloat lightPosition[] = {0.0, 0.0, 100.0, 1};
    GLfloat lightAmbient[] = {1, 1, 1, 0};
    GLfloat lightDiffuse[] = {1, 1, 1, 0};
    GLfloat lightSpecular[] = {1, 1, 1, 0};

    glLightfv(GL_LIGHT2, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT2, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, lightSpecular);

    glEnable(GL_LIGHT2);

    elapsedTime = calcElapsedTime();
    updateCameraPosition(&camera, elapsedTime);
    setViewPoint(&camera);

    drawGround(world.ground, world.garden);
    for (i = 0; i < TREE_PIECE; i++) {
        drawTree(treeCords[i][0], treeCords[i][1], treeCords[i][2], world.tree);
    }
    drawBigTree(bigTreeX, bigTreeY, bigTreeHeight, world.tree, bigTreeLeafCords);
    drawHouse(world);
    drawSkybox(world.skybox);

    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height){

    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(50.0, (GLdouble)width / (GLdouble)height, 0.01, 10000.0);

}

void mouseHandler(int button, int state, int x, int y) {
    mouseX = x;
    mouseY = y;
}

void motionHandler(int x, int y) {
    double horizontal, vertical;

    horizontal = mouseX - x;
    vertical = mouseY - y;

    rotateCamera(&camera, horizontal, vertical);

    mouseX = x;
    mouseY = y;

    glutPostRedisplay();
}

void keyHandler(unsigned char key, int x, int y) {
    switch (key){
        case 'w':
            action.moveForward = TRUE;
            break;
        case 's':
            action.moveBackward = TRUE;
            break;
        case 'a':
            action.moveLeft = TRUE;
            break;
        case 'd':
            action.moveRight = TRUE;
            break;
        case 32:        // SPACE
            action.moveUp = TRUE;
            break;
        case 'c':
            action.moveDown = TRUE;
            break;
        case 9:         // TAB
            action.speedUp = TRUE;
            break;
        case '+':
            action.increaseLight = TRUE;
            break;
        case '-':
            action.decreaseLight = TRUE;
            break;
        case 'f':
            if (action.lightOn == FALSE) {
                action.lightOn = TRUE;
            } else {
                action.lightOn = FALSE;
            }
            break;
    }
    glutPostRedisplay();
}

void keyUpHandler(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            action.moveForward = FALSE;
            break;
        case 's':
            action.moveBackward = FALSE;
            break;
        case 'a':
            action.moveLeft = FALSE;
            break;
        case 'd':
            action.moveRight = FALSE;
            break;
        case 32:        // SPACE
            action.moveUp = FALSE;
            break;
        case 'c':
            action.moveDown = FALSE;
            break;
        case 9:         // TAB
            action.speedUp = FALSE;
            break;
        case '+':
            action.increaseLight = FALSE;
            break;
        case '-':
            action.decreaseLight = FALSE;
            break;
    }
    glutPostRedisplay();
}

void idle() {
    glutPostRedisplay();
}

void setLights(World* world) {
    world->globalAmbient[0] = 0.7;
    world->globalAmbient[1] = 0.7;
    world->globalAmbient[2] = 0.7;
    world->globalAmbient[3] = 1.0;

    world->materialAmbient[0] = 0.7;
    world->materialAmbient[1] = 0.7;
    world->materialAmbient[2] = 0.7;
    world->materialAmbient[3] = 1.0;

    world->diffuseLightEmission[0] = 0.7;
    world->diffuseLightEmission[1] = 0.7;
    world->diffuseLightEmission[2] = 0.7;
    world->diffuseLightEmission[3] = 1;
}

void initDiffuseLight() {
    GLfloat lightPosition[] = {100.0, 100.0, 100.0, 1.0};
    GLfloat lightAmbient[] = {0.1, 0.1, 0.1, 1};
    GLfloat lightDiffuse[] = {0.5, 0.5, 0, 1};
    GLfloat lightSpecular[] = {1, 1, 1, 1};

    glLightfv(GL_LIGHT5, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT5, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT5, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT5, GL_SPECULAR, lightSpecular);
}

void initLighting() {
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, world.globalAmbient);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    initDiffuseLight();
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
}

void initMaterial() {
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, world.materialAmbient);
}

void initialize() {

    glClearColor(0.0, 0.0, 0.0, 0.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearDepth(1.0);

    setLights(&world);

    initLighting();
    initMaterial();

    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_TEXTURE_2D);

    initializeTexture();
}

void initTreeCords(){
    int i, good, wrong;
    int range = SKYBOX_WIDHT-3;
    int doubleRange = 2*SKYBOX_WIDHT-6;
    time_t t;

    srand((unsigned) time(&t));

    treeCords[0][0] = (double)(rand() % doubleRange) - range;
    treeCords[0][1] = (double)(rand() % doubleRange) - range;
    treeCords[0][2] = (double)(rand() % 4) + 3;

    for( i = 1 ; i < TREE_PIECE; i++ ) {
        good = 0;
        while (good != 1) {
            wrong = 0;
            int j = 0;

            treeCords[i][0] = (double) (rand() % doubleRange) - range;
            treeCords[i][1] = (double) (rand() % doubleRange) - range;
            if( (fabs(treeCords[i][0]) <10 && fabs(treeCords[i][1]) < 10) ) {
            } else {
                while (j < i && wrong != 1) {
                    if ((fabs(treeCords[j][0] - treeCords[i][0]) < 4) && (fabs(treeCords[j][1] - treeCords[i][1]) < 4)) {
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
        treeCords[i][2] = (double) (rand() % 4) + 3;
    }
}

void calcBigLeafCords(double posX, double posY, double width, double height, int* index) {
    double x, y, yMax, yMin;
    int step = 0, i = *index;

    x = posX;
    yMax = posY+width;
    yMin = posY-width;

    for (y = yMax; y > yMin; y -= 1.0) {
        if(y > posY) {
            x++;
            step += 2;
        } else if ( y < posY ) {
            x--;
            step -= 2;
        }

        bigTreeLeafCords[i][0] = x-1;
        bigTreeLeafCords[i][1] = y;
        bigTreeLeafCords[i][2] = height;

        bigTreeLeafCords[i-1][0] = x-step;
        bigTreeLeafCords[i-1][1] = y;
        bigTreeLeafCords[i-1][2] = height;

        i += 2;
        *index += 2;
    }
}

void initBigTreeLeafCords() {
    int index = 1;

    //// Level 0 (bottom)
    calcBigLeafCords(bigTreeX, bigTreeY, 3.0, bigTreeHeight, &index);

    //// Level 1
    calcBigLeafCords(bigTreeX, bigTreeY, 4.0, bigTreeHeight+1, &index);

    //// Level 2
    calcBigLeafCords(bigTreeX, bigTreeY, 3.0, bigTreeHeight+2, &index);

    //// Level 3
    calcBigLeafCords(bigTreeX, bigTreeY, 2.0, bigTreeHeight+3, &index);

    //// Level 4 top
    calcBigLeafCords(bigTreeX, bigTreeY, 1.0, bigTreeHeight+4, &index);

}


int main(int argc, char* argv[]) {

    initTreeCords();
    initBigTreeLeafCords();

    loadModel("models/house.obj", &world.house.model);
    // TODO x, y, z scales
    scaleModel(&world.house.model, 13.0, -5.0, 19.248);
    printBoundingBox(&world.house.model);

    glutInit(&argc, argv);

    glutInitWindowSize(640, 480);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    int window = glutCreateWindow("GLUT Window");
    glutSetWindow(window);

    initialize();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyHandler);
    glutKeyboardUpFunc(keyUpHandler);
    glutMouseFunc(mouseHandler);
    glutMotionFunc(motionHandler);
    glutIdleFunc(idle);

    initCamera(&camera);

    action.moveForward = FALSE;
    action.moveBackward = FALSE;
    action.moveLeft = FALSE;
    action.moveRight = FALSE;
    action.moveUp = FALSE;
    action.moveDown = FALSE;
    action.speedUp = FALSE;
    action.lightOn = FALSE;

    glutMainLoop();

    return 0;
}