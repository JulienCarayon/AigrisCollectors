#!/usr/bin/env bash

# Récupérer le répertoire du script
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PROJECT_DIR="$SCRIPT_DIR/"

# Nom du fichier de sortie
OUTPUT_FILE="output.txt"
OUTPUT_PDF="output.pdf"

# Fonction pour afficher la barre de progression
progress_bar() {
    echo "Progression: $1%"
}

# Ajouter les en-têtes
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

# compiler et placer dans le dossier /tmp
echo "___gcc-messages______"
gcc -std=c99 -pedantic main.c -o /tmp/misra-c | zenity --progress --pulsate --auto-close --width=300 --title="Compilation in progress" --text="Compiling MISRA-C code..."

# TODO : Répertoire à examiner (par défaut, le répertoire "/src")
# DIRECTORY_TO_EXAMINE="src"

SRC_DIR="$(dirname "$PROJECT_DIR")/$DIRECTORY_TO_EXAMINE"
# echo "$DIRECTORY_TO_EXAMINE"
# echo "$SRC_DIR"

echo "dans le répertoire $DIRECTORY_TO_EXAMINE"

# Vérifier si le répertoire source existe
if [ ! -d "$SRC_DIR" ]; then
    echo "Erreur: le répertoire source n'existe pas."
    exit 1
fi

# Se déplacer vers le répertoire
cd "$SRC_DIR" || exit 1

echo "dans le répertoire $SRC_DIR"

#liste des fichiers dans le repertoire
FILES=$(find "$SRC_DIR" -type f ! -name '*.pdf' ! -name '*.txt' ! -name '*.log' ! -path "*/FreeRTOS/*")
echo "liste de fichiers $FILES"

if [ -z "$FILES" ]; then
    echo "Aucun fichier trouvé dans le répertoire src."
    exit 1
fi

# Fonction pour ajouter une ligne dans le fichier de sortie
add_to_output() {
    echo "$1" >> "$OUTPUT_FILE"
}

# Nettoyer le fichier de sortie s'il existe déjà
#> "$OUTPUT_FILE"


# Si on est en mode test, tester uniquement le fichier mentionné
echo "Valeur test_mode : $TEST_MODE"
if [ "$TEST_MODE" == "true" ]; then
    echo "test MODE"
    echo "Mode test activé. Testing seulement le fichier $1"
    > "$1_$OUTPUT_FILE"
    /tmp/misra-c < $1 >> "$1_$OUTPUT_FILE"
    echo "___end_______________"

    sed -i 's/\\n/\'$'\n''/g' "$1_$OUTPUT_FILE"

    # TODO :Filtrer les sauts de ligne et afficher les commentaires "//"
    # sed -i -E 's/\\n/\'$'\n''/g; s/\/\/.*$//; s/\/\*.*\*\///' "$1_$OUTPUT_FILE"

    #pandoc -f markdown "$1_$OUTPUT_FILE" -o "$1_$OUTPUT_PDF" 2>&1 | tee pandoc_error.log
    pandoc -f markdown "$1_$OUTPUT_FILE" --variable geometry:"a3paper,landscape" -o "$1_$OUTPUT_PDF" 2>&1 | tee pandoc_error.log

    if [ ${PIPESTATUS[0]} -ne 0 ]; then
        echo "Erreur lors de la conversion en PDF. Veuillez consulter le fichier pandoc_error.log pour plus de détails."
        exit 1
    else
        rm "$1_$OUTPUT_FILE"
    fi
    rm /tmp/misra-c
    exit 0
fi

# le nombre total de fichiers
TOTAL_FILES=$(ls -1 | wc -l)
# Use for debug : echo "ensemble des fichiers : $TOTAL_FILES"

CURRENT_PROGRESS=0
INCREMENT=0

for file in $FILES; do
    echo "fichier : $file"
    echo "___Running misra-c for file: $file"
    INCREMENT=$((100/TOTAL_FILES))
    CURRENT_PROGRESS=$((CURRENT_PROGRESS+INCREMENT))

    progress_bar "$CURRENT_PROGRESS"
    OUTPUT_FILE="${file}_output.txt"
    /tmp/misra-c < "$file" >> "$OUTPUT_FILE"
    
    #Remplacement de "\n" --> saut de ligne
    sed -i 's/\\n/\'$'\n''/g' "$OUTPUT_FILE"
    
    OUTPUT_PDF="${file}_output.pdf"  
    #pandoc -f markdown "$OUTPUT_FILE" -o "$OUTPUT_PDF" 2>&1 | tee pandoc_error.log
    pandoc -f markdown "$OUTPUT_FILE" --variable geometry:"a3paper,landscape" -o "$OUTPUT_PDF" 2>&1 | tee pandoc_error.log

    
    if [ ${PIPESTATUS[0]} -ne 0 ]; then
        echo "Erreur lors de la conversion en PDF. Veuillez consulter le fichier pandoc_error.log pour plus de détails."
        exit 1
    else
        rm "$OUTPUT_FILE"
    fi
    echo "fichier : $file"
done