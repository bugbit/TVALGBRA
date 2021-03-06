// TVALGBRA.h: archivo de inclusión para archivos de inclusión estándar del sistema,
// o archivos de inclusión específicos de un proyecto.

#ifndef __TVALGEBRA_H

#define __TVALGEBRA_H

const int GreetThemCmd = 100;

class THeapView;
class TClockView;

class TTVAlgebraApp : public TApplication
{

public:

    TTVAlgebraApp();

    virtual void handleEvent(TEvent& event);
    static TMenuBar* initMenuBar(TRect);
    static TStatusLine* initStatusLine(TRect);

    virtual void idle();              // Updates heap and clock views

private:

    THeapView* heap;                  // Heap view
    TClockView* clock;                // Clock view

    void greetingBox();
};


#endif // !__TVALGEBRA_H