#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funkcje.h"
#include "struktury.h"

typedef struct node node_t;

int main(int argc, char* argv[])
{
    int in,out;
    if(switches(argc,argv,&in,&out)) //sprawdzenie czy zostaly podlaczone argumenty funkcji
    {
        FILE *fp1;
        fp1=fopen(argv[in],"r");
        if(fp1==NULL) //sprawdzenie czy plik wejsciowy istnieje
        {
            help();
        }
        else
        {
            node_t* proot=calloc(1,sizeof(node_t)); //ustawienie wskaznika na korzen drzewa
            proot=NULL;
            getstart(fp1,&proot); //przejscie do sedna programu //&proot
            if(proot==NULL)//przypadek pustego pliku
                {
                    printf("Plik wejsciowy jest pusty");
                    free(proot);
                    fclose(fp1);
                    return 0;
                }
            FILE *fp2;
            fp2=fopen(argv[out],"w");
            printree(fp2,proot);
            deltree(&proot);
            free(proot);
            fclose(fp1);
            fclose(fp2);
        }
    }
    else
        help();//przypadek niepoprawnych argumentow programu
}
