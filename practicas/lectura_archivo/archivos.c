#include "archivos.h"
#include <stdlib.h>

/* Static file pointer only accessible inside file_utils.c */
static FILE *file = NULL;

/* Opens a file in a given mode */
int file_open(const char *path, const char *mode) {
    // Check if a file is already open
    if (file != NULL) {
        handle_error("File already open.");
        return -1;
    }
    // Open the file
    file = fopen(path, mode);
    // Check if the file was opened successfully
    if (file == NULL) {
        handle_error("File opening failed.");
        return -1;
    }
    return 0;
}

/* Closes the currently open file */
int file_close() {
    // Check if a file is open
    if (file == NULL) {
        handle_error("No file is currently open.");
        return -1;
    }
    fclose(file);
    file = NULL;
    return 0;
}

/* Creates a new file */
int file_create(const char *path) {
    if (file_open(path, "w") == 0) {
        file_close();
        return 0;
    }
    return -1;
}

/* Deletes a file */
int file_delete(const char *path) {
    return remove(path);
}

/* Reads the entire content of a file */
char *file_read_all(const char *path) {
    // Open the file in read mode and check if it was opened successfully
    // If the file could not be opened, return NULL
    if (file_open(path, "r") != 0) {
        return NULL;
    }
    // Get the size of the file and allocate memory for the content
    long size = file_size(path);
    // If the file size is 0, return an empty string
    char *content = (char *)malloc((size + 1) * sizeof(char));
    
    // Check if memory allocation was successful
    if (content == NULL) {
        file_close();
        handle_error("Memory allocation failed.");
        return NULL;
    }
    // Read the content of the file into the allocated memory
    fread(content, sizeof(char), size, file);
    // Add a null terminator at the end of the content
    content[size] = '\0';
    file_close();
    return content;
}

/* Writes data to a file, overwriting existing content */
int file_write(const char *path, const char *data) {
    if (file_open(path, "w") != 0) {
        return -1;
    }
    fprintf(file, "%s", data);
    file_close();
    return 0;
}

/* Appends a line to a file */
int file_append_line(const char *path, const char *line) {
    if (file_open(path, "a") != 0) {
        return -1;
    }
    fprintf(file, "%s\n", line);
    file_close();
    return 0;
}

/* Removes a specific line from a file */
int file_remove_line(const char *path, int line_number) {
    if (file_open(path, "r") != 0) {
        return -1;
    }
    
    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        handle_error("Failed to open temporary file.");
        file_close();
        return -1;
    }
    // Buffer to store each line read from the file
    char buffer[256];
    int current_line = 1;
    // Read each line from the file and write it to the temporary file
    while (fgets(buffer, sizeof(buffer), file)) {
        if (current_line != line_number) {
            fputs(buffer, temp);
        }
        current_line++;
    }
    
    fclose(temp);
    file_close();
    
    remove(path);
    rename("temp.txt", path);
    
    return 0;
}

/* Inserts a line at a specific position in the file */
int file_insert_line(const char *path, const char *line, int position) {
    if (file_open(path, "r") != 0) {
        return -1;
    }
    
    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        handle_error("Failed to open temporary file.");
        file_close();
        return -1;
    }
    
    char buffer[256];
    int current_line = 1;
    
    while (fgets(buffer, sizeof(buffer), file)) {
        if (current_line == position) {
            fprintf(temp, "%s\n", line);
        }
        fputs(buffer, temp);
        current_line++;
    }
    
    if (current_line == position) {
        fprintf(temp, "%s\n", line);
    }
    
    fclose(temp);
    file_close();
    
    remove(path);
    rename("temp.txt", path);
    
    return 0;
}

/* Returns the size of the file */
long file_size(const char *path) {
    if (file_open(path, "r") != 0) {
        return -1;
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    file_close();
    return size;
}

/* Handles error messages */
void handle_error(const char *message) {
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}
