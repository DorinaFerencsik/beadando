#ifndef BEADANDO_CAMERA_H
#define BEADANDO_CAMERA_H

#include "model.h"

struct Camera {
    struct Vertex position;
    struct  Vertex pose;
};

//// Change degree to radian
double degreeToRadian(double degree);

//// Initialize the camera position and direction
void initCamera(struct Camera* camera);

//// Transform the models into the view point of the camera
void setViewPoint(struct Camera* camera);

//// Rotate the camera horizontally and vertically
void rotateCamera(struct Camera* camera, double horizontal, double vertical);

//// Move the camera forward
void moveForward(struct Camera* camera, double distance);

//// Move the camera backward
void moveBackward(struct Camera* camera, double distance);

//// Step the camera left
void moveLeft(struct Camera* camera, double distance);

//// Step the camera right
void moveRight(struct Camera* camera, double distance);

//// Move the camera up
void moveUp(struct Camera* camera, double distance);

//// Move the camera down
void moveDown(struct Camera* camera, double distance);

#endif //BEADANDO_CAMERA_H
