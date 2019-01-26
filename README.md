# Yun vs The Yellow K-Pop Gang

Bienvenue à _Yun vs The Yellow K-Pop Gang_ !

Vous assumez le rôle de Yun, un élève-ingénieur très talentueux, capable de lancer de boules de feu, et aussi le pire ennemi de la K-Pop ! Votre mission est de tuer le maximum d'artistes K-Pop et leurs disciplines afin de mettre une fin à cette horreur.

## Comment jouer ?

Utilisez les flèches pour bouger, et appuyez sur `Espace` pour lancer une boule de feu.

Le but est de tuer le maximum d'ennemis en évitant de se faire toucher par leurs boules de feu. Parfois, des boss de la K-Pop vont apparaître... attention ! Les boss meurent pas aussi facilement que les simples disciplines - en plus, ils sont beaucoup plus puissants !

Pour augmenter les capacités physiques de Yun, vous pouvez prendre les Power Up qui laissent derrière les boss une fois qu'ils sont morts.

Pour changer le volume de la musique du jeu ou le niveau difficulté, vous pouvez aller dans le menu "Options".

## Comment installer le jeu ?

C'est très simple ! Il suffit d'avoir une machine avec un OS de type UNIX (Linux ou Mac OS), et de droits d'administrateur (pour pouvoir installer la librairie utilisée par le jeu).

### Installation sur Linux

Pour installer le jeu, il suffit de lancer la commande suivante :

```
$ sudo apt-get install libsfml-dev
```

Puis, il faut compiler le jeu :

```
$ cd yun-vs-the-yellow-kpop-gang
$ make
```

Finalement, vous n'avez qu'à lancer l'exécutable :

```
$ ./yun
```


### Installation sur Mac OS

Pour installer le jeu, il suffit de lancer la commande suivante (via [Homebrew](https://brew.sh/)) :

```
$ brew install sfml
```

Puis, il faut compiler le jeu :

```
$ cd yun-vs-the-yellow-kpop-gang
$ make
```

Finalement, vous n'avez qu'à lancer l'exécutable :

```
$ ./yun
```

## Pourquoi voulez-vous tuer les star de la K-Pop ?

Car ils rendent Yun triste. Personne n'a envie que Yun soit triste. 
