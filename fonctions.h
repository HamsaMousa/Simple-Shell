#ifndef   	FONCTIONS_H_
#define     FONCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <fcntl.h>

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"


void fonction_pwd();

void fonction_cd(char *path);

void exec(char *argv[]);

void execute_background(int nbargs, char *tableau_arguments[]);

void fonction_pipe(char *tab_args[],int nbargstot);


void redirect(char *tab_args[],int nbargstot);

#endif   


