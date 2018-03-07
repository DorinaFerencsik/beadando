#include "camera.h"
#include "draw.h"
#include "model.h"

#include "math.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>

#define VIEWPORT_RATIO (4.0 / 3.0)
#define VIEWPORT_ASPECT 50.0



double CAMERA_SPEED = 2.0;

double rotateX;
double rotateY;

int mouseX, mouseY;

double treeCords[100][3];
const int TREE_PIECE = 100;

struct Camera camera;

struct Action
{
    int moveForward;
    int moveBackward;
    int moveLeft;
    int moveRight;
    int moveUp;
    int moveDown;
    int speedUp;
};

struct Action action;
int times;

struct World world;

typedef GLubyte Pixel;

GLuint loadTexture(const char* filename) {

    GLuint textureName;
    Pixel* image;
    glGenTextures(1, &textureName);

    int width;
    int height;

    image = (Pixel*)SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGBA);

    glBindTexture(GL_TEXTURE_2D, textureName);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (Pixel*)image);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    return textureName;
}

void initializeTexture() {
    unsigned int i;
    time_t t;
    int dayTime;
    srand((unsigned) time(&t));

//    for (i=0; i<20; i++){
        dayTime = (int)(rand() % 3);
        printf("Daytime number: %f", dayTime);
//    }
//    treeCords[0][0] = (double)(rand() % dRange) - range;


    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    world.ground = loadTexture("textures/grass.png");
    world.tree.trunkTexture = loadTexture("textures/trunk.png");
    world.tree.leafTexture = loadTexture("textures/leaf.png");

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
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

//    glEnable(GL_TEXTURE_2D);
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

}

void display(){

    double elapsedTime;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    elapsedTime = calcElapsedTime();
    updateCameraPosition(&camera, elapsedTime);
    setViewPoint(&camera);

    glPushMatrix();


    drawGround(world.ground);

    int i;
    for (i = 0; i < TREE_PIECE; i++){
            drawTree(treeCords[i][0], treeCords[i][1], treeCords[i][2], world.tree);
    }

    drawSkybox(world.skybox);

    glPopMatrix();

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
    //              milyen messze legyen a kamera??
    gluPerspective(50.0, (GLdouble)width / (GLdouble)height, 0.01, 10000.0);

}

void mouseHandler(int button, int state, int x, int y) {
    mouseX = x;
    mouseY = y;
}

void motionHandler(int x, int y) { //körbe forgatás??
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
        case 9:
            action.speedUp = TRUE;
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
        case 32:
            action.moveUp = FALSE;
            break;
        case 'c':
            action.moveDown = FALSE;
            break;
        case 9:
            action.speedUp = FALSE;
            break;
    }
    glutPostRedisplay();
}

void idle() {
    glutPostRedisplay();
}

void initialize() {
    //glShadeModel(GL_FLAT);  mi ez
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE); //enable something
    glEnable(GL_AUTO_NORMAL);

    glClearColor(1.0, 1.0, 1.0, 0.0); //maybe utolsó átlátszóság? try

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);
    //init the texture
    initializeTexture();
}

void initTreeCoords(){
    int i, good, wrong;
    int range = SKYBOX_WIDHT-3;
    int dRange = 2*SKYBOX_WIDHT-6;
    time_t t;

    srand((unsigned) time(&t));

    treeCords[0][0] = (double)(rand() % dRange) - range;
    treeCords[0][1] = (double)(rand() % dRange) - range;
    treeCords[0][2] = (double)(rand() % 4) + 3;

    for( i = 1 ; i < TREE_PIECE; i++ ) {
        good = 0;
        while (good != 1) {
            wrong = 0;
            int j = 0;

            treeCords[i][0] = (double) (rand() % dRange) - range;
            treeCords[i][1] = (double) (rand() % dRange) - range;
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
        };
        treeCords[i][2] = (double) (rand() % 4) + 3;
    }
}


int main(int argc, char* argv[]) {

    initTreeCoords();

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

    glutMainLoop();

    return 0;
}