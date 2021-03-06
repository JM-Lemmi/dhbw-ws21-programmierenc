/**
 * TINF21CS1, Programmieraufgabe
 * 1. Semester
 * 
 * Meine Matrikelnummer: 8424462
 * Mein Name: Julian Lemmerich
 *
 */

// System-Header-Dateien
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Eigene Header-Dateien
#include "datentypen.h"
#include "ausgaben.h"
#include "mein_qsort.h"

// Prototypen
int vgl_fkt_kurs_nachname_vorname(struct studenten_typ*v1_ptr, struct studenten_typ*v2_ptr);
struct studenten_typ* kopiere_studenten_auf_heap(struct studenten_typ);
int vgl_fkt_zeiger_matrikel_nr(struct studenten_typ* v1_ptr, struct studenten_typ* v2_ptr);
void studenten_feld_ausgeben(
	struct studenten_typ studenten_feld[],
	size_t studenten_feld_n,
	void(*ausgabe_fkt_ptr)(struct studenten_typ student)
);


/**
 * Hauptprogramm.
 */
int main(int argc, char*argv[])
{
	// Initialisierungsliste mit Testdaten
	struct studenten_typ studenten_feld[] = {
			{ 1000, { "Eva",	"Meier"		}, "TINF21CS1" },
			{ 1001, { "Eva",	"Meier"		}, "TINF21CS1" },
			{ 1002, { "Karla",	"Schulze"	}, "TINF21CS1" },
			{ 1003, { "Eva",	"Schlau"	}, "TINF21CS1" },
			{ 1004, { "Berta",	"Meier"		}, "TINF21CS1" },
			{ 1005, { "Tom",	"Schmitt"	}, "TINF21CS1" },
			{ 1006, { "Peter",	"Weise"		}, "TINF21CS1" },
			{ 1007, { "Max",	"Weise"		}, "TINF21CS1" },
			{ 1008, { "Anton",	"Meyer"		}, "TINF21CS1" },
			{ 1009, { "Eva",	"Meier"		}, "TINF20CS2" },
	};
	// Aufgabe 1.2
	// Anzahl der Beispieldatensaetze in "studenten_feld"
	size_t studenten_feld_n = sizeof(studenten_feld) / sizeof(studenten_feld[0]);
	// Zeiger fuer die Indizierung mit 1..n
	// pointer f?r [0] auf [-1], damit [1] = [0]
	struct studenten_typ* studenten_feld_1_bis_n_ptr = &(studenten_feld[-1]);
	// Zeigerfeld, das auf die im Heap liegenden Studenten-Objekte verweist
	struct studenten_typ **studenten_feld_2ptr = NULL;
	// Laufvariable
	size_t i;

	// Aufgabe 1.7
	printf("Das urspruengliche Feld mit den Studenten (kurze Ausgabe):\n");
	if(0) {
		for(i = 0; i < studenten_feld_n; i++)
			drucke_studenten_kurz_by_val(studenten_feld[i]);
		printf("\n");
	}
	else {
		studenten_feld_ausgeben(&studenten_feld, studenten_feld_n, &drucke_studenten_kurz_by_val);
	}
	
	printf("Sortieren des Feldes nach dem Kurs, dem Nachnamen und dem Vornamen ...\n");
	mein_qsort(studenten_feld, studenten_feld_n, sizeof(studenten_feld[0]),
		vgl_fkt_kurs_nachname_vorname);

	printf("Das sortierte Feld mit den Studenten (lange Ausgabe):\n");
	if(0)
	{
		for(i = 0; i < studenten_feld_n; i++)
			drucke_studenten_lang_by_val(studenten_feld[i]);
		printf("\n");
	}
	else
	{
		studenten_feld_ausgeben(&studenten_feld, studenten_feld_n, &drucke_studenten_lang_by_val);
	}
	

	printf("Nach Eva Meier (TINF21CS1) suchen...\n");
	{
		// Aufgabe 1.4
		struct studenten_typ student;
		struct studenten_typ *ergebnis_ptr = NULL;
		struct studenten_typ *ergebnis2_ptr = NULL;

		// Studenten-Variable mit 0 fuellen, damit keine
		//  Warnung erscheint, auch wenn Sie die Aufgabe 1.4
		//  noch nicht bearbeitet haben
		// memset(&student, 0, sizeof(student));

		// student initialisieren
		student.name.nachname_ptr = "Meier";
		student.name.vorname_ptr = "Eva";
		strcpy(&student.kurs, "TINF21CS1");
		
		// bsearch() aufrufen
		ergebnis_ptr = bsearch(
			&student,
			studenten_feld,
			studenten_feld_n,
			sizeof(studenten_feld[0]),
			vgl_fkt_kurs_nachname_vorname
		);
		// Suchergebnis auswerten
		// Aufgabe 1.5
		if (ergebnis_ptr != NULL) {
			printf("Die Studentin gibt es; Matrikelnummer = %d\n", ergebnis_ptr->matrikel_nr);
			do {
				ergebnis2_ptr = ergebnis_ptr + 1;
				if (vgl_fkt_kurs_nachname_vorname(ergebnis_ptr, ergebnis2_ptr) == 0) {
					printf("Die Studentin gibt es; Matrikelnummer = %d\n", ergebnis2_ptr->matrikel_nr);
				}
				else break;
				ergebnis_ptr = ergebnis2_ptr; ergebnis2_ptr = NULL;
			} while (1);
		}
		else printf("Die gesuchte Studentin wurde nicht gefunden.\n");
	}
	
	// Aufgabe 1.8 (2/2)
	printf("Das Feld in Kurzform; Ausgabefunktion erhaelt die Speicheradresse:\n");
	for(i = 0; i < studenten_feld_n; i++) {
		for (i = 0; i < studenten_feld_n; i++)
			drucke_studenten_kurz_by_ref(&studenten_feld[i]);
		printf("\n");
	}
	printf("\n");

	// Aufgabe 1.9
	printf("Das Feld mit der Indizierung 1..n durchlaufen:\n");
	for(i = 1; i <= studenten_feld_n; i++)
	{
		drucke_studenten_kurz_by_val(studenten_feld_1_bis_n_ptr[i]);
	}
	printf("\n");

	printf("Ein Feld mit Zeigern auf die Studenten-Objekte\n"
		"auf dem Heap einrichten...\n");
	studenten_feld_2ptr = (struct studenten_typ**)calloc(studenten_feld_n, sizeof(*studenten_feld_2ptr));
	if(studenten_feld_2ptr == NULL)
	{
		fprintf(stderr, "Heap voll! Datei %s, Zeile %d, Version %s %s\n",
			__FILE__, __LINE__, __DATE__, __TIME__);
		exit(EXIT_FAILURE);
	}

	// Aufgabe 1.10 (2/2)
	if(1)
	{
		printf("Die Studenten auf den Heap kopieren...\n");
		for(i = 0; i < studenten_feld_n; i++)
			studenten_feld_2ptr[i] = kopiere_studenten_auf_heap(studenten_feld[i]);

		printf("Das Feld mit den Zeigern auf die Studenten vom Heap ausgeben:\n");
		for(i = 0; i < studenten_feld_n; i++)
			drucke_studenten_lang_by_val(*studenten_feld_2ptr[i]);

		// Aufgabe 1.11 (2/2)
		if(1)
		{
			printf("Das Zeigerfeld entsprechend den Matrikelnummern sortieren...\n");
			mein_qsort(studenten_feld_2ptr, studenten_feld_n, sizeof(*studenten_feld_2ptr), vgl_fkt_zeiger_matrikel_nr);

			printf("Das sortierte Zeigerfeld ausgeben:\n");
			for(i = 0; i < studenten_feld_n; i++)
				drucke_studenten_lang_by_val(*studenten_feld_2ptr[i]);
		}
	}

	// Aufgabe 1.12
	for (size_t i = 0; i < studenten_feld_n; i++) {
		struct studenten_typ *student = studenten_feld_2ptr[i];
		free(student->name.nachname_ptr);
		free(student->name.vorname_ptr);
		free(student);
	}
	printf("Heap-Sepicher freigegeben\n");

	return EXIT_SUCCESS;
} // main



/**
 * Diese Vergleichsfunktion dient zum Vergleichen
 * von 2 Studentenobjekten, wobei die Adressen der
 * beiden Studenten als Parameter erwartet werden.
 * Als Vergleichskriterien dienen der Kurs, der Nachname
 * und der Vorname.
 * Parameter:
 *	v1_ptr - Adresse des 1. Studenten-Objektes.
 *	v2_ptr - Adresse des 2. Studenten-Objektes.
 * Rueckgabewert:
 *	neg. Wert --> 1. Student vor 2. Student einzusortieren.
 *	0 --> beide Studenten gleich.
 *	pos. Wert --> 1. Student nach 2. Student einzusortieren.
 */
// Aufgabe 1.3
int vgl_fkt_kurs_nachname_vorname(struct studenten_typ *v1_ptr, struct studenten_typ *v2_ptr) {
	if (strcmp(v1_ptr->kurs, v2_ptr->kurs) == 0) {
		// same kurs
		if (strcmp(v1_ptr->name.nachname_ptr, v2_ptr->name.nachname_ptr) == 0) {
			// same nachname
			// no deeper if is needed, because we have to return the value of strcmp anyway
			return strcmp(v1_ptr->name.vorname_ptr, v2_ptr->name.vorname_ptr);
		} else return strcmp(v1_ptr->name.nachname_ptr, v2_ptr->name.nachname_ptr);
	} else return strcmp(v1_ptr->kurs, v2_ptr->kurs);
} // vgl_fkt_kurs_nachname_vorname


/**
 * Diese Funktion gibt ein Feld mit Studenten aus,
 * wobei die Ausgabe nicht direkt erfolgt, sondern
 * mittels einer Callback-Funktion. Diese ermoeglicht
 * es, die Form der Ausgabe weitgehend frei einstellen
 * zu koennen.
 * Parameter:
 *	feld - Anfangsadresse des Feldes mit den Studenten.
 *	feld_n - Anzahl der Feldelemente.
 *	ausgabe_fkt_ptr - Einsprungadresse der aktuell
 *		gewuenschten Callback-Funktion fuer die
 *		Ausgabe eines Studenten.
 * Rueckgabewert:
 *	Keiner!
 */
// Aufgabe 1.6
void studenten_feld_ausgeben(
	struct studenten_typ studenten_feld[],
	size_t studenten_feld_n,
	void(*ausgabe_fkt_ptr)(struct studenten_typ student)
) {
	for (size_t i = 0; i < studenten_feld_n; i++) {
		ausgabe_fkt_ptr(studenten_feld[i]);
	}
} // studenten_feld_ausgeben


/**
 * Diese Funktion kopiert einen Studentendatensatz,
 * der mittels call-by-value uebergeben wird, auf 
 * den Heap, wobei auch der Vor- und Nachname als
 * neue Objekte angelegt werden.
 * Parameter:
 *  student - Auf den Heap zu kopierender Student; wird
 *		mittels call-by-value uebergeben.
 * Rueckgabewert:
 *	Adresse des Studenten-Objektes auf dem Heap.
 */
// Aufgabe 1.10 (1/1)
struct studenten_typ* kopiere_studenten_auf_heap(struct studenten_typ student) {
	struct studenten_typ* student_heap = (struct studenten_typ*)malloc(sizeof(struct studenten_typ));

	if (student_heap == NULL) {
		fprintf(stderr, "Heap voll!\nFile: %s\nLine %d\nVersion %s\n%s", __FILE__, __LINE__, __DATE__, __TIME__);
		exit(EXIT_FAILURE);
	}

	// *student_heap = student; // geht leider nicht, weil dann nur Pointer zu den namen auf den Stack sind. _strcopy ist n?tig.
	student_heap->matrikel_nr = student.matrikel_nr;
	student_heap->name.nachname_ptr = _strdup(student.name.nachname_ptr);
	student_heap->name.vorname_ptr = _strdup(student.name.vorname_ptr);
	strcpy(student_heap->kurs, student.kurs);


	return student_heap;
} // kopiere_studenten_auf_heap


/**
 * Diese Vergleichsfunktion dient zum Vergleichen
 * von 2 Studentenobjekten, wobei die Adressen der
 * Adressen der beiden Studenten als Parameter
 * erwartet werden.
 * Als Vergleichskriterium dient die Matrikelnummer.
 * Parameter:
 *	v1_ptr - Adresse der Adresse des 1. Studenten-Objektes.
 *	v2_ptr - Adresse der Adresse des 2. Studenten-Objektes.
 * Rueckgabewert:
 *	neg. Wert --> 1. Student vor 2. Student einzusortieren.
 *	0 --> beide Studenten gleich.
 *	pos. Wert --> 1. Student nach 2. Student einzusortieren.
 */
 // Aufgabe 1.11 (1/2)
int vgl_fkt_zeiger_matrikel_nr(
	struct studenten_typ *v1_ptr,
	struct studenten_typ *v2_ptr
) {
	struct studenten_typ* v1_ptr_ptr = *(struct studenten_typ**)v1_ptr;
	struct studenten_typ* v2_ptr_ptr = *(struct studenten_typ**)v2_ptr;

	return v1_ptr_ptr->matrikel_nr - v2_ptr_ptr->matrikel_nr;
}
