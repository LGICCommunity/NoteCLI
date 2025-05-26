#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/cli.h"
#include "../include/file_ops.h"
#include "../include/utils.h"

int main(int argc, char *argv[]) {
    // Parse command line arguments
    command_args_t args = parse_arguments(argc, argv);
    
    if (!args.valid) {
        print_usage();
        return EXIT_FAILURE;
    }

    bool success = false;

    // Route command to appropriate handler
    switch (args.cmd_type) {
        case CMD_CREATE:
            success = create_document(args.category, args.filename);
            break;
            
        case CMD_READ:
            success = read_document(args.category, args.filename);
            break;
            
        case CMD_UPDATE:
            success = update_document(args.category, args.filename);
            break;
            
        case CMD_DELETE:
            if (confirm_action("Are you sure you want to delete this document? (y/n): ")) {
                success = delete_document(args.category, args.filename);
            }
            break;
            
        default:
            log_error("Unknown command");
            print_usage();
            return EXIT_FAILURE;
    }

    return success ? EXIT_SUCCESS : EXIT_FAILURE;
} 