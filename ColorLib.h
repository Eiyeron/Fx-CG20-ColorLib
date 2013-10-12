/*************************************************************/
/** ColorLib - Color graphic library for fx-CG20 - fx-CG10 **/
/** ColorLib is a free software                             **/
/**                                                         **/
/** @author Lancelot                                        **/
/**                                                         **/
/** @file ColorLib.h                                       **/
/** Include header for ColorLib                            **/
/**                                                         **/
/** @date 10-06-2013                                        **/
/*************************************************************/

#ifndef COLORLIB
#define COLORLIB

/****************************************************/
/** uncomment #define of functions you want to use **/
/****************************************************/

// #define CGL_ALL //Auto define all functions

// #define KEY
// #define LINE
// #define PIXEL
// #define RANDOM
// #define ABS
// #define CIRCLE
// #define TEXT
// #define ALPHASPRITE
// #define SPRITE16
// #define SPRITE
// #define INT2STR
// #define FPS


/**************************/
/** Useful Constants     **/
/**************************/

#define LCD_WIDTH_PX 384
#define LCD_HEIGHT_PX 216
#define VRAM 0xA8000000

/**************************/
/** Structures           **/
/**************************/

typedef struct {
    char* data;
    int width, height, flags;
} Font;

/**************************/
/** Flags                **/
/**************************/
// Font flags :
#define MONOSPACE    0x00000001
#define ANTIALIASING 0x00000002


/**************************/
/** Functions prototypes **/
/**************************/

int key_down(int basic_keycode);

void line(int x1, int y1, int x2, int y2, short color);

void point(int x, int y, int color); 

void text_setFont(Font* font);

Font* text_getActualFont();

void text_printC(int x, int y, char c, int size, int color);

void text_print(int x, int y, char* c, int size, int color);

int text_widthC(char c);

int text_width(char* c);

void alphaSprite(int x, int y, int width, int height, short* bitmap, short alpha);

void CopySpriteMasked(short* bitmap, int x, int y, int width, int height, short mask);

void CopySpriteNbitMasked(const unsigned char* data, int x, int y, int width, int height, const short* palette, short maskColor, unsigned int bitwidth);
#endif // COLORLIB

