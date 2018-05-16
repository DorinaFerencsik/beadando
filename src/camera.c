#include "../includes/camera.h"
#include "../includes/draw.h"

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
//// START camera moving functions
void moveForward(struct Camera* camera, double distance) {
    double angle = degreeToRadian(camera->pose.z);
    if (camera->position.x > -SKYBOX_WIDHT+0.5 && camera->position.y > -SKYBOX_WIDHT+0.5 && camera->position.x < SKYBOX_WIDHT-0.5 && camera->position.y < SKYBOX_WIDHT-0.5) {
        camera->position.x += cos(angle) * distance;
        camera->position.y += sin(angle) * distance;
    } else {
        camera->position.x -= cos(angle) * distance;
        camera->position.y -= sin(angle) * distance;
    }

}

void moveBackward(struct Camera* camera, double distance) {
    double angle = degreeToRadian(camera->pose.z);
    if (camera->position.x > -SKYBOX_WIDHT+0.3 && camera->position.y > -SKYBOX_WIDHT+0.3 && camera->position.x < SKYBOX_WIDHT-0.3 && camera->position.y < SKYBOX_WIDHT-0.3) {
        camera->position.x -= cos(angle) * distance;
        camera->position.y -= sin(angle) * distance;
    }
}

void moveLeft(struct Camera* camera, double distance) {
    double angle = degreeToRadian(camera->pose.z + 90);
    if (camera->position.x > -SKYBOX_WIDHT+0.5 && camera->position.y > -SKYBOX_WIDHT+0.5 && camera->position.x < SKYBOX_WIDHT-0.5 && camera->position.y < SKYBOX_WIDHT-0.5) {
        camera->position.x += cos(angle) * distance;
        camera->position.y += sin(angle) * distance;
    } else {
        camera->position.x -= cos(angle) * distance;
        camera->position.y -= sin(angle) * distance;
    }
}

void moveRight(struct Camera* camera, double distance) {
    double angle = degreeToRadian(camera->pose.z - 90);
    if (camera->position.x > -SKYBOX_WIDHT+0.5 && camera->position.y > -SKYBOX_WIDHT+0.5 && camera->position.x < SKYBOX_WIDHT-0.5 && camera->position.y < SKYBOX_WIDHT-0.5) {
        camera->position.x += cos(angle) * distance;
        camera->position.y += sin(angle) * distance;
    } else {
        camera->position.x -= cos(angle) * distance;
        camera->position.y -= sin(angle) * distance;
    }
}

void moveUp(struct Camera* camera, double distance) {
    if (camera->position.z < SKYBOX_HEIGHT-1) {
        camera->position.z += distance;
    }
}

void moveDown(struct Camera* camera, double distance) {
    if(camera->position.z > 2.2) {
        camera->position.z -= distance;
    }

}
//// END camera moving functions
