// Created by: Dawid Holewa
// Date: 01-09-2010
#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include "include/Kula.h"
#include "include/Pokoj.h"
#include "include/Pudelko.h"
#include "include/Tekstura.h"

using namespace std;
Tekstura* textura;

float obrot = 0.0f;
bool obrot_kol = false;

// Funkcja ustawiajaca podstaweowe ustawienia.
void init() {

    // Uruchomienie i zaladowanie tekstru.
    glEnable(GL_TEXTURE_2D);
    textura = new Tekstura();
    textura->laduj("data/podloga.bmp");
    textura->laduj("data/sciana.bmp");
    textura->laduj("data/box.bmp");

    // Wlaczenie pomijania niewidocznych scian podczas renderowania.
    glEnable(GL_CULL_FACE);

    // Niezbedne do tego aby uniknac wzajemnego przenikania sie obiektow.
    glEnable(GL_DEPTH_TEST);
}

// Funkcja obslugujaca rysowanie obrazu wyswietlanego uzytkownikowi.
void wyswietl() {
    // Przelaczamy sie na macierz dotyczaca modelu.
    glMatrixMode(GL_MODELVIEW);

    // Resetujemy ustawienia macierzy modelu.
    glLoadIdentity();

    // Czyszczenie buforow.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Ustawienie kierunku w ktorym bedziemy patrzec.
    gluLookAt(  140.0f, 80.0f, 140.0f, // x,y,z Lokalizacja oka.
                0.0f,  0.0f,   0.0f, // x,y,z Lokalizacja centralnego punktu.
                0.0f,  1.0f,   0.0f);

    // TUTAJ RESZTA KODU !!!
    glPushMatrix();
        Pokoj* p = new Pokoj(140.0f, true);
        p->SetTeksturaPodlogi(textura->pobierz(0));
        p->SetTeksturaSciany(textura->pobierz(1));
        p->Rysuj();
    glPopMatrix();

//    glPushMatrix();
//        Pudelko* box = new Pudelko(10);
//        box->SetTekstura(textura->pobierz(2));
//        box->RysujPiramide(3,2);
//    glPopMatrix();

    glPushMatrix();
        float s[3] = {0.0f,30.0f,0.0f};
        Kula* ball = new Kula(2,s);
        float o[4] = {obrot,0.0f, 1.0f, 0.0f};
        ball->RysujAnimacje(10,5,o);
    glPopMatrix();


    // Polecenie wykonania wywolanych do tej pory funkcji.
    glFlush();

    // Przelaczenie bufforu rysowania ramki.
    glutSwapBuffers();
}

// Funkcja skalujaca obraz odpowiednio do rozmiaru wyswietlanego okna.
void skalujObraz(int szer, int wys) {

    // Stosunek szerokosci do wysokosci.
    GLfloat stosunek = (GLfloat) szer / (GLfloat) wys;

    glViewport(0, 0, szer, wys);

    // Przelaczamy sie na macierz dotyczaca ustawien perspektywy.
    glMatrixMode(GL_PROJECTION);

    // Resetujemy ustawienia zaladowanej przed chwila macierzy (ladujemy macierz identycznosciowa).
    glLoadIdentity();

    // Ustawiamy widok odpowiedniej perspektywy.
    gluPerspective(45, stosunek, 0.1f, 1000.0f);

}

// Funkcja obslugujaca klawiature.
void klawiatura(unsigned char klawisz, int x, int y) {
    switch(klawisz) {
        case 27: // Zamkniecie programu po wcisnieciu klawisza ESC.
            exit(0);
            break;
        case '+':
            obrot += 2.0f;
            fmod(obrot, 360);
            glutPostRedisplay();
            break;
        case '-':
            obrot -= 2.0f;
            fmod(obrot, 360);
            glutPostRedisplay();
            break;
        case 'k':
            obrot_kol = !obrot_kol;
            break;
    }
}

// Glowna funkcja programu.
int main(int argc, char * argv[]) {

    // Inicjalizacja gluta.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);

    // Ustawienie nazwy okna.
    glutCreateWindow("Projekt na zaliczenie");

    // Zaladowanie naszych ustawien.
    init();

    // Ustawienie funkcji odpowiedzialnych kolejno za obsluge sceny, skalowania obrazu oraz klawiatury.
    glutDisplayFunc(wyswietl);
    glutReshapeFunc(skalujObraz);
    glutKeyboardFunc(klawiatura);

    // Uruchomienie glownej petli OpenGLa programu
    glutMainLoop();

    return 0;
}
