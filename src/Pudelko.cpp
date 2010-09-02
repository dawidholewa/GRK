#include <GL/glut.h>
#include "../include/Pudelko.h"

Pudelko::Pudelko(float wys, float szer, float gl, float polozenie_y)
{
    // Ustawienie niezbednych zmiennych.
    wygenerowane = false;

    // Sprawdzenie poprawnosci wymiarow bokow.
    if (wys == 0)  wys = 1;
    if (szer == 0) szer = wys;
    if (gl == 0)   gl = szer;

    szerokosc = szer;
    wysokosc = wys;
    glebokosc = gl;

    // Kolejne wspolrzedne wierzcholkow pudelka.
    // Wspolrzedne gory
    w[0][0] = -szer/2; w[0][1] = 0.0f + polozenie_y; w[0][2] =  gl/2;
    w[1][0] =  szer/2; w[1][1] = 0.0f + polozenie_y; w[1][2] =  gl/2;
    w[2][0] =  szer/2; w[2][1] = 0.0f + polozenie_y; w[2][2] = -gl/2;
    w[3][0] = -szer/2; w[3][1] = 0.0f + polozenie_y; w[3][2] = -gl/2;
    // Wspolrzedne dolu
    w[4][0] = -szer/2; w[4][1] =  wys + polozenie_y; w[4][2] = -gl/2;
    w[5][0] = -szer/2; w[5][1] =  wys + polozenie_y; w[5][2] =  gl/2;
    w[6][0] =  szer/2; w[6][1] =  wys + polozenie_y; w[6][2] =  gl/2;
    w[7][0] =  szer/2; w[7][1] =  wys + polozenie_y; w[7][2] = -gl/2;
}
void Pudelko::generujPudelko() {
    bool isTekstura = false;
    int pt = 1;

    box = glGenLists(1);

    glNewList(box,GL_COMPILE);
        glPushMatrix();
            if(t) {
                glEnable(GL_TEXTURE_2D);
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
    glEndList();
}
void Pudelko::Rysuj() {
    if(!wygenerowane) {
        generujPudelko();
        wygenerowane = true;
    }
    glCallList(box);
}

void Pudelko::RysujPiramide(int szer, int wys) {
    if(!wygenerowane) {
        generujPudelko();
        wygenerowane = true;
    }

    if(wys > szer) wys = szer;

    float przes = (szer)*szerokosc;
    glTranslatef(-przes/2,0.0f,-przes/2);
    glPushMatrix();
        for(int i = 0; i < wys; i++) {
            // Generowanie kolejnych poziomow. 0 <-> y
            glTranslatef(0.0f,szerokosc,0.0f);
            glPushMatrix();
                for(int j = szer-i; j > 0; j--) {
                    // Generowanie kolejnych rzedow. -z <-> z
                    glTranslatef(0.0f,0.0f,szerokosc);
                    glPushMatrix();
                        for(int k = szer-i; k > 0; k--) {
                            // Generowanie jednego rzedu. -x <-> x
                            glTranslatef(szerokosc,0.0f,0.0f);
                            glCallList(box);
                        }
                    glPopMatrix();
                }
            glPopMatrix();
            // Przesuniecie poziomu tak aby kazy poziom byl ulozony na srodku poprzedniego.
            glTranslatef(szerokosc/2,0.0f,szerokosc/2);
        }
    glPopMatrix();
}

// TODO: Poprawa obliczania wspolrzednych cienia
bool Pudelko::obliczCien(float podloga, float swiatlo[]) {
    if(swiatlo[1] <= w[4][1]) return false;
    // Obliczenia dla wierzcholka w0
     wsp[0] = (w[0][1] - podloga) / (swiatlo[1] - w[0][1]);
    c[0][0] = w[0][0] + (-(swiatlo[0] - w[0][0])) * wsp[0];
    c[0][1] = podloga;
    c[0][2] = w[0][0] + (-(swiatlo[2] - w[0][2])) * wsp[0];

    // Obliczenia dla wierzcholka w1
     wsp[1] = (w[1][1] - podloga) / (swiatlo[1] - w[1][1]);
    c[1][0] = w[1][0] + (-(swiatlo[0] - w[1][0])) * wsp[1];
    c[1][1] = podloga;
    c[1][2] = w[1][0] + (-(swiatlo[2] - w[1][2])) * wsp[1];

    // Obliczenia dla wierzcholka w2
     wsp[2] = (w[2][1] - podloga) / (swiatlo[1] - w[2][1]);
    c[2][0] = w[2][0] + (-(swiatlo[0] - w[2][0])) * wsp[2];
    c[2][1] = podloga;
    c[2][2] = w[2][0] + (-(swiatlo[2] - w[2][2])) * wsp[2];

    // Obliczenia dla wierzcholka w3
     wsp[3] = (w[3][1] - podloga) / (swiatlo[1] - w[3][1]);
    c[3][0] = w[3][0] + (-(swiatlo[0] - w[3][0])) * wsp[3];
    c[3][1] = podloga;
    c[3][2] = w[3][0] + (-(swiatlo[2] - w[3][2])) * wsp[3];

    // Obliczenia dla wierzcholka w4
     wsp[4] = (w[4][1] - podloga) / (swiatlo[1] - w[4][1]);
    c[4][0] = w[4][0] + (-(swiatlo[0] - w[4][0])) * wsp[4];
    c[4][1] = podloga;
    c[4][2] = w[4][0] + (-(swiatlo[2] - w[4][2])) * wsp[4];

    // Obliczenia dla wierzcholka w5
     wsp[5] = (w[5][1] - podloga) / (swiatlo[1] - w[5][1]);
    c[5][0] = w[5][0] + (-(swiatlo[0] - w[5][0])) * wsp[5];
    c[5][1] = podloga;
    c[5][2] = w[5][0] + (-(swiatlo[2] - w[5][2])) * wsp[5];

    // Obliczenia dla wierzcholka w6
     wsp[6] = (w[6][1] - podloga) / (swiatlo[1] - w[6][1]);
    c[6][0] = w[6][0] + (-(swiatlo[0] - w[6][0])) * wsp[6];
    c[6][1] = podloga;
    c[6][2] = w[6][0] + (-(swiatlo[2] - w[6][2])) * wsp[6];

    // Obliczenia dla wierzcholka w7
     wsp[7] = (w[7][1] - podloga) / (swiatlo[1] - w[7][1]);
    c[7][0] = w[7][0] + (-(swiatlo[0] - w[7][0])) * wsp[7];
    c[7][1] = podloga;
    c[7][2] = w[7][0] + (-(swiatlo[2] - w[7][2])) * wsp[7];
    c[7][2] = w[7][0] + (-(swiatlo[2] - w[7][2])) * wsp[7];

    return true;
}

// TODO: Poprawa rysowania cienia
void Pudelko::RysujCien() {
    glDisable(GL_CULL_FACE);
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
        glColor3f(0.2f, 0.2f, 0.2f);
        glBegin(GL_QUADS);
            // Podloga
            glVertex3fv(c[0]);
            glVertex3fv(c[1]);
            glVertex3fv(c[2]);
            glVertex3fv(c[3]);

            // Sufitc
            glVertex3fv(c[4]);
            glVertex3fv(c[5]);
            glVertex3fv(c[6]);
            glVertex3fv(c[7]);

            // Sciana przednia
            glVertex3fv(c[0]);
            glVertex3fv(c[1]);
            glVertex3fv(c[6]);
            glVertex3fv(c[5]);

            // Sciana prawa
            glVertex3fv(c[1]);
            glVertex3fv(c[2]);
            glVertex3fv(c[7]);
            glVertex3fv(c[6]);

            // Sciana tylnia
            glVertex3fv(c[2]);
            glVertex3fv(c[3]);
            glVertex3fv(c[4]);
            glVertex3fv(c[7]);

            // Sciana lewa
            glVertex3fv(c[3]);
            glVertex3fv(c[0]);
            glVertex3fv(c[5]);
            glVertex3fv(c[4]);
        glEnd();
    glPopMatrix();
    glEnable(GL_CULL_FACE);
}
