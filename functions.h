#pragma once
 
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>

// global variables
int const WINDOW_WIDTH = 400;
int const WINDOW_HEIGHT = 400;

// function identifiers

void drawAll(sf::RenderWindow& window);
void drawCircle(sf::RenderWindow& window);
void printNothing();
int randBetweenBounds(int lowerBound, int upperBound);
class MyShapes;
class XYCoordinates;
void displayBezier(sf::RenderWindow& window, std::vector<sf::Vector2f> controlPoints, int lineResolutionPoints, float thickness);
int binomialCoefficient(int n, int k);
void drawLineOnCoordinates(sf::RenderWindow& window, sf::Vector2f XYCoordinate1, sf::Vector2f XYCoordinate2, float thickness);

void drawAll(sf::RenderWindow& window)
{
	window.clear();
	// put all function here

	std::vector<sf::Vector2f> controlPoints;
	controlPoints.push_back(sf::Vector2f(0, 0));
	controlPoints.push_back(sf::Vector2f(200, 0));
	controlPoints.push_back(sf::Vector2f(200, 200));


	
	displayBezier(window, controlPoints, 100, 10);

    window.display();

    return;
}

void drawCircle(sf::RenderWindow& window)
{
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Blue);
    window.draw(shape);
}



void printNothing()
{ // test function
	std::cout << "Nothing" << std::endl;
}

int randBetweenBounds(int lowerBound, int upperBound)
{
	if (upperBound > lowerBound)
	{
		int randomValue = (int)((rand() % (upperBound - lowerBound + 1)) + lowerBound);
		std::cout << randomValue << std::endl;
		return randomValue;
	}
}

class MyShapes
{
public:
	sf::CircleShape shape;
	sf::Vector2f setVelocity(sf::Vector2f newVelocity)
	{
		velocity = newVelocity;
	}
	sf::Vector2f getVelocity()
	{
		return velocity;
	}
	sf::Vector2f incrementPosition()
	{
		shape.setPosition(shape.getPosition() + getVelocity());
	}

private:
	sf::Vector2f velocity; // velocity is (X, Y). +X is to the right, +Y is down
};

class XYCoordinates
{
public:
	void setX(float xPosition)
	{
		xCoordinate = xPosition;
	}
	void setY(float yPosition)
	{
		yCoordinate = yPosition;
	}
	void setXY(float xPosition, float yPosition)
	{
		xCoordinate = xPosition;
		yCoordinate = yPosition;
	}
	float getX()
	{
		return xCoordinate;
	}
	float getY()
	{
		return yCoordinate;
	}

private:
	float xCoordinate;
	float yCoordinate;
};


void displayBezier(sf::RenderWindow& window, std::vector<sf::Vector2f> controlPoints, int lineResolutionPoints, float thickness)
{
	// bezierCoordinates is the coordinates that are given back to be printed to the screen. 
	// control points are the points that control the 
	// lineResolutionPoints is the number of points on the line. 
	// use the number of controlPoints to calculate which point lies where
	
	std::vector<sf::Vector2f> bezierCoordinates;
	int nControlPoints = (int)controlPoints.size();
	int curveOrder = nControlPoints - 1;

	if (lineResolutionPoints < 2)
	{
		// we need at least two points to make a line!
		lineResolutionPoints = 2;
	}

	sf::Vector2f coordinate;

	float t;
	float controlPointTermX;
	float controlPointTermY;

	for (int tNumber = 0; tNumber < lineResolutionPoints; tNumber++)
	{
		t = 1.f / (lineResolutionPoints - 1) * tNumber; // t value for the Bezier curve
		coordinate.x = 0.f;
		coordinate.y = 0.f;
		bezierCoordinates.push_back(coordinate);
		for (int i = 0; i < nControlPoints; i++)
		{
			controlPointTermX = (float)binomialCoefficient(curveOrder, i) * pow(t, i) * pow(1 - t, curveOrder - i) * controlPoints[i].x;
			controlPointTermY = (float)binomialCoefficient(curveOrder, i) * pow(t, i) * pow(1 - t, curveOrder - i) * controlPoints[i].y;
			bezierCoordinates[tNumber].x = bezierCoordinates[tNumber].x + controlPointTermX;
			bezierCoordinates[tNumber].y = bezierCoordinates[tNumber].y + controlPointTermY;
		}

		if (tNumber > 0)
		{
			drawLineOnCoordinates(window, bezierCoordinates[tNumber-1], bezierCoordinates[tNumber], thickness);
		}
	}
}

int binomialCoefficient(int n, int k)
{
	if (k == 0 || k == n)
		return 1;
	return binomialCoefficient(n - 1, k - 1) + binomialCoefficient(n - 1, k);
}


void drawLineOnCoordinates(sf::RenderWindow& window, sf::Vector2f XYCoordinate1, sf::Vector2f XYCoordinate2, float thickness)
{
	float xDifference = XYCoordinate2.x - XYCoordinate1.x;
	float yDifference = XYCoordinate2.y - XYCoordinate1.y;
	float length = (float) pow(xDifference * xDifference + yDifference * yDifference, 0.5);
	
	sf::RectangleShape thickLine;
	thickLine.setSize(sf::Vector2f(length, thickness));
	thickLine.setOrigin(sf::Vector2f(0, thickness / 2));
	thickLine.setPosition(XYCoordinate1);
	
	float angle = 0.f;

	if (xDifference != 0.f)
	{
		if (xDifference < 0)
		{
			angle = M_PI + atan(yDifference / xDifference); // atan() gives the angle in radians.
		}
		else
		{
			angle = atan(yDifference / xDifference); // atan() gives the angle in radians.
		}
	}

	if (xDifference == 0.f)
	{
		if (yDifference > 0.f)
		{
			angle = (float)(+M_PI / 2.f);
		}
		if (yDifference < 0.f)
		{
			angle = (float)(-M_PI / 2.f);
		}
	}
	thickLine.setRotation((float)(angle * 180.f / M_PI));
	window.draw(thickLine);
}
