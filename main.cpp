// Created by: Dawid Holewa
// Date: 01-09-2010

#include <iostream>
#include <GL/glut.h>

// Funkcja ustawiajaca podstaweowe ustawienia.
void init() {

    // Ustawienie koloru tla calej aplikacji.
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

}

// Funkcja obslugujaca rysowanie obrazu wyswietlanego uzytkownikowi.
void wyswietl() {

    // Czyszczenie buforow.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // TUTAJ RESZTA KODU !!!

    // Polecenie wykonania wywolanych do tej pory funkcji.
    glFlush();

    // Przelaczenie bufforu rysowania ramki.
    glutSwapBuffers();
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

}
