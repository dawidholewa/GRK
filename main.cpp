// Created by: Dawid Holewa
// Date: 01-09-2010

#include <iostream>
#include <GL/glut.h>

// Funkcja obslugujaca klawiature
void klawiatura(unsigned char klawisz, int x, int y) {
    switch(klawisz) {
        case 27: // Zamkniecie programu po wcisnieciu klawisza ESC.
            exit(0);
            break;
    }
}

// Glowna funkcja programu
int main(int argc, char * argv[]) {

}
