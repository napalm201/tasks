#pragma once
#include "Point2d.h"
#include "Event.h"
#include <cmath>
#define PI 3.14



class WDraw
{

public:
    WDraw(void);
    virtual ~WDraw(void);


public:
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 640;


    Event event;
    /************************************************************************/
    /* Основной метод отрисовки                                             */
    /************************************************************************/
public:
    virtual void drawSegment(const Point2d& p1, const Point2d& p2);
    virtual void drawArcCircle(const Point2d& p, double r, double startAngle, double endAngle);
    virtual void drawCircle(const Point2d& p, double r);

    /************************************************************************/
    /*                                                                      */
    /************************************************************************/
    virtual void drawText(const char* text);
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

};
