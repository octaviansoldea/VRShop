#include <stdlib.h>
#include <typeinfo>
#include <iostream>

#include "Color.h"
#include "ColorGenerator.h"

using namespace std;

ColorGenerator::ColorGenerator() {

	Color<unsigned char> arrColors[NUMBER_OF_LABELS] = {
		Color<unsigned char>(255,0,0), 
		Color<unsigned char>(0,255,0),
		Color<unsigned char>(0,0,255),
		Color<unsigned char>(255,255,0),
		Color<unsigned char>(0,255,255),
		Color<unsigned char>(255,255,0),
		Color<unsigned char>(255,255,255), 
		Color<unsigned char>(64,128,128),
		Color<unsigned char>(128,64,128),
		Color<unsigned char>(128,128,64), 
		Color<unsigned char>(64,64,128),
		Color<unsigned char>(64,128,64),
		Color<unsigned char>(64,64,128),  
		Color<unsigned char>(0,64,128),
		Color<unsigned char>(64,0,128), 
		Color<unsigned char>(128,64,0),
		Color<unsigned char>(32,64,128)
	};

	int nI;
	for(nI = 0; nI< NUMBER_OF_LABELS; nI++) {
		m_arrColors[nI] = arrColors[nI];
		m_arrbLabelColors[nI] = false;
	}
}

Color<unsigned char> ColorGenerator::GetNextColor() {

	Color<unsigned char> color_RGB;
	
	if(isColorArrayFull()) {
		color_RGB = GenerateNewRandomColor();
	} else {
		int nI;
		for(nI = 0; (nI < NUMBER_OF_LABELS) && (m_arrbLabelColors[nI] == true); nI++);
		color_RGB = m_arrColors[nI];
		this->m_arrbLabelColors[nI] = true;
	}


	//bool bFreeColor;
	//bool bFullColorArray = 0;
	//double dbMaxVal =255.0;
	//int nIdx = 0;

	//bFreeColor = m_arrbLabelColors[0];
	//bFullColorArray = isColorArrayFull();
	//while((bFreeColor == 1)&&(bFullColorArray!=1)){
	//	nIdx++;
	//	bFreeColor = m_arrbLabelColors[nIdx];
	//}
	//if(bFreeColor == 0){
	//	color_RGB = m_arrColors[nIdx];
	//	m_arrbLabelColors[nIdx] = 1;
	//}
	//if(bFullColorArray == 1){		
	//	color_RGB = GenerateRandomColor();
	//}
	return(color_RGB);	
}

Color<unsigned char> ColorGenerator::GenerateRandomColor() {
	double dbRangeMin = 0;
	double dbRangeMax = 255;
	unsigned char uchRandomVal;
	unsigned char arruchRandomVal[3];
	for(int nI = 0; nI < 3; nI++){
		uchRandomVal = (unsigned char)(ceil(((double)rand()/((double)RAND_MAX)) *
			(dbRangeMax - dbRangeMin) + dbRangeMin));
		arruchRandomVal[nI] = uchRandomVal;
	}
	Color<unsigned char> colorRGB(arruchRandomVal[0], arruchRandomVal[1], arruchRandomVal[2]);
	return(colorRGB);
}

Color<unsigned char> ColorGenerator::GenerateNewRandomColor(){
	Color<unsigned char> color_RGB = GenerateRandomColor();
	const int nUpperBound = 100;
	int nI;
	for(nI = 0; nI < nUpperBound; nI++) {
		color_RGB = GenerateRandomColor();
		if(isColorUsed(color_RGB) == false) {
			m_lstColors.push_back(color_RGB);
			return(color_RGB);
		}
	}
	if(nI == nUpperBound) {
		cerr << "Color generated is already used" << endl;
	}
	return(color_RGB);	
}

void ColorGenerator::ReleaseColor(const Color<unsigned char> & aColor){

	int nIdx;
	for(nIdx = 0; nIdx < NUMBER_OF_LABELS; nIdx++) {
		if((aColor == m_arrColors[nIdx]) &&	(m_arrbLabelColors[nIdx] == true)) {
			m_arrbLabelColors[nIdx] = false;
			return;
		}
	}
	std::list<Color<unsigned char> >::iterator itlstColors;
	for(itlstColors = m_lstColors.begin(); itlstColors != m_lstColors.end(); itlstColors++) {
		if((*itlstColors) == aColor) {
			m_lstColors.erase(itlstColors);
			return;
		}
	}
};

bool ColorGenerator::isColorUsed(const Color<unsigned char> & aColor) const {
	int nI;
	for(nI = 0; nI < NUMBER_OF_LABELS; nI++) {
		if((aColor == m_arrColors[nI]) && (m_arrbLabelColors[nI] == true)) {
			return(true);
		}
	}
	std::list<Color<unsigned char> >::const_iterator citlstColors;
	for(citlstColors = m_lstColors.begin(); citlstColors != m_lstColors.end(); citlstColors++) {
		if((*citlstColors) == aColor)
			return(true);
	}
	return(false);
}

bool ColorGenerator::isColorArrayFull() const {

	int nIdx;	
	bool bFullArray = 0;
	for (nIdx = 0; ((nIdx<NUMBER_OF_LABELS) && (m_arrbLabelColors[nIdx] == true)); nIdx++);
	bFullArray = (nIdx == NUMBER_OF_LABELS);
	return(bFullArray);

}

void ColorGenerator::print() const {
	printf("\n\n===============================");
	int nI;
	for(nI = 0; nI < NUMBER_OF_LABELS; nI++) {
		if(m_arrbLabelColors[nI] == true) {
			printf("%d %d %d\n", m_arrColors[nI].m_R, m_arrColors[nI].m_G, m_arrColors[nI].m_B);
		}
	}
	printf("===============================\n");
	std::list<Color<unsigned char> >::const_iterator citlstColors;
	for(citlstColors = m_lstColors.begin(); citlstColors != m_lstColors.end(); citlstColors++) {
		printf("%d %d %d\n", citlstColors->m_R, citlstColors->m_G, citlstColors->m_B);
	}
	printf("===============================\n\n");
}

