#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../include/file_ops.h"
#include "../include/utils.h"

bool create_document(const char *c, const char *f) {
    if (!ensure_category_dir(c)) return 0;
    char *p = get_full_path(c, f); if (!p) return 0;
    if (file_exists(p)) { log_error("File exists: %s", p); free(p); return 0; }
    printf("Enter content (Ctrl+D to finish):\n");
    char *ct = read_user_input(); if (!ct) { free(p); return 0; }
    FILE *fl = fopen(p, "w"); if (!fl) { log_error("Create fail: %s", p); free(p); free(ct); return 0; }
    fputs(ct, fl); fclose(fl); free(p); free(ct);
    log_operation(OP_CREATE, c, f); log_success("Created"); return 1;
}

bool read_document(const char *c, const char *f) {
    char *p = get_full_path(c, f); if (!p) return 0;
    FILE *fl = fopen(p, "r"); if (!fl) { log_error("Open fail: %s", p); free(p); return 0; }
    char b[MAX_INPUT_SIZE]; while (fgets(b, sizeof(b), fl)) printf("%s", b);
    fclose(fl); free(p); log_operation(OP_READ, c, f); return 1;
}

bool update_document(const char *c, const char *f) {
    char *p = get_full_path(c, f); if (!p) return 0;
    if (!file_exists(p)) { log_error("No file: %s", p); free(p); return 0; }
    if (!ensure_versions_dir()) { free(p); return 0; }
    char *ts = get_timestamp_string(); if (!ts) { free(p); return 0; }
    char vp[1024]; snprintf(vp, 1024, "%s/%s_%s_%s", VERSIONS_DIR, c, ts, f); free(ts);
    FILE *cur = fopen(p, "r"); if (!cur) { log_error("Open fail: %s", p); free(p); return 0; }
    FILE *bak = fopen(vp, "w"); if (!bak) { log_error("Backup fail: %s", vp); fclose(cur); free(p); return 0; }
    char b[4096]; size_t sz = 0;
    while (fgets(b, sizeof(b), cur)) { fputs(b, bak); sz += strlen(b); }
    rewind(cur);
    if (sz) { printf("\nCurrent %s:\n----------------\n", f); while (fgets(b, sizeof(b), cur)) printf("%s", b); if (b[strlen(b)-1]!='\n') printf("\n"); printf("----------------\n"); }
    fclose(cur); fclose(bak);
    printf("\nEnter new content (Ctrl+D to finish):\n");
    char *nc = read_user_input(); if (!nc) { free(p); return 0; }
    FILE *fl = fopen(p, "a"); if (!fl) { log_error("Update fail: %s", p); free(p); free(nc); return 0; }
    if (sz) fputs("\n---------------------\n\n", fl);
    fputs(nc, fl); if (nc[strlen(nc)-1]!='\n') fputs("\n", fl);
    fclose(fl); free(p); free(nc);
    log_operation(OP_UPDATE, c, f); log_success("Updated (backup saved)"); return 1;
}

bool delete_document(const char *c, const char *f) {
    char *p = get_full_path(c, f); if (!p) return 0;
    log_operation(OP_DELETE, c, f);
    if (remove(p)) { log_error("Delete fail: %s", p); free(p); return 0; }
    free(p); log_success("Deleted"); return 1;
}

bool ensure_category_dir(const char *c) {
    char path[512]; snprintf(path, 512, "%s/%s", DATA_DIR, c);
    struct stat st={0};
    return stat(path, &st)==-1 ? mkdir(path, 0755)!=-1 : 1;
}

char *get_full_path(const char *c, const char *f) {
    char *p = malloc(512); if (!p) return 0;
    snprintf(p, 512, "%s/%s/%s", DATA_DIR, c, f); return p;
}

bool file_exists(const char *p) {
    struct stat st; return !stat(p, &st);
} 