#include "WDraw.h"
#include <stdio.h>

WDraw::WDraw(void)
{
}

WDraw::~WDraw(void)
{
}

void WDraw::drawSegment (const Point2d& p1, const Point2d& p2) {
    printf("(%f, %f) - (%f, %f)\n", p1.x(), p1.y(), p2.x(), p2.y());
}

void WDraw::drawText(const char* text) {
    printf("%s\n", text);
}
