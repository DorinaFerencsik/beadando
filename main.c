#include <stdio.h>
#include "brick.h"

#include <GL/glut.h>

#include <SOIL/SOIL.h>

double rotateX;
double rotateY;

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
            "textures/box1.png",
            "textures/fox_texture.png",
            "textures/box3.png"
    };

    for (i=0; i<3;i++){
        textureNames[i] = loadTexture(textureFilenames[i], images[i]);
    }

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glEnable(GL_TEXTURE_2D);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glRotatef(rotateX, 1.0, 0, 0);
    glRotatef(rotateY, 0, 1.0, 0);

    // First texture, to top
    glBindTexture(GL_TEXTURE_2D, textureNames[2]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0,0.0);          // 0 0
        glVertex3d(0.0, 0.0, 0.0);

        glTexCoord2f(0.0, 1.0);         // 0 1
        glVertex3d(0.0,1.0,0.0);

        glTexCoord2f(1.0, 1.0);         // 1 1
        glVertex3d(1.0,1.0,0.0);

        glTexCoord2f(1.0,0.0);          // 1 0
        glVertex3d(1.0,0.0,0.0);
    glEnd();
    //end of first texture

    //Second texture, to left
    glBindTexture(GL_TEXTURE_2D, textureNames[2]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);         // 0 0
            //top-right
        glVertex3d(0.0, 0.0, 0.0);     //x, y, z ??

        glTexCoord2f(0.0, 1.0);         // 0 1
            //bottom-right
        glVertex3d(0.0, 0.0, 1.0);

        glTexCoord2f(1.0, 1.0);         // 1 1
            //bottom-left
        glVertex3d(1.0, 0.0, 1.0);

        glTexCoord2f(1.0, 0.0);         // 1 0
            //top-left
        glVertex3d(1.0, 0.0, 0.0);
    glEnd();
    //end of second texture

    //Third texture, to right
    glBindTexture(GL_TEXTURE_2D, textureNames[2]);
    glBegin(GL_QUADS);
        glTexCoord2s(0.0, 0.0);         // 0 0
        glVertex3d(0.0, 0.0, 0.0);

        glTexCoord2s(0.0, 1.0);         // 0 1
        glVertex3d(0.0, 0.0, 1.0);

        glTexCoord2s(1.0, 1.0);         // 1 1
        glVertex3d(0.0, 1.0, 1.0);

        glTexCoord2s(1.0, 0.0);         // 1 0
        glVertex3d(0.0, 1.0, 0.0);
    glEnd();
    //end of third texture

    glBindTexture(GL_TEXTURE_2D, textureNames[2]);
    glBegin(GL_QUADS);
        glTexCoord2s(0.0, 0.0);         // 0 0
        glVertex3d(1.0, 0.0, 0.0);

        glTexCoord2s(0.0, 1.0);         // 0 1
        glVertex3d(1.0, 0.0, 1.0);

        glTexCoord2s(1.0, 1.0);         // 1 1
        glVertex3d(1.0, 1.0, 1.0);

        glTexCoord2s(1.0, 0.0);         // 1 0
        glVertex3d(1.0, 1.0, 0.0);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textureNames[2]);
    glBegin(GL_QUADS);
        glTexCoord2s(0.0, 0.0);         // 0 0
        glVertex3d(0.0, 1.0, 0.0);

        glTexCoord2s(0.0, 1.0);         // 0 1
        glVertex3d(0.0, 1.0, 1.0);

        glTexCoord2s(1.0, 1.0);         // 1 1
        glVertex3d(1.0, 1.0, 1.0);

        glTexCoord2s(1.0, 0.0);         // 1 0
        glVertex3d(1.0, 1.0, 0.0);
    glEnd();


    glBindTexture(GL_TEXTURE_2D, textureNames[2]);
    glBegin(GL_QUADS);
        glTexCoord2s(0.0, 0.0);         // 0 0
        glVertex3d(0.0, 0.0, 1.0);

        glTexCoord2s(0.0, 1.0);         // 0 1
        glVertex3d(0.0, 1.0, 1.0);

        glTexCoord2s(1.0, 1.0);         // 1 1
        glVertex3d(1.0, 1.0, 1.0);

        glTexCoord2s(1.0, 0.0);         // 1 0
        glVertex3d(1.0, 0.0, 1.0);
    glEnd();

    glPopMatrix();      // ??

    glutSwapBuffers();
}


void reshape(GLsizei width, GLsizei height){
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    //              milyen messze legyen a kamera??
    gluPerspective(50.0, (GLdouble)width / (GLdouble)height, 0.01, 10.0);

}

void mouseHandler(int button, int state, int x, int y) {
//    cout << "button : " << button << endl;
//    cout << "state  : " << state << endl;
//    cout << "x      : " << x << endl;
//    cout << "y      : " << y << endl;
}

void motionHandler(int x, int y) { //körbe forgatás??
    rotateX = x;
    rotateY = y;

    glutPostRedisplay();
}

void idle() {
//    count << "idle()" << endl;
}

void initialize() {
    //glShadeModel(GL_FLAT);  mi ez
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE); //enable something
    glEnable(GL_AUTO_NORMAL);

    glClearColor(1.0, 1.0, 1.0, 0.0); //maybe utolsó átlátszóság? try

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt( //merre nézzen a kamera?
            1.0, 1.0, 2.0, // eye
            0.0, 0.0, 0.0, // look at
            0.0, 0.0, 1.0  // up
    );

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    //init the texture
    initializeTexture();
}


int main(int argc, char* argv[]) {
    Brick brick;
    double area;
    char string;

    setBrickData(&brick, 5, 10, 8);
    area = getBrickArea(&brick);

    printf("Brick area: %lf\n", area);

    rotateX = 0.0;
    rotateY = 0.0;

    glutInit(&argc, argv);

    glutInitWindowSize(640, 480);// set window size I guess

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    int window = glutCreateWindow("GLUT Window");
    glutSetWindow(window);

    initialize();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseHandler);
    glutMotionFunc(motionHandler);
    glutIdleFunc(idle);

    glutMainLoop();


    //printf("...");
    //scanf("%c", &string);
    return 0;
}