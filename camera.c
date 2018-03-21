#include "camera.h"

#include <GL/glut.h>
#include <math.h>


double degreeToRadian(double degree) {
    return degree * M_PI / 180.0;
}

void initCamera(struct Camera* camera) {
    camera->position.x = 1;
    camera->position.y = -7;
    camera->position.z = 2;

    camera->pose.x = 0;
    camera->pose.y = 0;
    camera->pose.z = 0;
}

void setViewPoint(struct Camera* camera) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-(camera->pose.x + 90), 1.0, 0, 0);
    glRotatef(-(camera->pose.z - 90), 0, 0, 1.0);
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

void rotateCamera(struct Camera* camera, double horizontal, double vertical) {
    camera->pose.z += horizontal;
    camera->pose.x += vertical;

    if (camera->pose.z < 0) {
        camera->pose.z += 360.0;
    }

    if (camera->pose.z > 360.0) {
        camera->pose.z -= 360.0;
    }

    if (camera->pose.x < 0) {
        camera->pose.x += 360.0;
    }

    if (camera->pose.x > 360.0) {
        camera->pose.x -= 360.0;
    }
}

void moveForward(struct Camera* camera, double distance) {
    double angle = degreeToRadian(camera->pose.z);

    camera->position.x += cos(angle) * distance;
    camera->position.y += sin(angle) * distance;
}

//// Move the camera backward
void moveBackward(struct Camera* camera, double distance) {
    double angle = degreeToRadian(camera->pose.z);

    camera->position.x -= cos(angle) * distance;
    camera->position.y -= sin(angle) * distance;
}

//// Step the camera left
void moveLeft(struct Camera* camera, double distance) {
    double angle = degreeToRadian(camera->pose.z + 90);

    camera->position.x += cos(angle) * distance;
    camera->position.y += sin(angle) * distance;
}

//// Step the camera right
void moveRight(struct Camera* camera, double distance) {
    double angle = degreeToRadian(camera->pose.z - 90);

    camera->position.x += cos(angle) * distance;
    camera->position.y += sin(angle) * distance;
}

//// Step the camera up
void moveUp(struct Camera* camera, double distance) {
//    double angle = degreeToRadian(camera->pose.z);
    camera->position.z += distance;
}

//// Step the camera down
void moveDown(struct Camera* camera, double distance) {
//    double angle = degreeToRadian(camera->pose.z);
    camera->position.z -= distance;
}

