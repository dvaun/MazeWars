#ifndef PNG_LOADER_H
#define PNG_LOADER_H

 #include <GL/gl.h>
 #include <GL/glu.h>
 #include <png.h>
 #include <cstdio>
 #include <string>

GLuint loadTexture(const string filename, int &width, int &height);

#endif