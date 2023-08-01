#include "BoundyBox.h"

void BoundyBox::draw(WDraw& wdraw) const
{
	wdraw.fillStroke(67, 67, 0);
	rect.draw(wdraw);
	wdraw.drawText(name.c_str());
	wdraw.drawText(std::to_string(length).c_str());
}
