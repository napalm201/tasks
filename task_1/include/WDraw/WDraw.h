#pragma once 
#include <GLFW/glfw3.h>
#include "Objects/Point2d.h"
#include "Event.h"
#include <string>

class WDraw 
{
public:
	WDraw(const WDraw& other) = delete;
	WDraw& operator=(const WDraw& other) = delete;

private:
	WDraw(void);
	WDraw(std::string name);
	~WDraw(void);
	static WDraw wDraw;

public:
	static WDraw& getWDraw();

public:
    void drawSegment(const Point2d& p1, const Point2d& p2);
    void drawArcCircle(const Point2d& p, double r, double startAngle, double endAngle);
    void drawCircle(const Point2d& p, double r);
    void drawRect(const Point2d& p1, double w, double h);

    void drawText(const char* text);

	void background(int r, int g, int b);
    void render();

    void fillStroke(int r, int g, int b);
    void wStroke(float w);

private:
    void init();
    static void mouseEvent(GLFWwindow* window, int button, int action, int mode);
    static void BoardEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	static void windowCloseCallback(GLFWwindow* window);

public:
	Event event;

private:
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 640;

	std::string name;
	GLFWwindow* window;

	static int detailLevel;
};