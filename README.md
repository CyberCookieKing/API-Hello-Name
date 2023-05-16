# API Hello Name

Ce code implémente un serveur API simple utilisant la bibliothèque libmicrohttpd. Le serveur est disponible sur le port 8080 et répond à une requête POST sur l'URL "/hello" avec le paramètre "name" en renvoyant un message "Hello" suivi du paramètre "name" s'il est présent, sinon le serveur renvoie "Hello unknown".

## Installation

Il est nécessaire d'installer la bibliothèque libmicrohttpd-dev pour pouvoir compiler et exécuter ce code. L'installation peut être effectuée avec la commande suivante :

```bash
apt install libmicrohttpd-dev
```

## Compilation

La compilation peut être effectuée avec la commande suivante :

```bash
gcc -o api api.c -lmicrohttpd
```

## Utilisation

Pour lancer le serveur, il suffit d'exécuter l'exécutable "api". Le serveur sera disponible sur le port 8080. Lorsqu'une requête POST est reçue sur l'URL "/hello" avec le paramètre "name", le serveur répondra avec "Hello" et le paramètre "name" s'il est présent, sinon il répondra avec "Hello unknown".
