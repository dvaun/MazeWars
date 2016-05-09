#ifndef PICOPNG_H
#define PICOPNG_H

#include <vector>
#include <stdlib.h>
#include <sstream>
#include <iomanip>
#include <cstring>

void loadFile(std::vector<unsigned char>& buffer, const std::string& filename);

#endif
/* PICOPNG_H */