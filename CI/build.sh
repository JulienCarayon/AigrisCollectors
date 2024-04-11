#!/bin/bash

# Nom du fichier de sortie
OUTPUT_DUMP=".dump"
OUTPUT_CTU=".ctu-info"
OUTPUT_FILE="_MISRA.txt"

# Fonction pour afficher la barre de progression
progress_bar() {
    echo "Progression: $1%"
}
# Vérifier si le répertoire existe
if [ ! -d "$DIRECTORY_TO_EXAMINE" ]; then
  echo "Le répertoire spécifié n'existe pas."
  exit 1
fi

# Récupérer la liste des fichiers .c dans le répertoire spécifié
files=$(find "$DIRECTORY_TO_EXAMINE" ! -name '*.pdf' ! -name '*.txt' ! -name '*.log' ! -path "*/FreeRTOS/*" -name "*.c")
echo "liste de fichiers $files"

# le nombre total de fichiers
TOTAL_FILES=$(ls -1 | wc -l)
# Use for debug : echo "ensemble des fichiers : $TOTAL_FILES"

CURRENT_PROGRESS=0
INCREMENT=0
NEEDS_MODIFICATION=false
# Boucler à travers chaque fichier .c trouvé
for file in $files; do
    INCREMENT=$((100/TOTAL_FILES))
    CURRENT_PROGRESS=$((CURRENT_PROGRESS+INCREMENT))
    progress_bar "$CURRENT_PROGRESS"
    OUTPUT_FILE="${file}_MISRA.txt"
    OUTPUT_DUMP="${file}.dump"
    OUTPUT_CTU="${file}.ctu-info"
    > "$OUTPUT_FILE"
    # Exécuter les commandes pour chaque fichier .c
    cppcheck --dump "$file"
    python3.9 CI/misra.py "$file.dump" --rule-texts CI/misra_2023.txt 2>> "$OUTPUT_FILE"
    cat $OUTPUT_FILE

    if grep -q "Required" "$OUTPUT_FILE"; then
        echo "Le fichier $file nécessite des modifications selon les règles MISRA."
        NEEDS_MODIFICATION=true
    fi
    rm $OUTPUT_DUMP
    rm $OUTPUT_CTU
done

if [ "$NEEDS_MODIFICATION" == "true" ]; then
    echo ""
    echo "TEST KO :"
    echo "Les fichiers suivants nécessitent des modifications selon les règles MISRA :"
    for file in $files; do
        if grep -q "Required" "${file}_output.txt"; then
            echo "$file"
        fi
    done
    exit 1
else
    echo ""
    echo "TEST OK :"
    echo "Aucun fichier ne nécessite de modifications selon les règles MISRA."
    exit 0
fi