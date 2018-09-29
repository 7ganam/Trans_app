#include <X11/Xlib.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <malloc.h>


int main(void) {

    int i;
    Bool result;
    Window *root_windows;
    Window window_returned;
    XEvent abc , myevent ;

    int root_x, root_y;
    int win_x , win_y;
    unsigned int mask_return;

    Display *display = XOpenDisplay(NULL);
    assert(display);

    root_windows = new(Window);
    *root_windows = XRootWindow(display, 0);
    XGrabPointer(display, *root_windows, False, ButtonPressMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);

    XSelectInput(display, *root_windows, ButtonPressMask) ;
    while(1)
    {
        sleep(1);
        
        XNextEvent ( display , &abc ) ;
        switch ( abc . type ) 
        {
                                case ButtonPress :
                                                    result = XQueryPointer(display, *root_windows, &window_returned,  &window_returned, &root_x, &root_y, &win_x, &win_y,  &mask_return);
                                                    printf("Mouse is at (%d,%d)\n", root_x, root_y);
                                                    break ;
        }
    }
    
    free(root_windows);
    XCloseDisplay(display);
    return 0;
}
