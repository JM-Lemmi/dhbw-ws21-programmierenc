/**
 * TINF21CS1, Programmieraufgabe
 * 1. Semester
 *
 * Meine Matrikelnummer: 8424462
 * Mein Name: Julian Lemmerich
 *
 * Header-Datei für Ausgaben-Modul
 *
 */

#pragma once

// Prototypen

void drucke_studenten_kurz_by_ref(struct studenten_typ* student_ptr);
void drucke_studenten_kurz_by_val(struct studenten_typ student);
void drucke_studenten_lang_by_val(struct studenten_typ student);