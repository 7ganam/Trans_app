#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
void mouseClick(int button);
int main (){
    int x=-1,y=-1;
    XEvent event;
    int button;
    Display *display = XOpenDisplay(NULL);
    
    Window root= XDefaultRootWindow(display);
    XGrabPointer(display, root, False, ButtonPressMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
    XSelectInput(display, root, ButtonPressMask) ;
    while(1)
    {
        XNextEvent(display,&event);
        switch(event.type)
        {
        case ButtonPress:
            switch(event.xbutton.button)
            {
            case Button1:
                x=event.xbutton.x;
                y=event.xbutton.y;
                button=Button1;
                printf("leftclick at %d %d \n",x,y);
                mouseClick(1);
                break;

            case Button3:
                x=event.xbutton.x;
                y=event.xbutton.y;
                button=Button3;
                printf("rightclick at %d %d \n",x,y);
                break;
            default:
                break;

            }
            break;
        default:
            break;
        }
        //if(x>=0 && y>=0)break;
    }
    if(button==Button1)printf("leftclick at %d %d \n",x,y);
    else printf("rightclick at %d %d \n",x,y);
    XCloseDisplay(display);
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
