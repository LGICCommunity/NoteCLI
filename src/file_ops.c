#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#ifdef _WIN32
#include <direct.h>
#else
#include <unistd.h>
#endif
#include "../include/file_ops.h"
#include "../include/utils.h"

bool create_document(const char *category, const char *filename) {
    if (!ensure_category_dir(category)) {
        return false;
    }

    char *filepath = get_full_path(category, filename);
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

    // Log the create operation
    log_operation(OP_CREATE, category, filename);

    log_success("Document created successfully");
    return true;
}

bool read_document(const char *category, const char *filename) {
    char *filepath = get_full_path(category, filename);
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

    // Log the read operation
    log_operation(OP_READ, category, filename);

    return true;
}

bool update_document(const char *category, const char *filename) {
    char *filepath = get_full_path(category, filename);
    if (!filepath) {
        return false;
    }

    if (!file_exists(filepath)) {
        log_error("File does not exist: %s", filepath);
        free(filepath);
        return false;
    }

    // Create versions directory if it doesn't exist
    if (!ensure_versions_dir()) {
        free(filepath);
        return false;
    }

    // Get timestamp for version filename
    char *timestamp = get_timestamp_string();
    if (!timestamp) {
        free(filepath);
        return false;
    }

    // Create version filename
    char version_path[1024];
    snprintf(version_path, sizeof(version_path), "%s%c%s_%s_%s", 
             VERSIONS_DIR, PATH_SEP, category, timestamp, filename);
    free(timestamp);

    // First read and display existing content
    FILE *current = fopen(filepath, "r");
    if (!current) {
        log_error("Failed to open file: %s", filepath);
        free(filepath);
        return false;
    }

    // Create backup version
    FILE *backup = fopen(version_path, "w");
    if (!backup) {
        log_error("Failed to create version file: %s", version_path);
        fclose(current);
        free(filepath);
        return false;
    }

    // Read and display existing content while creating backup
    char buffer[4096];
    size_t file_size = 0;
    
    while (fgets(buffer, sizeof(buffer), current) != NULL) {
        fputs(buffer, backup); // Write to backup
        file_size += strlen(buffer);
    }
    
    // Reset file position to start
    rewind(current);
    
    // Only show the current content if file is not empty
    if (file_size > 0) {
        printf("\nCurrent content of %s:\n", filename);
        printf("----------------\n");
        
        while (fgets(buffer, sizeof(buffer), current) != NULL) {
            printf("%s", buffer);
        }
        
        if (buffer[strlen(buffer) - 1] != '\n') {
            printf("\n");
        }
        printf("----------------\n");
    }
    
    // Close the files
    fclose(current);
    fclose(backup);

    // Now get the new content
    printf("\nEnter new content (Ctrl+D to finish):\n");
    char *new_content = read_user_input();
    if (!new_content) {
        free(filepath);
        return false;
    }

    // Open file in append mode
    FILE *file = fopen(filepath, "a");
    if (!file) {
        log_error("Failed to update file: %s", filepath);
        free(filepath);
        free(new_content);
        return false;
    }

    // If file is not empty, add separator
    if (file_size > 0) {
        // Add newlines and separator before new content
        fputs("\n", file);
        fputs("---------------------\n", file);
        fputs("\n", file);
    }

    // Append the new content
    fputs(new_content, file);
    
    // Add a newline if the content doesn't end with one
    if (new_content[strlen(new_content) - 1] != '\n') {
        fputs("\n", file);
    }
    
    // Cleanup
    fclose(file);
    free(filepath);
    free(new_content);

    // Log the update operation
    log_operation(OP_UPDATE, category, filename);

    log_success("Document updated successfully (previous version saved)");
    return true;
}

bool delete_document(const char *category, const char *filename) {
    char *filepath = get_full_path(category, filename);
    if (!filepath) {
        return false;
    }

    // Log the delete operation
    log_operation(OP_DELETE, category, filename);

    if (remove(filepath) != 0) {
        log_error("Failed to delete file: %s", filepath);
        free(filepath);
        return false;
    }

    free(filepath);
    log_success("Document deleted successfully");
    return true;
}

bool ensure_category_dir(const char *category) {
    char path[512];
    snprintf(path, sizeof(path), "%s%c%s", DATA_DIR, PATH_SEP, category);

    struct stat st = {0};
    if (stat(path, &st) == -1) {
        if (MKDIR(path) == -1) {
            log_error("Failed to create directory: %s", path);
            return false;
        }
    }
    return true;
}

char *get_full_path(const char *category, const char *filename) {
    char *filepath = malloc(512);
    if (!filepath) {
        log_error("Memory allocation failed");
        return NULL;
    }
    snprintf(filepath, 512, "%s%c%s%c%s", DATA_DIR, PATH_SEP, category, PATH_SEP, filename);
    return filepath;
}

bool file_exists(const char *path) {
    struct stat st;
    return (stat(path, &st) == 0);
} 