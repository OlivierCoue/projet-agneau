#include "algosubstraction.h"
#include <QImage>
#include <QDebug>
#include <time.h>
#include <conio.h>

AlgoSubstraction::AlgoSubstraction(int shiftMax, Mat& startFrame, Mat* choosenObject, int nbFrame)
{
    biggestSurface=0;
    biggestSurfaceId=0;
    count_refond=0;
    this->shiftMax = shiftMax;
    this->startFrame = startFrame;
    this->choosenObject = choosenObject;
    //Initialiser la limite inférieure et la limite supérieure
    thresholdRedMin = 0;
    thresholdRedMax = 255;
    thresholdBlueMin = 0;
    thresholdBlueMax = 255;
    thresholdGreenMin = 0;
    thresholdGreenMax = 255;

    //Calculer la limite inférieure et la limite supérieure
    computeHistogram(*choosenObject);
    //Générer l'image binaire de la prémière image de la vidéo
    binaryBackground = generateBinaryImage(startFrame);

    firstFrame = (nbFrame == 0 ) ? true : false ;
}


/**
 * La fonction principale de détection et suivie
 * @brief AlgoSoustraction::decter
 * @param currentFrame: Image courante de la vidéo
 * @param nbFrame: Numéro du frame courante
 */
void AlgoSubstraction::run(Mat & currentFrame, int nbFrame, int& x, int& y)
{
    clock_t t_start,t_end, t_start1, t_end1;
    Mat binary_frame;   //the current frame on binary
    Mat img_act;        //the binary image which contains only the moving object
    Mat clean_act;      //img_act do erosion = clean_act
    Point2f center;     //the center of the circle
    float radius;       //the radius of the circle
    Mat obj_courant;    //current object
    Mat drawing = Mat::zeros( currentFrame.size(), CV_8UC3 );
    t_start = clock();
    // Générer l'image binaire du frame courant
    binary_frame = generateBinaryImage(currentFrame);
    t_end = clock();
    t_start1 = clock();

    /******foreground OU background – background =
     * the binary image which contains only the moving object*************/
    absdiff(binary_frame+binaryBackground,binaryBackground,img_act);

    // Erode the frame
    morphologyEx(img_act,clean_act,MORPH_OPEN,element);

    // Find the contours
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours(clean_act, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
    myObject.setContours(contours);
    t_end1 = clock();


    // Determine whether or not the object moves out of range of video
    if(contours.size() == 0){
        if(!myTrajectoire.getCenterList().empty())
            myTrajectoire.setLastCenter(myTrajectoire.getCenterList().back());
        myTrajectoire.getCenterList().clear();
    }else if(contours.size() >= 1){
        // Find the biggest Connected domain
        for( unsigned int i = 0; i < contours.size(); i++ )
            if(contourArea(contours[i])>biggestSurface){
                biggestSurface = contourArea(contours[i]);
                biggestSurfaceId = i;
            }
        //define a color
        Scalar color( rand()&255, rand()&255, rand()&255 );
        //computes the minimal enclosing circle for the biggest Connected domain
        minEnclosingCircle( (Mat)contours[biggestSurfaceId], center, radius);
        biggestSurface = 0;
        biggestSurfaceId = 0;
        if(!myTrajectoire.getCenterList().empty()){
             double x = myTrajectoire.getCenterList().back().getCenter().x;
             double y = myTrajectoire.getCenterList().back().getCenter().y;
            if(sqrt((x-center.x)*(x-center.x) + (y-center.y)*(y-center.y))<shiftMax){
                Node nodecenter(center, QDateTime::currentDateTime(), nbFrame);
                myTrajectoire.addPoint(nodecenter);
                double obj_x = center.x - radius*2/3;
                double obj_y = center.y - radius*2/3;
                if(obj_x < 0 )obj_x = 0;
                if(obj_y < 0) obj_y = 0;
                obj_courant = currentFrame(Rect((int)(obj_x),(int)(obj_y),
                                             (int)radius*4/3,(int)radius*4/3));
                //this->calculeHistogram(obj_courant);
                *choosenObject = obj_courant;
            //Clear trajectoire
            }else
                myTrajectoire.getCenterList().clear();
        }else{
            //If it is the first image
            if(firstFrame){
                firstFrame = false;
                Node nodecenter(center, QDateTime::currentDateTime(), nbFrame);
                myTrajectoire.addPoint(nodecenter);
                //circle( currentFrame, center, (int)radius, color, 2, 8, 0 );//draw circle
                //circle( currentFrame, center, 2, color, -1, 8, 0 );//draw the center of circle
                x = center.x ;
                y = center.y ;
            //If it moves too fast in the last image
            }else if(sqrt((myTrajectoire.getLastCenter().getCenter().x-center.x)*(myTrajectoire.getLastCenter().getCenter().x-center.x)
                     + (myTrajectoire.getLastCenter().getCenter().y-center.y)*(myTrajectoire.getLastCenter().getCenter().y-center.y))<shiftMax*3/2)
            {
                Node nodecenter(center, QDateTime::currentDateTime(), nbFrame);
                myTrajectoire.addPoint(nodecenter);
                //circle( currentFrame, center, (int)radius, color, 2, 8, 0 );
                //circle( currentFrame, center, 2, color, -1, 8, 0 );
                x = center.x ;
                y = center.y ;
            //If it display again in the screen
            }else{
                if(count_refond<=2){
                    binaryBackground = generateBinaryImage(currentFrame);
                    count_refond++;
                }else{
                    count_refond=0;
                    if(center.x > 0 && center.y > 0){
                        Node nodecenter(center, QDateTime::currentDateTime(), nbFrame);
                        myTrajectoire.addPoint(nodecenter);
                        //circle( currentFrame, center, (int)radius, color, 2, 8, 0 );
                        //circle( currentFrame, center, 2, color, -1, 8, 0 );
                        x = center.x ;
                        y = center.y ;
                    }
                }
            }

        }
    }
}



/**
 * Get the binary image
 * @brief AlgoSoustraction::generateBinaryImage
 * @param tmp
 * @return
 */
Mat AlgoSubstraction::generateBinaryImage(Mat& tmp)
{
    Mat binary;
    Mat mv_fond[3];
    split(tmp, mv_fond);

    Mat binaryRedMin;
    threshold(mv_fond[2], binaryRedMin, thresholdRedMin, 255, THRESH_BINARY_INV);
    Mat binaryRedMax;
    threshold(mv_fond[2], binaryRedMax, thresholdRedMax, 255, THRESH_BINARY);
    Mat binaryRed = binaryRedMin + binaryRedMax;

    Mat binaryGreenMin;
    threshold(mv_fond[1], binaryGreenMin, thresholdGreenMin, 255, THRESH_BINARY_INV);
    Mat binaryGreenMax;
    threshold(mv_fond[1], binaryGreenMax, thresholdGreenMax, 255, THRESH_BINARY);
    Mat binaryGreen = binaryGreenMin + binaryGreenMax;

    Mat binaryBlueMin;
    threshold(mv_fond[0], binaryBlueMin, thresholdBlueMin, 255, THRESH_BINARY_INV);
    Mat binaryBlueMax;
    threshold(mv_fond[0], binaryBlueMax, thresholdBlueMax, 255, THRESH_BINARY);
    Mat binaryBlue = binaryBlueMin + binaryBlueMax;

    threshold(binaryBlue+binaryGreen+binaryRed, binary, 254, 255, THRESH_BINARY_INV);
    return binary;
}


/**
 * Histogram
 * @brief AlgoSoustraction::calculeHistogram
 * @param src
 */
void AlgoSubstraction::computeHistogram(Mat & src){
    // Separate the image in 3 places ( B, G and R )
    vector<Mat> bgr_planes;
    double maxRedVal = 0, maxGreenVal = 0, maxBlueVal = 0;
    double redVal = 0, greenVal = 0, blueVal = 0;
    split( src, bgr_planes );

    // Establish the number of bins
    int histSize = 256;

    // Set the ranges ( for B,G,R) )
    float range[] = { 0, 256 } ;
    const float* histRange = { range };

    bool uniform = true; bool accumulate = false;

    Mat b_hist, g_hist, r_hist;

    // Compute the histograms:
    calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
    calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
    calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );

    // Calcule max and min value
    // obtain the maximum (peak) value for each channel
    for (int j = 0; j < 256; j++){
        if(b_hist.at<float>(j) > maxBlueVal ){
            maxBlueVal = b_hist.at<float>(j);
            blueVal = j;
        }
        if(g_hist.at<float>(j) > maxGreenVal ){
            maxGreenVal = g_hist.at<float>(j);
            greenVal = j;
        }
        if(r_hist.at<float>(j) > maxRedVal ){
          maxRedVal = r_hist.at<float>(j);
          redVal = j;
        }
    }
      // obtain the minimum value on the abscissa
      while(thresholdRedMin < 256 && r_hist.at<float>(thresholdRedMin) <= 5)
          thresholdRedMin++;

      while(thresholdGreenMin < 256 && g_hist.at<float>(thresholdGreenMin) <= 5)
          thresholdGreenMin++;

      while(thresholdBlueMin < 256 && b_hist.at<float>(thresholdBlueMin) <= 5)
          thresholdBlueMin++;


      // obtain the maximum value on the abscissa
      while(thresholdRedMax >= 0 && r_hist.at<float>(thresholdRedMax) <= 5)
          thresholdRedMax--;

      while(thresholdGreenMax >= 0 && g_hist.at<float>(thresholdGreenMax) <= 5)
          thresholdGreenMax--;

      while(thresholdBlueMax >= 0 && b_hist.at<float>(thresholdBlueMax) <= 5)
          thresholdBlueMax--;


      // calcule six values
      thresholdRedMin=(int)(thresholdRedMin-15);
      thresholdRedMax=(int)(thresholdRedMax+15);
      if((thresholdRedMax-redVal)>3*(redVal-thresholdRedMin)) thresholdRedMax=redVal+3*(redVal-thresholdRedMin);
      if((redVal-thresholdRedMin)>3*(thresholdRedMax-redVal)) thresholdRedMin=redVal-3*(thresholdRedMax-redVal);
      if(thresholdRedMin<=0)thresholdRedMin=1;
      if(thresholdRedMax>=256)thresholdRedMax=255;

      thresholdGreenMin=(int)(thresholdGreenMin-15);
      thresholdGreenMax=(int)(thresholdGreenMax+15);
      if((thresholdGreenMax-greenVal)>3*(greenVal-thresholdGreenMin)) thresholdGreenMax=greenVal+3*(greenVal-thresholdGreenMin);
      if((greenVal-thresholdGreenMin)>3*(thresholdGreenMax-greenVal)) thresholdGreenMin=greenVal-3*(thresholdGreenMax-greenVal);
      if(thresholdGreenMin<=0)thresholdGreenMin=1;
      if(thresholdGreenMax>=256)thresholdGreenMax=255;

      thresholdBlueMin=(int)(thresholdBlueMin-15);
      thresholdBlueMax=(int)(thresholdBlueMax+15);
      if((thresholdBlueMax-blueVal)>3*(blueVal-thresholdBlueMin)) thresholdBlueMax=blueVal+3*(blueVal-thresholdBlueMin);
      if((blueVal-thresholdBlueMin)>3*(thresholdBlueMax-blueVal)) thresholdBlueMin=blueVal-3*(thresholdBlueMax-blueVal);
      if(thresholdBlueMin<=0)thresholdBlueMin=1;
      if(thresholdBlueMax>=256)thresholdBlueMax=255;
}

Trajectory AlgoSubstraction::getTrajectory(){return myTrajectoire ; }


