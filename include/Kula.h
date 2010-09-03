#ifndef KULA_H
#define KULA_H


class Kula
{
    public:
        Kula(float promien, float srodek[]);
        void Rysuj();
        void SetKolors(int num, float *kolory);
        void RysujAnimacje(float p, int ilosc, bool mix_color = false);

    protected:
    private:
        void generujKule();

        float r; // Promien kuli.
        float s[3]; // Wspolrzedne punkut srodka.
        float *k; // Zestaw kolorów dla kul.
        int num_k; // Ilosc kolorow w powyzszej macierzy.

//        bool wygenerowane;
//
//        GLuint ball; // Lista wyswietlania kuli.
};

#endif // KULA_H
