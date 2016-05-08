#ifndef PNG_LOADER_H
#define PNG_LOADER_H

 #include <GL/gl.h>
 #include <GL/glu.h>
 #include <png.h>
 #include <cstdio>
 #include <cstring>
 #include <sstream>
 #include <stdlib.h>

GLuint loadTexture(const std::string filename, int &width, int &height);

#endif