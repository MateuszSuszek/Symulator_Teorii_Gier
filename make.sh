#!/bin/bash
#Skompiluj projekt Symulator Gier

gcc -o SG main.c nim.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
