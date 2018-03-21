#include "model.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUFFER_SIZE 1024


int countTokens(const char* text) {
    int i = 0;
    int isToken = FALSE;
    int count = 0;

    while (text[i] != 0) {
        if (isToken == FALSE && text[i] != ' ') {
            count++;
            isToken = TRUE;
        } else if (isToken == TRUE && text[i] == ' ') {
            isToken = FALSE;
        }
        i++;
    }

    return count;
}

void extractTokens(const char* text, struct TokenArray* tokenArray) {
    int nTokens, tokenLength;
    char* token;
    int i;

    nTokens = countTokens(text);

    tokenArray->tokens = (char**)malloc(nTokens * sizeof(char*));
    tokenArray->nTokens = 0;

    i = 0;
    while (text[i] != 0) {
        if (text[i] != ' ') {
            tokenLength = calcTokenLength(text, i);
            token = copyToken(text, i, tokenLength);
            insertToken(token, tokenArray);
            i += tokenLength;
        } else {
            i++;
        }
    }
}

char* copyToken(const char* text, int offset, int length) {
    char* token;
    int i;

    token = (char*)malloc((length + 1) * sizeof(char));
    for (i = 0; i < length; i++) {
        token[i] = text[offset + i];
    }
    token[i] = 0;

    return token;
}

void insertToken(const char* token, struct TokenArray* tokenArray) {
    tokenArray->tokens[tokenArray->nTokens] = (char*)token;
    tokenArray->nTokens++;
}

int calcTokenLength(const char* text, int startIndex) {
    int endIndex, length;

    endIndex = startIndex;
    while (text[endIndex] != 0 && text[endIndex] != ' ') {
        endIndex++;
    }
    length = endIndex - startIndex;

    return length;
}

void freeTokens(struct TokenArray* tokenArray) {
    int i;

    for (i = 0; i < tokenArray->nTokens; i++) {
        free(tokenArray->tokens[i]);
    }
    free(tokenArray->tokens);
}

int loadModel(const char* filename, struct Model* model) {
    FILE* objFile = fopen(filename, "r");
    printf("Load model '%s' ...\n", filename);
    if (objFile == NULL) {
        printf("ERROR: Unable to open '%s' file!\n", filename);
        return FALSE;
    }
    printf("Count ..\n");
    countElements(objFile, model);
    printf("Create ..\n");
    createArrays(model);
    printf("Read ..\n");
    readElements(objFile, model);

    return TRUE;
}

void printModelInfo(const struct Model* model) {
    printf("Vertices: %d\n", model->nVertices);
    printf("Texture vertices: %d\n", model->nTextureVertices);
    printf("Normals: %d\n", model->nNormals);
    printf("Triangles: %d\n", model->nTriangles);
    printf("Quads: %d\n", model->nQuads);
}

void freeModel(struct Model* model) {
    free(model->vertices);
    free(model->textureVertices);
    free(model->normals);
    free(model->triangles);
    free(model->quads);
}

void countElements(FILE* file, struct Model* model) {
    char line[LINE_BUFFER_SIZE];

    initModelCounters(model);
    while (fgets(line, LINE_BUFFER_SIZE, file) != NULL) {
        clearComment(line);
        countElementInLine(line, model);
    }
}

void readElements(FILE* file, struct Model* model) {
    char line[LINE_BUFFER_SIZE];

    initModelCounters(model);
    model->nVertices = 1;
    model->nTextureVertices = 1;
    model->nNormals = 1;

    fseek(file, 0, SEEK_SET);
    while (fgets(line, LINE_BUFFER_SIZE, file) != NULL) {
        clearComment(line);
        readElementFromLine(line, model);
    }
}

void initModelCounters(struct Model* model) {
    model->nVertices = 0;
    model->nTextureVertices = 0;
    model->nNormals = 0;
    model->nTriangles = 0;
    model->nQuads = 0;
}

void clearComment(char* line) {
    int i = 0;
    while (line[i] != 0 && line[i] != '#' && line[i] != 0x0D && line[i] != 0x0A) {
        i++;
    }
    while (line[i] != 0) {
        line[i] = ' ';
        i++;
    }
}

void countElementInLine(const char* line, struct Model* model) {
    struct TokenArray tokenArray;
    char* firstToken;

    extractTokens(line, &tokenArray);

    if (tokenArray.nTokens > 0) {
        firstToken = tokenArray.tokens[0];
        if (strcmp(firstToken, "v") == 0) {
            model->nVertices++;
        } else if (strcmp(firstToken, "vt") == 0) {
            model->nTextureVertices++;
        } else if (strcmp(firstToken, "vn") == 0) {
            model->nNormals++;
        } else if (strcmp(firstToken, "f") == 0) {
            if (tokenArray.nTokens == 1 + 3) {
                model->nTriangles++;
            } else if (tokenArray.nTokens == 1 + 4) {
                model->nQuads++;
            } else {
                printf("WARN: Invalid number of face elements! %d\n", tokenArray.nTokens);
            }
        }
    }

    freeTokens(&tokenArray);
}

void readElementFromLine(const char* line, struct Model* model) {
    struct TokenArray tokenArray;
    char* firstToken;
    struct Triangle* triangle;
    struct Quad* quad;

    extractTokens(line, &tokenArray);

    if (tokenArray.nTokens > 0) {
        firstToken = tokenArray.tokens[0];
        if (strcmp(firstToken, "v") == 0) {
            readVertex(&tokenArray, &(model->vertices[model->nVertices]));
            model->nVertices++;
        } else if (strcmp(firstToken, "vt") == 0) {
            readTextureVertex(&tokenArray, &(model->textureVertices[model->nTextureVertices]));
            model->nTextureVertices++;
        } else if (strcmp(firstToken, "vn") == 0) {
            readNormal(&tokenArray, &(model->normals[model->nNormals]));
            model->nNormals++;
        } else if (strcmp(firstToken, "f") == 0) {
            if (tokenArray.nTokens == 1 + 3) {
                triangle = &(model->triangles[model->nTriangles]);
                readTriangle(&tokenArray, triangle);
                if (isValidTriangle(triangle, model) == FALSE) {
                    printf("line: '%s'\n", line);
                }
                model->nTriangles++;
            } else if (tokenArray.nTokens == 1 + 4) {
                quad = &(model->quads[model->nQuads]);
                readQuad(&tokenArray, quad);
                if (isValidQuad(quad, model) == FALSE) {
                    printf("line: '%s'\n", line);
                }
                model->nQuads++;
            }
        }
    }

    freeTokens(&tokenArray);
}

void createArrays(struct Model* model) {
    model->vertices = (struct Vertex*)malloc((model->nVertices + 1) * sizeof(struct Vertex));
    model->textureVertices = (struct TextureVertex*)malloc((model->nTextureVertices + 1) * sizeof(struct TextureVertex));
    model->normals = (struct Vertex*)malloc((model->nNormals + 1) * sizeof(struct Vertex));
    model->triangles = (struct Triangle*)malloc(model->nTriangles * sizeof(struct Triangle));
    model->quads = (struct Quad*)malloc(model->nQuads * sizeof(struct Quad));
}

void readVertex(const struct TokenArray* tokenArray, struct Vertex* vertex) {
    vertex->x = atof(tokenArray->tokens[1]);
    vertex->y = atof(tokenArray->tokens[2]);
    vertex->z = atof(tokenArray->tokens[3]);
}

void readTextureVertex(const struct TokenArray* tokenArray, struct TextureVertex* textureVertex) {
    textureVertex->u = atof(tokenArray->tokens[1]);
    textureVertex->v = atof(tokenArray->tokens[2]);
}

void readNormal(const struct TokenArray* tokenArray, struct Vertex* normal) {
    normal->x = atof(tokenArray->tokens[1]);
    normal->y = atof(tokenArray->tokens[2]);
    normal->z = atof(tokenArray->tokens[3]);
}

void readTriangle(const struct TokenArray* tokenArray, struct Triangle* triangle) {
    int i;

    for (i = 0; i < 3; i++) {
        readFacePoint(tokenArray->tokens[i + 1], &triangle->points[i]);
    }
}

void readQuad(const struct TokenArray* tokenArray, struct Quad* quad) {
    int i;

    for (i = 0; i < 4; i++) {
        readFacePoint(tokenArray->tokens[i + 1], &quad->points[i]);
    }
}

void readFacePoint(const char* text, struct FacePoint* facePoint) {
    int delimiterCount;
    const char* token;
    int length;

    token = text;
    delimiterCount = countFaceDelimiters(text);

    if (delimiterCount == 0) {
        facePoint->vertexIndex = readNextIndex(token, &length);
        facePoint->textureIndex = INVALID_VERTEX_INDEX;
        facePoint->normalIndex = INVALID_VERTEX_INDEX;
    } else if (delimiterCount == 1) {
        facePoint->vertexIndex = readNextIndex(token, &length);
        token += length;
        facePoint->textureIndex = readNextIndex(token, &length);
        facePoint->normalIndex = INVALID_VERTEX_INDEX;
    } else if (delimiterCount == 2) {
        // TODO: Handle the v//n special case!
        facePoint->vertexIndex = readNextIndex(token, &length);
        token += length;
        facePoint->textureIndex = readNextIndex(token, &length);
        token += length;
        facePoint->normalIndex = readNextIndex(token, &length);
    } else {
        printf("ERROR: Invalid face token! '%s'", text);
    }
}

int countFaceDelimiters(const char* text) {
    int count, i;

    count = 0;
    i = 0;
    while (text[i] != 0) {
        if (text[i] == '/') {
            count++;
        }
        i++;
    }

    return count;
}

int isDigit(char c) {
    if (c >= '0' && c <= '9') {
        return TRUE;
    }
    return FALSE;
}


int readNextIndex(const char* text, int* length) {
    int i, j, index;
    char buffer[32];

    i = 0;
    while (text[i] != 0 && isDigit(text[i]) == FALSE) {
        i++;
    }

    if (text[i] == 0) {
        return INVALID_VERTEX_INDEX;
    }

    j = 0;
    while (text[i] != 0 && isDigit(text[i]) == TRUE) {
        buffer[j] = text[i];
        i++;
        j++;
    }
    buffer[j] = 0;

    index = atoi(buffer);
    *length = i;

    return index;
}


int isValidTriangle(const struct Triangle* triangle, const struct Model* model) {
    int k;

    for (k = 0; k < 3; k++) {
        if (triangle->points[k].vertexIndex >= model->nVertices) {
            printf("ERROR: Invalid vertex index in a triangle!\n");
            return FALSE;
        }
        if (triangle->points[k].textureIndex >= model->nTextureVertices) {
            printf("ERROR: Invalid texture vertex index in a triangle!\n");
            return FALSE;
        }
        if (triangle->points[k].normalIndex >= model->nNormals) {
            printf("ERROR: Invalid normal index in a triangle!\n");
            return FALSE;
        }
    }
    return TRUE;
}

int isValidQuad(const struct Quad* quad, const struct Model* model) {
    int k;
    int vertexIndex, textureIndex, normalIndex;

    for (k = 0; k < 4; k++) {
        vertexIndex = quad->points[k].vertexIndex;
        textureIndex = quad->points[k].textureIndex;
        normalIndex = quad->points[k].normalIndex;
        if (vertexIndex < 0 || vertexIndex >= model->nVertices) {
            printf("ERROR: Invalid vertex index in a quad!\n");
            return FALSE;
        }
        if (textureIndex < 0 || textureIndex >= model->nTextureVertices) {
            printf("ERROR: Invalid texture vertex index in a quad!\n");
            return FALSE;
        }
        if (normalIndex < 0 || normalIndex >= model->nNormals) {
            printf("ERROR: Invalid normal index in a quad!");
            return FALSE;
        }
    }
    return TRUE;
}

void printBoundingBox(const struct Model* model) {
    int i;
    double x, y, z;
    double minX, maxX, minY, maxY, minZ, maxZ;

    if (model->nVertices == 0) {
        return;
    }

    minX = model->vertices[0].x;
    maxX = model->vertices[0].x;
    minY = model->vertices[0].y;
    maxY = model->vertices[0].y;
    minZ = model->vertices[0].z;
    maxZ = model->vertices[0].z;

    for (i = 0; i < model->nVertices; i++) {
        x = model->vertices[i].x;
        y = model->vertices[i].y;
        z = model->vertices[i].z;
        if (x < minX) {
            minX = x;
        }
        else if (x > maxX) {
            maxX = x;
        }
        if (y < minY) {
            minY = y;
        }
        else if (y > maxY) {
            maxY = y;
        }
        if (z < minZ) {
            minZ = z;
        }
        else if (z > maxZ) {
            maxZ = z;
        }
    }

    printf("Bounding box:\n");
    printf("x in [%lf, %lf]\n", minX, maxX);
    printf("y in [%lf, %lf]\n", minY, maxY);
    printf("z in [%lf, %lf]\n", minZ, maxZ);
}

void scaleModel(struct Model* model, double sx, double sy, double sz) {
    int i;

    for (i = 0; i < model->nVertices; i++) {
        model->vertices[i].x += sx;
        model->vertices[i].y += sy;
        model->vertices[i].z += sz;
//        model->vertices[i].x *= sx;
//        model->vertices[i].y *= sy;
//        model->vertices[i].z *= sz;
    }
}
