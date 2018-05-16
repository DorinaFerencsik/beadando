#include "../includes/camera.h"
#include "../includes/draw.h"
#include "../includes/model.h"

#include "math.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <time.h>

#define VIEWPORT_RATIO (4.0 / 3.0)

double CAMERA_SPEED = 2.0;

int WINDOW_WIDTH;
int WINDOW_HEIGHT;
int mouseX, mouseY;

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
    int helpOpen;
};

struct Action action;
int times;


//// START key and mouse handler functions
void updateCameraPosition(struct Camera* camera, double elapsedTime){
    double distance;

    distance = elapsedTime * CAMERA_SPEED;

    if (action.moveForward) {
        moveForward(camera, distance);
    }

    if (action.moveBackward) {
        moveBackward(camera, distance);
    }

    if (action.moveLeft) {
        moveLeft(camera, distance);
    }

    if (action.moveRight) {
       moveRight(camera, distance);
    }

    if(action.moveUp) {
        moveUp(camera, distance);
    }

    if (action.moveDown) {
        moveDown(camera, distance);
    }

    if(action.speedUp) {
        CAMERA_SPEED = 6.0;
    } else {
        CAMERA_SPEED = 2.0;
    }

    if (action.lightOn && action.increaseLight) {
        if (action.lightOn && world.globalAmbient[0] < 1) {
            world.globalAmbient[0] = world.globalAmbient[1] = world.globalAmbient[2] += 0.05;
        }
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, world.globalAmbient);
    }

    if (action.lightOn && action.decreaseLight) {
        if (world.globalAmbient[0] > 0) {
            world.globalAmbient[0] = world.globalAmbient[1] = world.globalAmbient[2] -= 0.05;
        }
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, world.globalAmbient);
    }

    if (action.lightOn) {
        glEnable(GL_LIGHT0);
    } else {
        glDisable(GL_LIGHT0);
    }
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
    printf("Camera position: x=%lf, y=%lf, z=%lf\n", camera.position.x, camera.position.y, camera.position.z);
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
        case 'l':
            if (action.lightOn == FALSE) {
                action.lightOn = TRUE;
            } else {
                action.lightOn = FALSE;
            }
            break;
        case 27:        // ESC
            exit(0);
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

void specialFunc(int key, int x, int y) {
    printf("spec funct;\n");
    switch (key) {
        case GLUT_KEY_F1:
            if (action.helpOpen) {
                action.helpOpen = FALSE;

                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, world.materialAmbient);
                glLightModelfv(GL_LIGHT_MODEL_AMBIENT, world.globalAmbient);
            } else {
                action.helpOpen = TRUE;

                GLfloat ones[] = {1, 1, 1, 1};
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ones);
                glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ones);
            }
            break;
    }
}
//// END key and mouse handler functions

void drawHelpMenu() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, world.helpMenu);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(0, 0, 0);

    glTexCoord2f(1, 0);
    glVertex3f(WINDOW_WIDTH, 0, 0);

    glTexCoord2f(1, 1);
    glVertex3f(WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    glTexCoord2f(0, 1);
    glVertex3f(0, WINDOW_HEIGHT, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    reshape(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutSwapBuffers();
}

double calcElapsedTime(){
    int currentTime;
    double elapsedTime;

    currentTime = glutGet(GLUT_ELAPSED_TIME);
    elapsedTime = (double)(currentTime - times) / 1000.0;
    times = currentTime;

    return elapsedTime;
}

void display(){
    if (action.helpOpen == FALSE) {
        double elapsedTime;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        GLfloat lightPosition[] = {0.0, 0.0, 10.0, 1};
        GLfloat lightAmbient[] = {1, 1, 1, 1};
        GLfloat lightDiffuse[] = {1, 1, 1, 1};
        GLfloat lightSpecular[] = {1, 1, 1, 1};

        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
        glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

        glEnable(GL_LIGHT0);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_NORMALIZE);
        glEnable(GL_DEPTH_TEST);

        elapsedTime = calcElapsedTime();
        updateCameraPosition(&camera, elapsedTime);
        setViewPoint(&camera);

        reshape(WINDOW_WIDTH, WINDOW_HEIGHT);

        drawWorld();

        glutSwapBuffers();
    } else {
        drawHelpMenu();
    }
    glFlush();
}

void reshape(GLsizei width, GLsizei height){
    int x, y, w, h;
    double ratio;

    WINDOW_WIDTH = width;
    WINDOW_HEIGHT = height;

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

    if (action.helpOpen == FALSE) {
        gluPerspective(50.0, (GLdouble)width / (GLdouble)height, 0.01, 10000.0);
    } else {
        gluOrtho2D(0, width, height, 0);
    }

}

void idle() {
    glutPostRedisplay();
}

//// START light functions
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
    GLfloat lightPosition[] = {0.0, 0.0, 200.0, 1.0};
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
//// END light functions

//// Init actions
void initActions() {
    action.moveForward = FALSE;
    action.moveBackward = FALSE;
    action.moveLeft = FALSE;
    action.moveRight = FALSE;
    action.moveUp = FALSE;
    action.moveDown = FALSE;
    action.speedUp = FALSE;
    action.lightOn = TRUE;
    action.helpOpen = FALSE;
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

    initializeAllTreeCoords();

    loadModel("src/models/house.obj", &world.house.model);
    // TODO x, y, z scales
    scaleModel(&world.house.model, 13.0, -5.0, 19.248);
    printBoundingBox(&world.house.model);

    initCamera(&camera);

    initActions();

}

int main(int argc, char* argv[]) {

    glutInit(&argc, argv);

    glutInitWindowSize(1024, 568);
    glutInitWindowPosition(100, 50);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    int window = glutCreateWindow("Roam in the forest");
    glutSetWindow(window);

    initialize();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyHandler);
    glutKeyboardUpFunc(keyUpHandler);
    glutMouseFunc(mouseHandler);
    glutMotionFunc(motionHandler);
    glutIdleFunc(idle);
    glutSpecialFunc(specialFunc);

    glutMainLoop();

    return 0;
}