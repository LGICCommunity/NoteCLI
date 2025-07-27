#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/cli.h"
#include "../include/utils.h"

void print_usage(void) {
    printf("Usage: NotesCLI <command> <filename>\n\n");
    printf("Commands:\n");
    printf("  create <filename>  - Create a new note\n");
    printf("  read   <filename>  - Read an existing note\n");
    printf("  update <filename>  - Update an existing note\n");
    printf("  delete <filename>  - Delete an existing note\n\n");
}

command_args_t parse_arguments(int argc, char *argv[]) {
    command_args_t args = {CMD_UNKNOWN, "", false};
    
    if (argc != 3) {
        return args;
    }

    // Parse command type
    if (strcmp(argv[1], "create") == 0) {
        args.cmd_type = CMD_CREATE;
    } else if (strcmp(argv[1], "read") == 0) {
        args.cmd_type = CMD_READ;
    } else if (strcmp(argv[1], "update") == 0) {
        args.cmd_type = CMD_UPDATE;
    } else if (strcmp(argv[1], "delete") == 0) {
        args.cmd_type = CMD_DELETE;
    } else {
        return args;
    }

    // Validate filename
    if (!is_valid_filename(argv[2])) {
        return args;
    }

    strncpy(args.filename, argv[2], sizeof(args.filename) - 1);
    args.valid = true;

    return args;
}

bool confirm_action(const char *message) {
    char response[8];
    printf("%s", message);
    if (fgets(response, sizeof(response), stdin) == NULL) {
        return false;  // Return false if fgets fails
    }
    return (tolower(response[0]) == 'y');
} 