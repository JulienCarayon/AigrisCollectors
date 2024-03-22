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

# Vérifier si test-case.c existe
if [ ! -f test-case.c ]; then
    echo "Avertissement: le fichier test-case.c n'existe pas."
else
    # run test-case
    echo "___test-case_________"
    /tmp/misra-c < "$PROJECT_DIR/test-case.c"
fi

# run self
echo "___stdin_____________"
/tmp/misra-c

echo "___end_______________"

rm /tmp/misra-c