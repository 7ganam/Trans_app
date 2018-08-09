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


cv::Mat crop( cv::Rect& ROI, cv::Mat& img  )
{ //this function takes a picutre to crop and cropping recatagle and makes sure that the
  //cropping rectangle area is withing the image area then applies crop

    //creat with the size of the image 
    int img_width = img.rows;
    int img_height= img.cols;
    cv::Rect screen_wide_rect(0,0,img_height,img_width);
    
    //creat a new cropping rectangle (region of interest) with the interesection of the two recatagles
    cv::Rect new_ROI = ROI & screen_wide_rect;

// //screen shot and display for debuggig   (uncomment this if you want to visualize)
//     int Width = 0;
//     int Height = 0;
//     int Bpp = 0;
//     std::vector<std::uint8_t> Pixels;  
//         ImageFromDisplay(Pixels, Width, Height, Bpp);
//         if (Width && Height)
//         {
//             Mat img = Mat(Height, Width, Bpp > 24 ? CV_8UC4 : CV_8UC3, &Pixels[0]); //Mat(Size(Height, Width), Bpp > 24 ? CV_8UC4 : CV_8UC3, &Pixels[0]); 
//             cv::rectangle(img,ROI, cv::Scalar(0, 255, 0));
//             cv::rectangle(img,screen_wide_rect, cv::Scalar(0, 0, 255));
//             imshow("Display window", img);   
// 
//             waitKey(0);
//         }
    
    
    cv::Mat croppedImage = img(new_ROI);
    return  croppedImage;
}




int main()
{
    
   while(1)
    {  
//         sleep(1);
    //first set the pointer pixel position to root_x , root_y
    int root_x, root_y;
    get_pointer(root_x, root_y) ; 
    
    
    // preparing the cropping rectangle    
    
    
    int cwidth=400;//this is the dimention of the croped image
    int cheight=100;
    
    int min_dx=cwidth/2;; // this is the value of the top left postion of the croped image relative to the screenshot of the desktop
    int min_dy=cheight/2; 
    
    int ccenter_x=min_dx; //this is the center of the cropped image ..it's the postion of the cursor
    int ccetner_y=min_dy;
    
    cv::Point2i p; 
    p.x=min_dx;
    p.y=min_dy;
    
    
    int x1=root_x-min_dx;
    int y1=root_y-min_dy;
        
        cv::Rect myROI(x1,y1,cwidth,cheight);
    
    // taking  the screenshot and applying the croping rectangle   
    
        int Width = 0;
        int Height = 0;
        int Bpp = 0;
        std::vector<std::uint8_t> Pixels;
        ImageFromDisplay(Pixels, Width, Height, Bpp);

        if (Width && Height)
        {
            Mat img = Mat(Height, Width, Bpp > 24 ? CV_8UC4 : CV_8UC3, &Pixels[0]); //Mat(Size(Height, Width), Bpp > 24 ? CV_8UC4 : CV_8UC3, &Pixels[0]); 
        
        //apply crope
            cv::Mat croppedImage = crop( myROI, img  );
            
            cvtColor(croppedImage,croppedImage,COLOR_RGB2GRAY);

            
        // creatin ocr object and applying text detection
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
            //imshow("Display window", croppedImage);
    //          
            waitKey(100);
            
            
        }
    }
    return 0;
}
