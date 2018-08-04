#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cstdint>
#include <cstring>
#include <vector>
#include <X11/Xlib.h>
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <malloc.h>
#include <vector>
#include "opencv2/text.hpp"
#include <iostream>



#include "get_pointer.h"

using namespace cv;
using namespace std;
using namespace cv::text;


Mat binarize(Mat input)
{
    //Uses otsu to threshold the input image
    Mat binaryImage;
    cvtColor(input, input, cv::COLOR_BGR2GRAY);
    threshold(input, binaryImage, 0, 255, THRESH_OTSU);
    //Count the number of black and white pixels
    int white = countNonZero(binaryImage);
    int black = binaryImage.size().area() - white;
    //If the image is mostly white (white background), invert it
    return white < black ? binaryImage : ~binaryImage;
}




void ImageFromDisplay(std::vector<uint8_t>& Pixels, int& Width, int& Height, int& BitsPerPixel)
{
    Display* display = XOpenDisplay(nullptr);
    Window root = DefaultRootWindow(display);

    XWindowAttributes attributes = {0};
    XGetWindowAttributes(display, root, &attributes);

    Width = attributes.width;
    Height = attributes.height;

    XImage* img = XGetImage(display, root, 0, 0 , Width, Height, AllPlanes, ZPixmap);
    BitsPerPixel = img->bits_per_pixel;
    Pixels.resize(Width * Height * 4);

    memcpy(&Pixels[0], img->data, Pixels.size());

    XDestroyImage(img);
    XCloseDisplay(display);
}

int main()
{
    
    
 //first set the pointer pixel position to root_x , root_y
   int root_x, root_y;
   get_pointer(root_x, root_y)    ; 
   
 
// preparing the cropping rectangle    
   int min_dx=100; // this is the value of the top left postion of the croped image relative to the screenshot of the desktop
   int min_dy=20; 
   
   int cwidth=400;//this is the dimention of the croped image
   int cheight=50;
   
   int ccenter_x=min_dx; //this is the center of the cropped image ..it's the postion of the cursor
   int ccetner_y=min_dy;
   
   cv::Point2i p;
   p.x=min_dx;
   p.y=min_dy;
   
   
   int x1=root_x-min_dx;
   int y1=root_y-min_dy;
     
    cv::Rect myROI(x1,y1,cwidth,cheight);
   
// taking  the screenshot and applying the croping rectangle   
    int w,h,d;
    int Width = 0;
    int Height = 0;
    int Bpp = 0;
    std::vector<std::uint8_t> Pixels;

    ImageFromDisplay(Pixels, Width, Height, Bpp);

    if (Width && Height)
    {
        Mat img = Mat(Height, Width, Bpp > 24 ? CV_8UC4 : CV_8UC3, &Pixels[0]); //Mat(Size(Height, Width), Bpp > 24 ? CV_8UC4 : CV_8UC3, &Pixels[0]); 
    //apply crope
        cv::Mat croppedImage = img(myROI);
        cvtColor(croppedImage,croppedImage,COLOR_RGB2GRAY);

        
    // creatin ocr object and text detection
       Ptr<OCRTesseract> ocr = OCRTesseract::create();
        vector<Rect> boxes;
        vector<string> words;
        vector<float> confidences;
        string output;
        ocr->run( croppedImage, output, &boxes, &words, &confidences, OCR_LEVEL_WORD);
        for (int j=0; j<(int)boxes.size(); j++)
        {
           if(boxes[j].contains( p ))
           {
                cv::rectangle(croppedImage, boxes[j], cv::Scalar(255, 255, 0));
                cout << "  word = " << words[j] << "\t confidence = " << confidences[j] << endl;
           }
        }
        imshow("Display window", croppedImage);
//          
        waitKey(0);
    }
    return 0;
}
