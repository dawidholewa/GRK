#include <GL/glut.h>
#include "../include/Kula.h"

Kula::Kula(float promien, float srodek[])
{
    if (promien < 0)  r = -promien; // Upewniamy sie ze promien jest wartoscia dodatnia.
    if (promien == 0) r = 1; // Upewniamy sie ze minimalna wielkosc promienia to 1.

    r = promien;
    s[0] = srodek[0];
    s[1] = srodek[1];
    s[2] = srodek[2];

    wygenerowane = false;
}

void Kula::generujKule() {
    ball = glGenLists(1);

    GLUquadricObj *sphere = gluNewQuadric();
    gluQuadricDrawStyle(sphere, GLU_FILL );

    glNewList(ball,GL_COMPILE);
        glPushMatrix();
            glTranslatef(s[0],s[1],s[2]);
            gluSphere(sphere, r, 32, 32);
        glPopMatrix();
    glEndList();
}

void Kula::Rysuj() {
    if(!wygenerowane) {
        generujKule();
        wygenerowane = true;
    }

    glCallList(ball);
}

void Kula::RysujAnimacje(float x, float y, float z) {

}
