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
    int root_x, root_y;
    int win_x, win_y;
    unsigned int mask_return;

    Display *display = XOpenDisplay(NULL);
    assert(display);



    root_windows = malloc(sizeof(Window) * 1);
    
   
    root_windows = XRootWindow(display, 0);

    
    while(1)
    {
        sleep(1);
        result = XQueryPointer(display, root_windows, &window_returned,  &window_returned, &root_x, &root_y, &win_x, &win_y,  &mask_return);
        printf("Mouse is at (%d,%d)\n", root_x, root_y);
    }
    
    free(root_windows);
    XCloseDisplay(display);
    return 0;
}
