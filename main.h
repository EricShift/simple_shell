#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <sys/wait.h>

char **populate(char *s, int type);
char *_strdup(char *s);
char *trim(char *s);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);
void process(char **toks, char **env __attribute__((unused)), int *status);
char *pathfinder(char **env);
void addPath(char **command, char **env, int *status);
char *_strduppop(char *s);

#endif
