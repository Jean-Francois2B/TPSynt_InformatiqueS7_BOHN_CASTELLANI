#include "TP1_2.h"

int main(void)
{
	int nbCharCommande, status;
	char commande[TAILLE_MAX_COMMANDE];
	write(STDOUT_FILENO, BONJOUR, strlen(BONJOUR));
	
	while(1){
		write(STDOUT_FILENO, SHELL, strlen(SHELL));
		nbCharCommande = read(STDIN_FILENO, commande, TAILLE_MAX_COMMANDE);
		
		if(!strncmp("exit",commande,4) || (nbCharCommande == 0)){ //Pour le ctrl+D, cela correspond à un renvoi nul, donc on compare le nombre de caractères à 0.
			write(STDOUT_FILENO, EXIT, strlen(EXIT));
			exit(EXIT_SUCCESS); 
		}
		commande[nbCharCommande-1] = '\0'; //On met le \0 ici pour ne pas altérer le fonctionnement du ctrl+D qui doit renvoyer un signal null.
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
		}
	}
	exit(EXIT_SUCCESS); 
}
