#ifndef TEKSTURA_H
#define TEKSTURA_H
#include <GL/glaux.h>

class Tekstura
{
    public:
        Tekstura();
        bool laduj(char *nazwa);
        GLuint* pobierz(int i);

    protected:
    private:
        int ostatni_nr;
        GLuint textury[5];

        AUX_RGBImageRec* loadBMPFile(char *filename);
};

#endif // TEKSTURA_H
