#include <GL/glut.h>
#include "../include/Pudelko.h"

Pudelko::Pudelko(float wys, float szer, float gl)
{
    // Sprawdzenie poprawnosci wymiarow bokow
    if (wys == 0)  wys = 1;
    if (szer == 0) szer = wys;
    if (gl == 0)   gl = szer;

    // Kolejne wspolrzedne wierzcholkow pude³ka.
    // Wspolrzedne gory
    w[0][0] = -szer/2; w[0][1] = 0.0f; w[0][2] =  gl/2;
    w[1][0] =  szer/2; w[1][1] = 0.0f; w[1][2] =  gl/2;
    w[2][0] =  szer/2; w[2][1] = 0.0f; w[2][2] = -gl/2;
    w[3][0] = -szer/2; w[3][1] = 0.0f; w[3][2] = -gl/2;
    // Wspolrzedne dolu
    w[4][0] = -szer/2; w[4][1] = wys;  w[4][2] = -gl/2;
    w[5][0] = -szer/2; w[5][1] = wys;  w[5][2] =  gl/2;
    w[6][0] =  szer/2; w[6][1] = wys;  w[6][2] =  gl/2;
    w[7][0] =  szer/2; w[7][1] = wys;  w[7][2] = -gl/2;
}

void Pudelko::Rysuj() {
    bool isTekstura = false;
    int pt = 1;
        glPushMatrix();
        if(t) {
            glBindTexture(GL_TEXTURE_2D, *t);
            isTekstura = true;
        }

        // Zmieniamy kierunek wierzcholkow.
        glFrontFace(GL_CW); // Zgodny ze wskazowkami zegara.

        // Podloga
        glBegin(GL_QUADS);
            glNormal3f(0.0f, -1.0f, 0.0f);
            if(isTekstura) glTexCoord2f(0, pt);
            glVertex3fv(w[0]);
            if(isTekstura) glTexCoord2f(pt, pt);
            glVertex3fv(w[1]);
            if(isTekstura) glTexCoord2f(pt, 0);
            glVertex3fv(w[2]);
            if(isTekstura) glTexCoord2f(0, 0);
            glVertex3fv(w[3]);
        glEnd();

        // Zmieniamy kierunek wierzcholkow.
        glFrontFace(GL_CCW); // Przeciwny do kierunku wskazowek zegara.

        // Sufit
        glBegin(GL_QUADS);
            glNormal3f(0.0f, 1.0f, 0.0f);
            if(isTekstura) glTexCoord2f(0, pt);
            glVertex3fv(w[4]);
            if(isTekstura) glTexCoord2f(pt, pt);
            glVertex3fv(w[5]);
            if(isTekstura) glTexCoord2f(pt, 0);
            glVertex3fv(w[6]);
            if(isTekstura) glTexCoord2f(0, 0);
            glVertex3fv(w[7]);
        glEnd();

        float normalne[4][3] = {
            { 0.0f, 0.0f, 1.0f},
            { 1.0f, 0.0f, 0.0f},
            { 0.0f, 0.0f,-1.0f},
            {-1.0f, 0.0f, 0.0f}
        };

        glBegin(GL_QUADS);
            // Sciana przednia
            glNormal3fv(normalne[0]);
            if(isTekstura) glTexCoord2f(0, pt);
            glVertex3fv(w[0]);
            if(isTekstura) glTexCoord2f(pt, pt);
            glVertex3fv(w[1]);
            if(isTekstura) glTexCoord2f(pt, 0);
            glVertex3fv(w[6]);
            if(isTekstura) glTexCoord2f(0, 0);
            glVertex3fv(w[5]);

            // Sciana prawa
            glNormal3fv(normalne[1]);
            if(isTekstura) glTexCoord2f(0, pt);
            glVertex3fv(w[1]);
            if(isTekstura) glTexCoord2f(pt, pt);
            glVertex3fv(w[2]);
            if(isTekstura) glTexCoord2f(pt, 0);
            glVertex3fv(w[7]);
            if(isTekstura) glTexCoord2f(0, 0);
            glVertex3fv(w[6]);

            // Sciana tylnia
            glNormal3fv(normalne[2]);
            if(isTekstura) glTexCoord2f(0, pt);
            glVertex3fv(w[2]);
            if(isTekstura) glTexCoord2f(pt, pt);
            glVertex3fv(w[3]);
            if(isTekstura) glTexCoord2f(pt, 0);
            glVertex3fv(w[4]);
            if(isTekstura) glTexCoord2f(0, 0);
            glVertex3fv(w[7]);

            // Sciana lewa
            glNormal3fv(normalne[3]);
            if(isTekstura) glTexCoord2f(0, pt);
            glVertex3fv(w[3]);
            if(isTekstura) glTexCoord2f(pt, pt);
            glVertex3fv(w[0]);
            if(isTekstura) glTexCoord2f(pt, 0);
            glVertex3fv(w[5]);
            if(isTekstura) glTexCoord2f(0, 0);
            glVertex3fv(w[4]);
        glEnd();
    glPopMatrix();
}
