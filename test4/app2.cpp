#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xlib.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <cstdint>
#include <cstring>
#include <vector>
#include <stdio.h>

#include  <math.h>
#include  <assert.h>
#include  <unistd.h>
#include  <malloc.h>
#include  <vector>
#include  <iostream>
#include  <iostream>
#include  <string>
#include  <stdio.h>
#include  <stdlib.h>
#include  <fcntl.h>
#include  <unistd.h>

#include  "opencv2/text.hpp"
#include  "include/tinyxml.h"
#include  "include/tinystr.h"
#include  "include/Translate_xml.h"
#include  "get_pointer.h"

#include <chrono>
#include <thread>

using namespace cv;
using namespace std;
using namespace cv::text;



//global connection to x-server variables ..mainly used in imagefromdisplay functions
    Display* display;
    Window root;
    XWindowAttributes attributes ;



// g++ app1.cpp -lX11 `pkg-config --cflags --libs opencv` -ltinyxml -L. -Wl,-rpath=.
//g++ app1.cpp -o app1 -lX11 `pkg-config --cflags --libs opencv` -ltinyxml -L. -Wl,-rpath=.


void mouseClick(int button);
void ImageFromDisplay(std::vector<uint8_t>& Pixels, int& Width, int& Height, int& BitsPerPixel)
{
    display = XOpenDisplay(nullptr);
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
        // int Width = 0;
        // int Height = 0;
        // int Bpp = 0;
        // std::vector<std::uint8_t> Pixels;  
        //     ImageFromDisplay(Pixels, Width, Height, Bpp);
        //     if (Width && Height)
        //     {
        //         cout<<"display debug"<<endl;
        //         Mat img = Mat(Height, Width, Bpp > 24 ? CV_8UC4 : CV_8UC3, &Pixels[0]); //Mat(Size(Height, Width), Bpp > 24 ? CV_8UC4 : CV_8UC3, &Pixels[0]); 
        //         cv::rectangle(img,ROI, cv::Scalar(0, 255, 0));
        //         cv::rectangle(img,screen_wide_rect, cv::Scalar(0, 0, 255));
        //         imshow("Display window", img);   
    
        //         waitKey(0);
        //     }
    
    
    cv::Mat croppedImage = img(new_ROI);
    return  croppedImage;
}


std::string answer_buffer;
std::string detected_text;
std::string detected_text_buffer;
unsigned int sleep_microseconds=500;

bool is_window_open=0;

int main()
{
    //open connection whith the xserver
    //display = XOpenDisplay(nullptr);
    
    //dispense error so it doesn't eppear in the main terminal-------------------------
    int err = open("cerr.log", O_RDWR|O_CREAT|O_APPEND, 0600);
    if (-1 == err) { perror("opening cerr.log"); return 255; }
    int save_err = dup(fileno(stderr));
    if (-1 == dup2(err, fileno(stderr))) { perror("cannot redirect stderr"); return 255; }
    //---------------------------------------------------------------------------------
    
    
    
    //creat a display connection to x server to grap the hot key (ctr-w)
    Display*    dpy     = XOpenDisplay(0);
    Window      root    = DefaultRootWindow(dpy);
    XEvent      ev;

    unsigned int    modifiers       = ControlMask; //| ShiftMask;
    int             keycode         = XKeysymToKeycode(dpy,XK_W);//mask for the key w
    Window          grab_window     =  root;
    Bool            owner_events    = False;
    int             pointer_mode    = GrabModeAsync;
    int             keyboard_mode   = GrabModeAsync;

    XGrabKey(dpy, keycode, modifiers, grab_window, owner_events, pointer_mode,
             keyboard_mode);

    XSelectInput(dpy, root, KeyPressMask );
   while(1)
    { 
        XNextEvent(dpy, &ev);
        switch(ev.type)
        {
            case KeyPress:
                            {
                            cout << "Hot key pressed!" << endl;
                            
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
                            
                                int Width = 0; int Height = 0; int Bpp = 0;
                                std::vector<std::uint8_t> Pixels;
                                ImageFromDisplay(Pixels, Width, Height, Bpp);
                                
                                if (!Width && Height)//error checking 
                                {
                                    cout<<"error in image for display function";
                                    break;
                                }
                                Mat img = Mat(Height, Width, Bpp > 24 ? CV_8UC4 : CV_8UC3, &Pixels[0]); //Mat(Size(Height, Width), Bpp > 24 ? CV_8UC4 : CV_8UC3, &Pixels[0]); 
                                
                            //apply crope
                                cv::Mat croppedImage0 = crop( myROI, img  );
                                cv::Mat croppedImage;
                                
                                cvtColor(croppedImage0,croppedImage,COLOR_RGB2GRAY);//change to gray as ocr works better on it

                                    
                            // creatin ocr object and applying text detection
                                    Ptr<OCRTesseract> ocr = OCRTesseract::create();
                                    vector<Rect> boxes;
                                    vector<string> words;
                                    vector<float> confidences;
                                    string output;
                                    ocr->run( croppedImage, output, &boxes, &words, &confidences, OCR_LEVEL_WORD);
                                        
                            //display  OCR results for debugging-----------

                                if(is_window_open!=0)
                                {
                                    destroyWindow("Display window");
                                    is_window_open=1;
                                }

                                cv::Mat croppedImage2 = croppedImage0;
                                for (int j=0; j<(int)boxes.size(); j++)
                                {
                                    cv::rectangle(croppedImage2,boxes[j], cv::Scalar(0, 255, 0));
                                    if(boxes[j].contains( p ))
                                    {
                                        cv::rectangle(croppedImage2,boxes[j], cv::Scalar(0, 0, 255));
                                    }
                                }
                                imshow("Display window", croppedImage2);
                                waitKey(0);
                               
                            //---------------------------------------------

                            //finding the word in the box under cursor and applyting translation
                                    for (int j=0; j<(int)boxes.size(); j++) //found words loop
                                   {
                                        if(boxes[j].contains( p )) //right word if 
                                        {
                                            
                                            //cv::rectangle(croppedImage, boxes[j], cv::Scalar(255, 255, 0));
                                            //cout << "  word = " << words[j] << "\t confidence = " << confidences[j] << endl;
                                            detected_text=words[j];
                                            if(  !iequals(detected_text, detected_text_buffer)  ) 
                                            {
                                                detected_text_buffer=detected_text; //propmt the word only onece 
                                                cout << "  detected word: " << words[j] << endl;

                                                //preparation for calling   Translate_xml(return_str , input ,  doc , root) -------------------
                                                std::string input=words[j];
                                                std::string  return_str;
                                                const char   *Dict_file_name = "eng-ara.xml";
                                                TiXmlDocument doc;
                                                TiXmlElement* root;
                                                
                                                //opening file
                                                if(!doc.LoadFile(Dict_file_name))
                                                {  
                                                    cerr << doc.ErrorDesc() << endl;  
                                                    cout<<"failed to open file"<<endl;
                                                    return 0; 
                                                }
                                                root = doc.FirstChildElement();
                                                if(root == NULL)
                                                {
                                                    cerr << "Failed to load file: No root element." << endl;
                                                    doc.Clear();
                                                    return 0; 
                                                }
                                        
                                            
                                            

                                                if( Translate_xml(return_str , detected_text ,  doc , root) )
                                                {  
                                                            answer_buffer=return_str;                                                
                                                            cout << "  translation  : " << answer_buffer<< endl;                                            
                                                }
                                                else
                                                {
                                                        cout << "  translation  : " << "Not Found"<< endl;  
                                                }

                                            }
                                                
                                                
                                        
                                        }//end of right word if
                                    }//end of found words loop
                            } 

            default:
                break;
        }


   
    
    
    }
return 0;
}


void mouseClick(int button)
{
	Display *display = XOpenDisplay(NULL);
	XEvent event;
	
	if(display == NULL)
	{
		fprintf(stderr, "Errore nell'apertura del Display !!!\n");
		exit(EXIT_FAILURE);
	}
	
	memset(&event, 0x00, sizeof(event));
	
	event.type = ButtonPress;
	event.xbutton.button = button;
	event.xbutton.same_screen = True;
	
	XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
	
	event.xbutton.subwindow = event.xbutton.window;
	
	while(event.xbutton.subwindow)
	{
		event.xbutton.window = event.xbutton.subwindow;
		
		XQueryPointer(display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
	}
	
	if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) fprintf(stderr, "Errore nell'invio dell'evento !!!\n");
	
	XFlush(display);
	
	usleep(100000);
	
	event.type = ButtonRelease;
	event.xbutton.state = 0x100;
	
	if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) fprintf(stderr, "Errore nell'invio dell'evento !!!\n");
	
	XFlush(display);
	
	XCloseDisplay(display);
}
