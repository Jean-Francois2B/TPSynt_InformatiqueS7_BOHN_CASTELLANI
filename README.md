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

---

### Gestion de la sortie du Shell
La sortie du Shell se fait avec les commandes “exit” ou "CTRL+D".
On teste si l'une de ces deux commandes est écrite via la commande :
>   if(!strncmp("exit",commande,4) || (nbCharCommande == 0))

