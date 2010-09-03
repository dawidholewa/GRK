#ifndef KULA_H
#define KULA_H


class Kula
{
    public:
        Kula(float promien, float srodek[]);
        void Rysuj();
        void RysujAnimacje(float x, float y, float z);

    protected:
    private:
        void generujKule();

        float r; // Promien kuli.
        float s[3]; // Wspolrzedne punkut srodka.

        bool wygenerowane;

        GLuint ball; // Lista wyswietlania kuli.
        GLuint balls; // Lista wyswietlania kilku kuli.
};

#endif // KULA_H
