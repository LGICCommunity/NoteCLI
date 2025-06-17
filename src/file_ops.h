#ifndef FILE_OPS_H
#define FILE_OPS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#ifdef _WIN32
#include <direct.h>
#include <io.h>
#define F_OK 0
#define access _access
#define mkdir(path, mode) _mkdir(path)
#else
#include <unistd.h>
#include <sys/stat.h>
#endif

// File operation functions
bool create_directories(const char *path);
bool file_exists(const char *filepath);
bool ensure_directory_exists(const char *filepath);
char *get_version_path(const char *category, const char *filename);
bool backup_file(const char *source, const char *dest);
bool create_file(const char *filepath, const char *content);
char *read_file(const char *filepath);
bool update_file(const char *filepath, const char *content);
bool delete_file(const char *filepath);

// Path manipulation functions
char *join_path(const char *base, const char *component);
char *get_directory_path(const char *filepath);

#endif // FILE_OPS_H 