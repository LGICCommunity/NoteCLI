#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/cli.h"
#include "../include/utils.h"

void print_usage(void) {
    printf("Usage: NotesCLI <command> <category> <filename>\n\n");
    printf("Commands:\n");
    printf("  create <category> <filename>  - Create a new document\n");
    printf("  read   <category> <filename>  - Read an existing document\n");
    printf("  update <category> <filename>  - Update an existing document\n");
    printf("  delete <category> <filename>  - Delete an existing document\n\n");
    printf("Categories: recipes, notes, logs\n");
}

command_args_t parse_arguments(int argc, char *argv[]) {
    command_args_t args = {CMD_UNKNOWN, "", "", false};
    
    if (argc != 4) {
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

    // Validate category and filename
    if (!validate_category(argv[2]) || !is_valid_filename(argv[3])) {
        return args;
    }

    strncpy(args.category, argv[2], sizeof(args.category) - 1);
    strncpy(args.filename, argv[3], sizeof(args.filename) - 1);
    args.valid = true;

    return args;
}

bool validate_category(const char *category) {
    const char *valid_categories[] = {"recipes", "notes", "logs", NULL};
    
    for (const char **cat = valid_categories; *cat != NULL; cat++) {
        if (strcmp(category, *cat) == 0) {
            return true;
        }
    }
    
    log_error("Invalid category. Valid categories are: recipes, notes, logs");
    return false;
}

bool confirm_action(const char *message) {
    char response[8];
    printf("%s", message);
    if (fgets(response, sizeof(response), stdin) == NULL) {
        return false;  // Return false if fgets fails
    }
    return (tolower(response[0]) == 'y');
} 