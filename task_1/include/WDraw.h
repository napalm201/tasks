#pragma once
#include <GLFW/glfw3.h>
#include "Point2d.h"
#include "Event.h"
#include <cmath>
#include <string>
#define PI 3.14



class WDraw
{

public:
    WDraw(void);
    WDraw(std::string name);

    virtual ~WDraw(void);

public:
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 640;
    std::string name;

    Event event;
 
    GLFWwindow* window;
   
public:
    bool getStateWindow();

    virtual void drawSegment(const Point2d& p1, const Point2d& p2);
    virtual void drawArcCircle(const Point2d& p, double r, double startAngle, double endAngle);
    virtual void drawCircle(const Point2d& p, double r);
    virtual void drawRect(const Point2d& p1, double w, double h);

    virtual void drawText(const char* text);

    virtual void fillStroke(int r, int g, int b);
    virtual void translate(const Point2d& p1);
    virtual void wStroke(float w);

private:

    void init();
    static void mouseEvent(GLFWwindow* window, int button, int action, int mode);
    static void BoardEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

private:
    static int detailLevel;

};
