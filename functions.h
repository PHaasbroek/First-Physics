#pragma once

// global variables
int WINDOW_WIDTH = 400;
int WINDOW_HEIGHT = 400;

// function identifiers

void drawAll(sf::RenderWindow& window);
void drawCircle(sf::RenderWindow& window);
void printNothing();
int randBetweenBounds(int lowerBound, int upperBound);
class MyShapes;
class XYCoordinates;
void displayBezier(sf::RenderWindow& window, std::vector<XYCoordinates> controlPoints, int lineResolutionPoints);
int binomialCoefficient(int n, int k);

void drawAll(sf::RenderWindow& window)
{
	// put all function here
    
    window.clear();

    drawCircle(window);
    
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


void displayBezier(sf::RenderWindow& window, std::vector<XYCoordinates> controlPoints, int lineResolutionPoints)
{
	// bezierCoordinates is the coordinates that are given back to be printed to the screen. 
	// control points are the points that control the 
	// lineResolutionPoints is the number of points on the line. 
	// use the number of controlPoints to calculate which point lies where

	std::vector<XYCoordinates> bezierCoordinates;
	sf::
	int nControlPoints = controlPoints.size();
	int curveOrder = nControlPoints - 1;

	//std::cout << "nControlPoints = " << nControlPoints << std::endl;

	if (lineResolutionPoints < 2)
	{
		// we need at least two points to make a line!
		lineResolutionPoints = 2;
	}

	XYCoordinates coordinate;

	float t;
	float controlPointTermX;
	float controlPointTermY;

	for (int tNumber = 0; tNumber < lineResolutionPoints; tNumber++)
	{
		t = 1.f / (lineResolutionPoints - 1) * tNumber; // t value for the Bezier curve
		coordinate.setXY(0, 0);
		bezierCoordinates.push_back(coordinate);
		for (int i = 0; i < nControlPoints; i++)
		{
			controlPointTermX = (float)binomialCoefficient(curveOrder, i) * pow(t, i) * pow(1 - t, curveOrder - i) * controlPoints[i].getX();
			controlPointTermY = (float)binomialCoefficient(curveOrder, i) * pow(t, i) * pow(1 - t, curveOrder - i) * controlPoints[i].getY();
			bezierCoordinates[tNumber].setX(bezierCoordinates[tNumber].getX() + controlPointTermX);
			bezierCoordinates[tNumber].setY(bezierCoordinates[tNumber].getY() + controlPointTermY);
		}

		/*
		if (tNumber > 0)
		{
			
		}
		*/
		sf::Vertex()

	}


	sf::CircleShape circle;
	circle.setRadius(50.f);
	circle.setFillColor(sf::Color::Green); //!! The function can print a shape to the screen!!
	window.draw(circle);
}

int binomialCoefficient(int n, int k)
{
	if (k == 0 || k == n)
		return 1;
	return binomialCoefficient(n - 1, k - 1) + binomialCoefficient(n - 1, k);
}

//sf::RectangleShape line(sf::Vector2f(150, 5));
//line.rotate(45);

sf::RectangleShape thicklineShape(sf::Vector2f XYCoordinate1, sf::Vector2f XYCoordinate2, float thickness)
{
	float length = pow((XYCoordinate2.x - XYCoordinate1.x) ^ 2 + (XYCoordinate2.y - XYCoordinate1.y) ^ 2, 0.5);
	
	sf::RectangleShape thickLine( sf::Vector2f(100.f, 5.f), 5 );



	return thickLine;
}