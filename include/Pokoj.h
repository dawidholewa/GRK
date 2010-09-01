#ifndef POKOJ_H
#define POKOJ_H


class Pokoj
{
    public:
        Pokoj(float bok, bool sciany = false);

        bool GetSciany() { return bSciany; }
        void SetSciany(bool val) { bSciany = val; }

        void SetTeksturaPodlogi(GLuint* t) {tPodloga = t; }
        void SetTeksturaSciany(GLuint* t) {tSciany = t; }

        void Rysuj();
    protected:
    private:
        bool bSciany;

        GLuint* tPodloga;
        GLuint* tSciany;

        int pt;

        float w[8][3];
};

#endif // POKOJ_H
