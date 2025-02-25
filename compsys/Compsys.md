Programme stocké dans le disque, puis quand lancé est chargé dans la mémoire principale. (memory image). Il y a plusieurs segments :
- text (le code)
- data (stocke les variables globales et static)
- heap (stocke les données persistantes du programme)
- stack (stocke les variables locales et les pointeurs de retour, les arguments de fonctions...)

![[image-2.png|272x349]]

On les construit comme ça pour qu'ils aient une taille dynamique. Quand on veut remplir le stack on fait `addi sp, sp, -4` (on part des adresses hautes vers les adresses basses).

Dans le CPU, le registre `ip` pointe donc vers le text segment.
Et un process est créé (composé de plusieurs threads, un manager, et des worker threads).

Worker threads : p. exemple dans le cas d'un navigateur, un thread chargé de récupérer une image, une vidéo.. Ils sont créés par le main thread. Ils communiquent entre eux à travers la main memory.

Le CPU est **virtualisé** : chaque thread pense qu'il est le seul à s'exécuter (le CPU stocke différents copies des registres, du stack pointeur, du instruction pointeur, pour chaque thread --> on appelle ça le **contexte**). En comparch c'est le multi-threading (on réutilise la même pipeline mais on exécute différents programmes en même temps --> on fait du context switching à chaque fois qu'on exécute un nouveau thread pour maj les registers). Chaque thread a donc son CPU context.

- exemple d'un process qui a deux threads ? --> ils doivent être indépendants

## Lundi 24 février

#### Privilege modes, limited direct execution, kernel/loader

Le CPU stocke le **privilege level** (low/high). Certaines instructions ne peuvent être exécutées qu'en high (aussi appelé kernel mode). Les threads sont lancés en low (user mode).
Le CPU est **interrompu** pour donner une chance à tous les threads de s'exécuter (géré par le OS scheduler).

**Limited direct execution**: limited (en temps et privilèges) mais direct (pas d'unternédiaire entre les instructions et leur exécution).

Qui fait tourner l'OS ? Le même CPU qui fait tourner les threads! d'où l'intérêt du privilege level.

Quand on veut lancer un programme, le **kernel** du système se lance :
- il créé un thread/process
- il initialise l'image mémoire du process (il copie le code du programme dans le text segment, etc.)
- il change le privilege mode du CPU en **low**
- il lance le **loader**

Le **loader** (finit de préparer l'image mémoire du programme, il est en low privilege)
- il charge les arguments du programme dans le stack (pourquoi pas dans **data** ? --> les arguments du programme sont des arguments de la fonction main du progamme, donc considérés comme des variables à mettre sur le stack)

Les **syscall** sont donc utilisés par les threads en low privilege pour exécuter certaines high-privilege instructions. Dans le kernel, il y a un **syscall handler**. 

**Running**: at least one of the process threads is running
**Ready**: no process thread is running
**Blocked**: e.g: waiting for a network message to be received.
quand le kernel tourne pour un syscall exécuté pour un thread, on dit que le thread est running

Limited execution du thread :
- quand il y a une erreur, une exécution illégale (exception/trap) ou un double-clic par exemple, un interrupt est déclenché et est géré par le **interrupt handler** du **kernel**
- si rien ne se passe, il y a toujours le **timer interrupt** qui lance l'OS scheduler toutes les quelques ms (share the CPU fairly)

#### Quand est-ce que les process sont créés ?

Généralement, on passe par des **wrappers** :

direct syscall: 
```c
ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
```
wrapped syscall:
```c
size_t bytes_read = fread(buffer, 1, sizeof(buffer) - 1, file);
```
plus performants.

- `exit` syscall --> ne return jamais, il ferme le process
- `exec` --> mutation, remplace le code du process par le programme qu'on veut exécuter
- `fork` --> clone, créé un jumeau du process en cours (avec le même text segment, etc.). on appelle quand même le process qui l'a créé **parent** et le nouveau **enfant** (même s'ils sont à égalité). `fork` renvoie `0` pour l'enfant et le PID de l'enfant pour le parent.
```c
int fs = fork();
if (fs == 0) {
	// code de l'enfant
} else {
	// code du parent
}
```
- `wait` --> attend que le process enfant soit terminé

le process **init** est exécuté après le démarrage
**shell** est le process parent des commandes exécutées dans le terminal
**GUI** manager process pour les commandes lancées depuis une interface

syscalls --> to access resources from processes **and** to spawn/delete, etc. processes from processes