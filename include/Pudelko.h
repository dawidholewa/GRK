#ifndef PUDELKO_H
#define PUDELKO_H


class Pudelko
{
    public:
        Pudelko(float wys, float szer = 0, float gl = 0, float polozenie_y = 0);

        void SetTekstura(GLuint* textura) { t = textura; }
        bool obliczCien(float podloga, float swiatlo[]);

        void Rysuj();
        void RysujCien();
        void RysujPiramide(int szer, int wys);

    protected:
    private:
        GLuint* t; // Tekstura pudelka.
        GLuint box; // Lista wyswietlania pudelka.

        float szerokosc;
        float glebokosc;
        float wysokosc;

        float w[8][3];
        float c[8][3];
        float wsp[8];
        bool wygenerowane; // Czy pudelko zostalo juz wygenerowane.

        void generujPudelko();
};

#endif // PUDELKO_H
