// Created by: Dawid Holewa
// Date: 01-09-2010
#include <iostream>
#include <GL/glut.h>

using namespace std;

// Funkcja ustawiajaca podstaweowe ustawienia.
void init() {

}

// Funkcja obslugujaca rysowanie obrazu wyswietlanego uzytkownikowi.
void wyswietl() {

    // Czyszczenie buforow.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Ustawienie kierunku w ktorym bedziemy patrzec.
    gluLookAt(100.0f, 50.0f, 100.0f, // x,y,z Lokalizacja oka.
                0.0f,  0.0f,   0.0f, // x,y,z Lokalizacja centralnego punktu.
                0.0f,  1.0f,   0.0f);

    // TUTAJ RESZTA KODU !!!
    glPushMatrix();
        glutSolidSphere(10.0f, 100,100);
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

    // Przelaczamy sie na macierz dotyczaca modelu.
    glMatrixMode(GL_MODELVIEW);

    // Resetujemy ustawienia macierzy modelu.
    glLoadIdentity();

}

// Funkcja obslugujaca klawiature.
void klawiatura(unsigned char klawisz, int x, int y) {
    switch(klawisz) {
        case 27: // Zamkniecie programu po wcisnieciu klawisza ESC.
            exit(0);
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
