#ifndef CLI_H
#define CLI_H

#include <stdbool.h>

// Platform-specific definitions
#ifdef _WIN32
#include <windows.h>
#define PATH_SEPARATOR "\\"
#define mkdir(path, mode) _mkdir(path)
#define PATH_MAX MAX_PATH
#else
#include <sys/stat.h>
#include <unistd.h>
#define PATH_SEPARATOR "/"
#endif

// Command types supported by the NotesCLI
typedef enum {
    CMD_CREATE,
    CMD_READ,
    CMD_UPDATE,
    CMD_DELETE,
    CMD_INVALID
} command_type_t;

// Structure to hold parsed command arguments
typedef struct {
    command_type_t cmd_type;
    char category[64];
    char filename[256];
    bool valid;
} command_args_t;

// Function declarations
void print_usage(void);
command_args_t parse_arguments(int argc, char *argv[]);
bool validate_category(const char *category);
bool confirm_action(const char *message);

#endif // CLI_H 