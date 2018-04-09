#ifndef BEADANDO_MODEL_H
#define BEADANDO_MODEL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define INVALID_VERTEX_INDEX 0

struct TokenArray {
    char** tokens;
    int nTokens;
};

struct Vertex {
    double x;
    double y;
    double z;
};

struct TextureVertex {
    double u;
    double v;
};

struct FacePoint {
    int vertexIndex;
    int textureIndex;
    int normalIndex;
};

struct Triangle {
    struct FacePoint points[3];
};

struct Quad {
    struct FacePoint points[4];
};

typedef struct Model {
    int nVertices;
    int nTextureVertices;
    int nNormals;
    int nTriangles;
    int nQuads;
    struct Vertex* vertices;
    struct TextureVertex* textureVertices;
    struct Vertex* normals;
    struct Triangle* triangles;
    struct Quad* quads;
} Model;

typedef struct {
    int back, front, left, right, top;
} Skybox;

typedef struct {
    int leafTexture, trunkTexture;
} Tree;

typedef struct {
    Model model;
    int texture;
} Entity;

typedef struct World{
    int ground;
    int garden;

    Entity house;
    Skybox skybox;
    Tree tree;

    float globalAmbient[4];
    float materialAmbient[4];
    float diffuseLightEmission[4];
} World;

//// Load model
int loadModel(const char* filename, struct Model* model);

void extractTokens(const char* text, struct TokenArray* tokenArray);

void clearComment(char* line);

void initModelCounters(struct Model* model);

void freeTokens(struct TokenArray* tokenArray);

int countTokens(const char* text);

int calcTokenLength(const char* text, int startIndex);

char* copyToken(const char* text, int offset, int length);

void insertToken(const char* token, struct TokenArray* tokenArray);

void countElementInLine(const char* line, struct Model* model);

void countElements(FILE* filename, struct Model* model);

void createArrays(struct Model* model);

int countFaceDelimiters(const char* text);

int readNextIndex(const char* text, int* length);

void readFacePoint(const char* text, struct FacePoint* facePoint);

void readVertex(const struct TokenArray* tokenArray, struct Vertex* vertex);

void readTextureVertex(const struct TokenArray* tokenArray, struct TextureVertex* textureVertex);

void readNormal(const struct TokenArray* tokenArray, struct Vertex* normal);

void readTriangle(const struct TokenArray* tokenArray, struct Triangle* triangle);

void readQuad(const struct TokenArray* tokenArray, struct Quad* quad);

int isDigit(char c);

int isValidTriangle(const struct Triangle* triangle, const struct Model* model);

int isValidQuad(const struct Quad* quad, const struct Model* model);

void readElementFromLine(const char* line, struct Model* model);

void readElements(FILE* file, struct Model* model);

void printBoundingBox(const struct Model* model);

void scaleModel(struct Model* model, double sx, double sy, double sz);
#endif //BEADANDO_MODEL_H
