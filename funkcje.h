#ifndef FUNKCJE_H_INCLUDED
#define FUNKCJE_H_INCLUDED

#include <stdbool.h>

#include "struktury.h"

typedef struct node node_t;

bool switches (int argc, char* argv[],int* input, int* output);//funkcja odpowiadajaca za podlaczenie argumentow programu

void help();//funkcja wyswietlajaca pomoc

bool getword(FILE *fp,char *word);//funkcja pobierajaca slowo z pliku

void addtotree(char* word,node_t** proot);//funkcja dodajaca wezel do drzewa

void deltree(struct node** proot);//funkcja usuwajaca drzewo

void printree2(node_t* proot);//funkcja drukujaca drzewo na konsoli

void getstart(FILE *fp,node_t ** proot);//funkcja odpowiadajaca za kolejno: -pobranie slowa, -sprawdzenie jego dlugosci, - w zaleznosci od dlugosci dodania go do drzewa lub przejscia do kolejnego slowa

void printree(FILE* fp,node_t* proot);//funkcja drukuje drzewo do pliku

#endif // FUNKCJE_H_INCLUDED
