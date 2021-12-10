/**
 * Angelehnt an das Beispielprogramm "quicksrt.c" von
 * Goll S.490 (7.Aufl.).
 * 1. Semester
 * 
 * Meine Matrikelnummer: 8424462
 * Mein Name: Julian Lemmerich
 *
 */
// Standard-Header
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prototypen
void zerlege(int teil_feld[], int startLinks, int startRechts);
void quickSort(int feld[], int n);
int vgl_fkt_int_aufsteigend(int one, int two);
void mein_zerlegen(void* teil_feld[], int startLinks, int startRechts, int(*vgl_fkt_ptr)(void* one, void* two));
void mein_qsort(void* feld[], int n);

/**
 * Hauptprogramm
 */
int main(int argc, char*argv[])
{
	// Feld mit zu sortierenden Ganzzahlen
	int feld[] = { 7, 3, 8, 6, 9, 1, 2, 4 };
	// Anzahl der Feldelemente
	int feld_n = sizeof(feld)/sizeof(feld[0]);
	// Laufvariable
	int index;

	// Zu sortierendes Array ausgeben 
	printf("Das gegebene, unsortierte Feld:\n");
	for (index=0; index < feld_n; index++)
		printf("%i ", feld[index]);
	printf("\n\n");
	
	// Aufsteigend sortieren
	printf("Das Feld sortieren ...\n");
	if (0) quickSort(feld, feld_n);
	else mein_qsort(feld, feld_n, sizeof(feld[0]), vgl_fkt_int_aufsteigend);
	printf("\n");
	
	// Sortiertes Feld ausgeben 
	printf("Das sortierte Feld:\n");
	for(index = 0; index < feld_n; index++)
		printf("%i ", feld[index]);
	printf("\n");

	return EXIT_SUCCESS;
} // main


/**
 * Wrapper-Funktion von Goll.
 */
void quickSort (int feld[], int n) {
	zerlege (feld, 0, n-1);
} // quickSort


/**
 * Rekursive Funktion von Goll.
 */
void zerlege(int teil_feld [], int startLinks, int startRechts) {
	int i;
	int laufLinks = startLinks;
	int laufRechts = startRechts;
	int vergleichselementIndex =
		(startLinks + startRechts) / 2; /*(1)*/
	int vergleichselement = teil_feld[vergleichselementIndex];

	do /*(2)*/
	{ /* Schleife, bis laufLinks und laufRechts zusammentreffen */
		/* Suche von links groessere Elemente als */
		/* Vergleichselement (2.1)*/
		while (teil_feld[laufLinks] < vergleichselement)
			laufLinks++;
		/* Suche von rechts kleinere Elemente als */
		/* Vergleichselement (2.2)*/
		while (teil_feld[laufRechts] > vergleichselement)
			laufRechts-- ;
		if (laufLinks <= laufRechts) /* Vertauschen (2.3)*/
		{
			int zwischen = teil_feld[laufLinks];
			teil_feld[laufLinks] = teil_feld[laufRechts];
			teil_feld[laufRechts] = zwischen;
			laufLinks++; laufRechts--;
		}
	} while (laufLinks <= laufRechts); /*(2.4)*/

	/* Vorsortiertes Feld ausgeben */
	for (i = 0; i < startLinks; i++)
		printf(" ");
	for (i=startLinks; i <= startRechts; i++)
		printf("%i ", teil_feld[i]);
	printf("\n");
	/* Jetzt beide Teilfelder rekursiv gleich behandeln (3)*/
	if (startLinks < laufRechts)
		zerlege(teil_feld, startLinks, laufRechts);
	if (laufLinks < startRechts)
		zerlege(teil_feld, laufLinks, startRechts);
} // zerlege

/*
* Vergleiche zwei Ganzzahlen, dass sich eine aufsteigende Sortierung gibt
* Input: zwei int
* Returns: 
*	<0 : one ist kleiner als two
 *	0 : beide int gleich
 *	>0 : two ist kleiner als one
*/
// Aufgabe 2.2
int vgl_fkt_int_aufsteigend(int *one, int *two) {return *one - *two;}


void mein_zerlegen(
	void* teil_feld,
	int startLinks,
	int startRechts,
	int size,
	int(*vgl_fkt)(void* one, void* two)
) {
	int i;
	int laufLinks = startLinks;
	int laufRechts = startRechts;
	int vergleichselementIndex = (startLinks + startRechts) / 2;
	void* vergleichselement = (char*)teil_feld + (vergleichselementIndex * size);

	void* zwischen = malloc(size);
	if (!zwischen){fprintf(stderr, "Heap voll!"); exit(EXIT_FAILURE);}

	do { /* Schleife, bis laufLinks und laufRechts zusammentreffen */
		
		// wir brauchen *(& hier, da &teil_feld auf die adresse des ersten Elements zeigt, dh in der klammer steht eine adresse. Da wir aber mit dem Wert arbeiten wollen, brauchen wir noch den * davor
		
		/* Suche von links groessere Elemente als */
		while (vgl_fkt((char*)teil_feld + (laufLinks * size), vergleichselement) < 0)
			laufLinks++;
		/* Suche von rechts kleinere Elemente als */
		while (vgl_fkt((char*)teil_feld + (laufRechts * size), vergleichselement) > 0)
			laufRechts--;
		if (laufLinks <= laufRechts)
		{
			// statt einem for loop ist bei string.h die Funktion memcopy vorhanden, die genau diesen Loop für uns übernimmt
			memcpy(zwischen, (char*)teil_feld + (laufLinks * size), size);
			memcpy((char*)teil_feld + (laufLinks * size), (char*)teil_feld + (laufRechts * size), size);
			memcpy((char*)teil_feld + (laufRechts * size), zwischen, size);
			laufLinks++; laufRechts--;
		}
	} while (laufLinks <= laufRechts);

	free(zwischen);

	/* Jetzt beide Teilfelder rekursiv gleich behandeln (3)*/
	if (startLinks < laufRechts)
		mein_zerlegen(teil_feld, startLinks, laufRechts, size, vgl_fkt);
	if (laufLinks < startRechts)
		mein_zerlegen(teil_feld, laufLinks, startRechts, size, vgl_fkt);
}


// Aufgabe 2.4
void mein_qsort(
	void* feld,
	int nmemb,
	int size,
	int(*vgl_fkt)(void* one, void* two)
) {
	mein_zerlegen(feld, 0, nmemb-1, size, vgl_fkt);
}