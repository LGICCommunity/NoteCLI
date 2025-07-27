#include <stdbool.h>

// Command types supported by the NotesCLI
typedef enum {
    CMD_CREATE,
    CMD_READ,
    CMD_UPDATE,
    CMD_DELETE,
    CMD_UNKNOWN
} command_type_t;

// Structure to hold parsed command arguments
typedef struct {
    command_type_t cmd_type;
    char filename[256];
    bool valid;
} command_args_t;

// Function declarations
void print_usage(void);
command_args_t parse_arguments(int argc, char *argv[]);
bool confirm_action(const char *message);