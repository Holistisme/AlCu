# AlCu - Jeu de Nim

Un jeu de Nim où vous affrontez une IA qui utilise une stratégie basée sur le modulo 4.

## Clonage du dépôt

```bash
git clone https://github.com/Holistisme/AlCu.git
cd AlCu
```

## Compilation

```bash
make
```

## Utilisation

```bash
# Avec un fichier de map
./alum1 map/easy

# Avec l'entrée standard
./alum1
```

## Règles du jeu

- Le jeu se joue sur plusieurs lignes d'allumettes
- À tour de rôle, chaque joueur retire entre 1 et 3 allumettes de la dernière ligne
- Le joueur qui prend la dernière allumette perd
- L'IA commence toujours

## Maps disponibles

- `map/easy` - Niveau facile (10 lignes)
- `map/medium` - Niveau moyen (12 lignes)
- `map/hard` - Niveau difficile (14 lignes)
- `map/veryhard` - Niveau très difficile (16 lignes)
- `map/impossible` - Niveau quasi-imbattable (18 lignes)

## Stratégie de l'IA

L'IA utilise une stratégie modulo 4 :
- Elle laisse toujours un multiple de 4 sur la ligne actuelle
- Si la ligne précédente est un multiple de 4 ET qu'il reste ≤3 allumettes, elle vide complètement la ligne

## Vérification mémoire

```bash
valgrind --leak-check=full --track-fds=yes ./alum1 map/easy
```
