/**
 * TINF21CS1, Programmieraufgabe
 * 1. Semester
 *
 * Meine Matrikelnummer: 8424462
 * Mein Name: Julian Lemmerich
 *
 * Modul für Ausgaben
 * 
 */
// Aufgabe 1.13

// System-Header-Dateien
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Eigene Header-Dateien
#include "datentypen.h"
#include "ausgaben.h"

/**
 * Diese Funktion gibt einen Studenten aus,
 * dessen Anfangsadresse uebergeben wird.
 * Das Format der Ausgabe entspricht genau
 * demjenigen, das die Funktion
 * "drucke_studenten_kurz_by_val()"
 * verwendet; z.B.: Lang, Olga;
 * Parameter:
 *	student_ptr - Adresse des auszugebenden
 *		Studenten
 * Rueckgabewert:
 *	Keiner!
 */
 // Aufgabe 1.8 (1/2)
void drucke_studenten_kurz_by_ref(struct studenten_typ* student) {
	printf("%s, %s;  ",
		student->name.nachname_ptr,
		student->name.vorname_ptr);
} // drucke_studenten_kurz_by_ref


/**
 * Diese Funktion gibt den Nach- und Vornamen
 * einen Studenten aus, der mittels Call-by-value
 * uebergeben wird.
 * Beispiel fuer das Format: Lang, Olga;
 * Parameter:
 *	student - Vollstaendige Kopie des auszugebenden
 *		Studenten.
 * Rueckgabewert:
 *	Keiner!
 */
void drucke_studenten_kurz_by_val(struct studenten_typ student)
{
	printf("%s, %s;  ",
		student.name.nachname_ptr,
		student.name.vorname_ptr);
} // drucke_studenten_kurz_by_val


/**
 * Diese Funktion gibt in 1 Zeile alle Daten
 * eines Studenten aus, der mittels Call-by-value
 * uebergeben wird.
 * Parameter:
 *	student - Vollstaendige Kopie des auszugebenden
 *		Studenten.
 * Rueckgabewert:
 *	Keiner!
 */
void drucke_studenten_lang_by_val(struct studenten_typ student)
{
	// Linksbuendig (Minuszeichen!) spaltenweise formatiert
	//  ausgeben
	printf("%5d  %-10s %-10s %-10s\n",
		student.matrikel_nr,
		student.name.vorname_ptr,
		student.name.nachname_ptr,
		student.kurs);
} // drucke_studenten_lang_by_val