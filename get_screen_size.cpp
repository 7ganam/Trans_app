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
    int w, h;

    getScreenSize(&w, &h);
    printf (" Screen:  width = %d, height = %d \n", w, h);

    return 1;
    
}
