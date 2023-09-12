
#include <iostream>

#include "MyAplication/MyAplication.h"

int main() {
    MyAplication& app = MyAplication::getApp();
    app.runTimeConsole();

}
