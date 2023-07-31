#include "WDraw.h"
#include <stdio.h>
#include <functional>

int WDraw::detailLevel = 20;


WDraw::WDraw(void)
{
    init();
}

WDraw::WDraw(std::string name) : name(name)
{
    init();
}

WDraw::~WDraw(void)
{
    glfwTerminate();
}

void WDraw::init()
{
    if (!glfwInit())
        return;

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, name.c_str(), nullptr, nullptr);
    
    if (!window)
        return;

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);

    glfwSetMouseButtonCallback(window, mouseEvent);

    glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

}

 void WDraw::mouseEvent(GLFWwindow* window, int button, int action, int mode)
{
    WDraw* wdraw = static_cast<WDraw*>(glfwGetWindowUserPointer(window));
    wdraw->event.type = MOUSE;
    
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);
    
    wdraw->event.mouse.x = mouseX;
    wdraw->event.mouse.y = mouseY;
}

bool WDraw::getStateWindow()
{
    return glfwWindowShouldClose(window);
}



void WDraw::drawSegment(const Point2d& p1, const Point2d& p2) {
    printf("(%f, %f) - (%f, %f)\n", p1.x(), p1.y(), p2.x(), p2.y());
}

void WDraw::drawArcCircle(const Point2d& p, double r, double startAngle, double endAngle)
{
    double dAngle = (endAngle - startAngle) / detailLevel;
    double firstAngle = startAngle;

    double prevAngle = startAngle;
    startAngle += dAngle;

    for (; startAngle <= endAngle; prevAngle = startAngle, startAngle += dAngle) {

        Point2d p1(r * cos(prevAngle) + p.x(), r * sin(prevAngle) + p.y());
        Point2d p2(r * cos(startAngle) + p.x(), r * sin(startAngle) + p.y());

        drawSegment(p1, p2);
    }

    Point2d p1(r * cos(firstAngle) + p.x(), r * sin(firstAngle) + p.y());
    Point2d p2(r * cos(startAngle) + p.x(), r * sin(startAngle) + p.y());
    drawSegment(p1, p2);

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







