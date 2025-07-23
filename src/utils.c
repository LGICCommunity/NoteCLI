#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <time.h>
#include <sys/stat.h>
#include "../include/utils.h"

void log_error(const char *f, ...) { va_list a; va_start(a,f); fprintf(stderr,"\033[1;31mError: "); vfprintf(stderr,f,a); fprintf(stderr,"\033[0m\n"); va_end(a); }
void log_success(const char *f, ...) { va_list a; va_start(a,f); fprintf(stdout,"\033[1;32m"); vfprintf(stdout,f,a); fprintf(stdout,"\033[0m\n"); va_end(a); }

char *read_user_input(void) {
    char *b = malloc(MAX_INPUT_SIZE); if (!b) return 0;
    size_t t = 0; char tmp[1024];
    while (fgets(tmp,1024,stdin)) { size_t l=strlen(tmp); if (t+l>=MAX_INPUT_SIZE) { free(b); return 0; } strcpy(b+t,tmp); t+=l; }
    if (!t) { free(b); return 0; } return b;
}

bool is_valid_filename(const char *f) {
    if (!f||!*f||strstr(f,"..")) return 0;
    for (;*f;f++) if (!isalnum(*f)&&*f!='.'&&*f!='-'&&*f!='_') return 0;
    return 1;
}

void trim_whitespace(char *s) {
    if (!s) return;
    char *e=s+strlen(s)-1; while(e>s&&isspace(*e)) *e--=0;
    char *st=s; while(*st&&isspace(*st)) st++;
    if(st!=s) memmove(s,st,strlen(st)+1);
}

char *get_timestamp_string(void) {
    time_t n=time(0); struct tm *t=localtime(&n); char *ts=malloc(32); if(!ts) return 0;
    strftime(ts,32,"%Y%m%d_%H%M%S",t); return ts;
}

bool ensure_versions_dir(void) {
    struct stat st={0};
    return stat(VERSIONS_DIR,&st)==-1 ? mkdir(VERSIONS_DIR,0755)!=-1 : 1;
}

bool ensure_logs_dir(void) {
    struct stat st={0};
    return stat(LOGS_DIR,&st)==-1 ? mkdir(LOGS_DIR,0755)!=-1 : 1;
}

const char *get_operation_name(operation_type_t o) {
    switch(o){case OP_CREATE:return"CREATE";case OP_READ:return"READ";case OP_UPDATE:return"UPDATE";case OP_DELETE:return"DELETE";default:return"UNKNOWN";}
}

bool log_operation(operation_type_t o,const char*c,const char*f) {
    if(!ensure_logs_dir())return 0;
    time_t n=time(0); struct tm *t=localtime(&n); char ts[32];
    strftime(ts,32,"%Y-%m-%d %H:%M:%S",t);
    FILE*h=fopen(HISTORY_FILE,"a"); if(!h)return 0;
    fprintf(h,"[%s] %s: %s/%s\n",ts,get_operation_name(o),c,f);
    fclose(h); return 1;
} 