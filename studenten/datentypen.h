/**
 * TINF21CS1, Programmieraufgabe
 * 1. Semester
 *
 * Meine Matrikelnummer: 8424462
 * Mein Name: Julian Lemmerich
 * 
 * Header-Datei f?r Datentypendefinition
 *
 */

#pragma once

// Aufgabe 1.1
// Eigene Datentypen
#define KURS_LEN 10

/**
 * Datentyp fuer die Namen.
 */
struct namens_typ {
	char* vorname_ptr;
	char* nachname_ptr;
};

/**
 * Datentyp fuer die Studenten.
 */
struct studenten_typ {
	int matrikel_nr;
	struct namens_typ name;
	char kurs[KURS_LEN];
};
