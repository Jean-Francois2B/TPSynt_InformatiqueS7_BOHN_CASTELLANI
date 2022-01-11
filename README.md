# TP de Synthèse – Ensea in the Shell
### BOHN Sébastien & CASTELLANI Jean-François
Tout au long du TP, des constantes sont définies dans le fichier TP1_2.h puis utilisées dans les fichiers Qx.c. Chaque fichier Qx.c correspond à une question de l'énoncé.

---

### Affichage d’un message d’accueil
On commence par afficher un message à l'utilisateur via la ligne de commande :
> 	write(STDOUT_FILENO, BONJOUR, strlen(BONJOUR));

Ici, le programme n'attend rien de l'utilisateur, il se contente d'afficher des messages.

---

### Exécution d'une commande saisie
On récupère la ligne de commande saisie par l'utilisateur via la commande suivante :
> 	nbCharCommande = read(STDIN_FILENO, commande, TAILLE_MAX_COMMANDE);

On créé deux processus via la commande :
>   int pid = fork();

Cela permet d'avoir un processus fils qui exécute la commande souhaitée pendant que le processus père attend la fin du fils pour reprendre la main et continuer l'affichage du Shell.
On fait appel à la fonction souhaitée via la commande :
>   execlp(commande, commande,NULL);

---

### Gestion de la sortie du Shell
La sortie du Shell se fait avec les commandes “exit” ou "CTRL+D".
On teste si l'une de ces deux commandes est écrite via la commande :
>   if(!strncmp("exit",commande,4) || (nbCharCommande == 0))

La fonction strncmp compare les 4 premiers caractères de "commande" avec "exit" pour voir si le mot "exit" a été écrit. 
Un appui sur la commannde CTRL+D renvoie une chaîne de caractère vide, d'où le second test.
On quitte le Shell via la commande :
>   write(STDOUT_FILENO, EXIT, strlen(EXIT));
        exit(EXIT_SUCCESS); 
    

---
### Affichage du code de retour/de signal d'une commande
La récupération du code de retour ou du signal se fait dans le processus père. On modifie donc uniquement ce code par rapport à la question Q3.c.
Les commandes "WIFEXITED(status)" et "WIFSIGNALED(status)" permettent de savoir respectivement si le processus fils s'est fini normalement, ou à cause d'un signal.
On test donc ces deux possibilités :
>   if(WIFEXITED(status));
>>   else if(WIFSIGNALED(status));

On récupère la donnée sur le premier caractère du tableau STATUS via la commande :
>   STATUS[0] = (WEXITSTATUS(status))+'0'; 

Ou
>   STATUS[0] = (WTERMSIG(status))+'0';





