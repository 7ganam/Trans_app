#include <opencv2/opencv.hpp>
#include <vector>
using namespace std;
using namespace cv;
Mat binarize(Mat input)
{
//Uses otsu to threshold the input image
Mat binaryImage;
cvtColor(input, input, CV_BgR2gRAY);
threshold(input, binaryImage, 0, 255, THRESH_OTSU);
//Count the number of black and white pixels
int white = countnonZero(binaryImage);
int black = binaryImage.size().area() - white;
//If the image is mostly white (white background), invert it
return white < black ? binaryImage : ~binaryImage;
}
