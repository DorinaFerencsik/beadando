#include "camera.h"
#include "draw.h"

#include <GL/glut.h>
#include <SOIL/SOIL.h>

#define VIEWPORT_RATIO (4.0 / 3.0)
#define VIEWPORT_ASPECT 50.0

#define CAMERA_SPEED 2.0

double rotateX;
double rotateY;

int mouseX, mouseY;

struct Camera camera;

struct Action
{
    int moveForward;
    int moveBackward;
    int moveLeft;
    int moveRight;
    int moveUp;
    int moveDown;
};

struct Action action;
int time;

double calcElapsedTime(){
    int currentTime;
    double elapsedTime;

    currentTime = glutGet(GLUT_ELAPSED_TIME);
    elapsedTime = (double)(currentTime - time) / 1000.0;
    time = currentTime;

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
}

void display(){

    double elapsedTime;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    elapsedTime = calcElapsedTime();
    updateCameraPosition(&camera, elapsedTime);
    setViewPoint(&camera);

    glPushMatrix();

    drawGround();
    drawTree(3.0, 3.0, 4.0);
    drawTree(0.0, 0.0, 3.0);

    glPopMatrix();      // ??

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
        case 'e':
            action.moveUp = TRUE;
            break;
        case 'q':
            action.moveDown = TRUE;
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
        case 'e':
            action.moveUp = FALSE;
            break;
        case 'q':
            action.moveDown = FALSE;
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

    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);
    //init the texture
    initializeTexture();
}


int main(int argc, char* argv[]) {

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

    glutMainLoop();

    return 0;
}