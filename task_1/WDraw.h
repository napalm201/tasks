#pragma once
#include "Point2d.h"
<<<<<<< HEAD
#include <cmath>
#define PI 3.14
=======
>>>>>>> b3690d5b2f029f078bfd182bf7b3949d62d5640f

class WDraw
{

public:
<<<<<<< HEAD
=======

>>>>>>> b3690d5b2f029f078bfd182bf7b3949d62d5640f
    WDraw(void);
    virtual ~WDraw(void);

    /************************************************************************/
    /* Основной метод отрисовки                                             */
    /************************************************************************/
    virtual void drawSegment(const Point2d& p1, const Point2d& p2);
<<<<<<< HEAD
    virtual void drawArcCircle(const Point2d& p, double r, double startAngle, double endAngle);
    virtual void drawCircle(const Point2d& p, double r);
=======

>>>>>>> b3690d5b2f029f078bfd182bf7b3949d62d5640f
    /************************************************************************/
    /*                                                                      */
    /************************************************************************/
    virtual void drawText(const char* text);
<<<<<<< HEAD
    virtual void fillColor(int r, int g, int b);
    virtual void translate(const Point2d& p1);

private:

    struct Color {
        Color() = default;
        Color(int r, int g, int b) : r(r), g(g), b(b) {}
        int r = 0;
        int g = 0;
        int b = 0;
    };

    Color color;

    static int detailLevel;
=======

>>>>>>> b3690d5b2f029f078bfd182bf7b3949d62d5640f
};
