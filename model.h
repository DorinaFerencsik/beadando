#ifndef BEADANDO_MODEL_H
#define BEADANDO_MODEL_H

#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define INVALID_VERTEX_INDEX 0

struct TokenArray
{
    char** tokens;
    int n_tokens;
};

struct Vertex
{
    double x;
    double y;
    double z;
};

struct TextureVertex
{
    double u;
    double v;
};

struct FacePoint
{
    int vertex_index;
    int texture_index;
    int normal_index;
};

struct Triangle
{
    struct FacePoint points[3];
};

struct Quad
{
    struct FacePoint points[4];
};

struct Model
{
    int n_vertices;
    int n_texture_vertices;
    int n_normals;
    int n_triangles;
    int n_quads;
    struct Vertex* vertices;
    struct TextureVertex* texture_vertices;
    struct Vertex* normals;
    struct Triangle* triangles;
    struct Quad* quads;
};

typedef struct {
    int front, back, left, right, top, texture;
}Skybox;

typedef struct {
//    Model model;
    int leafTexture, trunkTexture;
//    float material_ambient[4];
}Tree;

struct World{
    int ground;
    Skybox skybox;
    int skyTexture;
    Tree tree;

    float ambient[4];
    float material_ambient[4];
    float diffuse_light_emission[4];
};
#endif //BEADANDO_MODEL_H
