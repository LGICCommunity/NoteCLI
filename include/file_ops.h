#include <stdbool.h>

// Function declarations for file operations
bool create_document(const char *category, const char *filename);
bool read_document(const char *category, const char *filename);
bool update_document(const char *category, const char *filename);
bool delete_document(const char *category, const char *filename);

// Helper functions
bool ensure_category_dir(const char *category);
char *get_full_path(const char *category, const char *filename);
bool file_exists(const char *path);