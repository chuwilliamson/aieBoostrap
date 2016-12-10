#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Audio.h"
#include <math.h>
#include <vector>
#define UNITS 10
class GameObject
{
public:
	GameObject() {}
	virtual void Draw(aie::Renderer2D *r, float thickness = 1.0f) = 0;
};

class Point {
public:
	Point() : _x(0.f), _y(0.f) {}

	Point(float x1, float y1) :_x(x1), _y(y1)
	{
	}

	Point operator-(const Point& other)
	{
		Point p = { _x - other._x, _y - other._y };
		return p;
	}
	Point operator+(const Point& other)
	{
		Point p = { _x + other._x, _y + other._y };
		return p;
	}
	Point operator*(const float scale)
	{
		Point p = { _x *scale, _y*scale };
		return p;
	}

	void normalized(float width = 1280.0f, float height = 720.0f, float units = 10.0f)
	{

		_x *= width / units;
		_y *= height / units;

		_x += width / 2;
		_y += height / 2;

	}

	~Point()
	{

	}

	float _x, _y;


};

class Vector2 : Point
{

};

class Line : public GameObject {
public:
	Line() : start(new Point(0.f, 0.f)), end(new Point(0.f, 0.f))
	{
	}
	Line(const Point p1, const Point p2) : start(new Point(p1._x, p1._y)), end(new Point(p2._x, p2._y))
	{
	}
	Line(Point *p1, Point *p2) : start(p1), end(p2)
	{
	}

	//draw from coordinate starting in bot left of screen
	void Draw(aie::Renderer2D *r, float thickness = 1.0f) override
	{
		r->setRenderColour(0, 0, 0);
		r->drawLine(start->_x, start->_y, end->_x, end->_y, thickness, 0);
	}



	Line operator=(const Line l)
	{
		this->start = l.start;
		this->end = l.end;
		return *this;
	}
	~Line()
	{
		delete start, end;
		start = nullptr;
		end = nullptr;
	}

private:
	Point *start, *end;

};

class Triangle :public GameObject
{
public:
	Triangle()
	{
		p1 = new Point(-1, 0);
		p2 = new Point(1, 0);
		p3 = new Point(0, 1);

		p1->normalized();
		p2->normalized();
		p3->normalized();
		//counterclockwise
		l1 = new Line(p1, p2);
		l2 = new Line(p2, p3);
		l3 = new Line(p3, p1);
	};

	Vector2 _center;
	Point * p1;	Point * p2;	Point * p3;
	Line * l1;	Line * l2;	Line * l3;


	// Inherited via GameObject
	void Draw(aie::Renderer2D * r, float thickness = 1.0f) override
	{
		l1->Draw(r, thickness);
		l2->Draw(r, thickness);
		l3->Draw(r, thickness);
	}
	~Triangle()
	{
		delete p1; p1 = nullptr;
		delete p2; p2 = nullptr;
		delete p3; p3 = nullptr;
		delete l1; l1 = nullptr;
		delete l2; l2 = nullptr;
		delete l3; l3 = nullptr;

	}
};

class GridApplication : public aie::Application {

public:

	GridApplication();
	virtual ~GridApplication();

	virtual bool startup();
	virtual void shutdown();
	virtual void update(float deltaTime);
	virtual void draw();
	void aiedraw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Texture*		m_texture;
	aie::Texture*		m_shipTexture;
	aie::Font*			m_font;
	aie::Audio*			m_audio;

	std::vector<Line> m_grid;
	std::vector<GameObject*> m_gameObjects;
 

	float m_cameraX, m_cameraY;
	float m_timer;
};