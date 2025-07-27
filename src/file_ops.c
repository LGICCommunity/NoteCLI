#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include "../include/file_ops.h"
#include "../include/utils.h"

#ifndef FILE_OPS_COPY_FILE_DECLARED
#define FILE_OPS_COPY_FILE_DECLARED
bool copy_file(const char *src, const char *dest);
#endif

bool create_document(const char *filename) {
    if (!ensure_notes_dir()) {
        return false;
    }
    char *filepath = get_full_path(filename);
    if (!filepath) {
        return false;
    }
    if (file_exists(filepath)) {
        log_error("File already exists: %s", filepath);
        free(filepath);
        return false;
    }
    printf("Enter content (Ctrl+D to finish):\n");
    char *content = read_user_input();
    if (!content) {
        free(filepath);
        return false;
    }
    FILE *file = fopen(filepath, "w");
    if (!file) {
        log_error("Failed to create file: %s", filepath);
        free(filepath);
        free(content);
        return false;
    }
    fputs(content, file);
    fclose(file);
    free(filepath);
    free(content);
    log_operation(OP_CREATE, filename);
    log_success("Note created successfully");
    return true;
}

bool read_document(const char *filename) {
    char *filepath = get_full_path(filename);
    if (!filepath) {
        return false;
    }
    FILE *file = fopen(filepath, "r");
    if (!file) {
        log_error("Failed to open file: %s", filepath);
        free(filepath);
        return false;
    }
    char buffer[MAX_INPUT_SIZE];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    fclose(file);
    free(filepath);
    log_operation(OP_READ, filename);
    return true;
}

bool update_document(const char *filename) {
    char *filepath = get_full_path(filename);
    if (!filepath) {
        return false;
    }
    if (!file_exists(filepath)) {
        log_error("File does not exist: %s", filepath);
        free(filepath);
        return false;
    }
    if (!ensure_versions_dir()) {
        free(filepath);
        return false;
    }
    char *timestamp = get_timestamp_string();
    if (!timestamp) {
        free(filepath);
        return false;
    }
    char version_path[512];
    snprintf(version_path, sizeof(version_path), "%s/notes_%s_%s", VERSIONS_DIR, timestamp, filename);
    free(timestamp);
    if (!copy_file(filepath, version_path)) {
        free(filepath);
        return false;
    }
    FILE *current = fopen(filepath, "r");
    FILE *backup = fopen(version_path, "a");
    if (!current || !backup) {
        if (current) fclose(current);
        if (backup) fclose(backup);
        free(filepath);
        return false;
    }
    char buffer[MAX_INPUT_SIZE];
    size_t file_size = 0;
    while (fgets(buffer, sizeof(buffer), current) != NULL) {
        fputs(buffer, backup);
        file_size += strlen(buffer);
    }
    fclose(current);
    fclose(backup);
    printf("\nEnter new content (Ctrl+D to finish):\n");
    char *new_content = read_user_input();
    if (!new_content) {
        free(filepath);
        return false;
    }
    FILE *file = fopen(filepath, "a");
    if (!file) {
        log_error("Failed to update file: %s", filepath);
        free(filepath);
        free(new_content);
        return false;
    }
    if (file_size > 0) {
        fputs("\n", file);
        fputs("---------------------\n", file);
        fputs("\n", file);
    }
    fputs(new_content, file);
    if (new_content[strlen(new_content) - 1] != '\n') {
        fputs("\n", file);
    }
    fclose(file);
    free(filepath);
    free(new_content);
    log_operation(OP_UPDATE, filename);
    log_success("Note updated successfully (previous version saved)");
    return true;
}

bool delete_document(const char *filename) {
    char *filepath = get_full_path(filename);
    if (!filepath) {
        return false;
    }
    log_operation(OP_DELETE, filename);
    if (remove(filepath) != 0) {
        log_error("Failed to delete file: %s", filepath);
        free(filepath);
        return false;
    }
    free(filepath);
    log_success("Note deleted successfully");
    return true;
}

bool ensure_notes_dir(void) {
    char path[512];
    snprintf(path, sizeof(path), "%s/notes", DATA_DIR);
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        if (mkdir(path, 0755) == -1) {
            log_error("Failed to create directory: %s", path);
            return false;
        }
    }
    return true;
}
char *get_full_path(const char *filename) {
    char *filepath = malloc(512);
    if (!filepath) {
        log_error("Memory allocation failed");
        return NULL;
    }
    snprintf(filepath, 512, "%s/notes/%s", DATA_DIR, filename);
    return filepath;
}

bool file_exists(const char *path) {
    struct stat st;
    return (stat(path, &st) == 0);
}

bool copy_file(const char *src, const char *dest) {
    FILE *source = fopen(src, "r");
    if (!source) {
        log_error("Failed to open source file for copy: %s", src);
        return false;
    }
    FILE *destination = fopen(dest, "w");
    if (!destination) {
        log_error("Failed to open destination file for copy: %s", dest);
        fclose(source);
        return false;
    }
    char buffer[4096];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        if (fwrite(buffer, 1, bytes, destination) != bytes) {
            log_error("Failed to write to destination file: %s", dest);
            fclose(source);
            fclose(destination);
            return false;
        }
    }
    fclose(source);
    fclose(destination);
    return true;
} 