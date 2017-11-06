#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include "node.h"

using namespace cv ;
using namespace std ;

class Trajectory{
    public:
        Trajectory();
        void addPoint(Node& node) ;
        void drawTrajectoire(Mat& frame);
        vector<Node>& getCenterList();
        void setLastCenter(Node& node);
        Node getLastCenter();
    private:
        vector<Node> centerList;
        Node centerBack;  //The last value of the array 'center'
};

#endif // TRAJECTORY_H
