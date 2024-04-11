#!/bin/bash

# Nom du fichier de sortie
OUTPUT_DUMP=".dump"
OUTPUT_CTU=".ctu-info"
OUTPUT_FILE="output.txt"
OUTPUT_PDF="output.pdf"

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

# Boucler à travers chaque fichier .c trouvé
for file in $files; do
    INCREMENT=$((100/TOTAL_FILES))
    CURRENT_PROGRESS=$((CURRENT_PROGRESS+INCREMENT))
    progress_bar "$CURRENT_PROGRESS"
    OUTPUT_FILE="${file}_output.txt"
    OUTPUT_DUMP="${file}.dump"
    OUTPUT_CTU="${file}.ctu-info"
    > "$OUTPUT_FILE"
    # Exécuter les commandes pour chaque fichier .c
    cppcheck --dump "$file"
    python3.9 CI/misra.py "$file.dump" --rule-texts CI/misra_2023.txt 2>> "$OUTPUT_FILE"
    cat $OUTPUT_FILE
    OUTPUT_PDF="${file}_output.pdf" 
    #sed -i 's/\\n/\'$'\n''/g' "$OUTPUT_FILE" 
    #pandoc -f markdown "$OUTPUT_FILE" -o "$OUTPUT_PDF" 2>&1 | tee pandoc_error.log

    #pandoc -f txt "$OUTPUT_FILE" --variable geometry:"a3paper,landscape" -o "$OUTPUT_PDF" 2>&1 | tee pandoc_error.log

    if [ ${PIPESTATUS[0]} -ne 0 ]; then
        echo "Erreur lors de la conversion en PDF. Veuillez consulter le fichier pandoc_error.log pour plus de détails."
        exit 1
    else
        #rm "$OUTPUT_FILE"
        rm "$OUTPUT_DUMP"
        rm "$OUTPUT_CTU"
    fi
done
