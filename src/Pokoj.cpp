#include <GL/glut.h>
#include "../include/Pokoj.h"

Pokoj::Pokoj(float bok, bool sciany){

    // Czy wyswietlac sciany pokoju (domyslnie false - nie).
    bSciany = sciany;

    // Upewniamy sie ze wymiary naszego pokoj nie sa za male.
    if (bok < 1.0f) bok = 1.0f;

    // Kolejne wspolrzedne wierzcholkow pokoju.
    // w[0-3] - wspolrzedne podlogi.
    w[0][0] = -bok/2; w[0][1] = 0.0f; w[0][2] =  bok/2;
    w[1][0] =  bok/2; w[1][1] = 0.0f; w[1][2] =  bok/2;
    w[2][0] =  bok/2; w[2][1] = 0.0f; w[2][2] = -bok/2;
    w[3][0] = -bok/2; w[3][1] = 0.0f; w[3][2] = -bok/2;
}

void Pokoj::Rysuj() {
    glPushMatrix();
        glBegin(GL_QUADS);
            // Ustawienie normalnej dla podlogi (niezbedna do oswietlenia).
            glNormal3f(0.0f,1.0f, 0.0f);
            for (int i = 0; i < 4 ;i++ ) glVertex3fv(w[i]);
        glEnd();
    glPopMatrix();
}
