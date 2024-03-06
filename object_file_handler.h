/*!
 * Author: James Carppe
 * Date: 6/3/2024
 *
 * @brief Object File Loader
 */

#ifndef OFF_READER_OBJECT_FILE_HANDLER_H
#define OFF_READER_OBJECT_FILE_HANDLER_H

typedef struct Vertex {
    float *data;
    int length;
} Vertex;

typedef struct Face {
    int *data;
    int length;
} Face;

typedef struct Edge {
    int *data;
    int length;
} Edge;

typedef struct Object_File_Data {
    // Vertexes
    Vertex *vertices;
    int vertex_count;

    // Faces
    Face *faces;
    int face_count;

    // Edges
    Edge *edges;
    int edge_count;
} Object_File_Data;

struct Object_File_Data readOFFFile(const char* file_name);

void free_Vertex(Vertex *self);
void free_Face(Face *self);
void free_Edge(Edge *self);
void free_OFD(Object_File_Data *self);
void writeOFFFile(const char *file_name, Object_File_Data *data);

#endif //OFF_READER_OBJECT_FILE_HANDLER_H
