#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

const string FILE_PATH = "points.txt";

struct Point {
    double x;
    double y;
    
    Point(double xValue, double yValue) {
        x = xValue;
        y = yValue;
    }
};

struct Line {
    double A;
    double B;
    double C;
    
    Line(double aValue, double bValue, double cValue) {
        A = aValue;
        B = bValue;
        C = cValue;
    }
    
    double getValue(double x) {
        return (A * x + C) / (-B);
    }
    
    double getSlopeCoefficient() {
        return A / (-B);
    }
};

vector<string> explode(string stringValue, char separator)
{
	string currentString;
	vector<string> explodedString;
	for (int i = 0; i < stringValue.length(); i++) {
		if (stringValue[i] == separator) {
			explodedString.push_back(currentString);
			currentString = "";
			continue;
		}
		currentString += stringValue[i];
	}
	explodedString.push_back(currentString);

	return explodedString;
}

vector<Point*> getPointsFromFile(string filePath)
{
    vector<Point*> pointCollection;
    ifstream file(filePath);
    
    string line;
    vector<string> explodedLine;
    int firstLineRead = 0;
	while (std::getline(file, line))
	{
		if (!firstLineRead) {
			firstLineRead = 1;
			continue;
		}
		explodedLine = explode(line, ' ');
	    pointCollection.push_back(
			new Point(stoi(explodedLine[0]), stoi(explodedLine[1])) 
		);
	}

    return pointCollection;
}

vector<Point*> getPointsOnTheRightOfTheLine(Line* line, vector<Point*> pointsCollection)
{
    vector<Point*> pointsOnTheRight;
    Point* currentPoint;
    for (int i = 0; i < pointsCollection.size(); i++) {
        currentPoint = pointsCollection[i];
        
        double slopeCoefficient = line->getSlopeCoefficient();
        if (slopeCoefficient >= 0 && currentPoint->y < line->getValue(currentPoint->x)) {
            pointsOnTheRight.push_back(currentPoint);
        }
        
        if (slopeCoefficient < 0 && currentPoint->y > line->getValue(currentPoint->x)) {
            pointsOnTheRight.push_back(currentPoint);
        }
    }
    return pointsOnTheRight;
}

vector<Point*> getPointsOnTheLeftOfTheLine(Line* line, vector<Point*> pointsCollection)
{
    vector<Point*> pointsOnTheLeft;
    Point* currentPoint;
    for (int i = 0; i < pointsCollection.size(); i++) {
        currentPoint = pointsCollection[i];
        
        if (line->getSlopeCoefficient() >= 0 && currentPoint->y > line->getValue(currentPoint->x)) {
            pointsOnTheLeft.push_back(currentPoint);
        }
        
        if (line->getSlopeCoefficient() < 0 && currentPoint->y < line->getValue(currentPoint->x)) {
            pointsOnTheLeft.push_back(currentPoint);
        }
    }
    return pointsOnTheLeft;
}

double euclideanDistanceDeterminant(Point* point, Line* line)
{
    return abs((line->A * point->x) + (line->B * point->y) + line->C);
}

Point* findTheFurthestPointFromLine(Line* line, vector<Point*> pointsCollection)
{
    Point* furthestPoint = pointsCollection[0];
    double maxDistance = 0;
    double currentDistance = 0;
    for (int i = 0; i < pointsCollection.size(); i++) {
        currentDistance = euclideanDistanceDeterminant(pointsCollection[i], line);
        if (currentDistance > maxDistance) {
            furthestPoint = pointsCollection[i];
            maxDistance = currentDistance;
        }
    }
    return furthestPoint;
}

Line* getLineIntersectingTwoPoints(Point* A, Point* B)
{
    double aCoefficient = (A->y - B->y); 
    double cCoefficient = A->y * (A->x - B->x) - aCoefficient * A->x;
    return new Line(aCoefficient, -(A->x - B->x), cCoefficient);
}

vector<Point*> quickHull(vector<Point*> convexHullPoints, Point* A, Point* B, vector<Point*> pointsCollection)
{
    if (pointsCollection.size() == 1) {
        convexHullPoints.push_back(pointsCollection[0]);
        return convexHullPoints;
    }
    
    if (pointsCollection.size() == 0) {
        return convexHullPoints;
    }
    
    Line* lineAB = getLineIntersectingTwoPoints(A, B);
    Point* C = findTheFurthestPointFromLine(lineAB, pointsCollection);

    convexHullPoints.push_back(C);
    
    Line* lineAC = getLineIntersectingTwoPoints(A, C);
    Line* lineBC = getLineIntersectingTwoPoints(B, C);
    
    convexHullPoints = quickHull(convexHullPoints, A, C, getPointsOnTheLeftOfTheLine(lineAC, pointsCollection));
    convexHullPoints = quickHull(convexHullPoints, C, B, getPointsOnTheRightOfTheLine(lineBC, pointsCollection));
    return convexHullPoints;
}

vector<Point*> findConvexHull(vector<Point*> pointsCollection)
{
    vector<Point*> convexHullPoints;
    
    // We are searching for the point with minimum and maximum x value
    Point* minPoint = pointsCollection[0];
    Point* maxPoint = pointsCollection[0];
    
    Point* currentPoint;
    for (int i = 0; i < pointsCollection.size(); i++) {
        currentPoint = pointsCollection[i];
        if (currentPoint->x < minPoint->x) {
            minPoint = currentPoint;
        }
        
        if (currentPoint->x > maxPoint->x) {
            maxPoint = currentPoint;
        }
    }
    
    convexHullPoints.push_back(minPoint);
    convexHullPoints.push_back(maxPoint);
    
    Line* line = getLineIntersectingTwoPoints(minPoint, maxPoint);

    convexHullPoints = quickHull(convexHullPoints, minPoint, maxPoint, getPointsOnTheRightOfTheLine(line, pointsCollection));
    convexHullPoints = quickHull(convexHullPoints, maxPoint, minPoint, getPointsOnTheLeftOfTheLine(line, pointsCollection));
    
    return convexHullPoints;
}

int main()
{
    vector<Point*> pointsCollection = getPointsFromFile(FILE_PATH);
    vector<Point*> convexHullPoints = findConvexHull(pointsCollection);
    
    Point* currentPoint;
    for (int i = 0; i < convexHullPoints.size(); i++) {
        currentPoint = convexHullPoints[i];
        cout << "(" << currentPoint->x << ", " << currentPoint->y << ")" << endl;
    }
    
    return 0;
}




