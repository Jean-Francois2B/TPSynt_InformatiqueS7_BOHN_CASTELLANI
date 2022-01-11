#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <stdio.h>


#define TAILLE_MAX_COMMANDE 32

#define BONJOUR "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"
#define SHELL "enseash % "
#define EXIT "Bye bye ...\n"
#define SHELL_EXIT "enseash [exit:"
#define SHELL_SIGN "enseash [sign:"
#define SHELL_CLOSE "] %"
