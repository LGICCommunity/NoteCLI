#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/cli.h"
#include "../include/utils.h"

void print_usage(void) {
    puts("Usage: NotesCLI <command> <category> <filename>\nCommands:\n  create <category> <filename>\n  read   <category> <filename>\n  update <category> <filename>\n  delete <category> <filename>\n\nCategories: recipes, notes, logs\n");
}

command_args_t parse_arguments(int argc, char *argv[]) {
    command_args_t a = {CMD_UNKNOWN, "", "", 0};
    if (argc == 4) {
        if (!strcmp(argv[1], "create")) a.cmd_type = CMD_CREATE;
        else if (!strcmp(argv[1], "read")) a.cmd_type = CMD_READ;
        else if (!strcmp(argv[1], "update")) a.cmd_type = CMD_UPDATE;
        else if (!strcmp(argv[1], "delete")) a.cmd_type = CMD_DELETE;
        if (a.cmd_type && validate_category(argv[2]) && is_valid_filename(argv[3])) {
            strncpy(a.category, argv[2], sizeof(a.category)-1);
            strncpy(a.filename, argv[3], sizeof(a.filename)-1);
            a.valid = 1;
        }
    }
    return a;
}

bool validate_category(const char *c) {
    const char *v[] = {"recipes", "notes", "logs", 0};
    for (int i=0; v[i]; i++) if (!strcmp(c, v[i])) return 1;
    log_error("Invalid category. Valid: recipes, notes, logs");
    return 0;
}

bool confirm_action(const char *m) {
    char r[8];
    printf("%s", m);
    return fgets(r, 8, stdin) && tolower(r[0]) == 'y';
} 