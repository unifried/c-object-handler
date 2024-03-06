/*!
 * Author: James Carppe
 * Date: 29/02/2024
 * Version: 1.0.2
 *
 * @brief Defines & implements types to simplify file input & output.
 *
 * Primary comments are provided in the header file.
 */

#include <stdio.h>
#include <stdlib.h>
#include "files.h"

// Gets the number of lines in a given file
int get_lines_in_file(FILE *target) {
    // Count the lines
    int lines = 0;

    int current_character;
    do {
        // Read the next character in the file
        current_character = fgetc(target);

        // If the character is a new line character, add 1 to lines
        if (current_character == '\n') lines++;
    } while (current_character != EOF);

    // Return lines
    return lines;
}

// Opens and returns a read-only file inside a ReadOnly_File struct
struct ReadOnly_File open_readonly_file(const char *file_path) {
    // Open the file
    FILE *file = fopen(file_path, "r");

    // Create result template
    ReadOnly_File result = {};

    // Check open success
    if (file == NULL) {
        // File didnt open

        // Return a blank struct
        result.pointer = NULL;
        result.lines = 0;

        return result;
    }

    // File opened successfully

    // Get the lines in the file
    const int lines = get_lines_in_file(file);

    // Reset pointer
    fclose(file);
    file = fopen(file_path, "r");

    // Return a completed struct
    result.pointer = file;
    result.lines = lines;

    return result;
}

// Opens and returns a read+write file inside a ReadWrite_File struct
struct ReadWrite_File open_readwrite_file(const char *file_path) {
    // Open the file
    FILE *file = fopen(file_path, "w");

    // Create result template
    ReadWrite_File result = {};

    // Check open success
    if (file == NULL) {
        // File didnt open

        // Return a blank struct
        result.pointer = NULL;
        result.lines = 0;

        return result;
    }

    // File opened successfully

    // Get the lines in the file
    const int lines = get_lines_in_file(file);

    // Reset pointer
    fclose(file);
    file = fopen(file_path, "w");

    // Return a completed struct
    result.pointer = file;
    result.lines = lines;

    return result;
}
