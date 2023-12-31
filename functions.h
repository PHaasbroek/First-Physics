#pragma once
 
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>

// global variables
const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 400;

// function identifiers

void drawAll(sf::RenderWindow& window);
void drawCircle(sf::RenderWindow& window);
void printNothing();
int randBetweenBounds(int lowerBound, int upperBound);
class MyShapes;
void drawBezier(sf::RenderWindow& window, std::vector<sf::Vector2f> controlPoints, int lineResolutionPoints, float thickness);
int binomialCoefficient(int n, int k);
void drawLineOnCoordinates(sf::RenderWindow& window, sf::Vector2f XYCoordinate1, sf::Vector2f XYCoordinate2, float thickness);
float atanFullRevolution(float xDifference, float yDifference);
void drawPiecewiseBezier(sf::RenderWindow& window, std::vector<std::vector< sf::Vector2f > > controlPoints, int lineResolutionPoints, float thickness);
sf::Vector2f mirrorAboutPoint(sf::Vector2f point, sf::Vector2f mirror); 
//void drawPBCircle(sf::RenderWindow& window, sf::Vector2f centreOrigin, float radius);
void testTimeOfFunction();
void initiateProgram();
class PhysicsBall;
float vectorDot(sf::Vector2f vector1, sf::Vector2f vector2);
sf::Vector2f normaliseVector(sf::Vector2f vector);
sf::Vector2f scaleVector(sf::Vector2f vector1, float scalar);
sf::Vector2f elementMultiply(sf::Vector2f vector1, sf::Vector2f vector2);
class MyWall;
std::vector<PhysicsBall> initiateVectorOfBalls(float radius, int numberOfBalls);
float NURBS_basis(float u, std::vector<float>& knots, int parameter_k, int i);
bool checkNonDecreasing(std::vector<float> knots);
std::vector<float> linearSpace(float startValue, float endValue, int numberOfElements);


class PhysicsBall
{
public:
	sf::CircleShape shape;

	void setXVelcity(float velocityNew)
	{
		velocity.x = velocityNew;
	}
	void setYVelcity(float velocityNew)
	{
		velocity.y = velocityNew;
	}

	void setVelocity(sf::Vector2f velocityNew)
	{
		velocity = velocityNew;
	}

	void changeXVelocity(float changeVelocity)
	{
		velocity.x = velocity.x + changeVelocity;
	}
	void changeYVelocity(float changeVelocity)
	{
		velocity.y = velocity.y + changeVelocity;
	}
	float getXVelocity()
	{
		return velocity.x;
	}
	float getYVelocity()
	{
		return velocity.y;
	}
	void reflectVelocity(sf::Vector2f reflectionNormal)
	{ // seems to work just fine!
		reflectionNormal = normaliseVector(reflectionNormal);
		velocity = velocity - scaleVector(scaleVector(reflectionNormal, vectorDot(velocity, reflectionNormal)), 2);
		//std::cout << " reflect vector " << velocity.x << " " << velocity.y << std::endl;
	}

	void printVelocity()
	{
		std::cout << "x velocity = " << velocity.x << " y velocity = " << velocity.y << std::endl;
	}

	bool pointCollide(sf::Vector2f coordinate)
	{
		// detect collision for a ball
		sf::Vector2f ballCoordinate = shape.getPosition();
		float distance = sqrt(pow(coordinate.x - ballCoordinate.x, 2) + pow(coordinate.y - ballCoordinate.y, 2));
		return (distance < shape.getRadius());
	}

	sf::Vector2f velocity = sf::Vector2f(0, 0); // x velocity and y velocity
};

class MyWall
{
public:
	sf::RenderWindow& window;

	void drawAll()
	{
		for (int i = 0; i < nWallElements; i++)
		{
			drawElement(i);
		}
	}
	void drawElement(int wallElement)
	{
		drawLineOnCoordinates(window, wallCoordinate1[wallElement], wallCoordinate2[wallElement], thickness);
	}

	void setWallCoordinates(std::vector < sf::Vector2f > newWallCoordinate1, std::vector < sf::Vector2f > newWallCoordinate2)
	{
		if (newWallCoordinate1.size() != newWallCoordinate2.size())
		{
			std::cout << "Error: wall coordinates vector should have equal length.\n";
			std::cout << "newWallCoordinate1.size() = " << newWallCoordinate1.size() << "\n";
			std::cout << "newWallCoordinate2.size() = " << newWallCoordinate2.size() << "\n";
			std::cout << std::endl;
			return;
		}
		int nWallElements = newWallCoordinate1.size();

		wallCoordinate1 = newWallCoordinate1;
		wallCoordinate2 = newWallCoordinate2;
	}

private:
	std::vector < sf::Vector2f > wallCoordinate1;
	std::vector < sf::Vector2f > wallCoordinate2;
	int nWallElements = 0;
	float thickness = 5.f;
};

class unpassableWall
{
public:
	void setWallCoordinates( sf::Vector2f newWallCoordinate1, sf::Vector2f newWallCoordinate2)
	{
		wallCoordinate1 = newWallCoordinate1;
		wallCoordinate2 = newWallCoordinate2;
	}

private:
	sf::Vector2f wallCoordinate1 = sf::Vector2f(0, 0);
	sf::Vector2f wallCoordinate2 = sf::Vector2f(0, 0);
	float thickness = 5.f;
};

void initiateProgram()
{// functions that run only once
	
	
	std::vector<float> knotVector;
	knotVector.push_back(0.0);
	knotVector.push_back(1.0);
	knotVector.push_back(2.0);
	knotVector.push_back(3.0);
	knotVector.push_back(4.0);

	int endVal = 100;
	float increment = (float)(4) / (float)(endVal);

	for (int i = 0; i < endVal; i++)
	{
		
		std::cout << i << "  " << (float)(i)*increment << "  " << NURBS_basis((float)(i)*increment, knotVector, 1, 1) << std::endl;

	}

	
	//MyWall firstWall();
	//NURBS_basis(1.f, 1);
	//testTimeOfFunction();
}

void drawAll(sf::RenderWindow& window)
{	// functions that run as long as the window is open.
	window.clear();
	// put all function here

	//std::vector<sf::Vector2f> controlPoints;
	//controlPoints.push_back(sf::Vector2f(0, 0));
	//controlPoints.push_back(sf::Vector2f(200, 100));
	//controlPoints.push_back(sf::Vector2f(300, 300));

	std::vector<std::vector<sf::Vector2f>> controlPointsMatrix;
	controlPointsMatrix.push_back({ sf::Vector2f(0, 0), sf::Vector2f(100, 100), sf::Vector2f(200, 200) , sf::Vector2f(200, 300) });
	controlPointsMatrix.push_back({ sf::Vector2f(200, 300) , mirrorAboutPoint(controlPointsMatrix[0][2], controlPointsMatrix[0][3]), sf::Vector2f(300, 300)});

	//drawBezier(window, controlPoints, 20, 5);
	
	drawPiecewiseBezier(window, controlPointsMatrix, 10, 5);
	//drawPBCircle(window, sf::Vector2f(0, 0), 50);

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

/*
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
*/

void drawBezier(sf::RenderWindow& window, std::vector<sf::Vector2f> controlPoints, int lineResolutionPoints, float thickness)
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

	float angle = atanFullRevolution(xDifference, yDifference);

	thickLine.setRotation((float)(angle * 180.f / M_PI));
	window.draw(thickLine);
}

float atanFullRevolution(float xDifference, float yDifference)
{
	float angle = 0.f;

	if (xDifference != 0.f)
	{
		if (xDifference < 0)
			angle = M_PI + atan(yDifference / xDifference); // atan() gives the angle in radians.

		if (xDifference > 0)
			angle = atan(yDifference / xDifference); // atan() gives the angle in radians.
	}

	if (xDifference == 0.f)
	{
		if (yDifference > 0.f)
			angle = (float)(+M_PI / 2.f);
		
		if (yDifference < 0.f)
			angle = (float)(-M_PI / 2.f);
	}

	return angle;
}

void drawPiecewiseBezier(sf::RenderWindow& window, std::vector<std::vector< sf::Vector2f > > controlPoints, int lineResolutionPoints, float thickness)
{
	//vectorOfVector.size() gives the number of rows.
	//vectorOfVector[i].size() gives the number of columns in the i'th row.
	//first piece order always determined by the number of points. 
	
	int nPieces = controlPoints.size();

	for (int iPiece = 0; iPiece < nPieces; iPiece++)
	{
		drawBezier(window, controlPoints[iPiece], lineResolutionPoints, thickness);	
	}
}

sf::Vector2f mirrorAboutPoint(sf::Vector2f point, sf::Vector2f mirror)
{
	sf::Vector2f mirroredPoint;
	// mirroredPoint = mirror + (mirror - point)
	mirroredPoint.x = 2 * mirror.x - point.x; 
	mirroredPoint.y = 2 * mirror.y - point.y;
	return mirroredPoint;
}

/*
void drawPBCircle(sf::RenderWindow& window, sf::Vector2f centreOrigin, float radius)
{
	//sf::Vector2f originPoint(sf::Vector2f(0, 0));
	int nControlsPerPiece = 4;
	int nKnots = 4; // number of knots in the circle
	int nPieces = nKnots * (nControlsPerPiece-1);

	std::vector<sf::Vector2f> coordinates;

	for (int i = 0; i < nPieces; i++)
	{
		float angle = i * 2 * M_PI / nPieces;
		coordinates.push_back(sf::Vector2f(centreOrigin.x + radius * cos(angle), centreOrigin.y + radius * sin(angle)));
	}

	std::cout << " length of coordinates = " << coordinates.size() << std::endl;
	//std::cout << coordinates[0].x << std::endl;

	std::vector<std::vector<sf::Vector2f>> controlPoints;
	std::vector<sf::Vector2f > controlPointsPiece;

	for (int i = 0; i < nKnots; i++)
	{
		std::cout << " i = " << i << std::endl;

		for (int j = 0; j < nControlsPerPiece; j++)
		{
			//std::cout << " j = " << j << std::endl;
			//std::cout << " element " << i * nControlsPerPiece + j << std::endl;
			//std::cout << " size of controlPoints " << i * nControlsPerPiece + j << std::endl;

			controlPointsPiece.push_back(coordinates[i * nControlsPerPiece + j]);

			std::cout << " i = " << i << " j = " << j << " x = " << coordinates[i * nControlsPerPiece + j].x << " y = " << coordinates[i * nControlsPerPiece + j].y << std::endl;
		}
		controlPoints.push_back(controlPointsPiece);
	}

	//drawPiecewiseBezier(window, controlPoints, 20, 5);
}
*/

sf::Vector2f normaliseVector(sf::Vector2f vector)
{
	float length = pow(vector.x * vector.x + vector.y * vector.y, 0.5);
	vector.x = vector.x / length;
	vector.y = vector.y / length;
	return vector;
}

float vectorDot(sf::Vector2f vector1, sf::Vector2f vector2)
{
	return float (vector1.x * vector2.x + vector1.y * vector2.y);
}

sf::Vector2f elementMultiply(sf::Vector2f vector1, sf::Vector2f vector2)
{
	return sf::Vector2f(vector1.x * vector2.x, vector1.y * vector2.y);
}
sf::Vector2f scaleVector(sf::Vector2f vector1, float scalar)
{
	return sf::Vector2f(vector1.x * scalar, vector1.y * scalar);
}

std::vector<PhysicsBall> initiateVectorOfBalls(float radius, int numberOfBalls)
{
	PhysicsBall firstBall;
	firstBall.shape.setOrigin(sf::Vector2f(radius, radius));
	firstBall.shape.setRadius(radius);
	firstBall.shape.setFillColor(sf::Color::Magenta);
	std::vector<PhysicsBall> vectorOfBalls;
	vectorOfBalls.push_back(firstBall);
	return vectorOfBalls;
}

void testTimeOfFunction()
{
	sf::Clock clockTotal1;
	int totalIterations = 500;
	sf::Clock clockIncrement;

	////////////////////////////////////////////////////////////////
	// using \n;
	std::vector< sf::Time > timeV;
	sf::Clock timeTotal2;
	clockIncrement.restart();
	for (int i = 0; i < totalIterations; i++)
	{
		sf::Time timeIncrement = clockIncrement.getElapsedTime();
		std::cout << "Iteration " << i << " time increment " << timeIncrement.asMicroseconds() << "\n";
		clockIncrement.restart();
	}
	sf::Time elapsedTime2 = timeTotal2.getElapsedTime();
	timeV.push_back(timeTotal2.getElapsedTime()); 

	////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////
	// using endl;
	clockIncrement.restart();
	for (int i = 0; i < totalIterations; i++)
	{
		sf::Time timeIncrement = clockIncrement.getElapsedTime();
		std::cout << "Iteration " << i << " increment time " << timeIncrement.asMicroseconds() << std::endl;
		clockIncrement.restart();
	}
	sf::Time elapsedTime1 = clockTotal1.getElapsedTime();
	////////////////////////////////////////////////////////////////

	std::cout << "Total for endl; = " << elapsedTime1.asMilliseconds() << std::endl;
	std::cout << "Total time for newline= " << elapsedTime2.asMilliseconds() << std::endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////// The NURBS function /////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*

order, k, is the number of times the NURBS basis function is iteratively employed. 
degree = k-1

a spline of order k can be defined as:

Q(u) = sum( i = 0 to n, p(i) * N(i, k, u) )

Q is the value of the spline. 
p are the control points. 
i is the control point being considered
n is the number of control points

k is the order of the spline. The lower the order, the closer the spline follows the control polygon. 
k-1 is the degree of the spline. 
Cubic = 3rd degree, 4th order.  

NURBS_basis(i, k, u)

*/




std::vector<sf::Vector2f> initialiseNURBS(std::vector<sf::Vector2f> controlPoints, std::vector<float> knots, int order)
{
	//if (knots.size() != )
	// maximum order = number of control points - 1
	if (!checkNonDecreasing(knots))
	{	
		std::vector<sf::Vector2f> returnVector;
		returnVector.push_back(sf::Vector2f(-1, -1));
		return returnVector;
	}

	int knotsSize = knots.size();
	int controlPointsSize = controlPoints.size();

	if (knotsSize != controlPointsSize + order) // chech for right number of knots
	{
		std::cout << "wrong number of knots\n";
		std::cout << "number of knots = number of control points + order\n";
		std::cout << "but you have\n";
		std::cout << "number of knots = " << knotsSize << " and control points = " << controlPointsSize + order;
		std::cout << std::endl;
		
		std::vector<sf::Vector2f> returnVector;
		returnVector.push_back(sf::Vector2f(-1, -1));
		return returnVector;
	}

	int numEqualKnots = 0;
	for (int i = 1; i < knotsSize; i++)
	{
		if (knots[i - 1] == knots[i])
		{
			numEqualKnots++;
		}
	}
	if (numEqualKnots > order)
	{
		std::vector<sf::Vector2f> returnVector;
		returnVector.push_back(sf::Vector2f(-1, -1));
		return returnVector;
	}

	float u = 1;
	sf::Vector2f sumControlPointParts;
	sumControlPointParts = sf::Vector2f(0.0, 0.0);
	float basisFunctionValue;

	for (int controlPointElement = 0; controlPointElement < controlPointsSize; controlPointElement++)
	{
		basisFunctionValue = NURBS_basis(u, knots, order, controlPointElement);

		sumControlPointParts = sumControlPointParts + sf::Vector2f(controlPoints[controlPointElement].x * basisFunctionValue, controlPoints[controlPointElement].y * basisFunctionValue);
	}
}

float NURBS_basis(float u, std::vector<float> & knots, int parameter_k, int i)
{ 
	// parameter = (traditionally "k") is the order
	// knots = non decreasing list (traditionally "t")
	// t = the point for which the spline is calculated
	// i  is the ... just look at the formula

	float currentKnot = knots[i];
	float nextKnot = knots[i+1];

	if (parameter_k == 1) 
	{
		if (currentKnot < u && u < nextKnot)
		{
			return 1.0;
		}
		else
		{
			return 0.0;
		}
	}
	else
	{
		float numerator1;
		float denominator1;
		float fraction1;
		float numerator2;
		float denominator2;
		float fraction2;
		
		if (parameter_k > 1)
		{
			numerator1 = (u - currentKnot);
			denominator1 = (knots[i + parameter_k - 1] - knots[i]);
			numerator2 = (knots[i + parameter_k] - u);
			denominator2 = knots[i + parameter_k] - knots[i + 1];

			if (denominator1 == 0)
			{
				fraction1 = 0;
			}
			else
			{
				fraction1 = numerator1 / denominator1;
			}

			if (denominator2 == 0)
			{
				fraction2 = 0;
			}
			else
			{
				fraction2 = numerator2 / denominator2;
			}

			return fraction1 * NURBS_basis(u, knots, parameter_k - 1, i) + fraction2 * NURBS_basis(u, knots, parameter_k - 1, i + 1);
		}
	}
}

bool checkNonDecreasing(std::vector<float> knots)
{
	// tested to work!
	
	// at least one value should be higher than the previous. 


	int knotsSize = knots.size();

	if (knotsSize < 2) // ensure that we have more than two entries
	{
		return false;
		std::cout << "Not enough entries!" << std::endl;
	}

	float firstEntry;
	float secondEntry;
	
	for (int index = 0; index < (knotsSize-1); index++)
	{
		firstEntry = knots[index];
		secondEntry = knots[index + 1];

		if (firstEntry > secondEntry)
		{
			return false;
		}
	}

	return true;
}


void TESTpassByRef(const int& var)
{
	// this works and does not allow modification of the variable that is defined as constant. 
	// call as follows: 
	//int var = 69;
	//TESTpassByRef(var);

	std::cout << "var = " << var << std::endl;
	return;
}

std::vector<float> linearSpace(float startValue, float endValue, int numberOfElements)
{
	// tested to work!
	float space = (endValue - startValue) / (numberOfElements - 1);
	std::vector<float> linearSpaceVector;
	
	linearSpaceVector.push_back(startValue);

	for (int i = 1; i < numberOfElements; i++)
	{
		linearSpaceVector.push_back(linearSpaceVector[i - 1] + space);
	}
	
	linearSpaceVector.pop_back(); // replace the last element with the given last element, in case of a numerical error. 
	linearSpaceVector.push_back(endValue);

	return linearSpaceVector;
}