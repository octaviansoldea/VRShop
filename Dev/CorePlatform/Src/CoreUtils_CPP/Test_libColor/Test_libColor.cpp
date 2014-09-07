#include "Color.h"
#include "ColorGenerator.h"

int main() {

	Color<int> col(5, 6, 7);
	Color<int> colNew(col);

	ColorGenerator colGen;

	int nI;
	for(nI = 0; nI < 20; nI++) {
		Color<unsigned char> coluchRGB = colGen.GetNextColor();
		printf("%d %d %d\n", coluchRGB.m_R, coluchRGB.m_G, coluchRGB.m_B);
	}
	colGen.print();

	Color<unsigned char> coluchRGB1;//colGen.GetNextColor();
	coluchRGB1.init(255, 255, 255);
	printf("%d %d %d\n", coluchRGB1.m_R, coluchRGB1.m_G, coluchRGB1.m_B);
	//Color<unsigned char> coluchRGB2 = colGen.GetNextColor();
	colGen.ReleaseColor(coluchRGB1);
	colGen.print();
	coluchRGB1 = colGen.GetNextColor();
	colGen.print();


	return(0);

}