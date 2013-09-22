#ifndef COLOR_GENERATOR_H
#define COLOR_GENERATOR_H

#include <typeinfo>
#include <list>

#include "Color.h"

#define NUMBER_OF_LABELS 17

class ColorGenerator{

	Color<unsigned char> m_arrColors[NUMBER_OF_LABELS];
	bool m_arrbLabelColors[NUMBER_OF_LABELS];
	std::list<Color<unsigned char> > m_lstColors;

	static Color<unsigned char> GenerateRandomColor();
	Color<unsigned char> GenerateNewRandomColor();

	bool isColorUsed(const Color<unsigned char> & aColor) const;
	bool isColorArrayFull() const;

public:
	ColorGenerator();
	Color<unsigned char> GetNextColor();

	void ReleaseColor(const Color<unsigned char> & aColor);
	void ReleaseColor(const Color<double> & aColor);

	void print() const;
};



#endif //COLOR_GENERATOR_H