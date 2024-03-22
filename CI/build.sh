#! /usr/bin/env bash

echo "___misra-c________________________________________________________"

# compile and put in /tmp folder 
# (tmp folder is wiped at every reboot)
echo "___gcc-messages______"
#gcc -std=gnu99 main.c -o /tmp/misra-c
gcc -std=c99 -pedantic main.c -o /tmp/misra-c | zenity --progress --pulsate --auto-close --width=300 --title="Compilation in progress" --text="Compiling MISRA-C code..."

# run test-case
echo "___test-case_________"
/tmp/misra-c < ./test-case.c | zenity --info --title="Test case output" --text-info --width=600 --height=400

# run self
echo "___stdin_____________"
/tmp/misra-c | zenity --info --title="Self output" --text-info --width=600 --height=400

echo "___end_______________"

rm /tmp/misra-c

