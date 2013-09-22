#ifndef COLOR_H
#define COLOR_H

#include "Array.h"

struct Color {
	int m_nR;
	int m_nG;
	int m_nB;
	Color();
	Color(int anR, int anG, int anB);
};

typedef Array<Color> COLOR_ARRAY;
typedef Array<COLOR_ARRAY> COLOR_TBL;

#endif //COLOR_H