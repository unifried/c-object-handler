#include <stdio.h>

#include "files.h"
#include "object_file_handler.h"

int main() {
    // File to load
    char *file_name = "C://Programming/C/off-reader/bone.off";

    // Load the data
    Object_File_Data loaded_off = readOFFFile(file_name);

    // Print the results
    printf("Vertices: %i, Faces: %i", loaded_off.vertex_count, loaded_off.face_count);
    /*
    char enter = ' ';

    enter = getchar();
    for (int vertex = 0; vertex < loaded_off.vertex_count; vertex++) {
        printf("Vertex: %i | [%f, %f, %f]\n", vertex + 1, loaded_off.vertices[vertex].data[0], loaded_off.vertices[vertex].data[1], loaded_off.vertices[vertex].data[2]);
    }

    enter = getchar();
    for (int triangle = 0; triangle < loaded_off.face_count; triangle++) {
        printf("Triangle: %i | [%i, %i, %i]\n", triangle + 1, loaded_off.faces[triangle].data[0], loaded_off.faces[triangle].data[1], loaded_off.faces[triangle].data[2]);
    }*/

    // Write the data
    char *write_file_name = "C://Programming/C/off-reader/new_bone.off";
    writeOFFFile(write_file_name, &loaded_off);

    // Free the memory
    free_OFD(&loaded_off);
    return 0;
}