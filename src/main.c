#include <stdio.h>
#include <stdlib.h>
#include "../include/cli.h"
#include "../include/file_ops.h"

int main(int argc, char *argv[]) {
    command_args_t a = parse_arguments(argc, argv);
    if (!a.valid) return print_usage(), EXIT_FAILURE;
    int ok = 0;
    if (a.cmd_type == CMD_CREATE) ok = create_document(a.category, a.filename);
    else if (a.cmd_type == CMD_READ) ok = read_document(a.category, a.filename);
    else if (a.cmd_type == CMD_UPDATE) ok = update_document(a.category, a.filename);
    else if (a.cmd_type == CMD_DELETE) ok = confirm_action("Delete? (y/n): ") && delete_document(a.category, a.filename);
    else print_usage();
    return ok ? EXIT_SUCCESS : EXIT_FAILURE;
} 