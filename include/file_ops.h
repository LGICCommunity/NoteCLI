#include <stdbool.h>

// Function declarations for file operations
bool create_document(const char *filename);
bool read_document(const char *filename);
bool update_document(const char *filename);
bool delete_document(const char *filename);

// Helper functions
bool ensure_category_dir(const char *category);
bool ensure_notes_dir(void);
char *get_full_path(const char *filename);
bool file_exists(const char *path);
bool copy_file(const char *src, const char *dest);