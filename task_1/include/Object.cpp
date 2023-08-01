#include "Object.h"

std::shared_ptr<BoundyBox> Object::getBoundyBox() const
{
    return boundyBox;
}
