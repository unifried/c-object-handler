/*!
 * Author: James Carppe
 * Date: 29/02/2024
 * Version: 1.0.1
 *
 * @brief Defines & implements types to simplify file input & output.
 */

// Header Guard
#ifndef FILES_H
#define FILES_H

/*!
 * @brief ReadOnly_File is a type that cointains a pointer to a file that only has read permission, & the number of lines within the file.
 *
 * @field pointer   FILE*       pointer to a open file
 * @field lines     const int   number of lines in the file
 */
typedef struct ReadOnly_File {
    FILE* pointer;
    int lines;
} ReadOnly_File;

/*!
 * @brief ReadWriter_File is a type that cointains a pointer to a file that has read & write permissions, & the number of lines within the file.
 *
 * @field pointer   FILE*   pointer to a open file
 * @field lines     int     number of lines in the file
 */
typedef struct ReadWrite_File {
    FILE* pointer;
    int lines;
} ReadWrite_File;

/*!
 * @brief Gets the number of lines in a file
 *
 * @param target FILE* valid file pointer
 */
int get_lines_in_file(FILE* target);

/*!
 * @brief Opens a read-only file
 *
 * @param file_path const char* file to be opened
 *
 * @return ReadOnly_File representing the opened file
 *  - a NULL pointer will be assigned to ReadOnly_File.pointer is the open failed & lines will be set to 0
 */
struct ReadOnly_File open_readonly_file(const char* file_path);

/*!
 * @brief Opens a read & write file
 *
 * @param file_path const char* file to be opened
 *
 * @return ReadWrite_File representing the opened file
 *  - a NULL pointer will be assigned to ReadWrite_File.pointer is the open failed & lines will be set to 0
 */
struct ReadWrite_File open_readwrite_file(const char* file_path);

#endif //FILES_H