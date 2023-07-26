#include "ArcCircle.h"

void ArcCircle::draw(WDraw& wdraw)
{
	wdraw.fillColor(0, 0, 0);
	wdraw.drawArcCircle(p, r, startAngle, endAngle);
}
