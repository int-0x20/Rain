#!/bin/bash

clear

echo "Welcome to Rain build option"

PS3='What do you want to do?'
options=("Compile" "Run" "Clean" "All" "About" "Quit")
select opt in "${options[@]}"
do
    case $opt in
        "Compile")
            clear
            make && make iso
            clear
            ;;
        "Run")
            clear
            qemu-system-x86_64 -cdrom kernel.iso
            clear
            ;;
        "Clean")
            clear
            make clean
            clear
            ;;
        "All")
            clear && make clean && make && make iso && qemu-system-x86_64 -cdrom kernel.iso && make clean && clear
            break
            ;;
        "About")
            clear 
            echo "This is a build option for Rain"
            echo "Rain is a custom OS that is build for tinkerers"
            echo "Rain is a Exokernel-like, it means that the kernel and user program are almost on the same level of privilege
            so be careful about using this OS beacuse one simple mistake in modern OS can be fatal here."            
            ;;
        "Quit")
            clear
            break
            ;;
        *) echo "invalid cohice";;
    esac
done
