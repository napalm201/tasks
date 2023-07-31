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
 
private:
    GLFWwindow* window;
   
public:
    bool getStateWindow();

    virtual void drawSegment(const Point2d& p1, const Point2d& p2);
    virtual void drawArcCircle(const Point2d& p, double r, double startAngle, double endAngle);
    virtual void drawCircle(const Point2d& p, double r);


    virtual void drawText(const char* text);
    virtual void fillColor(int r, int g, int b);
    virtual void translate(const Point2d& p1);

private:

    void init();
    static void mouseEvent(GLFWwindow* window, int button, int action, int mode);

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
