#!/bin/bass

gcc main.c `pkg-config python-3.10 --cflags` -lpython3.10

