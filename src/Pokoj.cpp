#include <GL/glut.h>
#include "../include/Pokoj.h"

Pokoj::Pokoj(float bok, bool sciany){

    // Czy wyswietlac sciany pokoju (domyslnie false - nie).
    SetSciany(sciany);

    // Upewniamy sie ze wymiary naszego pokoj nie sa za male.
    if (bok < 1.0f) bok = 1.0f;

    // Kolejne wspolrzedne wierzcholkow pokoju.
    // w[0-3] - wspolrzedne podlogi.
    w[0][0] = -bok/2; w[0][1] = 0.0f; w[0][2] =  bok/2;
    w[1][0] =  bok/2; w[1][1] = 0.0f; w[1][2] =  bok/2;
    w[2][0] =  bok/2; w[2][1] = 0.0f; w[2][2] = -bok/2;
    w[3][0] = -bok/2; w[3][1] = 0.0f; w[3][2] = -bok/2;

    if(sciany) {
        w[4][0] = -bok/2; w[4][1] = bok;  w[4][2] = -bok/2;
        w[5][0] = -bok/2; w[5][1] = bok;  w[5][2] =  bok/2;
        w[6][0] =  bok/2; w[6][1] = bok;  w[6][2] =  bok/2;
        w[7][0] =  bok/2; w[7][1] = bok;  w[7][2] = -bok/2;
    }
}

void Pokoj::Rysuj() {
    glPushMatrix();
        glBegin(GL_QUADS);
            // Ustawienie normalnej dla podlogi (niezbedna do oswietlenia).
            glNormal3f(0.0f, 1.0f, 0.0f);
            for (int i = 0; i < 4 ;i++ ) glVertex3fv(w[i]);
        glEnd();

        if (GetSciany()) {
            glBegin(GL_QUADS);
                // Lewa sciana
                glNormal3f(1.0f, 0.0f, 0.0f);
                glVertex3fv(w[0]);
                glVertex3fv(w[3]);
                glVertex3fv(w[4]);
                glVertex3fv(w[5]);

                // Tylnia sciana
                glNormal3f(0.0f, 0.0f, 1.0f);
                glVertex3fv(w[3]);
                glVertex3fv(w[2]);
                glVertex3fv(w[7]);
                glVertex3fv(w[4]);
            glEnd();
        }
    glPopMatrix();
}
