#include <string>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <opencv2/opencv.hpp>
#include "opencv2/text.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>

using namespace std;
using namespace cv;
using namespace cv::text;


 
int main(int argc, char* argv[])
{
    string outText;
    string imPath = argv[1];
 
// Create Tesseract object
    //tesseract::TessBaseAPI *ocr = new tesseract::TessBaseAPI();
    Ptr<OCRTesseract> ocr = OCRTesseract::create();
    Mat im = cv::imread(imPath, IMREAD_COLOR);
   
// Set image data
    //ocr->SetImage(im.data, im.cols, im.rows, 3, im.step);
 
// Run Tesseract OCR on image
    //outText = string(ocr->GetUTF8Text());
 
//g my code
     vector<Rect> boxes;
     vector<string> words;
     vector<float> confidences;
     string output;
     ocr->run(im, output, &boxes, &words, &confidences, OCR_LEVEL_WORD);
    
     for (int j=0; j<(int)boxes.size(); j++)
        {

           cout << "  word = " << words[j] << "\t confidence = " << confidences[j] << endl;
            
        }
    
    
// print recognized text
    //cout << outText << endl; // Destroy used object and release memory ocr->End();
   
    return 0;
}
