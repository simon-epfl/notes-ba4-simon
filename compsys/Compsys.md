## Lundi 17 février

Programme stocké dans le disque, puis quand lancé est chargé dans la mémoire principale. (memory image). Il y a plusieurs segments :
- text (le code)
- data (stocke les variables globales et static)
- heap (stocke les données persistantes du programme)
- stack (stocke les variables locales et les pointeurs de retour, les arguments de fonctions...)

> [!info] variables locales dans le stack ?
> On alloue à toutes les variables locales potentiellement créées par la fonction une place dans le stack -- en les laissant vides, non initialisées -- comme ça on sait que si on a plus de place dans les registres on pourra les stocker/récupérer dans le stack.

![[assets/structure-memory.png]]

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
> 
> Le fork reçoit aussi une copie de la file descriptor table du parent.

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
### Segmentation et paging : utiliser des chunks continus

On appelle **segmentation** un système de chunks à taille variable, peu utilisé en pratique. C'est par exemple ce qu'on utilise en base and bound. 
L'intérêt avec cette méthode, c'est que l'image mémoire d'un process est **continue** dans la mémoire ! (elle démarre à `start` et finie à `bound`). Elle nécessite aussi un hardware simple.
Problèmes : **external fragmentation**, des trous de mémoire inutilisables apparaissent entre les segments. Si un segment doit s'agrandir mais qu'un autre le bloque, il faut le déplacer, ce qui est coûteux.

On a vu en comparch le **paging**, où chaque chunk (chaque **frame**, c'est-à-dire une série d'adresses physiques, est associé à une page d'un programme). Ces frames ont une taille fixe. L'intérêt c'est qu'on a pas besoin d'une range d'adresses continue en mémoire. On peut redimensionner facilement la mémoire en allouant et désallouant des pages/frames. (c'est de la **fragmentation interne** -- il y a des petits trous au sein des frames allouées parce que si on veut stocker 6Kib on est obligés de prendre un segment de 8Kib par exemple si c'est la taille des frames).

> [!info] Où se situe le code de l'OS ?
> 
> Le système d'adresses virtuelles nous permettent de toujours mettre le code de l'OS à la même place pour chaque programme (par exemple tout en haut de la range d'adresses virtuelles `0xffff8000`). Ainsi le programme a juste à `jump` jusqu'à `0xffff8000` dans le cas d'un syscall. C'est toujours le même thread qui exécute le code, c'est juste qu'au lieu de lire son code il va lire le code de l'OS.

![[image-16.png|236x284]]
### Caching

Le cache stocke les valeurs des adresses mémoires accédées recémment ou fréquemment. 
Le CPU passe toujours par le cache pour accéder à la mémoire.

On a souvent plusieurs niveaux de cache (L1, L2, L3.. du plus rapide/petit au plus lent/gros).

Le cache est séparé entre une partie pour les instructions et une partie pour les données (comme ça on est sûr de garder de la place pour les deux types de cache).

## Mercredi 5 mars

#### Rappel sur les pages

Une page est l'unité minimale d'un espace d'adresse (elle doit être suffisamment petite pour éviter la fragmentation interne). On créé aussi des **super pages**, qui sont des aggrégations de plusieurs pages/frames ensemble.

L'OS maintient une **page table** pour garder le mapping entre les pages et les frames. Il y a une table par process.

![[image-18.png|450x196]]

Si on a une page de taille $2^8$, on a donc un offset de $8$ bits.

Il y a un registre spécial qui stocke un pointeur vers la page table.
Lors d'un context switch, le registre qui stocke le pointeur vers la page table est changé aussi.

**PTE (Page table entry)**

Chaque entrée dans la page table contient un numéro de frame mais aussi... :
- present bit (_indique si la page est en RAM ou swap, si absent → page fault_)
- protection bit (_définit les permissions : lecture/écriture/exécution_)
- User / Supervisor bit (_contrôle si l'accès est réservé au kernel ou autorisé à l’utilisateur_)
- Dirty (_indique si la page a été modifiée et doit être écrite sur disque avant d’être remplacée_)
- Access/Reference bit (_marque si la page a été récemment utilisée, utile pour l’algorithme de remplacement_)

En comparch on a vu que les page tables étaient **linéaires**. Si une PTE fait 4B, et qu'on a des adresses virtuelles de 32 bits dont 12 bits pour l'offset --> on a 20 bits pour les entries donc $2^20$ PTE donc $2^20 dot 4B$ pour la table.

Si on veut accéder à la PTE de la page 6, on fait $"pageTable"[6 * 4 B]$.

Problème : les **page tables prennent trop de place** ! La solution serait de créer des pages plus grandes ? mais on augmente la fragmentation interne !

Une solution est de créer des **multi-level page table**

![[image-19.png|452x238]]

Comme ça, pas besoin de créer les tables inutiles !

**TLB (translation lookaside buffer)** est un cache des adresses virtuelles récemment converties (le CPU va toujours voir dans le TLB. s'il y a un TLB miss, on doit faire tout le travail d'aller dans chaque niveau de page table avec le MMU)
Le TLB n'est pas dans la mémoire, c'est du hardware.

Certaines pages non utilisées sont stockées sur le disque (temporairement), et quand l'OS les charge il y a une page fault, puis il les fait revenir dans la mémoire principale.

## Mercredi 12 mars

On a des blocks dans un appareil de stockage (par exemple, un bloc est un stockage de 4Kb de SSD, c'est la plus petite unite sur laquelle on peut écrire). On veut arriver à gérer ces blocks de façon efficace, c'est-à-dire gérer les modifications et lectures concurrentes par exemple (+ stocker des metadata, un nom de fichier, des permissions, un propriétaire, etc).

| Les différents layers                                                                                                                                                            |
| -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Application                                                                                                                                                                      |
| Library (`fopen`, `fread`, `fwrite`, `fseak`, etc. voir `man 3 fread`) qui appellent des commandes Unix/Linux au moyen de **syscalls** (`open`, `write`, etc. voir `man 2 read`) |
| File System                                                                                                                                                                      |
| Physical device                                                                                                                                                                  |
On peut utiliser `strace ./a.out` pour voir tous les calls faits par le programme C `a`!

### Fichiers

![[image-23.png]]

- L'humain/utilisateur voir le fichier comme un **chemin**, une chaîne de caractères. Chaque nom local est unique en local, et chaque chemin complet est unique globalement. L'OS voit le fichier comme un tableau de bytes (untyped files). Il se fiche et n'a aucune connaissance sur le format du fichier (c-a-d que l'extension dans le nom ne compte pas).

- L'OS voit le fichier comme un inode. Un inode ID est assigné à chaque fichier et est unique **au sein du file system**. Il est recyclé après supression du fichier. Le inode contient les permissions, la taille, le nombre d'accès, la position des blocks de données, etc. Chaque fichier a exactement un inode.

> [!info] On peut accéder aux inodes des fichiers/dossiers en utilisant `ls -lih`

#### Comment le file system gère les inodes ?

Il y a une partie du disque réservée au stockage de la inode table (comme une page table linéaire). 

![[image-24.png|494x422]]
#### Comment passer d'un path à un inode ?

Le **inode** ne stocke **pas** le nom du fichier. En fait c'est le dossier (un fichier spécifique) qui stocke ça. Ils sont marqués avec un flag spécial pour les distinguer des fichiers normaux. 

> [!example] Par exemple, si on veut accéder à `/tmp/test.txt` :
> 
> ![[image-25.png|284x253]]
> 
> On sait que le inode de `/` est à la position `0` dans la `inode_tables`.  On y trouve la référence vers les données de `/` ("location"). Quand on regarde dans les données de `/`, on trouve les références des inodes des dossiers et fichiers stockés dans `/`. On va à la `inodes_table[2]` puis on trouve la référence vers les données de `/tmp` ! et ensuite on charge les données et on trouve `Hello world`!

Les inodes ont toujours la même taille, que ce soit pour un fichier, pour un dossier, etc. 
#### Bits de permission

Les neufs caractères après `d` ou `.` sont les bits de permission.
- `rwx` pour propriétaire, groupe, tout le monde
	- Owner can read and write; group and others can just read
	- `x` set on a file means that the file is executable
	- `x` set on a directory: user/group/others are allowed to cd to that directory

#### Références vers des fichiers (links)

Si on fait un **hard-link**, on va lier le nouveau nom au même inode que le fichier original. Si on supprime le nouveau nom, on ne va pas supprimer le fichier (l'ancien pointera toujours vers le inode).

Si on fait un **soft-link** (lien symbolique), on va mapper logiquement le nouveau nom de fichier au fichier cible. Ce nouveau fichier aura un nouvel inode. 

> [!info] Le inode contient une propriété qui est le **nombre de références**.
> 
> Si le nombre de références atteint 0, le inode du fichier est supprimé. Dans le cas d'un hard-link, le nombre de référence est augmenté de 1 quand créé (et diminué de 1 quand supprimé), mais pas dans le cas d'un soft-link.
### Vue du process : file descriptors

On peut tout faire avec les chemins des fichiers + un inode/device IDs (pour savoir où trouver la inode table, puis que chercher dans la table) mais c'est très long! on doit faire tout le chemin à chaque fois.

C'est pour ça qu'on stocke le inode final du fichier dans une sorte de cache par process (**file descriptor table**). C'est une table linéaire qui stocke la liste des fichiers ouverts par process. Elle stocke aussi l'offset de lecture dans chaque fichier ("là où on en est").

![[image-26.png|373x313]]

Les trois premières entrées sont réservées au STDIN, STDOUT et STDERR.
Si on lit 23 bytes de `out.txt`, l'offset du fichier est augmentée.
Le 3 est stocké dans le `fd1`.

Si on réouvre le même fichier, un nouveau file descriptor est créé.

> [!tip] On peut ouvrir les fichiers avec des **FLAGS**
> 
> - `O_RDONLY` : ouvre le fichier en lecture seule
> - `O_RDWR` : ouvre le fichier en lecture et écriture
> - `O_CREAT` : ouvre le fichier et le créé s'il n'existe pas déjà
> - `O_TRUNC` : ouvre le fichier, et s'il existe déjà, le vide (il est donc incompatible avec le flag `O_RDONLY`)
### Mount points

Un système est composé de plusieurs file systems. Par exemple, on peut avoir un disque très rapide pour les tâches du quotidien, un disque plus lent pour les sauvegardes, etc. 

Tous les systèmes de fichiers ont une racine commune, le `/`! Par exemple `/home` peut être un système de fichiers différent.

`mount <device> <directory-to-mount>` 

> [!question] Qu'est-ce qui est stocké `/b/c` est un nouveau file system, `/b` un autre, qu'est-ce qui est stocké dans la inode table de `b`?
> 
> Rien. L'OS va voir qu'il n'existe pas de inode pour `b` donc il va chercher s'il y a un autre file system monté à cet endroit-là.

### Comment implémenter un file system?

Un **disque** est divisé en plusieurs partitions. Le secteur 0 du disque stocke le MBR (master boot record), qui contient :
- le boostrap code (qui est chargé et exécuté par le firmware. le firmware c'est le code qui tourne sur le disque (pour faire tourner la tête de lecture par exemple). C'est une API entre le hardware et l'OS).
- la table de partitions (les adresses de début et de fin de chaque partition)

Le premier bloc de chaque partition a un bloc de boot, qui est chargé.
#### Qu'y a-t-il dans une partition ?

64 blocks, chacun de 4 kb. Certains blocks stockent des données, d'autres des metadonnées.
On peut avoir 5 blocks **i** pour les inodes, un block **d** et **i** pour stocker les blocks libres pour les données et les inodes, et un block **b** pour le boot block et le super block.

> [!info] C'est quoi un superblock ?
> 
> - il stocke le nombre de **inodes**
> - le nombre de **data blocks**
> - où commence la **inode table**
> - il est lu en premier quand on monte le filesystem

![[image-27.png]]

#### Comment allouer un fichier ?

- **contiguous allocation** : tous les bytes de façon continue
	- mais les fichiers ont pas forcément une taille fixe !
	- et de la fragmentation externe !
	- et si on veut accéder au bloc 2, on doit tout traverser !

![[image-36.png]]

- **linked blocks**: on stocke à la fin du bloc le pointeur vers le bloc suivant
	- + pas de fragmentation externe
	- - ça supporte les fichiers de taille dynamique
	- - ça mixe les données et les métadonnées

- **file allocation table** (FAT)
	- - on sépare les données et les métadonnées
	- + on a pas de fragmentation externe
	- + on a besoin que du premier bloc de chaque fichier
	- - **mais...** comme les linked list, poor random access (c'est-à-dire accès au milieu de fichier)
	- - et puis de la **RAM perdue!** (parce que comme la metadata est stocké dans une giga table et qu'on ne veut pas perdre du temps pour trouver les bouts de fichiers, on doit charger la metadata table dans la RAM, c'est énorme ! pour un disque de 1TB on a 1GB de données à stocker dans la RAM!)

![[image-28.png]]

> [!question] Question de série
> 
> A process can insert entries to a directory inode using a write syscall. (Hint: "Look again at slides 32-35 that discuss the file-system interface. According to those slides, how
> does a process add a file to a directory?")
> 
> **Ans** : non, le write syscall ne suffit pas, il faut aussi avoir ouvert le fichier avec l'option `O_CREATE` (créé-le s'il n'existe pas).

## Lundi 17 mars

### Multi-level indexing

- Il y a beaucoup de **petits fichiers** et de temps en temps de gros fichiers. Le inode pointe **directement** les pointeurs vers les data blocks pour gagner du temps et de l'espace mémoire. Car :
	- moins de redirections
	- pas besoin de stocker des tables pour rien !
- **puis**, si les fichiers sont gros, on passe en metadata blocks, un peu comme les multi-level page tables.

Ainsi notre Inode va avoir 12 blocs de direct block, 1 bloc de indirect block, 1 bloc de double indirect block, etc. 

![[image-37.png]]

Ici nos tables intermédiaires stockent 1000 pointeurs vers des data blocks, donc on a 1,000 * 4Kb = 4Mb!

> [!question] Comment allouer un fichier de 5Gb ?
> 
> Si on a fichier de 5Gb, on va donc :
> - allouer les petits blocs verts du début de 48Kb
> - puis ensuite le bloc violet de 4Mb
> - puis le bloc jaune de 4Gb
> - puis comme ce n'est pas assez, le bloc rouge

**Idées clefs :**
- structure d'arbre : efficace pour trouver les blocs
- efficace pour lire en séquence (une fois qu'un bloc indirect est lu, on peut lire 1k blocs de plus !)
- structure fixe : simple à implémenter
- asymétrique : supporte des fichiers petits et gros sans coût supplémentaire

**Avantages/Incovénients :**
- pas de fragmentation externe
- on a simplement besoin de trouver le premier bloc
- performances sont OK
- **mais** il y a des reads supplémentaires pour les blocs indirects
### Lire depuis un fichier

> [!question] 
> 
> - on ouvre le fichier en read only
> - on trouve l'inode de `root`, on lit, on vérifie les permissions, etc, pour trouver l'inode de `cs202`, etc. jusqu'à l'inode du fichier
> - on le lit, on vérifie les permissions, etc, puis on renvoie un fd
>   
> - pour chaque `read()` appelé on lit l'iinode et on lit le bon data block (en fonction de l'offset) puis on modifie le Last Access Time

![[image-38.png|654x387]]
Les `write` sont là pour le Last Access Time.

### Écrire dans un fichier

> [!question] 
> 
> - on va peut-être allouer des nodes en plus ! (l'écriture n'est pas forcément in place). pour ça on doit lire les blocks libres et peut-être modifier l'inode
>   
>  - si on doit créer le fichier, on doit aussi modifier l'inode du dossier ! et si le dossier est plein, on doit aussi allouer plus de data blocks pour lui...

![[image-39.png|628x372]]

- le file system se rend compte avec le read du `cs202/data` que le fichier n'existe pas !
- il va chercher dans le inode bitmap **qui stocke les inode libres**
- il va allouer un nouveau block et modifier la taille du dossier, etc.
- comme le fichier est vide, on veut allouer un block de données
- le fs trouve un data block vide dans le data bitmap, il **écrit** dans le bitmap pour mettre à jour, il écrit **dans** les données, puis il **écrit** dans le inode

(rappel que le bitmap est stocké dans le superblock)

**Comment mesurer la perf ?**
- I/O operations per second (IOPS)
- le débit (throughput)
- la latence
on peut améliorer les perfs avec le **caching** (éviter les ops non nécessaires), ou le **batching** (grouper les opérations pour augmenter le débit, sans doute au prix de la latence)

### Block cache

L'OS et le FS vont allouer une page pour certaines paires `(inode, offset)` dans la mémoire principale et va lire là-bas après. Donc pas de I/O après la première lecture.

Le FS a un buffer cache qui stocke ce page frame number à partir de l'inode et de l'offset.
### Batching operations

Chaque opération I/O a de la latence et peu de concurrence, donc on préfère quelques gros transferts.

Pour ça, on peut essayer de **retarder les write**. Les faire attendre au plus 30 secondes, les réorganiser, etc. mais... le contenu est perdu si l'OS crash !

Où write-through caches --> écrire de façon synchrone, mais il y a des coûts de perf.

### Crash consistency

![[image-40.png]]

On veut écrire `D2`.

- si seul D2 a été écrit c'est **OK**, le write est perdu mais le FS est consistent
- par contre, si le inode est écrit c'est **PAS OK,** car le inode dit que data est utilisé alors que le bitmap dit qu'il est libre !
- si le data bitmap seulement est écrit c'est **PAS OK**, il dit qu'il est pris alors qu'aucun inode ne pointe vers lui

### FSCK (file system checker)

Périodiquement, après un crash ou un certains nombres d'opérations, cet outil va vérifier la consistence du système.

> [!example] Par exemple, le FSCK peut corriger le nombre de liens pointant vers un inode (quand on créé un lien symbolique ou un hard link).

> [!example] Le FSCK peut déplacer TODO lost+found

> [!example] Si deux inodes pointent vers le même block de données (ça ne devrait pas arriver), il peut copier le data block vers un nouveau et modifier le lien.

Problèmes :
- c'est lent
- c'est pas toujours correct (il essaye de retrouver un état consistent, mais est-ce que c'est le **bon** état ? consistency $eq.not$ correctness)

### Journaling (logs)

Objectifs :
- limiter le travail à faire to recover
- obtenir l'état **correct** et non plus seulement l'état consistent
- être plus rapide (plus besoin de scanner tout le disque)

$arrow$ écrire dans le journal **avant** d'écrire dans le disque (**write-ahead** logs)
et écrire ce qu'il y avait avant d'overwrite le contenu d'un fichier

#### Transactions 

Propriétés :
- **atomic** : soit tout fonctionne, soit rien
- **consistent** : amène toujours à un état correct
- **isolée** : opérations n'interagissent pas être elles
- **durable** : une fois qu'elle est complétée, les effets sont persistents

Il peut y avoir deux résultats : un **commit** (la transaction est un succès), un **abort** (elle a échouée, complètement)

![[image-41.png]]

**TxBeg** indique le début de la transaction, **TxEnd** la fin.

![[image-42.png]]


> [!question] mais comment on fait pour le swapping ? on peut pas écrire directement dans les blocks ?
> 
> on crée un fichier pagefile.sys ou qqch de similaire.
## Mercredi 19 mars

Le FS fait des appels IO au disque, l'OS n'a pas à les faire.
Chaque appareil donne au système une API IO d'entrée et de sortie.

Chaque appareil expose un status (busy/read), CMD (ce qu'on veut faire), DTA (lui envoyer des données..).

- à l'intérieur de l'appareil, il y a un micro-controller (avec un CPU, de la RAM, du stockage, des puces custom...)

- l'OS configure l'appareil et communique avec lui au moyen d'un protocole et utilise un **driver**. Le controller de l'appareil envoie des signaux au CPU soit par du **polling** (keep the CPU busy for nothing) ou des **interrupts**.

### CPU communique avec l'appareil

Via **memory-mapped IO** (des instructions load/store). L'OS map l'appareil sur une adresse physique.

avantage :
- supporte tous les appareils

### Paramètres pour l'IO

Certains appareils fonctionnent par **byte** (par exemple le clavier, un caractère par caractère) ou par **block** (par exemple un disque).

Certains appareils permettent uniquement l'accès **séquentiel** (tape), tandis que d'autres permettent l'accès **random** (disques..).

### Interrupts

- les interrupts sont gérés de façon centrale dans un thread dédié de l'OS
- quand l'interrupt arrive, on réveille un thread kernel qui attendait un interrupt

**est-ce que le polling est parfois mieux que l'interrupt ?** oui, par exemple si il y a énormément de paquets qui arrivent en même temps, par exemple plus vite que interrupt handling + context switching. **livelock** -> on ne traite plus rien
donc les systèmes réels utilisent les deux
on peut aussi utiliser du delay and batch pour éviter beaucoup de contexts switch (mais augmente la latence)

### DMA/PIO


Il y a deux moyens d'envoyer des données au controlleur de l'appareil :
- **PIO (programmed IO)** : le CPU envoie les **données** à l'appareil (prend un temps de CPU proportionnel à la taille des données, efficace pour les petits transferts)
- **DMA (direct memory access)** : le CPU dit à l'appareil **où sont les données** (efficace pour les gros transferts, on doit donner l'accès au bus à l'appareil)

#### Fonctionnement du DMA

- le driver de l'appareil (du disque) reçoit une requête pour tranférer des données à l'adresse **X** (via le memory bus)
- le driver dit au disk controller de transférer **C** bytes du disque vers le buffer à l'adresse **X**
- le disk controller commence un DMA transfer
- le disk controller envoie chaque byte au DMA
- le DMA controller transfère chaque byte à l'adresse X augmente l'adresse mémoire, et diminue C jusqu'à ce que C = 0
- quand C = 0, le DMA **interrupt** le CPU pour dire que le transfert est fini

![[image-57.png|262x322]]

### Trop d'appareils...

Challenge : trop d'appareils ont des protocoles différents

Le drive implémente une API. Les appareils similaires (de la même class) utilisent la même API. Le kernel supporte donc quelques APIs, une par classe.
Comment bien designer cette API ?

### Abstraction stack

Les systèmes IO sont accédés par une série de layer d'abstraction.
Par exemple si on charge un block de 16Kb, alors que le disque ne supporte que des blocks de 512, il va split les blocks.

### Storage hierarchy

![[image-58.png]]

Volatile : disparaît quand shut down

**RAID** (redundant array of inexpensive disks)
- meilleur débit (on peut écrire à plusieurs endroits en même temps)
- meilleur MTTF (mean time to failure -- temps avant que le système ne fonctionne plus)

![[image-59.png|309x357]]

**RAID 0** : dans l'exemple ci-dessus, pas de redondance, on fait que du data striping pour un meilleur débit.

![[image-60.png]]

**RAID 1** : bien quand on perd un disque, mais on a qu'un disque, c'est cher, etc. et ça ne gère pas la corruption  

![[image-62.png|384x246]]

**RAID 5** : utilise la parité 
$$P_(i -j) = S_i  xor S_(i + 1) xor ... xor s_j $$
Si un disque meurt, on peut reconstruire les données en xorant les drives restants ! à partir du 2 et du parity 0/2, on peut retrouver le 0. à partir du 0 et du parity 0/2, on peut retrouver le 2, etc.
problème : les write sont un peu compliqués


