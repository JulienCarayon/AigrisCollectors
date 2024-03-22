#!/usr/bin/env bash

# Récupérer le répertoire du script
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PROJECT_DIR="$SCRIPT_DIR/"

echo "___misra-c________________________________________________________"
echo "Répertoire du script : $SCRIPT_DIR"
echo "Répertoire du projet : $PROJECT_DIR"

# Se déplacer vers le répertoire du projet
cd "$PROJECT_DIR" || exit 1

# Vérifier si main.c existe
if [ ! -f main.c ]; then
    echo "Erreur: le fichier main.c n'existe pas."
    exit 1
fi

# compile and put in /tmp folder 
# (tmp folder is wiped at every reboot)
echo "___gcc-messages______"
gcc -std=c99 -pedantic main.c -o /tmp/misra-c | zenity --progress --pulsate --auto-close --width=300 --title="Compilation in progress" --text="Compiling MISRA-C code..."

# Obtenir le répertoire source
SRC_DIR="$(dirname "$PROJECT_DIR")/src"

# Vérifier si le répertoire source existe
if [ ! -d "$SRC_DIR" ]; then
    echo "Erreur: le répertoire source n'existe pas."
    exit 1
fi

# Se déplacer vers le répertoire src
cd "$SRC_DIR" || exit 1
echo "files pour repertoire SRC_DIR : $SRC_DIR"
# Se déplacer vers le répertoire src
# cd "$SRC_DIR" || exit 1

# Afficher la liste des fichiers dans le répertoire src
echo "Liste des fichiers dans le répertoire src :"
ls -l

# Liste des fichiers dans le répertoire src/
#FILES="$SRC_DIR"/*
FILES=$(find "$SRC_DIR" -type f)

# Afficher les fichiers contenus dans $FILES
echo "Contenu de la variable FILES :"
echo "$FILES"

# Si on est en mode test, tester uniquement le fichier main.c
if [ "$TEST_MODE" == "true" ]; then
    echo "Mode test activé. Testing seulement le fichier main.c."
    /tmp/misra-c < main.c
    exit 0
fi

# Si aucun fichier n'est présent dans le répertoire, afficher un message d'avertissement
if [ -z "$FILES" ]; then
    echo "Aucun fichier trouvé dans le répertoire src."
    exit 1
fi

# Calculer le nombre total de fichiers
TOTAL_FILES=$(ls -1 | wc -l)
echo "TOTAL_FILES: $TOTAL_FILES"

# Initialiser la progression
CURRENT_PROGRESS=0
INCREMENT=0


for file in $FILES; do
    #echo "___Running misra-c for file: $file"
     # Increment progress
    INCREMENT=$((100/TOTAL_FILES))
    CURRENT_PROGRESS=$((CURRENT_PROGRESS+INCREMENT))
    # Update progress bar
    echo "$CURRENT_PROGRESS"

    /tmp/misra-c < "$file"
done

# run self
echo "___Running misra-c for self"
/tmp/misra-c

echo "___end_______________"

rm /tmp/misra-c