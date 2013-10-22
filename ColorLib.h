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

// #define CL_ALL //Auto define all functions


// #define CL_LINE
// #define CL_PIXEL
// #define CL_CIRCLE
// #define CL_TEXT
// #define CL_ALPHASPRITE
// #define CL_SPRITE16
// #define CL_SPRITE



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
} CL_font;

/**************************/
/** Flags                **/
/**************************/
// Font flags :
#define MONOSPACE    0x00000001
#define ANTIALIASING 0x00000002


/**************************/
/** Functions prototypes **/
/**************************/


void CL_line(int x1, int y1, int x2, int y2, short color);

void CL_point(int x, int y, int color); 

void CL_text_setFont(Font* font);

CL_font* CL_text_getActualFont();

void CL_text_printC(int x, int y, char c, int size, int color);

void CL_text_print(int x, int y, char* c, int size, int color);

int CL_text_widthC(char c);

int CL_text_width(char* c);

void CL_bmp_alpha(int x, int y, int width, int height, short* bitmap, short alpha);

void CL_bmp_masked(short* bitmap, int x, int y, int width, int height, short mask);

void CL_bmp_masked_nbit(const unsigned char* data, int x, int y, int width, int height, const short* palette, short maskColor, unsigned int bitwidth);
#endif // COLORLIB

