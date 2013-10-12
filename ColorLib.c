/*************************************************************/
/** ColorLib - Color graphic library for fx-CG20 - fx-CG10 **/
/** ColorLib is a free software                             **/
/**                                                         **/
/** @author Lancelot                                        **/
/**                                                         **/
/** @file ColorLib.c                                       **/
/** Code file of ColorLib                                  **/
/**                                                         **/
/** @date 10-06-2013                                        **/
/*************************************************************/

#include "ColorLib.h"
#include <display_syscalls.h>

/******************************/
/** Dependencies management  **/
/******************************/

#ifdef CGL_ALL
	
	#define KEY
	#define PIXEL
	#define LINE
	#define RANDOM
	#define ABS
	#define CIRCLE
	#define TEXT
	#define ALPHASPRITE
	#define SPRITE16
	#define SPRITE
	#define INT2STR
	#define FPS
	
	#endif


/***********************/
/****   Functions   ****/
/***********************/

#ifdef KEY

 int key_down(int basic_keycode);

 /***************/
 /** Key codes **/
 /***************/
 
 #define K_F1    79
 #define K_F2    69
 #define K_F3    59
 #define K_F4    49
 #define K_F5    39
 #define K_F6    29

 #define K_SHIFT 78
 #define K_OPTN  68
 #define K_VARS  58
 #define K_MENU  48
 #define K_LEFT  38
 #define K_UP    28

 #define K_ALPHA 77
 #define K_SQR   67
 #define K_EXPO  57
 #define K_EXIT  47
 #define K_DOWN  37
 #define K_RIGHT 27

 #define K_THETA 76
 #define K_LOG   66
 #define K_LN    56
 #define K_SIN   46
 #define K_COS   36
 #define K_TAN   26

 #define K_FRAC  75
 #define K_FD    65
 #define K_LPAR  55
 #define K_RPAR  45
 #define K_COMMA 35
 #define K_STORE 25

 #define K_7     74
 #define K_8     64
 #define K_9     54
 #define K_DEL   34

 #define K_4     73
 #define K_5     63
 #define K_6     53
 #define K_MULT  43
 #define K_DIV   33

 #define K_1     72
 #define K_2     62
 #define K_3     52
 #define K_PLUS  42
 #define K_MINUS 32

 #define K_0     71
 #define K_DOT   61
 #define K_EXP   51
 #define K_NEG   41
 #define K_EXE   31

 #define K_AC    10

 
 int keydown(int basic_keycode)
 {
     const unsigned short* keyboard_register = (unsigned short*)0xA44B0000;
     int row, col, word, bit;
     row = basic_keycode%10;
     col = basic_keycode/10-1;
     word = row>>1;
     bit = col + 8*(row&1);
     return (0 != (keyboard_register[word] & 1<<bit));
 }
 

 #endif //KEY
 
#ifdef LINE

void line(int x1, int y1, int x2, int y2, short color)
{
	int i, x, y, dx, dy, sx, sy, cumul;
	x = x1;
	y = y1;
	dx = x2 - x1;
	dy = y2 - y1;
	sx = sgn(dx);
	sy = sgn(dy);
	dx = abs(dx);
	dy = abs(dy);
	Bdisp_SetPoint_VRAM( x,  y,(int)  color );
	if(dx > dy)
	{
		cumul = dx / 2;
		for(i=1 ; i<dx ; i++)
		{
			x += sx;
			cumul += dy;
			if(cumul > dx)
			{
				cumul -= dx;
				y += sy;
			}
			Bdisp_SetPoint_VRAM( x, y,(int)  color );
		}
	}
	else
	{
		cumul = dy / 2;
		for(i=1 ; i<dy ; i++)
		{
			y += sy;
			cumul += dx;
			if(cumul > dy)
			{
				cumul -= dy;
				x += sx;
			}
			Bdisp_SetPoint_VRAM(x, y,(int) color);
		}
	}
}

#endif //LINE

#ifdef PIXEL

void point(int x, int y, int color) 
 {
     char* VRAM = (char*)0xA8000000;
     VRAM += 2*(y*LCD_WIDTH_PX + x);
     *(VRAM++) = (color&0x0000FF00)>>8;
     *(VRAM++) = (color&0x000000FF);
     return;
 }

#endif // PIXEL
#ifdef RANDOM

unsigned int random(int seed, int value) // Function from Simon Lothar
{
    static unsigned int lastrandom = 0x12345678;
    if(seed) lastrandom = seed;
    lastrandom = (0x41C64E6D * lastrandom) + 0x3039;
    return ((lastrandom >> 16) % value);
}

#endif // RANDOM

#ifdef ABS

int abs (int nombre)
{
    if(nombre < 0)return -nombre;
    return nombre;
}

#endif // ABS

#ifdef CIRCLE

void drawCircle(int x0, int y0, int rayon, int couleur)
 {
    int er = 1 - rayon;
    int erY = 1;
    int erX = -2 * rayon;
    int x = rayon, y = 0;

    point(x0, y0 + rayon, couleur);
    point(x0, y0 - rayon, couleur);
    point(x0 + rayon, y0, couleur);
    point(x0 - rayon, y0, couleur);

    while(y < x)
    {
      if(er > 0)
      {
        x--;
        erX += 2;
        er += erX;
      }
      y++;
      erY += 2;
      er += erY;    
      point(x0 + x, y0 + y, couleur);
      point(x0 - x, y0 + y, couleur);
      point(x0 + x, y0 - y, couleur);
      point(x0 - x, y0 - y, couleur);
      point(x0 + y, y0 + x, couleur);
      point(x0 - y, y0 + x, couleur);
      point(x0 + y, y0 - x, couleur);
      point(x0 - y, y0 - x, couleur);
    }
 }

#endif // CIRCLE

#ifdef TEXT


typedef struct {
	char* data;
	int width, height, flags;
} Font;

// Flags :
#define MONOSPACE    0x00000001
#define ANTIALIASING 0x00000002

const static char default_data[] = {
	0,0,0,0,0,           // ' '
	128,128,128,0,128,   // '!'
	160,160,0,0,0,       // '"'
	80,248,80,248,80,    // '#'
	64,224,64,224,64,    // '$'
	200,208,32,88,152,   // '%'
	0,96,64,144,96,      // '&'
	128,128,0,0,0,       // '''
	64,128,128,128,64,   // '('
	128,64,64,64,128,    // ')'
	64,224,64,160,0,     // '*'
	32,32,248,32,32,     // '+'
	0,0,0,128,128,       // ','
	0,0,248,0,0,         // '-'
	0,0,0,0,128,       // '.'
	8,16,32,64,128,      // '/'
	248,136,136,136,248, // '0'
	192,64,64,64,64,     // '1'
	240,16,240,128,240,  // '2'
	240,16,112,16,240,   // '3'
	128,136,136,248,8,   // '4'
	248,128,248,8,248,   // '5'
	248,128,248,136,248, // '6'
	248,8,8,8,8,         // '7'
	248,136,248,136,248, // '8'
	248,136,248,8,248,   // '9'
	0,0,128,0,128,       // ':'
	0,128,0,128,128,     // ';'
	32,64,128,64,32,     // '<'
	0,248,0,248,0,       // '='
	128,64,32,64,128,    // '>'
	224,16,96,0,64,      // '?'
	248,136,184,168,184, // '@'
	248,136,248,136,136, // 'A'
	240,136,248,136,240, // 'B'
	248,128,128,128,248, // 'C'
	240,136,136,136,240, // 'D'
	248,128,240,128,248, // 'E'
	248,128,240,128,128, // 'F'
	120,128,184,136,120, // 'G'
	136,136,248,136,136, // 'H'
	128,128,128,128,128, // 'I'
	16,16,16,144,96,     // 'J'
	136,144,224,144,136, // 'K'
	128,128,128,128,248, // 'L'
	136,216,168,136,136, // 'M'
	248,136,136,136,136, // 'N'
	248,136,136,136,248, // 'O'
	248,136,248,128,128, // 'P'
	112,136,136,152,120, // 'Q'
	248,136,248,144,136, // 'R'
	248,128,248,8,248,   // 'S'
	248,32,32,32,32,     // 'T'
	136,136,136,136,248, // 'U'
	136,136,80,80,32,    // 'V'
	168,168,168,168,248, // 'W'
	136,80,32,80,136,    // 'X'
	136,80,32,32,32,     // 'Y'
	248,8,112,128,248,   // 'Z'
	192,128,128,128,192, // '['
	128,64,32,16,8,      // '\'
	192,64,64,64,192,    // ']'
	64,160,0,0,0,        // '^'
	0,0,0,0,248,         // '_'
	128,64,0,0,0,        // '`'
	0,112,144,144,112,   // 'a'
	128,224,144,144,224, // 'b'
	0,96,128,128,96,     // 'c'
	16,112,144,144,112,  // 'd'
	96,144,240,128,112,  // 'e'
	48,64,224,64,64,     // 'f'
	112,144,112,16,224,  // 'g'
	128,128,224,144,144, // 'h'
	128,0,128,128,128,   // 'i'
	64,0,64,64,128,      // 'j'
	128,128,160,192,160, // 'k'
	128,128,128,128,128, // 'l'
	0,0,240,168,168,     // 'm'
	0,0,224,144,144,     // 'n'
	0,96,144,144,96,     // 'o'
	0,240,144,240,128,   // 'p'
	0,240,144,240,16,    // 'q'
	0,176,192,128,128,   // 'r'
	0,112,64,32,224,     // 's'
	0,128,224,128,96,    // 't'
	0,0,144,144,96,      // 'u'
	0,0,136,80,32,       // 'v'
	0,0,168,168,80,      // 'w'
	0,0,144,96,144,      // 'x'
	0,160,224,32,192,    // 'y'
	0,240,32,64,240,     // 'z'
	96,64,192,64,96,     // '{'
	128,128,128,128,128, // '|'
	192,64,96,64,192,    // '}'
	0,0,80,160,0         // '~'
};

static Font default_font = {default_data, 5, 5, 0};

/*
color on 32bits : 16 bits for alpha transparency + 16 bits for color.
alpha=0 mean opaque, alpha=32 mean totaly transparent.
example : 0x0010FFFF mean "white, 50% opacity"
*/


//Local variables
#define LCD_WIDTH_PX 384
#define LCD_HEIGHT_PX 216
#define VRAM 0xA8000000
Font* used_font = &default_font;

//private functions
static void text_drawPoint(int x, int y, int size, int color, int alpha)
{
	int i, j;
	short* vram = VRAM;
	if(x+size>=LCD_WIDTH_PX || x<0 || y+size>=LCD_HEIGHT_PX || y<0) return;
	vram += y*LCD_WIDTH_PX + x;
	if(alpha == 32) {
		for(i=size ; i ; i--, vram+=LCD_WIDTH_PX-size) {
			for(j=size ; j ; j--) {
				*(vram++) = color;
			}
		}
	} else {
		for(i=size ; i ; i--, vram+=LCD_WIDTH_PX-size) {
			for(j=size ; j ; j--) {
				*(vram++) = ((((color & 0xf81f) * alpha + (*vram & 0xf81f) * (32-alpha)) >> 5) & 0xf81f) |
							((((color & 0x07e0) * alpha + (*vram & 0x07e0) * (32-alpha)) >> 5) & 0x07e0);
			}
		}
	}
}

static int text_readPix(char* data, int x, int y, int w, int h)
{
	int byte_width = ((w-1)>>3)+1;
	if(x<0 || x>=w || y<0 || y>=h) return 0;
	return 0 != (data[y*byte_width+(x>>3)] & (128>>(x&7)));
}

static void text_antialias(int x, int y, int size, int color, int alpha, int corner)
{
	int i, j, m=size>>1;
	switch(corner) {
		case 0: //top left
			for(i=0 ; i<size-m ; i++) {
				for(j=0 ; j<size-i-m-1 ; j++)
					text_drawPoint(x+j, y+i, 1, color, alpha);
				text_drawPoint(x+j, y+i, 1, color, alpha>>1);
			}
			break;
		case 1: //top right
			for(i=0 ; i<size-m ; i++) {
				text_drawPoint(x+i+m, y+i, 1, color, alpha>>1);
				for(j=i+m+1 ; j<size ; j++)
					text_drawPoint(x+j, y+i, 1, color, alpha);
			}
			break;
		case 2: //bottom left
			for(i=m ; i<size ; i++) {
				for(j=0 ; j<i-m ; j++)
					text_drawPoint(x+j, y+i, 1, color, alpha);
				text_drawPoint(x+j, y+i, 1, color, alpha>>1);
			}
			break;
		case 3: //bottom right
			for(i=m-1 ; i<size ; i++) {
				text_drawPoint(x+size-i+m-1, y+i, 1, color, alpha>>1);
				for(j=size-i+m ; j<size ; j++)
					text_drawPoint(x+j, y+i, 1, color, alpha);
			}
			break;
	}
}

//public functions
void text_setFont(Font* font)
{
	used_font = font;
}

Font* text_getActualFont()
{
	return used_font;
}

void text_printC(int x, int y, char c, int size, int color)
{
	int i, j, byte_width, alpha;
	char* data;
	if(c<32 || c>127 || size<1) return;
	byte_width = ((used_font->width-1)>>3)+1;
	data = used_font->data + byte_width * used_font->height * (c-32);
	alpha = 32 - ((color>>16) % 32);
	color &= 0xFFFF;
	for(i=0 ; i<used_font->height ; i++) {
		for(j=0 ; j<used_font->width ; j++) {
			if(data[i*byte_width+(j>>3)] & (128>>(j&7)))
				text_drawPoint(x+j*size, y+i*size, size, color, alpha);
			else if(used_font->flags & ANTIALIASING) { // Antialiasing
				if(text_readPix(data, j, i-1, used_font->width, used_font->height)) {
					if(text_readPix(data, j-1, i, used_font->width, used_font->height)) text_antialias(x+j*size, y+i*size, size, color, alpha, 0);
					if(text_readPix(data, j+1, i, used_font->width, used_font->height)) text_antialias(x+j*size, y+i*size, size, color, alpha, 1);
				}
				if(text_readPix(data, j, i+1, used_font->width, used_font->height)) {
					if(text_readPix(data, j-1, i, used_font->width, used_font->height)) text_antialias(x+j*size, y+i*size, size, color, alpha, 2);
					if(text_readPix(data, j+1, i, used_font->width, used_font->height)) text_antialias(x+j*size, y+i*size, size, color, alpha, 3);
				}
			}
		}
	}
}

void text_print(int x, int y, char* c, int size, int color)
{
	int save_x = x;
	for( ; *c ; c++) {
		if(*c == '\n') {
			x = save_x;
			y += (used_font->height + used_font->height/2) * size;
		} else {
			text_printC(x, y, *c, size, color);
			x += size * text_widthC(*c);
		}
	}
}

int text_widthC(char c)
{
	if(used_font->flags & MONOSPACE || c==' ') return used_font->width+1;
	unsigned char *data, col=0;
	int i, j, byte_width, width;
	byte_width = ((used_font->width-1)>>3)+1;
	width = 8 * byte_width;
	data = used_font->data + byte_width * used_font->height * (c-32);
	for(j=byte_width-1 ; j>=0 && !col ; j--) {
		col = 0;
		for(i=0 ; i<used_font->height ; i++) {
			col |= data[i*byte_width + j];
		}
		if(col) {
			while(!(col&1)) {
				col>>=1;
				width--;
			}
		} else width -= 8;
	}
	return width + 1;
}

int text_width(char* c)
{
	int width = 0;
	for( ; *c ; c++) width += text_widthC(*c);
	return width;
}


#endif //TEXT

#ifdef ALPHASPRITE

void alphaSprite(int x, int y, int width, int height, short* bitmap, short alpha)
{
    short* VRAM = (short*)0xA8000000;
    int x_inc = width;
    if (y < 0)
    {
        bitmap -= y * width;
        height += y;
        y = 0;
    }
    if (height > 216 - y) height = 216 - y;

    if (x < 0)
    {
        bitmap -= x;
        width += x;
        x = 0;
    }
    if (width > 128*3 - x) width = 128*3 - x;

    x_inc -= width;

    int y_index;
    int x_index;
    short * base = y * 128*3 + x + VRAM;
    for (y_index = height; y_index > 0; y_index--, base += 128*3 - width, bitmap += x_inc)
    {
        for (x_index = width; x_index > 0; x_index--, base++ , bitmap++ )
        {
            if (*bitmap!=alpha && *bitmap!= 0xffff) *base = *bitmap;
        }
    }
}

#endif //ALPHASPRITE

#ifdef SPRITE16

void CopySpriteMasked(short* bitmap, int x, int y, int width, int height, short mask)
{
	short* VRAM = (short*)0xA8000000;

	int y_index;
	int x_index;
	short * base = y * 128*3 + x + VRAM;
	for (y_index = height; y_index > 0; --y_index, base += 128*3 - width) {
		for (x_index = width; x_index > 0; --x_index, ++base, ++bitmap) {
			if (*bitmap != mask) *base = *bitmap;
		}
	}
}

#endif // SPRITE16

#ifdef SPRITE

void CopySpriteNbitMasked(const unsigned char* data, int x, int y, int width, int height, const short* palette, short maskColor, unsigned int bitwidth)
{
    short* VRAM = (short*)0xA8000000; //ou  color_t* VRAM = (color_t*) GetVRAMAddress();
    int offset = 0;
    int availbits ;
    int j,i;
    unsigned char buf;
    short thiss;
    short color;

    VRAM += (128*3*y + x);
    for(j=y; j<y+height; j++)
    {
        availbits = 0;

        for(i=x; i<x+width;  i++)
        {
            if (!availbits)
            {
                buf = data[offset++];
                availbits = 8;
            }
            thiss = ((short)buf>>(8-bitwidth));
            color = palette[thiss];
            if(color != maskColor && i >= 0 && i<384)
            {
                *VRAM = color;
            }
            VRAM++;
            buf<=bitwidth;
            availbits-=bitwidth;
        }
        VRAM += (128*3-width);
    }
}


#endif // SPRITE

#ifdef INT2STR

char* int2str(char* c, int n)
 {
     if(n==0)
     {
         c[0] = '0';
         c[1] = 0;
     }
     else
     {
         int i, l=0;
         for(i=n ; i ; i/=10)
             l++;
         c[l] = 0;
         for(i=n ; i ; i/=10)
             c[--l] = i%10+'0';
     }
     return c;
 }

#endif // INT2STR

#ifdef FPS

void setFps(int fpsWish) //1 pour 128, 2 pour 64, 3 pour 42, 128/fpsWish en fait
 {
      static unsigned int fps = 0, fps_count = 0;

      do
      {
          fps = RTC_GetTicks();
      }
      while(fps < fps_count+fpsWish);
      fps_count = RTC_GetTicks();
 }

#endif // FPS

