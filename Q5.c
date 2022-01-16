#include "TP1_2.h"

int main(void)
{
	int nbCharCommande, status;
	struct timespec tempsDebut, tempsFin;
	float tempsExecution; //Temps en mS
	char commande[TAILLE_MAX_COMMANDE];
	char information[TAILLE_MAX_INFORMATIONS];
	write(STDOUT_FILENO, BONJOUR, strlen(BONJOUR));
	
	while(1){
		write(STDOUT_FILENO, SHELL, strlen(SHELL));
		nbCharCommande = read(STDIN_FILENO, commande, TAILLE_MAX_COMMANDE);
		if(!strncmp("exit",commande,4) || (nbCharCommande == 0)){ //Pour le ctrl+D, cela correspond à un renvoi nul, donc on compare le nombre de caractères à 0.
			write(STDOUT_FILENO, EXIT, strlen(EXIT));
			exit(EXIT_SUCCESS); 
		}
		commande[nbCharCommande-1] = '\0';

		clock_gettime(CLOCK_REALTIME,&tempsDebut); //On mesure le temps juste avant d'entrer dans le processus fils
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
			clock_gettime(CLOCK_REALTIME,&tempsFin); //On mesure le temps juste après la fin de l'exécution du processus fils
			tempsExecution = (tempsFin.tv_nsec-tempsDebut.tv_nsec)/1000000; //On obtient un temps en secondes qu'on convertit en millisecondes
			if(WIFEXITED(status)){
				write(STDOUT_FILENO, SHELL_EXIT, strlen(SHELL_EXIT));
				sprintf(information, "%d|%.2f ms", WEXITSTATUS(status), tempsExecution); //On stocke les données de exit et du temps dans le tableau informations.
				write(STDOUT_FILENO, information, strlen(information));
				write(STDOUT_FILENO, SHELL_CLOSE, strlen(SHELL_CLOSE));
			}
			else if(WIFSIGNALED(status)){
				write(STDOUT_FILENO, SHELL_SIGN, strlen(SHELL_SIGN));
				sprintf(information, "%d|%f ms", WEXITSTATUS(status), tempsExecution); //On stocke les données du signal et du temps dans le tableau informations.
				write(STDOUT_FILENO, information, strlen(information));
				write(STDOUT_FILENO, SHELL_CLOSE, strlen(SHELL_CLOSE));
			}
		}
	}
	exit(EXIT_SUCCESS); 
}




