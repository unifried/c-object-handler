/*!
 * Author: James Carppe
 * Date: 6/3/2024
 *
 * @brief Object File Loader
 */

#include <stdio.h>
#include <stdlib.h>

#include "files.h"
#include "object_file_handler.h"

void free_Vertex(Vertex *self) {
    free(self->data);
}

void free_Face(Face *self) {
    free(self->data);
}

void free_Edge(Edge *self) {
    free(self->data);
}

void free_OFD(Object_File_Data *self) {
    if (self->vertices != NULL && self->vertex_count < 1) {
        for (int vertex = 0; vertex < self->vertex_count; vertex++) {
            printf("Vertex: %i\n", vertex);
            if (&self->vertices[vertex] == NULL) continue;
            free_Vertex(&self->vertices[vertex]);
        }
    }

    if (self->faces != NULL && self->face_count < 1) {
        for (int face = 0; face < self->face_count; face++) {
            if (&self->faces[face] == NULL) continue;
            free_Face(&self->faces[face]);
        }
    }

    if (self->edges != NULL && self->edge_count < 1) {
        for (int edge = 0; edge < self->edge_count; edge++) {
            if (&self->edges[edge] == NULL) continue;
            free_Edge(&self->edges[edge]);
        }
    }

    free(self->vertices);
    free(self->faces);
    free(self->edges);
}

struct Object_File_Data create_empty_OFD() {
    Object_File_Data empty_file = {
            .vertices = NULL,
            .vertex_count = 0,
            .faces = NULL,
            .face_count = 0,
            .edges = NULL,
            .edge_count = 0
    };

    return empty_file;
}

struct Object_File_Data readOFFFile(const char* file_name) {
    // Open the file
    ReadOnly_File file = open_readonly_file(file_name);

    // Check the file has data
    if (file.lines < 1) {
        // File doesn't have data
        return create_empty_OFD();
    }

    // OFF identifier
    fscanf(file.pointer, "OFF");

    // Load counts
    Object_File_Data data = {};

    int vertex_count;
    int face_count;
    int edge_count;

    if (fscanf(file.pointer, "%i %i %i", &vertex_count, &face_count, &edge_count) != EOF) {
        data.vertex_count = vertex_count;
        data.face_count = face_count;
        data.edge_count = edge_count;
    } else return create_empty_OFD();

    // Load the data
    int data_point = 0;

    data.vertices = (Vertex *)malloc(vertex_count * sizeof(Vertex));
    for (data_point = 0; data_point < vertex_count; data_point++) {
        Vertex new_vertex = {
                .data = (float *)malloc(3 * sizeof(float)),
                .length = 3
        };

        float line_data[3] = {0};

        if (fscanf(file.pointer, "%f %f %f", &line_data[0], &line_data[1], &line_data[2]) != EOF) {
            new_vertex.data[0] = line_data[0];
            new_vertex.data[1] = line_data[1];
            new_vertex.data[2] = line_data[2];

            data.vertices[data_point] = new_vertex;
        }
    }

    data.faces = (Face *)malloc(face_count * sizeof(Face));
    for (data_point = 0; data_point < face_count; data_point++) {
        Face new_face = {
                .data = (int *)malloc(3 * sizeof(int)),
                .length = 3
        };

        int line_data[3] = {0};

        if (fscanf(file.pointer, "%i %i %i", &line_data[0], &line_data[1], &line_data[2]) != EOF) {
            new_face.data[0] = line_data[0];
            new_face.data[1] = line_data[1];
            new_face.data[2] = line_data[2];

            data.faces[data_point] = new_face;
        }
    }

    data.edges = (Edge *)malloc(edge_count * sizeof(Edge));
    for (data_point = 0; data_point < edge_count; data_point++) {
        Edge new_edge = {
                .data = (int *)malloc(3 * sizeof(int)),
                .length = 3
        };

        int line_data[3] = {0};
        if (fscanf(file.pointer, "%i %i %i", &line_data[0], &line_data[1], &line_data[2]) != EOF) {
            new_edge.data[0] = line_data[0];
            new_edge.data[1] = line_data[1];
            new_edge.data[2] = line_data[2];

            data.edges[data_point] = new_edge;
        }
    }

    // Return
    return data;
}

void writeOFFFile(const char *file_name, Object_File_Data *data) {
    // Open read-write file
    ReadWrite_File file = open_readwrite_file(file_name);

    if (file.pointer == NULL) return;

    // Write the initial information
    fprintf(file.pointer, "OFF\n");
    fprintf(file.pointer, "%i %i %i\n", data->vertex_count, data->face_count, data->edge_count);

    // Write vertices
    if (data->vertices != NULL) {
        for (int vertex = 0; vertex < data->vertex_count; vertex++) {
            if (data->vertices[vertex].data == NULL) continue;
            fprintf(file.pointer, "%f %f %f\n", data->vertices[vertex].data[0], data->vertices[vertex].data[1],
                    data->vertices[vertex].data[2]);
        }
    }

    // Write faces
    if (data->faces != NULL) {
        for (int face = 0; face < data->face_count; face++) {
            if (data->faces[face].data == NULL) continue;
            fprintf(file.pointer, "%i %i %i\n", data->faces[face].data[0], data->faces[face].data[1],
                    data->faces[face].data[2]);
        }
    }

    // Write edges
    if (data->edges != NULL) {
        for (int edge = 0; edge < data->edge_count; edge++) {
            if (data->edges[edge].data == NULL) continue;
            fprintf(file.pointer, "%i %i %i\n", data->edges[edge].data[0], data->edges[edge].data[1],
                    data->edges[edge].data[2]);
        }
    }
}