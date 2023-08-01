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
    glfwSetKeyCallback(window, BoardEvent);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);


    glOrtho(- SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, - SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2, -1, 1);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

}

 void WDraw::mouseEvent(GLFWwindow* window, int button, int action, int mode)
{
    WDraw* wdraw = static_cast<WDraw*>(glfwGetWindowUserPointer(window));
    
    if (action == GLFW_PRESS)
        wdraw->event.type = MOUSE_PRESS;
    else if (action == GLFW_RELEASE)
        wdraw->event.type = MOUSE_RELEASE;
    
    wdraw->event.mouse.button = static_cast<MouseButton>(button);

    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);
    
    wdraw->event.mouse.x = mouseX;
    wdraw->event.mouse.y = mouseY;
}

 void WDraw::BoardEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
 {
     WDraw* wdraw = static_cast<WDraw*>(glfwGetWindowUserPointer(window));

     if (action == GLFW_PRESS)
         wdraw->event.type = KEYBOARD_PRESS;
     else if (action == GLFW_RELEASE)
         wdraw->event.type = KEYBOARD_RELEASE;

     wdraw->event.keyboard = key;
     
 }

 void WDraw::framebufferSizeCallback(GLFWwindow* window, int width, int height)
 {
     WDraw* wdraw = static_cast<WDraw*>(glfwGetWindowUserPointer(window));
     wdraw->event.type = RESIZE;

     glLoadIdentity();
     glOrtho(- width / 2, width / 2, - height / 2, height / 2, -1, 1);

     
     glfwSwapBuffers(window);
 }


bool WDraw::getStateWindow()
{
    return glfwWindowShouldClose(window);
}



void WDraw::drawSegment(const Point2d& p1, const Point2d& p2) {

    glBegin(GL_LINES);
    glVertex2d(p1.x(), p1.y());
    glVertex2d(p2.x(), p2.y());
    glEnd();
}

void WDraw::drawArcCircle(const Point2d& p, double r, double startAngle, double endAngle)
{
    glPushMatrix();
    
    glTranslatef(p.x(), p.y(), 0.0);

    glBegin(GL_LINE_STRIP);

    for (int i = 0; i <= detailLevel; ++i) {
        double angle = startAngle + (endAngle - startAngle) * static_cast<double>(i) / detailLevel;
        double x = r * std::cos(angle);
        double y = r * std::sin(angle);
        glVertex2d(x, y);
    }

    glEnd();
    glPopMatrix();
}

void WDraw::drawCircle(const Point2d& p, double r)
{
    drawArcCircle(p, r, 0, 2 * PI);
}

void WDraw::drawRect(const Point2d& p1, double w, double h)
{
    glBegin(GL_LINE_LOOP);

    glVertex2d(p1.x(), p1.y());
    glVertex2d(p1.x() + w, p1.y());
    glVertex2d(p1.x() + w, p1.y() + h);
    glVertex2d(p1.x(), p1.y() + h);

    glEnd();
}

void WDraw::drawText(const char* text) {
    
}

void WDraw::fillStroke(int r, int g, int b)
{
    glColor3f(r, g, b);
}

void WDraw::translate(const Point2d& p1)
{

}

void WDraw::wStroke(float w)
{
    glLineWidth(w);
}







