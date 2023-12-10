#include <stdio.h>
#include <malloc.h>
#include "timer.h"


// Fonction pour démarrer le minuteur
void startTimer() {
    _timer._start = clock();
}

// Fonction pour arrêter le minuteur et calculer la durée en millisecondes
void stopTimer() {
    _timer._end = clock();
    // Calcul de la durée en millisecondes par rapport à CLOCKS_PER_SEC
    _timer._msecs = (1000.0 * (double)(_timer._end - _timer._start)) / CLOCKS_PER_SEC;
}


void displayTime() {
    printf("%s\n", getTimeAsString());
}


char *getTimeAsString() {

    // return a string with the time in seconds and milliseconds
    // format : integers, with 3 digits, fill with 0
    // example : 001,123


    // use sprintf to write the string in a dynamically allocated buffer
    char *buffer = (char *)malloc(20 * sizeof(char)); // on a mis 20 en facteur car ca marche contrairement à 10.


    // use sprintf to write the string in a dynamically allocated buffer
    sprintf(buffer, "[%g] %03d,%03d", _timer._msecs, (int)(_timer._msecs) / 1000, (int)(_timer._msecs) % 1000);

    // return the buffer
    return buffer;
}
