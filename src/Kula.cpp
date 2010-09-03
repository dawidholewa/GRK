#include <GL/glut.h>
#include <math.h>
#include "../include/Kula.h"

Kula::Kula(float promien, float srodek[])
{
    if (promien < 0)  r = -promien; // Upewniamy sie ze promien jest wartoscia dodatnia.
    if (promien == 0) r = 1; // Upewniamy sie ze minimalna wielkosc promienia to 1.

    r = promien;
    s[0] = srodek[0];
    s[1] = srodek[1];
    s[2] = srodek[2];

//    wygenerowane = false;
    num_k = 0;
}

void Kula::generujKule() {
//    ball = glGenLists(1);

    GLUquadricObj *sphere = gluNewQuadric();
    gluQuadricDrawStyle(sphere, GLU_FILL );

//    glNewList(ball,GL_COMPILE);
        glPushMatrix();
            glTranslatef(s[0],s[1],s[2]);
            gluSphere(sphere, r, 32, 32);
        glPopMatrix();
//    glEndList();
}

void Kula::SetKolors(int num, float *kolory) {
    num_k = num;
    k = kolory;
}
void Kula::Rysuj() {
//    if(!wygenerowane) {
//        generujKule();
//        wygenerowane = true;
//    }
//
//    glCallList(ball);
    generujKule();
}

void Kula::RysujAnimacje(float p, int ilosc, bool mix_color) {
//    if(!wygenerowane) {
//        generujKule();
//        wygenerowane = true;
//    }

    int lc_index = 0; // Ostatnio uzyty index koloru.
    glPushAttrib(GL_CURRENT_BIT);
        glPushMatrix();
            for(float kat=0;kat<360;kat+=360/ilosc)
            {
                GLfloat x,z;
                x = p*cos(kat/180*3.14);
                z = p*sin(kat/180*3.14);
                glPushMatrix();
                    if(num_k > 0 && lc_index < num_k && mix_color) {
                        glColor3fv(&k[lc_index]);
                        lc_index++;

                        if(lc_index >= num_k) lc_index = 0;
                    } else if(num_k > 0 && !mix_color) {
                        glColor3fv(&k[0]);
                    }

                    glTranslatef(x, 0.0f, z);
                    Rysuj();
//                    glCallList(ball);
                glPopMatrix();
            }
        glPopMatrix();
    glPopAttrib();
}
