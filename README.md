# README Shell

Projet shell de ROB4 - 2022-2022 - ALONSO Benito et MOUSA Hamsa

---

Ce Readme présente brièvement les commandes possibles de notre Shell ainsi que les instructions pour le lancer.

# 📂Compilation et lancement du Shell

Pour lancer notre shell, il faut écrire les commandes suivantes dans le terminal :

`$ make`

`$ ./shell`

Pour quitter notre shell, il suffit d’écrire la commande **exit** 

`$ exit`

ou

`$ Exit`

# ⌨️Commandes possibles et explications

Dans le terminal recréé, nous avons essayé de reproduire le plus fidèlement le shell Linux. Nous avons donc à chaque fois le texte suivant qui s’affiche.

![Untitled](README%20Shell%2025d1468364cd478f90ee82540c5a97d1/Untitled.png)

L’utilisateur peut ensuite rentrer les commandes qu’il souhaite.

Pour exécuter les fonctions, il suffit d’écrire le nom de la fonction comme dans un shell normal et saisir les arguments souhaités avec un maximum de 20 arguments par ligne de commande.

## 1. Fonctions de base

Il s’agit des commandes directement exécutées par le shell normal (hors commandes builtin). 

Dans cette première partie de TP, il s’agissait de réussir à exécuter ces commandes avec ou sans arguments.

### 1.1 Exécution de programmes sans arguments au premier plan

Toutes les fonctions classiques sont prise en charge grâce à l’appel execvp.

Parmis les plus utiles il y a par exemple :

```c
$ ls
$ who
$ ps
```

D’autres commandes comme `mkdir` créer un nouveau dossier par exemple ou encore `touch nomdufichier.txt` pour créer un nouveau fichier sont également supportées. 

### 1.2 Fonctions de base avec arguments

On peut compléter les fonctions de base avec des arguments comme `-a` `-l` `-o` `-x`

Exemple: fonction ls avec arguments :

`$ ls -l` 

`$ ls -l -a`

Pour chaque fonction l’argument `--help` permettra également d’afficher l’aide sur l’utilisation d’une commande en particulier.

### 1.3 Builtin

Il s’agit des commandes du shell qui sont directement interprétées par celui-ci. Créer un nouveau processus serait donc inutilement lourds.

Ici elles sont prises en charge avec les fonctions `cd` et `pwd`.

La commande **cd** permet de changer de répertoire en entrant le chemin d'accès du répertoire cible. Par exemple, `$ cd /home/user/documents` permet de se déplacer dans le répertoire documents qui se trouve dans le répertoire user qui se trouve à la racine du système de fichiers.

`$ cd ..` permettra de revenir au répertoire précedent.

La gestion des cas d’erreurs est également faite, si le changement n’est pas possible un message s’affichera.

La commande **pwd** permet d'afficher le chemin d'accès du répertoire courant. Cela peut être utile pour savoir où vous vous trouvez dans le système de fichiers.

## 2. Fonctions avancées

Remarque, les fonctions suivantes ne peuvent pas être combinées par exemple

`$ ls &` et `$ ls | wc` fonctionneront mais `$ ls | wc &` n’est pas pris en charge

### 2.1 Commandes en arrière plan

Le symbole “&” permet de lancer une commande en arrière-plan. Cela signifie que vous pouvez continuer à utiliser votre shell pendant que la commande s'exécute.

Nous avons aussi pris en compte le fait de coller ou non le & aux autres arguments

`$ ls&`

`$ ls &`

Et également lorsqu'il y a plusieurs arguments

`$ ls -a -l&`

`$ ls -a -l &`

Avec les fonctions background, comme dans le vrai terminal, l’utilisateur aura de nouveau la main avec le texte classique avant commande qui s’affichera. 

![Untitled](README%20Shell%2025d1468364cd478f90ee82540c5a97d1/Untitled.png)

Ensuite le résultat de la commande viendra s’ajouter.

Exemple de comportement:

![Untitled](README%20Shell%2025d1468364cd478f90ee82540c5a97d1/Untitled%201.png)

Nb: Les commandes multiples avec arrière plan ne sont pas gérées, comme par exemple `who & ls`

### 2.2 Tuyaux

Le pipe “|” permet de rediriger la sortie standard d'une commande vers l'entrée standard d'une autre commande.

Par exemple, la commande suivante permet de compter le nombre de mots affichés par ls -l :

`$ ls -l | wc`   

Nb: on ne gèrera que le cas avec un seul tuyau de la forme: `commande1 | commande2`

### 2.3 Redirection de stdout

La redirection “>” permet de rediriger la sortie standard d'une commande vers un fichier.Si le nom du fichier saisi ne correspond pas à un fichier existant, alors le fichier sera créer, sinon il sera écrasé.

Par exemple, la commande suivante écrira la liste des fichiers et leurs droits dans le fichier fichier1.txt :

`$ ls -l > fichier1.txt` 

Si on met le mot “echo” en début de commande alors ce qui a été écrit avant le symbole de redirection  “>” sera recopié dans le fichier.

Par exemple, la commande suivante permettra de recopier le mot “bonjourr” dans le fichier fichier1.txt :

`$ echo "bonjourr"> fichier1.txt` 

En faisant un `$ cat fichier1.txt` on obtient alors:

![Untitled](README%20Shell%2025d1468364cd478f90ee82540c5a97d1/Untitled%202.png)

La seule différence avec le vrai comportement est que ici les “ “ sont aussi envoyés dans le fichier1.txt

Pour simplement envoyer bonjour, il suffirait d’écrire:

![Untitled](README%20Shell%2025d1468364cd478f90ee82540c5a97d1/Untitled%203.png)

## 3. Bonus

Ces deux questions n’ont pas étés traitées.