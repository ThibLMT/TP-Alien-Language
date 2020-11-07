// gcc -W -Wall -std=c99 alienLanguage-main.c alienLanguage.c -g 
//valgrind --leak-check=yes --leak-check=full --show-leak-kinds=all --show-reachable=no ./a.out

// Input
// 3 5 4			// nbLettersInAWord nbWords nbTestCases
// abc
// bca
// dac
// dbc
// cba
// (ab)(bc)(ca)
// abc
// (abc)(abc)(abc)
// (zyx)bc
//
// Output
// Case #1: 2
// Case #2: 1
// Case #3: 3
// Case #4: 0

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include "alienLanguage.h"






int main(int argc, char *argv[]){
	char *filename = "A-large-practice.in"; 
	FILE* dataFile;
	
	if( argc > 1)
		filename = argv[1];

	// open file
	dataFile = fopen(filename,"r");
	if( dataFile == NULL ) {
		printf("Error opening file %s : %d (%s)\n",filename,errno,strerror(errno)); 
		exit(1);
	}
	
	// read file header
	unsigned int wordSize, nbWords, nbTestCases;
	fscanf(dataFile,"%u %u %u\n", &wordSize, &nbWords, &nbTestCases);
	printf("%u %u %u\n", wordSize, nbWords, nbTestCases);

	 Dictionary *dictionary = createDictionary(dataFile, nbWords, wordSize);

	//printDictionary(dictionary, nbWords);

	Pattern *pattern = (Pattern*)createPattern(dataFile,wordSize,nbTestCases);
 	//freeDico(dictionary, nbWords);
	//printPatternBrut(pattern,nbTestCases);
 
	/* char *uneLigne = "(opqrsvwxyzabcdefghijklmn)(yzabcdefgijklmnpqrstuvwx)(ijklmopqrstuvwxzabcefgh)(stuvwxyzabcdefhijklmnopq)(mnopqrstuvwxyzabdefghijkl)(ijklmnopqrstuvwxzbcdefh)(stuvwzabcdefgijklmnopq)(efghijklmnopqrsuvwxyacd)(rstuvxyzadefghijklmnopq)(noqrsuwxyzabdfghjlm)";



	Pattern *patternTest = splitUnPattern(uneLigne,wordSize);
	printf("%s\n","test");
	printPatternBrut (patternTest, wordSize);
	printf("%s\n","test");
	printf("%s\n",patternTest->mots[5]); */
	afficherResultatsTests(dictionary, pattern, nbTestCases, wordSize,  nbWords);	
	//printf("%i",rechercheNombreOccurrenceUnPatternDansDictionnaire(dictionary,patternTest , nbWords, wordSize));



	
	// close file 
	fclose(dataFile);
	
	return EXIT_SUCCESS;
}
