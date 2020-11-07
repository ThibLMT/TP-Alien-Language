#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include "alienLanguage.h"
#include <stdint.h>




Dictionary* createDictionary(FILE* dataFile,unsigned int nbWords,unsigned int wordSize){
	Dictionary *dico = malloc(sizeof(Dictionary));
	dico->mots = calloc(nbWords,sizeof(Words));
	for (unsigned int i = 0; i < nbWords; i++)
	{
		dico->mots[i]= calloc(wordSize,sizeof(char));
		fscanf(dataFile,"%s\n",dico->mots[i]);
	}
	dico->size=wordSize;
	return dico;
}


void printDictionary(Dictionary* dico,unsigned int nbWords){
	for (unsigned int i = 0; i < nbWords ; i++)
	{
		printf("%s\n",dico->mots[i]);
	}
}

//Free l'ensemble du dico
//ça ne marche pas très bien pour une raison obscure
void freeDico(Dictionary* dico,unsigned int nbWords){
	for (unsigned int i = 0; i <nbWords; i++){
		free(dico->mots[i]);
	}
	free(dico->mots);
	free(dico);
}

Pattern* createPattern(FILE* dataFile, unsigned int wordSize, unsigned int nbTestCase){
	Pattern *patternsBruts = malloc(sizeof(Pattern));
	patternsBruts->mots = calloc(nbTestCase,sizeof(Words));
	for (unsigned int i = 0; i < nbTestCase; i++)
	{
		patternsBruts->mots[i] =  calloc(50000,sizeof(char));
		fscanf(dataFile,"%s\n",patternsBruts->mots[i]);
	}
	patternsBruts->size = nbTestCase;
	return patternsBruts;
}

void printPatternBrut(Pattern* pattern,unsigned int nbTestCase){
	for (unsigned int i = 0; i < nbTestCase ; i++)
	{
		printf("%s\n",pattern->mots[i]);
	}
}

char* concatenate(const char *s1, const char *s2) {
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    //test d'erreur du malloc
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

char* charVersStr(char caractere) {
	char *pChar = malloc(2*sizeof(char));
	if(pChar != NULL) {
		pChar[0] = caractere;
		pChar[1] = '\0';
	}
	return pChar;
}



Pattern *splitUnPattern(char *uneLigne,unsigned int wordSize){
	Pattern *pattern = malloc(sizeof(Pattern));
	pattern->mots = calloc(wordSize,sizeof(Words));
	pattern->size = wordSize;
   // printf("%s","DébutFunc\n");
	int i = 0;
	int numToken=0;
	while(uneLigne[i] != '\0'){
		pattern->mots[numToken] = calloc(30,sizeof(char));
		//printf("%s","DébutLecture\n");
		if(uneLigne[i]== '('){
			i++;
			//printf("%s","ParenthèseTrouvée\n");
			//printf("%c\n",uneLigne[i]);

			Words chaineIntermediaire = "";
			
			while (uneLigne[i] != ')') 
			{
				chaineIntermediaire = concatenate(chaineIntermediaire,charVersStr(uneLigne[i]));
				//printf("%c\n",ligneIntermediaire);
				//ligne pour éviter que la ligne suivante nique tout
				//printf("%s","allocToken\n");
				i++;
				
			}
			
			pattern->mots[numToken] = chaineIntermediaire;
			numToken++;
			//printf("%s\n",chaineIntermediaire);
		}		
		else {
			//printf("%c\n",uneLigne[i]);
			pattern->mots[numToken]=  charVersStr(uneLigne[i]);
			numToken++;
		}
		i++;
	}
	//printf("%s\n","Fonction terminée");
	return pattern;

}

int rechercheNombreOccurrenceUnPatternDansDictionnaire(Dictionary *dico, Pattern *unPattern, int nbWords, int wordSize){
int count =0;
	
	for(int i = 0; i<nbWords ;i++){
		int j=0;
		bool OccurrenceDePattern = true;
		while(j<wordSize && OccurrenceDePattern){
			int k =0;
			bool lettreContenu=false;
			while(unPattern->mots[j][k] != '\0' && lettreContenu==false){
				if(dico->mots[i][j]==unPattern->mots[j][k]){
					lettreContenu=true;
				}
				k++;
			}
				
			if (!lettreContenu)
			{
				OccurrenceDePattern=false;
			}
			
			j++;
		}
		if(OccurrenceDePattern){
			count++;
		}
	}
	return count;
}   

void afficherResultatsTests(Dictionary *dico, Pattern *pattern, unsigned int nbTestCase, unsigned int wordSize, unsigned int nbWords){
	
	for(unsigned int i=0; i<nbTestCase; i++){
		Pattern *unPattern =splitUnPattern(pattern->mots[i],wordSize);
		int nbOccurrence = rechercheNombreOccurrenceUnPatternDansDictionnaire(dico,unPattern , nbWords, wordSize);
		printf("Case #%i : %i\n",i+1,nbOccurrence);
	}
	
}