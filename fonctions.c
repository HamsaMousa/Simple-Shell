#include "fonctions.h"
#define MAXARGS 30

void fonction_pwd(){
    fflush(stdin);
    fflush(stdout);

    char buffer[1024];

    if(getcwd(buffer, sizeof(buffer))== NULL)
    {
        fprintf( stderr, "Impossible de récupérer le répertoire de travail\n" );
        printf("%d",errno);
        exit( EXIT_FAILURE );
    }
    printf("Répertoire de travail: %s\n", buffer);
}

void fonction_cd(char *path){
    if(chdir(path)!=0)
    {
        fprintf( stderr, "Impossible de changer de répertoire\n" );
        //printf("%d",errno);
        //exit( EXIT_FAILURE );
    }
    else
    {
        printf("Changement de répertoire effectué\n");
        fonction_pwd(); //affiche le nouveau répertoire courant
    }
    //change le répertoire courant du processus et pas du shell attention
}


void exec(char *argv[]){
	//fflush(stdout); //Effacer les buffers precedents
    pid_t p = fork(); //Creation d'un processus
    
    if(p==-1)
    {
    	printf("Erreur creation processus enfant \n");
    }
    if (p == 0)
    { 
        //Si on est dans le processus enfant
	    //execvp ne permet pas de creer un processus mais de muter un processus
        if(execvp(argv[0],argv)==-1)
        {
        	printf("%s : commande introuvable \n",argv[0]);
        	exit(1);
        }

    }
    else
    {
    	waitpid(p, NULL, 0);
    }
}

void execute_background(int nbargs, char *tableau_arguments[]) {
	pid_t chilpid;
	chilpid = fork();
	//tableau_arguments[nbargs-1]=NULL;
	tableau_arguments[nbargs]=NULL;
	if(chilpid == 0)
    {
		if(-1 == execvp(tableau_arguments[0], tableau_arguments))
        {
			perror("execvp");
			printf("  (could'nt find command)\n");
		}
	}
	return;
}

void fonction_pipe(char *tab_args[],int nbargstot){
	int pipefd[2]; //tableau de descripteurs
	int fd;
	pid_t enfant1,enfant2; 
	
	int i=0; //indice pour le tableau de base tab_args
	int j=0; //indice pour la partie droite apres le symbole "|" de la ligne de commande 
	
	char *argproc1[MAXARGS]; //Tableau contenant la commande ecrite avant le symbole "|"
	char *argproc2[MAXARGS]; //Tableau contenant la commande ecrite apres le symbole "|"
	
	while(strcmp(tab_args[i],"|")){
		argproc1[i]=tab_args[i];
		i++;
	}
	argproc1[i]=NULL;
	
	j=i+1;
	int k=0;
	while(j<nbargstot){
		argproc2[k]=tab_args[j];
		k++;
		j++;
	}
	argproc2[k]=NULL;
	
	//AFFICHAGE POUR TESTER
   	/*for(int l=0;l<i;l++){
   		printf("Premiere partie:");
		printf("%s\n",argproc1[l]);
	}
	
	for(int m=0;m<k;m++){
		printf("Deuxieme partie:");
		printf("%s\n",argproc2[m]);
	} */
	
	if(pipe(pipefd)){ //Sans erreur pipe retourne 0
		perror("Erreur creation pipe");
	}
	enfant1=fork();
	if(enfant1){
		enfant2=fork();
	}
	if(enfant1==0){ //Processus enfant 1 "ls | ..."
		fd=dup2(pipefd[1],STDOUT_FILENO);
		if (fd==-1){
			perror("Erreur dup");
		}
        
        close(pipefd[0]);
		close(pipefd[1]); 
		
		if(execvp(argproc1[0],argproc1)==-1){
        	perror("Erreur execvp");
        }
	}
	
	if (enfant2==0){ //Processus enfant 2 "... | wc"
		fd=dup2(pipefd[0],STDIN_FILENO);
		if (fd==-1){
			perror("Erreur dup");
		}
       		 
		close(pipefd[0]); 
		close(pipefd[1]); //Pas utiliser par l'enfant 2
		
		if(execvp(argproc2[0],argproc2)==-1){
        	perror("Erreur execvp");
       	}
	} 
	else{
		
		close(pipefd[0]);
        close(pipefd[1]);
        
        if (waitpid(enfant1, NULL, 0)==-1 ){
        	perror("waitpid");
        }
        if (waitpid(enfant2, NULL, 0)==-1 ){
        	perror("waitpid");
       	} 
       		
	}
}

//new du 18/12/2022
void redirect(char *tab_args[],int nbargstot){
	int i=0;		//indice pour le tableau de base tab_args
	int j=0;		//indice pour la partie droite apres le symbole "|" de la ligne de commande 
	int indice=0;	//indice de la ou se trouve le symbole dans la chaine de commande 
	int output;
	
	char *argproc1[MAXARGS]; //Tableau contenant la commande ecrite avant le symbole ">"
	char *argproc2[MAXARGS]; //Tableau contenant la commande ecrite apres le symbole ">"
	
	while(strcmp(tab_args[i],">")){ 
		argproc1[i]=tab_args[i];
		i++;
		indice++;
	}
	argproc1[i]=NULL;
	
	j=i+1;
	int k=0;
	while(j<nbargstot){
		argproc2[k]=tab_args[j];
		k++;
		j++;
	}
	argproc2[k]=NULL;
	
	//AFFICHAGE POUR TESTER
   	/*for(int l=0;l<indice;l++){
   		printf("Premiere partie:");
		printf("%s\n",argproc1[l]);
	}
	
	for(int m=0;m<k;m++){
		printf("Deuxieme partie:");
		printf("%s\n",argproc2[m]);
	} */
	
	if(strcmp(tab_args[indice],">")==0){ 
		output=open(argproc2[0],O_RDWR | O_CREAT | O_TRUNC,S_IRWXU | S_IRGRP);
		if(output == -1){
			perror("open");
		}
		pid_t pid = fork();
		if(pid == 0){
			close(STDOUT_FILENO);
			dup2(output,STDOUT_FILENO);
			if(execvp(argproc1[0],argproc1)==-1){
        		perror("Erreur execvp");
       		}
		}
		wait(NULL);
	}
	close(output);
	
}