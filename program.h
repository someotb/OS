#ifndef PROGRAM_H
#define PROGRAM_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pwd.h>

// Глобальные переменные (extern объявления)
extern char **environ;

// Объявления функций
void print_author_info(void);
void print_env_method1(void);
void print_env_method2(void);
int print_file(const char *filename);
void print_usage(const char *progname);

#endif