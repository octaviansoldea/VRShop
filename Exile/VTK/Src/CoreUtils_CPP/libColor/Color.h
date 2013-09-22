#ifndef COLOR_H
#define COLOR_H

#include <typeinfo>
#include <iostream>
#include <stdlib.h>
#include <math.h>

template<class T>
struct Color {
	T m_R;
	T m_G;
	T m_B;
	T m_Alpha;

	Color();
	Color(const Color & aColor);
	Color(T aR, T aG, T aB);
	Color(T aR, T aG, T aB, T aAlpha);

	void init(T aR, T aG, T aB);
	void init(T aR, T aG, T aB, T aAlpha);

	Color<T> & operator=(const Color<T> & aColor);

	operator Color<unsigned char>();
	operator Color<double>();
	
	bool operator==(const Color<T> & aColor) const;

};

template<class T>
Color<T>::Color() {
	if((typeid(T)==typeid(double))){
		init(1.0, 1.0, 1.0, 1.0);
	} else {
		init(255, 255, 255, 255);
	}
}

template<class T>
Color<T>::Color(const Color<T> & aColor) {
	init(aColor.m_R, aColor.m_G, aColor.m_B, aColor.m_Alpha);
}

template<class T>
Color<T>::Color(T aR, T aG, T aB) {
	init(aR, aG, aB);
}

template<class T>
Color<T>::Color(T aR, T aG, T aB, T aAlpha) {
	init(aR, aG, aB, aAlpha);
}

template<class T>
void Color<T>::init(T aR, T aG, T aB) {
	m_R = aR;
	m_G = aG;
	m_B = aB; 	
	if((typeid(T)==typeid(double))){
		m_Alpha = 1.0;
	} else {
		m_Alpha = 255;
	}
}

template<class T>
void Color<T>::init(T aR, T aG, T aB, T aAlpha) {
	m_R = aR;
	m_G = aG;
	m_B = aB;
	m_Alpha = aAlpha;
}

template<class T>
Color<T> & Color<T>::operator=(const Color<T> & aColor) {
	init(aColor.m_R, aColor.m_G, aColor.m_B, aColor.m_Alpha);
	return(*this);
}

template<class T>
Color<T>::operator Color<unsigned char>() {
	Color<unsigned char> color;

	if((typeid(T)==typeid(double))){
		color.m_R = (unsigned char)ceil((m_R)*255.0);
		color.m_G = (unsigned char)ceil((m_G)*255.0);
		color.m_B = (unsigned char)ceil((m_B)*255.0);
		color.m_Alpha = (unsigned char)ceil((m_Alpha)*255.0);
	}
	else {
		std::cerr << "Conversion error" <<  std::endl;
		exit(-1);
	}
	return(color);
}

template<class T>
Color<T>::operator Color<double>() {
	
	Color<double> color;

	if((typeid(T)==typeid(unsigned char))){
		color.m_R = ((double)m_R)/255.0;
		color.m_G = ((double)m_G)/255.0;
		color.m_B = ((double)m_B)/255.0;
		color.m_Alpha = ((double)m_Alpha)/255.0;
	}
	else {
		std::cerr << "Conversion error" <<  std::endl;
		exit(-1);
	}
	return(color);
}

template<class T>
bool Color<T>::operator==(const Color<T> & aColor) const {
	double dbDiffR = (double)(m_R - aColor.m_R);
	double dbDiffG = (double)(m_G - aColor.m_G);
	double dbDiffB = (double)(m_B - aColor.m_B);
	double dbDiffAlpha = (double)(m_Alpha - aColor.m_Alpha);
	double dbTotDist =
		fabs(dbDiffR) + fabs(dbDiffG) + fabs(dbDiffB) + fabs(dbDiffAlpha);
	return(dbTotDist < (1.0 / 256.0));
}

#endif //COLOR_H