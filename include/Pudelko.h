#ifndef PUDELKO_H
#define PUDELKO_H


class Pudelko
{
    public:
        Pudelko(float wys, float szer = 0, float gl = 0);

        void SetTekstura(GLuint* textura) { t = textura; }

        void Rysuj();
    protected:
    private:
        GLuint* t; // Tekstura pudelka
        float w[8][3];
};

#endif // PUDELKO_H
