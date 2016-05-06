#ifndef _FONTS_H_
#define _FONTS_H_

#include "../defs.h"

extern void initialize_fonts(void);
extern void cleanup_fonts(void);
extern void ggprint06(Rect *r, int advance, int cref, const char *fmt, ...);
extern void ggprint07(Rect *r, int advance, int cref, const char *fmt, ...);
extern void ggprint08(Rect *r, int advance, int cref, const char *fmt, ...);
extern void ggprint8b(Rect *r, int advance, int cref, const char *fmt, ...);
extern void ggprint10(Rect *r, int advance, int cref, const char *fmt, ...);
extern void ggprint12(Rect *r, int advance, int cref, const char *fmt, ...);
extern void ggprint13(Rect *r, int advance, int cref, const char *fmt, ...);
extern void ggprint16(Rect *r, int advance, int cref, const char *fmt, ...);
extern void ggprint17(Rect *r, int advance, int cref, const char *fmt, ...);
extern void ggprint40(Rect *r, int advance, int cref, const char *fmt, ...);
extern int texState();

#endif //_FONTS_H_

