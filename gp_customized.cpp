#include <X11/Xlib.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <malloc.h>




void get_pointer(int& root_x, int& root_y)
{
    
    int i;
    Bool result;
    Window *root_windows;
    Window window_returned;
    //int root_x, root_y;
    int win_x , win_y;
    unsigned int mask_return;

    Display *display = XOpenDisplay(NULL);
    assert(display);




    root_windows = new(Window);
    *root_windows = XRootWindow(display, 0);

    
        result = XQueryPointer(display, *root_windows, &window_returned,  &window_returned, &root_x, &root_y, &win_x, &win_y,  &mask_return);
        printf("Mouse is at (%d,%d)\n", root_x, root_y);

    
    free(root_windows);
    XCloseDisplay(display);

}


int main(void)
{
int root_x, root_y;
get_pointer(root_x, root_y)    ;
return 0;
    
}
