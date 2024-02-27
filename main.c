#include "fonctions.h"
#include <stdbool.h>
#include <fcntl.h>


#define MAXLINE 200  
#define MAXARGS 20
#define STDIN 0
#define STDOUT 1

bool is_pipe = false;
bool is_redirect = false;
bool background = false;
bool pointvirgule = false;
int nbpointvirgule = 0;

void fonction_terminal()
{
    int nbargs=0;
    char *tableau_arguments[MAXARGS]; 
    char buffer[200];

//DEB RECUPER LES ARGUMENTS DANS UN TABLEAU------------------ 
    char *res=fgets(buffer, 200, stdin); //fgets recupere l'entree clavier + le \n 
    //printf("nb de caractères lus: |%ld| ", strlen(res));
    //printf("buffer: |%s|",buffer);  //LE BUFFER CONTIENT LE \n ATTENTION

//Rapide test pour savoir si le caractère & est présent + au bon endroit
    if(buffer[strlen(res)-2]=='&'){ //car le& doit etre a la fin et decalage des indices car tableau commence a 0
        background=true;
        int nb=0;
        for (int i = 0; i < strlen(res); i++)
        {
            if(buffer[i]=='&'){
                nb++;
            }
        }
        if(nb>1){
            printf("ERREUR: trop de &, attention pour la prochaine fois, il ne doit y avoir qu'un seul & en fin de ligne pour lancer un processus en background");
        }
        //indicebackground=strlen(res)-2;
    }

//Rapide test pour savoir si les caractères ; ou > ou | sont présents
    for (int i = 0; i < strlen(res); i++)
    {
        if(buffer[i]==';'){
            pointvirgule=true;
            nbpointvirgule++;
        }
        if(buffer[i]=='|'){
            is_pipe=true;
            //printf("is_pipe = true %d\n",i);
        }
        if(buffer[i]=='>'){
            is_redirect=true;
            //printf("is_redirect = true %d\n",i);
        }
    }
    const char *separateurs=" \t\n";
    const char *separateursbck=" &\t\n"; //pour le background, on va chercher le & en plus et le supprimer 

    if(background){
        char * token=strtok(buffer,separateursbck);
        int i=0;
        while (token!=NULL)
        { 
            nbargs=nbargs+1;                            //si on est rentré alors on a trouvé un argument 
            tableau_arguments[i]=token;                 //si l'ancien token n'était pas nul = on a bien trouvé qql chose, on met l'argument dans le tableau
            //printf("%s\n",token);                     //pour deboggage
            //printf("%s\n", tableau_arguments[i]);     //pour deboggage
            token=strtok(NULL,separateursbck);             //on passe au token suivant
            i++;
        }
    }
    else{
        char * token=strtok(buffer,separateurs);
        int i=0;
        while (token!=NULL)
        { 
            nbargs=nbargs+1;                            //si on est rentré alors on a trouvé un argument 
            tableau_arguments[i]=token;                 //si l'ancien token n'était pas nul = on a bien trouvé qql chose, on met l'argument dans le tableau
            //printf("%s\n",token);                     //pour deboggage
            //printf("%s\n", tableau_arguments[i]);     //pour deboggage
            token=strtok(NULL,separateurs);             //on passe au token suivant
            i++;
        }
    }
    
    // for(int i=0;i<nbargs;i++){
    //     printf("[%s]",tableau_arguments[i]);
    // }
    // printf("  nbargs: %d\n",nbargs);


//DEB GESTION DES COMMANDES------------------
    if(background){
        execute_background(nbargs, tableau_arguments);
        background=false; //remise a false pour la prochaine commande
    }
    else if (nbargs > 0 && strcmp(tableau_arguments[0],"pwd")==0)
    {
        fonction_pwd();
    }
    else if (nbargs > 0 && strcmp(tableau_arguments[0],"cd")==0)
    {
        //tableau_arguments[1] contient le chemin
        fonction_cd(tableau_arguments[1]);
    }
    else if ( nbargs > 0 && ( (strcmp(tableau_arguments[0], "exit")==0) || (strcmp(tableau_arguments[0], "Exit")==0) ))
    {
        exit(0);
    }
    else{
        tableau_arguments[nbargs]=NULL;
        if (is_pipe) {
            fonction_pipe(tableau_arguments,nbargs);
            is_pipe =false;
        }
        else if (is_redirect) {
            redirect(tableau_arguments,nbargs);
            is_redirect =false;
        }
        else{
            exec(tableau_arguments);
        }
    }
}




int main(int argc, char *argv[])
{
    //DEFINITION DES VARIABLES DE STOCKAGE
        char* username = getenv("USER");

    //BOUCLE PRINCIPALE
        while (1) {
            if (argc < 2){
                printf(ANSI_COLOR_GREEN "\n%s@os:" ANSI_COLOR_RESET,username);
                printf(ANSI_COLOR_BLUE "%s"ANSI_COLOR_RESET,getcwd(NULL,0)); 
                printf("$ ");
            }
            fflush(stdout); /* flush from output buffer to terminal itself */
            
            fonction_terminal();
        }



        return 0;
}    
