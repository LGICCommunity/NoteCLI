#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

// Constants
#define MAX_INPUT_SIZE 4096
#define DATA_DIR "data"
#define VERSIONS_DIR "data/versions"
#define LOGS_DIR "data/logs"
#define HISTORY_FILE "data/logs/history.txt"

// Operation types for logging
typedef enum {
    OP_CREATE,
    OP_READ,
    OP_UPDATE,
    OP_DELETE
} operation_type_t;

// Utility function declarations
void log_error(const char *format, ...);
void log_success(const char *format, ...);
char *read_user_input(void);
bool is_valid_filename(const char *filename);
void trim_whitespace(char *str);
char *get_timestamp_string(void);
bool ensure_versions_dir(void);
bool ensure_logs_dir(void);
bool log_operation(operation_type_t op_type, const char *category, const char *filename);
const char *get_operation_name(operation_type_t op_type);

#endif // UTILS_H 