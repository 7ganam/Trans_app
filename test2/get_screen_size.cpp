// -----------------------------------------------------------
// Purpose : simply retrieve current X screen resolution and 
//    the size of current root window of the default 
//    screen of curent default window
// -----------------------------------------------------------

#include <X11/Xlib.h>
#include <stdio.h>
#include "get_screen_size.h"

int main()
{
    int w, h,d;

    getScreenSize(&w, &h);
    printf (" Screen:  width = %d, height = %d \n", w, h);

    getRootWindowSize(&w, &h,&d);
    printf (" Root Window:  width = %d, height = %d ,depth = %d\n", w, h ,d);
    
    return 1;
    
}
