#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

//Words c'est des pointeurs vers des chaines de caractères
typedef char* Words;

//Dictionary c'est un pointeur vers un ensemble de Words
typedef struct {
    Words *mots;
    int size;
}Dictionary;

typedef struct {
    Words *mots;
    int size;
}Pattern;

//Cree le Dictionary à partir des infos données
//Alloue
Dictionary* createDictionary(FILE* dataFile, unsigned int nbWords, unsigned int wordSize);

//affiche le dictionnaire
void printDictionary(Dictionary* dico, unsigned int nbWords);

//Free les calloc
void freeDico(Dictionary *dico,unsigned int nbWords);

//Crée un pattern brut contenant toutes les chaines à tester à partir des données scannées d'une file
Pattern* createPattern(FILE* dataFile, unsigned int wordSize, unsigned int nbTestCase);

//Crée un nouveau pattern à partir d'une ligne de charactères et les sépare en fonction des "( )"
Pattern *splitUnPattern(char *uneLigne,unsigned int wordSize);

//Sert à afficher le patterBrut fait dans createPattern
void printPatternBrut(Pattern* pattern,unsigned int nbTestCase);

//La fonction prend un caractère en paramètre et renvoie une chaine de caractère correspondante
char* charVersStr(char caractere);

//Concatène deux chaines de char
char* concatenate(const char *s1, const char *s2);


int rechercheNombreOccurrenceUnPatternDansDictionnaire(Dictionary *dico, Pattern *unPattern, int nbWords, int wordSize);

void afficherResultatsTests(Dictionary *dico, Pattern *pattern, unsigned int nbTestCase, unsigned int wordSize, unsigned int nbWords);