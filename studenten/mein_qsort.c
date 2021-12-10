/**
 * Meine Matrikelnummer: 8424462
 * Mein Name: Julian Lemmerich
 *
 * Eigenes Qsort Modul
 * 
 */
 // Standard-Header
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

	void* vergleichselement = malloc(size);
	void* zwischen = malloc(size);
	if (!zwischen || !vergleichselement) { fprintf(stderr, "Heap voll!"); exit(EXIT_FAILURE); }

	// dies ist nötig, da falls das vergleichselement getauscht wird, der ursprüngliche pointer auf etwas anderes zeigen kann und die sortierung fehlschlägt
	memcpy(vergleichselement, (char*)teil_feld + (vergleichselementIndex * size), size);

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

	free(zwischen); free(vergleichselement)

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
	mein_zerlegen(feld, 0, nmemb - 1, size, vgl_fkt);
}
