#ifndef KEYS_H
#define KEYS_H

#ifdef _WIN32

#define KEY_DOWN        40      /* down-arrow key */
#define KEY_UP          38      /* up-arrow key */
#define KEY_LEFT        37      /* left-arrow key */
#define KEY_RIGHT       39      /* right-arrow key */
#define KEY_BACKSPACE   8
#define KEY_ENTER       13      /* tecla Enter */

#else

#define KEY_DOWN        0402    /* down-arrow key */
#define KEY_UP          0403    /* up-arrow key */
#define KEY_LEFT        0404    /* left-arrow key */
#define KEY_RIGHT       0405    /* right-arrow key */
#define KEY_BACKSPACE   0407
#define KEY_ENTER       012     /* tecla Enter */

#endif

#endif
