//
// copyright 2018 Palestine Polytechnic Univeristy
//
// This software can be used and/or modified for academich use as long as 
// this commented part is listed
//
// Last modified by: Zein Salah, on 24.02.2021
//


#include "RenderWidget.h"
#include <QPainter>
#include <set>
#include <iostream>

using namespace std;

struct point
{
	float x;
	float y;
};

set<char> getDIrections(point p);
point clipAgainstLeft(point p1, point p2);
point clipAgainstbottom(point p1, point p2);
point clipAgainstright(point p1, point p2);
point clipAgainstTop(point p1, point p2);



int xmin = 200, xmax = 400, ymin = 200, ymax = 400;
RenderWidget::RenderWidget(QWidget *parent) : QWidget(parent)
{
	// to be implemeted later
}

QSize RenderWidget::minimumSizeHint() const
{
	return QSize(100, 100);
}

QSize RenderWidget::sizeHint() const
{
	return QSize(600, 600);
}

void RenderWidget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	QColor color(0, 0, 0);
	painter.setPen(color);

	painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
	painter.drawRect(QRect(xmin, ymin, xmax - xmin, ymax - ymin));

	point p1 = { 350 , 350 }, p2 = {180 ,150 };
	painter.drawLine(QLine(p1.x, p1.y, p2.x, p2.y));

	set <char> s1 = getDIrections(p1), s2 = getDIrections(p2);
	//check if the whole line is outside the window 
	// we may need to update the directions after each clip
	if (s1.count('L'))
	{
		p1 = clipAgainstLeft(p1, p2);
		s1.clear();
		s1 = getDIrections(p1);
	}
	if (s1.count('B'))
	{
		p1 = clipAgainstbottom(p1, p2);
		s1.clear();
		s1 = getDIrections(p1);
	}
	if (s1.count('R'))
	{
		p1 = clipAgainstright(p1, p2);
		s1.clear();
		s1 = getDIrections(p1);
	}
	if (s1.count('T'))
	{
		p1 = clipAgainstTop(p1, p2);
		s1.clear();
		s1 = getDIrections(p1);
	}
	////////
	if (s2.count('L'))
	{
		p2 = clipAgainstLeft(p1, p2);
		s2.clear();
		s2 = getDIrections(p2);
	}
	if (s2.count('B'))
	{
		p2 = clipAgainstbottom(p1, p2);
		s2.clear();
		s2 = getDIrections(p2);
	}
	if (s2.count('R'))
	{
		p2 = clipAgainstright(p1, p2);
		s2.clear();
		s2 = getDIrections(p2);
	}
	if (s2.count('T'))
	{
		p2 = clipAgainstTop(p1, p2);
		s2.clear();
		s2 = getDIrections(p2);
	}

	QColor color2(255, 0, 0);
	painter.setPen(color2);


	painter.drawLine(QLine(p1.x, p1.y, p2.x, p2.y));
}

set<char> getDIrections(point p)
{
	set<char>s;
	if (p.x < xmin)	s.insert('L');
	if (p.y > ymax) s.insert('B');
	if (p.x > xmax) s.insert('R');
	if (p.y < ymin) s.insert('T');
	return s;
}

point clipAgainstLeft(point p1, point p2)
{
	float slope = (p2.y - p1.y) / (p2.x - p1.x);
	point final;
	final.x = xmin;
	final.y = p2.y - (slope*(p2.x - xmin));
	return final;
}
point clipAgainstbottom(point p1, point p2)
{
	float slope = (p2.y - p1.y) / (p2.x - p1.x);
	point final;
	final.y = ymax;
	final.x = ((ymax - p2.y) / slope) + p2.x;
	return final;
}
point clipAgainstright(point p1, point p2)
{
	float slope = (p2.y - p1.y) / (p2.x - p1.x);
	point final;
	final.x = xmax;
	final.y = p2.y - (slope*(p2.x - xmax));
	return final;
}
point clipAgainstTop(point p1, point p2)
{
	float slope = (p2.y - p1.y) / (p2.x - p1.x);
	point final;
	final.y = ymin;
	final.x = ((ymin - p2.y) / slope) + p2.x;
	return final;

}