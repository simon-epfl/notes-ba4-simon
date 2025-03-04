## Lundi 17 février

Programme stocké dans le disque, puis quand lancé est chargé dans la mémoire principale. (memory image). Il y a plusieurs segments :
- text (le code)
- data (stocke les variables globales et static)
- heap (stocke les données persistantes du programme)
- stack (stocke les variables locales et les pointeurs de retour, les arguments de fonctions...)

> [!info] variables locales dans le stack ?
> On alloue à toutes les variables locales potentiellement créées par la fonction une place dans le stack -- en les laissant vides, non initialisées -- comme ça on sait que si on a plus de place dans les registres on pourra les stocker/récupérer dans le stack.

![[structure-memory.png|272x349]]

On les construit comme ça pour qu'ils aient une taille dynamique. Quand on veut remplir le stack on fait `addi sp, sp, -4` (on part des adresses hautes vers les adresses basses).

Dans le CPU, le registre `ip` pointe donc vers le text segment.
Et un process est créé (composé de plusieurs threads, un manager, et des worker threads).

Worker threads : p. exemple dans le cas d'un navigateur, un thread chargé de récupérer une image, une vidéo.. Ils sont créés par le main thread. Ils communiquent entre eux à travers la main memory.

Le CPU est **virtualisé** : chaque thread pense qu'il est le seul à s'exécuter (le CPU stocke différents copies des registres, du stack pointeur, du instruction pointeur, pour chaque thread --> on appelle ça le **contexte**). En comparch c'est le multi-threading (on réutilise la même pipeline mais on exécute différents programmes en même temps --> on fait du context switching à chaque fois qu'on exécute un nouveau thread pour maj les registers). Chaque thread a donc son CPU context.

- exemple d'un process qui a deux threads ? --> ils doivent être indépendants

> [!info] Que partagent les threads d'un même process ?
> Chaque thread a son propre stack, son propre CPU context (c'est-à-dire, ses propres registres, son propre stack) mais ils partagent le même text segment, data segment, heap..

## Lundi 24 février

#### Privilege modes, limited direct execution, kernel/loader

Le CPU stocke le **privilege level** (low/high). Certaines instructions ne peuvent être exécutées qu'en high (aussi appelé kernel mode). Les threads sont lancés en low (user mode).
Le CPU est **interrompu** pour donner une chance à tous les threads de s'exécuter (géré par le OS scheduler).

**Limited direct execution**: limited (en temps et privilèges) mais direct (pas d'intermédiaire entre les instructions et leur exécution).

Qui fait tourner l'OS ? Le même CPU qui fait tourner les threads! d'où l'intérêt du privilege level.

Quand on veut lancer un programme, le **kernel** du système se lance :
- il créé un thread/process
- il initialise l'image mémoire du process (il copie le code du programme dans le text segment, etc.)
- il change le privilege mode du CPU en **low**
- il lance le **loader**

Le **loader** finit de préparer l'image mémoire du programme, il est en low privilege :
- il charge les arguments du programme dans le stack (pourquoi pas dans **data** ? --> les arguments du programme sont des arguments de la fonction main du progamme, donc considérés comme des variables à mettre sur le stack)

Les **syscall** sont donc utilisés par les threads en low privilege pour exécuter certaines high-privilege instructions. Dans le kernel, il y a un **syscall handler**. Il y a donc un context switch en cas de syscall pour que le kernel passe en exécution.

**Running**: au moins un des threads du process est running
**Ready**: aucun thread du process est running
**Blocked**: il ne peut pas run tant qu'un évènement arrive comme un message réseau reçu
quand le kernel tourne pour un syscall exécuté pour un thread, on dit que le thread est running
--> attention, un thread **ne passe pas en blocked dès qu'un syscall est fait** ! si un syscall n'est pas bloquant (accès à du stockage ou au réseau par exemple), alors le thread est toujours running (le kernel tourne pour le thread) ! par contre à partir du moment où le kernel fait un appel bloquant (I/O), alors le thread est blocked.

Limited execution du thread :
- quand il y a une erreur, une exécution illégale (exception/trap) ou un double-clic par exemple, un interrupt est déclenché et est géré par le **interrupt handler** du **kernel**
- si rien ne se passe, il y a toujours le **timer interrupt** qui lance l'OS scheduler toutes les quelques ms (share the CPU fairly)
#### Quand est-ce que les process sont créés ?

Généralement, on passe par des **wrappers** :

direct syscall: 
```c
size_t bytes_read = read(fd, buffer, sizeof(buffer));
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
puts("Programme lancé !");
int fs = fork();
if (fs == 0) {
	// code de l'enfant
} else {
	// code du parent
}
```
- `wait` --> attend que le process enfant soit terminé

> [!danger] Subilités du fork
> Le fork reçoit une **copie** de la mémoire du parent (c'est-à-dire qu'il reprend exactement les mêmes valeurs dans les variables mais s'il modifie les variables ou que le parent modifie les variables, ça ne sera pas visible entre eux)
> 
> Le fork démarre exactement de là où il est appelé chez le parent. Dans l'exemple ci-dessus, seul le parent affichera le print, l'enfant non.

le process **init** est exécuté après le démarrage
**shell** est le process parent des commandes exécutées dans le terminal
**GUI** manager process pour les commandes lancées depuis une interface

syscalls --> to access resources from processes **and** to spawn/delete, etc. processes from processes

## Lundi 3 mars

> [!tldr] **Méthode** : comment représenter l'image mémoire d'un programme ?
> 
> On dessine le text segment, le data segment, le heap segment et le stack segment.
> 
> On ajoute le code dans le text segment.
> 
> On ajoute les variables globales dans le `data` segment (c'est-à-dire toutes les variables au dessus du `int main(){}`).
> 
> On ajoute dans le stack :
> - les `return pointer` quand on appelle une fonction (à la ligne +1 de l'appel de la fonction)
> - les variables locales (en `uninitialized` si elles sont plus loin dans la fonction / pas encore initialisées, ou avec leur valeur si elles sont déjà initialisées)

### Convention appeleur/appelé

- le caller doit sauver dans les **saved registers** les valeurs importantes
- le callee doit sauver dans le **stack** les **saved registers** s'il prévoit de les modifier (ou de faire un autre appel de fonction), puis les restaurer dans les **saved registers** avant de `ret`
- le caller doit donner ses arguments via les registres `a0`, `a1`, etc.
- le callee doit renvoyer la valeur de retour 

$arrow$ le callee ne doit **jamais écrire** dans le stack frame du caller ! c'est ce qu'on appelle le  **stack smashing**
### Mémoire entre threads/processes

Chaque process dispose de son propre espace d'adresses virtuelles. Si deux processes référencent la même adresse virtuelle, ils tomberont sur deux adresses physiques différentes !

Si deux threads du même process accèdent à la même adresse virtuelle, ils tomberont sur la même adresse physique ! En effet comme ils n'ont pas les mêmes registers (chacun ont leur propre) -- ils communiquent via la mémoire principale.

Ce qui est **sécurisé** et assure que deux process ne peuvent pas accéder à leurs données entre eux et à la fois une **illusion**, car le process pense qu'il a la mémoire principale pour lui. C'est pour ça qu'on parle de **safe illusion**. 

Une première méthode, c'est que l'OS stocke, pour chaque process une adresse **base** et une adresse **bound**. Ainsi, quand le MMU (Memory Management Unit) reçoit une adresse virtuelle, il vérifie les bounds (c'est-à-dire que $"base" + "input" < "bound"$), et va ensuite faire $"physical" = "base" + "input"$.
L'intérêt avec cette méthode, c'est que l'image mémoire d'un process est **continue** dans la mémoire ! (elle démarre à `start` et finie à `bound`)
### Segmentation et paging : utiliser des chunks continus

On a vu en comparch le **paging**, où chaque chunk (chaque **frame**, c'est-à-dire une série d'adresses physiques, est associé à une page d'un programme). Ces frames ont une taille fixe.

On appelle **segmentation** un système de chunks à taille variable, mais c'est moins utilisé en pratique. C'est par exemple ce qu'on utilise en base and bound.

> [!info] Où se situe le code de l'OS ?
> 
> Le système d'adresses virtuelles nous permettent de toujours mettre le code de l'OS à la même place pour chaque programme (par exemple tout en haut de la range d'adresses virtuelles `0xffff8000`). Ainsi le programme a juste à `jump` jusqu'à `0xffff8000` dans le cas d'un syscall. C'est toujours le même thread qui exécute le code, c'est juste qu'au lieu de lire son code il va lire le code de l'OS.

### Caching

Le cache stocke les valeurs des adresses mémoires accédées recémment ou fréquemment. 
Le CPU passe toujours par le cache pour accéder à la mémoire.

On a souvent plusieurs niveaux de cache (L1, L2, L3.. du plus rapide/petit au plus lent/gros).

Le cache est séparé entre une partie pour les instructions et une partie pour les données (comme ça on est sûr de garder de la place pour les deux types de cache).
