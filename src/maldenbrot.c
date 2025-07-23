#include <X11/Xlib.h>
#include <X11/Xos.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>

#define X_RESN 800 /* x resolution */
#define Y_RESN 600 /* y resolution */

typedef struct complextype {
    float real;
    float imag;
} Compl;

int main() {
    Display *display;
    Window window;
    GC gc;
    XGCValues values;
    XSizeHints size_hints;
    Pixmap bitmap;
    XEvent report;
    XSetWindowAttributes attr[1];
    XPoint points[800];
    unsigned int width, height,        /* window size */
        x, y,                          /* window position */
        border_width,                  /* border width in pixels */
        display_width, display_height, /* size of screen */
        screen;                        /* which screen */

    char *display_name = NULL;
    char *window_name = "Mandelbrot Set";
    unsigned long valuemask = 0;

    /* Mandlebrot variables */
    int i, j, k;
    Compl z, c;
    float lengthsq, temp;

    /* Connect to display */
    if ((display = XOpenDisplay(display_name)) == NULL) {
        fprintf(stderr, "Cannot connect to X server %s\n", XDisplayName(display_name));
        exit(-1);
    }

    /* Get screen size */
    screen = DefaultScreen(display);
    display_width = DisplayWidth(display, screen);
    display_height = DisplayHeight(display, screen);

    /* Set window size */
    width = X_RESN;
    height = Y_RESN;

    /* Set window position */
    x = 0;
    y = 0;

    /* Create opaque window */
    border_width = 4;
    window = XCreateSimpleWindow(display, RootWindow(display, screen), x, y, width, height, border_width,
                                 BlackPixel(display, screen), WhitePixel(display, screen));

    size_hints.flags = USPosition | USSize;
    size_hints.x = x;
    size_hints.y = y;
    size_hints.width = width;
    size_hints.height = height;
    size_hints.min_width = X_RESN;
    size_hints.min_height = Y_RESN;

    XSetNormalHints(display, window, &size_hints);
    XStoreName(display, window, window_name);

    /* Create graphics context */
    gc = XCreateGC(display, window, valuemask, &values);

    XSetBackground(display, gc, WhitePixel(display, screen));
    XSetForeground(display, gc, BlackPixel(display, screen));
    XSetLineAttributes(display, gc, 1, LineSolid, CapRound, JoinRound);

    attr[0].backing_store = Always;
    attr[0].backing_planes = 1;
    attr[0].backing_pixel = BlackPixel(display, screen);

    XChangeWindowAttributes(display, window, CWBackingStore | CWBackingPlanes | CWBackingPixel, attr);

    XSelectInput(display, window, ExposureMask);

    XMapWindow(display, window);
    XSync(display, 0);

    /* Calculate and draw points */
    do {
        XNextEvent(display, &report);
    } while (report.type != Expose);

    for (i = 0; i < X_RESN; i++) {
        for (j = 0; j < Y_RESN; j++) {
            z.real = z.imag = 0.0;
            /* Scale factors */
            c.real = ((float)j - width / 2.0) * 4.0 / width;
            c.imag = ((float)i - height / 2.0) * 4.0 / width;
            k = 0;

            do { /* Iterate for pixel color */

                temp = z.real * z.real - z.imag * z.imag + c.real;
                z.imag = 2 * z.real * z.imag + c.imag;
                z.real = temp;
                lengthsq = z.real * z.real + z.imag * z.imag;
                k++;

            } while (lengthsq < 4 && k < 100);

            if (k == 100) {
                XDrawPoint(display, window, gc, j, i);
            }
        }
    }

    XFlush(display);

    sleep(10);

    /* Cleanup */
    XFreeGC(display, gc);
    XDestroyWindow(display, window);
    XCloseDisplay(display);

    /* Program Finished */
    return 0;
}
