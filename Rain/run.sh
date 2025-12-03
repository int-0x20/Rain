#!/bin/bash

PS3='What do you want to do?'
options=("Compile" "Run" "Clean" "All" "Quit")
select opt in "${options[@]}"
do
    case $opt in
        "Compile")
            make && make iso
            ;;
        "Run")
            qemu-system-x86_64 -cdrom kernel.iso
            ;;
        "Clean")
            make clean
            ;;
        "All")
            make clean && make && make iso && qemu-system-x86_64 -cdrom kernel.iso && make clean
            break
            ;;
        "Quit")
            break
            ;;
        *) echo "invalid cohice";;
    esac
done
