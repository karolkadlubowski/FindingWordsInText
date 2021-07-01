#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "funkcje.h"
#include "struktury.h"

typedef struct node node_t;

bool switches (int argc, char* argv[],int* input, int* output)//funkcja odpowiadajaca za podlaczenie argumentow programu
{
    int i;
    for(i=1;i<argc-1;i++)
    {
        if(!strcmp(argv[i],"-i"))
        {
            i++;
            *input=i;
        }
        else if(!strcmp(argv[i],"-o"))
        {
            i++;
            *output=i;
        }
        else
            return false;
    }
    if(i==5)
        return true;
    else
        return false;
}

void help()//funkcja wyswietlajaca pomoc
{
    printf("Wpisz wlasciwe parametry programu:\nprogram.exe -o PLIK WYJSCIOWY -i PLIK WEJSCIOWY");
}

bool getword(FILE *fp,char* word)//funkcja pobierajaca slowo z pliku
{
    int i=0;
    int sign;
    sign=fgetc(fp);
    while(sign!=EOF)//w kazdej iteracji petli pomijane sa znaki inne niz litery
    {
        if(sign>='a' && sign <='z')
            {
                word[i]=sign;
                i++;
            }
        else if(sign>='A' && sign<='Z')
            {
                word[i]=sign+32;
                i++;
            }
        else if(sign==' '||sign=='\n')
            {
                word[i]='\0';
                break;
            }
        sign=fgetc(fp);
        if(sign==EOF && word[i]!='\0')
            word[i]='\0';
    }
    if(feof(fp)&&i==0)
        return false;
    return true;
}

void addtotree(char* word,struct node** proot)//funkcja dodajaca wezel do drzewa
{
    if((*proot==NULL))
    {
        *proot=calloc(1,sizeof(node_t));
        (*proot)->pword=calloc(strlen(word)+1,sizeof(char));
        strcpy(((*proot)->pword),word);
        (*proot)->pleft=NULL;
        (*proot)->pright=NULL;
    }
    else
    {
        if(strcmp(word,(*proot)->pword)<0)
            addtotree(word,&(*proot)->pleft);
        else
            addtotree(word,&(*proot)->pright);
    }
}

void deltree(struct node** proot)//funkcja usuwajaca drzewo
{
    if(*proot!=NULL)
    {
        deltree(&(*proot)->pleft);
        deltree(&(*proot)->pright);
        free((*proot)->pword);
        free(*proot);
        *proot=NULL;
    }
}

void printree2(node_t* proot)//funkcja drukujaca drzewo na konsoli
{
    if(proot!=NULL)
    {
        printree2(proot->pleft);
        printf("%s\n",proot->pword);
        printree2(proot->pright);
    }
}

void getstart(FILE *fp, node_t **proot)//funkcja odpowiadajaca za kolejno: -pobranie slowa, -sprawdzenie jego dlugosci, - w zaleznosci od dlugosci dodania go do drzewa lub przejscia do kolejnego slowa
{
    int i=0;
    int stringlen;
    char word[100];//rezerwacja miejsca na slowo
    while(!feof(fp))
    {
        if(!getword(fp,word))//przypadek pliku pustego
        {
            break;
        }
        stringlen=strlen(word);
        if(i<stringlen)//sprawdzenie dlugosci slowa 
        {
            i=stringlen;//jesli jest dluzsze niz dotychczasowe najdluzsze slowo, dotychczasowe drzewo jest usuwane i tworzone jest nowe z obecnym slowem w korzeniu
            deltree(proot);
            addtotree(word,proot);
        }
        else if(i==stringlen)//jesli slowo jest tej samej dlugosci co obecne najdluzsze slowo, nowe slowo zostaje dodane do drzewa
                addtotree(word,proot);
    }
    printree2(*proot);//drukuje drzewo na konsoli by programista byl w stanie sprawdzic stan programu
}


void printree(FILE* fp,node_t* proot)//funkcja drukuje drzewo do pliku
{
    if(proot!=NULL)
    {
        printree(fp,proot->pleft);
        fprintf(fp,"%s\n",proot->pword);
        printree(fp,proot->pright);
    }
}