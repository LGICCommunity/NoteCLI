#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <time.h>
#include <sys/stat.h>
#include <errno.h>
#include "../include/utils.h"

void log_error(const char *format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "\033[1;31mError: ");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\033[0m\n");
    va_end(args);
}

void log_success(const char *format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stdout, "\033[1;32m");
    vfprintf(stdout, format, args);
    fprintf(stdout, "\033[0m\n");
    va_end(args);
}

char *read_user_input(void) {
    char *buffer = malloc(MAX_INPUT_SIZE);
    if (!buffer) {
        log_error("Memory allocation failed");
        return NULL;
    }

    size_t total_size = 0;
    size_t bytes_read;
    char temp[1024];

    while (fgets(temp, sizeof(temp), stdin) != NULL) {
        bytes_read = strlen(temp);
        
        if (total_size + bytes_read >= MAX_INPUT_SIZE) {
            log_error("Input too large");
            free(buffer);
            return NULL;
        }

        strcpy(buffer + total_size, temp);
        total_size += bytes_read;
    }

    if (total_size == 0) {
        free(buffer);
        return NULL;
    }

    return buffer;
}

bool is_valid_filename(const char *filename) {
    if (!filename || strlen(filename) == 0) {
        log_error("Filename cannot be empty");
        return false;
    }

    // Check for directory traversal
    if (strstr(filename, "..") != NULL) {
        log_error("Invalid filename: contains directory traversal");
        return false;
    }

    // Check for valid characters
    for (const char *p = filename; *p; p++) {
        if (!isalnum(*p) && *p != '.' && *p != '-' && *p != '_') {
            log_error("Invalid filename: contains invalid characters");
            return false;
        }
    }

    return true;
}

void trim_whitespace(char *str) {
    if (!str) return;

    // Trim trailing whitespace
    char *end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) {
        *end = '\0';
        end--;
    }

    // Trim leading whitespace
    char *start = str;
    while (*start && isspace(*start)) {
        start++;
    }

    if (start != str) {
        memmove(str, start, strlen(start) + 1);
    }
}

char *get_timestamp_string(void) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char *timestamp = malloc(32);
    
    if (!timestamp) {
        log_error("Memory allocation failed for timestamp");
        return NULL;
    }
    
    strftime(timestamp, 32, "%Y%m%d_%H%M%S", t);
    return timestamp;
}

bool ensure_versions_dir(void) {
    struct stat st = {0};
    if (stat(VERSIONS_DIR, &st) == -1) {
        if (mkdir(VERSIONS_DIR, 0755) == -1) {
            log_error("Failed to create versions directory: %s", VERSIONS_DIR);
            return false;
        }
    }
    return true;
}

bool ensure_logs_dir(void) {
    struct stat st = {0};
    if (stat(LOGS_DIR, &st) == -1) {
        if (mkdir(LOGS_DIR, 0755) == -1) {
            log_error("Failed to create logs directory");
            return false;
        }
    }
    return true;
}

const char *get_operation_name(operation_type_t op_type) {
    switch (op_type) {
        case OP_CREATE: return "CREATE";
        case OP_READ:   return "READ";
        case OP_UPDATE: return "UPDATE";
        case OP_DELETE: return "DELETE";
        default:        return "UNKNOWN";
    }
}

bool log_operation(operation_type_t op_type, const char *filename) {
    // Ensure logs directory exists
    if (!ensure_logs_dir()) {
        return false;
    }
    // Get current timestamp
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char timestamp[32];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", t);
    // Open history file in append mode
    FILE *history_file = fopen(HISTORY_FILE, "a");
    if (!history_file) {
        log_error("Failed to open history file");
        return false;
    }
    // Write operation record (no category)
    fprintf(history_file, "[%s] %s: %s\n", 
            timestamp, 
            get_operation_name(op_type),
            filename);
    fclose(history_file);
    return true;
} 