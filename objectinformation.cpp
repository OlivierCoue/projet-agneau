#include "objectinformation.h"

ObjectInformation::ObjectInformation(){}
void ObjectInformation::setContours(vector<vector<Point> > tmpContours){contours = tmpContours;}
void ObjectInformation::setCenter(Point2f tmpCenter){center = tmpCenter;}
void ObjectInformation::setRadius(float tmpRadius){radius = tmpRadius;}
vector<vector<Point> > ObjectInformation::getContours(){return contours;}
Point2f ObjectInformation::getCenter(){return center;}
float ObjectInformation::getRadius(){return radius;}
