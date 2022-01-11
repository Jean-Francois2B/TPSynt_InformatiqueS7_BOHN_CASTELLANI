#include "TP1_2.h"

int main(void)
{
	int nbCharCommande, status;
	char commande[TAILLE_MAX_COMMANDE];
	char STATUS[1];
	write(STDOUT_FILENO, BONJOUR, strlen(BONJOUR));
	
	while(1){
		write(STDOUT_FILENO, SHELL, strlen(SHELL));
		nbCharCommande = read(STDIN_FILENO, commande, TAILLE_MAX_COMMANDE);
		//int difference = strncmp("exit",commande,4);
		if(!strncmp("exit",commande,4) || (nbCharCommande == 0)){ //Pour le ctrl+D, cela correspond à un renvoi nul, donc on compare le nombre de caractères à 0.
			write(STDOUT_FILENO, EXIT, strlen(EXIT));
			exit(EXIT_SUCCESS); 
		}
		commande[nbCharCommande-1] = '\0';
		
		int pid = fork();
		if(pid==0){
		//On sait que si pid==0, on est dans le fils. On execute donc la commande
			int retour = execlp(commande, commande,NULL);
			if (retour ==-1){ //Si le programme se passe mal, il faut fermer manuellement le processus fils.
				exit(EXIT_FAILURE);
			}
		}
		else{
		//On sait qu'on est ici dans le père :
			wait(&status);
			if(WIFEXITED(status)){
				write(STDOUT_FILENO, SHELL_EXIT, strlen(SHELL_EXIT));
				STATUS[0] = (WEXITSTATUS(status))+'0';
				write(STDOUT_FILENO, STATUS, 1);
				write(STDOUT_FILENO, SHELL_CLOSE, strlen(SHELL_CLOSE));
			}
			else if(WIFSIGNALED(status)){
				write(STDOUT_FILENO, SHELL_SIGN, strlen(SHELL_SIGN));
				STATUS[0] = (WTERMSIG(status))+'0';
				write(STDOUT_FILENO, STATUS, 1);
				write(STDOUT_FILENO, SHELL_CLOSE, strlen(SHELL_CLOSE));
			}
		}
	}
	exit(EXIT_SUCCESS); 
}









