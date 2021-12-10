/**
 * TINF21CS1, Programmieraufgabe
 * 1. Semester
 *
 * Meine Matrikelnummer: 8424462
 * Mein Name: Julian Lemmerich
 *
 * Header-Datei für Qsort-Modul
 *
 */

#pragma once

void mein_zerlegen(void* teil_feld, int startLinks, int startRechts, int size, int(*vgl_fkt)(void* one, void* two));
void mein_qsort(void* feld, int nmemb, int size, int(*vgl_fkt)(void* one, void* two));