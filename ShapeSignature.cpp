// ShapeSignature.cpp : Defines the entry point for the console application.
//
#include <vector>
#include <math.h>
#include <iostream>


struct point2D {
	float m_x;
	float m_y;
};

struct shapesig {
	std::vector<float> distancesToPreviouVertex;
	std::vector<float> distancesToCentroid;
};

float calcDistance(const point2D &p1, const point2D &p2){
	return sqrt(pow((p2.m_x - p1.m_x), 2) + pow((p2.m_y - p1.m_y), 2));
}

shapesig signature(const std::vector<point2D> & polygon) {
	
	//1st calculte the polygon centroid
	float xSum = 0;
	float ySum = 0;
	for (int i = 0; i < polygon.size(); i++){
		const point2D &currentPoint = polygon[i];
		xSum += currentPoint.m_x;
		ySum += currentPoint.m_y;
	}
	point2D centroid;
	centroid.m_x = xSum / polygon.size();
	centroid.m_y = ySum / polygon.size();

	//2nd normalize polygon, dividing all coordinates by MaxDist
	//MaxDist is the maximum distance to the polygons centroid
	
	//2.1 find the maximum distance to the centroid
	float maxDist = 0;
	for (int i = 0; i < polygon.size(); i++){
		const point2D &currentPoint = polygon[i];
		float dist = calcDistance(centroid, currentPoint);
		if (dist>maxDist)
			maxDist = dist;
	}

	//2.2 divide the poligons vertexes by the maximum distance to the centroid
	std::vector<point2D> normalizedPolygon;
	std::cout << "Normalized polygon "<< std::endl;
	for (int i = 0; i < polygon.size(); i++){
		const point2D &currentPoint = polygon[i];
		point2D normalizedPoint;
		normalizedPoint.m_x = currentPoint.m_x / maxDist;
		normalizedPoint.m_y = currentPoint.m_y / maxDist;
		normalizedPolygon.push_back(normalizedPoint);
		std::cout << "(" << normalizedPoint.m_x << ", " << normalizedPoint.m_y << ")" << std::endl;
	}

	//2.3 recalculate centroid
	centroid.m_x /= maxDist;
	centroid.m_y /= maxDist;

	std::cout << "Centroid=(" << centroid.m_x << ", " << centroid.m_y << ")" << std::endl;

	//3rd calculate signature
	std::cout << "Shape signature" << std::endl;
	shapesig shapeSignature;
	for (int i = 0; i < normalizedPolygon.size(); i++){
		const point2D &currentPoint = normalizedPolygon[i];
		int previousIdx = (i + 1) % normalizedPolygon.size();
		const point2D &previousPoint = normalizedPolygon[previousIdx];
		
		float distanceToCentroid = calcDistance(centroid, currentPoint);
		float distanceToPreviousVertex = calcDistance(currentPoint, previousPoint);

		shapeSignature.distancesToPreviouVertex.push_back(distanceToPreviousVertex);
		shapeSignature.distancesToCentroid.push_back(distanceToCentroid);

		std::cout << i << ". (" << currentPoint.m_x << ", " << currentPoint.m_y << ") distToCentr=" << shapeSignature.distancesToCentroid[i] << ". distToPrev=" << shapeSignature.distancesToPreviouVertex[i] << std::endl;

	}

	return shapeSignature;

}

int main(int argc, char* argv[])
{
	point2D p1;
	p1.m_x = 0;
	p1.m_y = 0;
	point2D p2;
	p2.m_x = 1;
	p2.m_y = 0;
	point2D p3;
	p3.m_x = 1;
	p3.m_y = 1;
	point2D p4;
	p4.m_x = 0;
	p4.m_y = 1;
	
	point2D polyArr[] = {p1, p2, p3, p4};
	std::vector<point2D> poly(polyArr, polyArr + sizeof polyArr / sizeof polyArr[0]);

	shapesig sig = signature(poly);

	for (int i = 0; i < sig.distancesToCentroid.size(); i++){
		std::cout << i << ". distToCentr=" << sig.distancesToCentroid[i] << ". distToPrev=" << sig.distancesToPreviouVertex[i] << std::endl;
	}

	getchar();

	return 0;
}

