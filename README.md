# PSAR_simulateur_synchrone
simulateur pour tester des algorithmes reparties sous forme de clause gardé sous une hypothèse synchrone dans un modèle a etat. 

## le simulateur
Ce simulateur a été developpé dans le cadre d'un projet de 1er année de Master en informatique de Sorbonne Université. 

le but est de pouvoir implementer facilement un algorithme ecrit en clause gardé et de pouvoir le tester avec des differentes topologies et configurations de departs. 
Le paradigme est une modèle a etat synchrone, il n'y a donc pas de messages et tout les processus calcule le passage de leurs gardes avant qu'un processus commence a modifier son etat.

### configuration de l'algorithme 
pour adapter le simulateur a un algorithme particulier il faut modifier le fichier clauses.c et clauses.h dans le fichier clauses.c on ajoute le code C correspondant aux guardes et aux clauses de l'algorithme ainsi que mettre a jour le contenu de la structure de connée dans lequels sont stocké les pointeurs de fonctions. le nombre de clauses doit etre declaré en constante dans clauses.h (NBCLAUSE). notre implementations supporte aussi les macros qui sont delcarer de la meme manières. 

### configurations du graphe 
pour connaitre la topologie du graphe et sa configuration initial on a un fichier topo.txt de la forme :

8
0 1 0 0 0 0 0 0
1 0 1 0 1 0 0 0
0 1 0 1 0 1 1 0
0 0 1 0 0 0 1 0
0 1 0 0 0 1 0 1
0 0 1 0 1 0 0 1
0 0 1 1 0 0 0 1
0 0 0 0 1 1 1 0

où la 1er ligne indique le nombre de sommet du graphe et le restre represente un matrice d'adjacence.

et un fichier var.txt de la forme :

8
1
0;7
1;8
2;4
3;3
4;2
5;7
6;0
7;7

ou la 1er ligne reporesente le nombre de sommet, la 2e ligne le nombre de variable par sommet et le reste l'indice du sommet suivit de ses variables (id;var1;var2;...;varN).

### condition d'arret du simulateur et trace d'execution

## exemples 

### exemple_1 

exemple le plus complet les fichiers sont commenté si vous voulez regarder ce que font les fonctions et avoir un exemple d'algorithme implementé. 


### exemple_2 

même code que l'exempl_1 mais avec une topologie et une configuration differentes. cela permet de voir que les seuls fichier a modifiers sont topo.txt et var.txt.

### exemple_3 

algorithme differents de exemple_1 et exemple_2 permet de voir quel modifications apporter a clauses.c et clauses.h pour adapter le programme a n'importe quel nombre de clauses et de macro.