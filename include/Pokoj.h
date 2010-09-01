#ifndef POKOJ_H
#define POKOJ_H


class Pokoj
{
    public:
        Pokoj(float bok, bool sciany = false);

        bool GetSciany() { return bSciany; }
        void SetSciany(bool val) { bSciany = val; }

        void Rysuj();
    protected:
    private:
        bool bSciany;
        float w[4][3];
};

#endif // POKOJ_H
