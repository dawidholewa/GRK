// Created by: Dawid Holewa
// Date: 01-09-2010
#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include "include/Kula.h"
#include "include/Mgla.h"
#include "include/Pokoj.h"
#include "include/Pudelko.h"
#include "include/Tekstura.h"

using namespace std;
Tekstura* textura;

float obrot = 0.0f;
bool obrot_orbit = true;
bool swiatla = true;

// Listy obiektow w celu przyspieszenia renderowania.
GLuint orbity1, orbity2;

// Tutaj tworzymy generujemy listy wszystkich obiektow.
void initObjects() {

    // Choinka z kulek.
    orbity1 = glGenLists(3);
    orbity2 = orbity1+1;

    // Srodek orbit
    float so[3] = {0.0f, 0.0f, 0.0f};

    // Tablica kolorow
    float kolor[10][3] = {
        {1.0f, 0.0f, 0.0f}, // Jasny czerwony
        {1.0f, 0.5f, 0.0f}, // Jasny pomaranczowy
        {1.0f, 1.0f, 0.0f}, // Jasny zolty
        {0.0f, 1.0f, 0.0f}, // Jasny zielony
        {0.0f, 1.0f, 1.0f}, // Jasny niebieski
        {0.5f, 0.0f, 0.0f}, // Ciemny czerwony
        {0.5f, 0.25f,0.0f}, // Ciemny pomaranczowy
        {0.5f, 0.5f, 0.0f}, // Ciemny zolty
        {0.0f, 0.5f, 0.0f}, // Ciemny zielony
        {0.0f, 0.5f, 0.5f}  // Ciemny niebieski
    };

    Kula* planeta = new Kula(2,so);
    planeta->SetKolors(10,*kolor);

    // Orbita pozioma
    glNewList(orbity1,GL_COMPILE);
        glPushMatrix();
            glTranslatef(0.0f, 20.0f, 0.0f);
            planeta->RysujAnimacje(10,6, true);
        glPopMatrix();
    glEndList();

    // Orbita pionowa
    glNewList(orbity2,GL_COMPILE);
            glPushMatrix();
                glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
                planeta->RysujAnimacje(10,5, true);
            glPopMatrix();
    glEndList();
}

void initSwiatlo() {
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

    // Swiatlo otaczajace, rozproszone
    float s_otoczenia[4]   = {0.2f, 0.2f, 0.2f, 1.0f};
    float s_rozproszone[4] = {0.5f, 0.5f, 0.5f, 1.0f};

    // Pozycja swiatla
    float p_light1[3] = {0.0f, 30.0f, 0.0f};
    float p_light2[3] = {80.0f, 10.0f, 0.0f};

    glLightfv(GL_LIGHT1, GL_AMBIENT, s_otoczenia);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, s_rozproszone);
    glLightfv(GL_LIGHT1, GL_POSITION, p_light1);
    glEnable(GL_LIGHT1);

    glLightfv(GL_LIGHT2, GL_AMBIENT, s_otoczenia);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, s_rozproszone);
    glLightfv(GL_LIGHT2, GL_POSITION, p_light1);
    //glEnable(GL_LIGHT2);

    float material[4]={1.0, 1.0, 1.0,1.0};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material);

}

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

    // Miekie cieniowanie
    glEnable(GL_SMOOTH);

    // Uruchomienie swiatla
    initSwiatlo();

    // Generowanie listy obiektow.
    initObjects();
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
    gluLookAt(  80.0f, 40.0f, 80.0f, // x,y,z Lokalizacja oka.
                0.0f,  0.0f,   0.0f, // x,y,z Lokalizacja centralnego punktu.
                0.0f,  1.0f,   0.0f);

    // Tworzymy obiekt pokoju.
    Pokoj* pokoj = new Pokoj(140, true);
    pokoj->SetTeksturaPodlogi(textura->pobierz(0));
    pokoj->SetTeksturaSciany(textura->pobierz(1));

    // Tworzymy obiekt pudelka.
    Pudelko* pudelko = new Pudelko(6);
    pudelko->SetTekstura(textura->pobierz(2));

    glPushMatrix();
        // Rysujemy pomieszczenie.
        pokoj->Rysuj();

        // Rysujemy piramide pudelek.
        pudelko->RysujPiramide(6,4);
    glPopMatrix();

    // Latajace orbity
    glPushMatrix();
        glRotatef(fmod(obrot/2,360), 0.0f, 1.0f, 0.0f);
        glTranslatef(-20.0f, 15.0f, -20.0f);

        // Obrot poziomej orbity
        glPushMatrix();
            glRotatef(obrot, 0.0f, 1.0f, 0.0f);
            glCallList(orbity1);
        glPopMatrix();

        // Obrot pionowej orbity
        glPushMatrix();
            glTranslatef(7.0f, 20.0f, 0.0f);
            glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
            glRotatef(-fmod(obrot*2,360), 0.0f, 0.0f, 1.0f);
            glCallList(orbity2);
        glPopMatrix();
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
        case 'q':
            if(obrot_orbit) {
                obrot += 2.0f;
                fmod(obrot, 360);
                glutPostRedisplay();
            }
            break;
        case 'w':
            if(obrot_orbit) {
                obrot -= 2.0f;
                fmod(obrot, 360);
                glutPostRedisplay();
            }
            break;
        case 'o':
            obrot_orbit = !obrot_orbit;
            break;
        case 's':
            swiatla = !swiatla;
            break;
    }
}

// Funkcja obslugi animacji
void animuj() {
    if(obrot_orbit) {
        obrot += 0.75f;
        fmod(obrot, 360);
        glutPostRedisplay();
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
    glutIdleFunc(animuj);

    // Uruchomienie glownej petli OpenGLa programu
    glutMainLoop();

    return 0;
}
