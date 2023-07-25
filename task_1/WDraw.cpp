#include "WDraw.h"
#include <stdio.h>


int WDraw::detailLevel = 20;

WDraw::WDraw(void)
{
}

WDraw::~WDraw(void)
{
}

void WDraw::drawSegment(const Point2d& p1, const Point2d& p2) {
    printf("(%f, %f) - (%f, %f)\n", p1.x(), p1.y(), p2.x(), p2.y());
}

void WDraw::drawArcCircle(const Point2d& p, double r, double startAngle, double endAngle)
{
    double dAngle = (endAngle - startAngle) / detailLevel;
    double prevAngle = startAngle;
    startAngle += dAngle;

    for (; startAngle <= endAngle; prevAngle = startAngle, startAngle += dAngle) {
        Point2d p1(r * cos(prevAngle), r * sin(prevAngle));
        Point2d p2(r * cos(startAngle), r * sin(startAngle));
        drawSegment(p1, p2);
    }
}

void WDraw::drawCircle(const Point2d& p, double r)
{
    drawArcCircle(p, r, 0, 2 * PI);
}

void WDraw::drawText(const char* text) {
    printf("%s\n", text);
}

void WDraw::fillColor(int r, int g, int b)
{
    color = Color(r, g, b);
}

void WDraw::translate(const Point2d& p1)
{
}
