#ifndef _ARCHIVOS_H
#define _ARCHIVOS_H

#include <stdio.h>
#include <stdlib.h>

/* File Handling */
int file_open(const char *path, const char *mode);
int file_close();
int file_create(const char *path);
int file_delete(const char *path);

/* Read/Write Operations */
char *file_read_all(const char *path);
int file_write(const char *path, const char *data);
int file_append_line(const char *path, const char *line);

/* Line Manipulation */
int file_remove_line(const char *path, int line_number);
int file_insert_line(const char *path, const char *line, int position);

/* Utility Functions */
long file_size(const char *path);
void handle_error(const char *message);

#endif /* _ARCHIV_H */
