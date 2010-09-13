#include "../include/Tekstura.h"
#include <stdio.h>

Tekstura::Tekstura()
{
    ostatni_nr = 0;
}

// Ladowanie pliku tekstury.
AUX_RGBImageRec* Tekstura::loadBMPFile(char *filename) {
    FILE *plik = NULL;

    if(!filename) return NULL;

    plik = fopen(filename, "r");

    // Sprawdziamy czy plik wogole istnieje.
    if (plik) {
        fclose(plik);
        return auxDIBImageLoad(filename);
    }

    // Zwracamy NULL jezeli plik tekstury nie istnieje.
    return NULL;
}


bool Tekstura::laduj(char *nazwa) {
    bool status = false;

    AUX_RGBImageRec * t[1];

    if (t[0] = loadBMPFile(nazwa)) {
        status = true;

        glGenTextures(1, &textury[ostatni_nr]);
        glBindTexture(GL_TEXTURE_2D, textury[ostatni_nr]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, t[0]->sizeX, t[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, t[0]->data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    }

    ostatni_nr++;
    return status;
}

GLuint* Tekstura::pobierz(int i) {
    if (textury[i]) return &textury[i];
    return NULL;
}
