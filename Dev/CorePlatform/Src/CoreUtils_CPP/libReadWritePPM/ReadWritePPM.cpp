#include <string>
#include <fstream>

#include "BasicDefinitions.h"
#include "Color.h"

#include "ReadWritePPM.h"

using namespace std;

int getNextParam(std::ifstream * apifstreamfrom) {
	string strAux;
	int nVal;
	
	while(!apifstreamfrom->eof()) {
		(*apifstreamfrom) >> strAux;
		if(strAux[0] == '#'){
			while((!apifstreamfrom->eof()) && (strAux[0] != '\n')) {
				apifstreamfrom->get(strAux[0]);
			}
			if(apifstreamfrom->eof()) {
				std::cout << "Problems in the ppm file" << std::endl;
				exit(-1);
			}
			(*apifstreamfrom) >> strAux;
		}
		nVal=atoi(strAux.c_str());
		return(nVal);
	}
	
	std::cout << "Problems in the ppm file" << std::endl;
	exit(-1);	
}

void read(COLOR_TBL & atblOut, const char * apchFileName) {

	std::string strId;
	std::ifstream * pifstreamFrom;
	string strLine;

	string strAux;
	int nI, nJ;
 
	int nHeight, nWidth;

	pifstreamFrom = new std::ifstream(apchFileName, ios_base::binary);
	if (pifstreamFrom->is_open() == true) { 
		cout <<"I can't open input file \n" << apchFileName << endl;

	}

	(*pifstreamFrom) >> strId;
	if(strId != "P6")
		std::cerr << "Wrong format" << endl;
    nWidth = getNextParam(pifstreamFrom);
    nHeight = getNextParam(pifstreamFrom);
	int nDummyCol;
	nDummyCol = getNextParam(pifstreamFrom);

	unsigned char arruchAux[3];
	int count= 0 ;
	char arrchBux[3];

	int nA = 0;
	int nB = 0;
	int nC = 0;

	pifstreamFrom->get(arrchBux[0]);

	atblOut.setSize(nHeight);
	for(nI = 0; nI < nHeight; nI++) {
		atblOut[nI].setSize(nWidth);
	}

	for(nI = 0; nI < nHeight; nI++) {
		for(nJ = 0; nJ < nWidth ; nJ++) {
			pifstreamFrom->get(arrchBux[0]);
			pifstreamFrom->get(arrchBux[1]);
			pifstreamFrom->get(arrchBux[2]);
			for(int nK=0; nK<3; nK++)
				arruchAux[nK] = arrchBux[nK];
			nA=arruchAux[0];
			nB=arruchAux[1];
			nC=arruchAux[2];
			
			if((nI==0) && (nJ==0)){
				printf("nI = %d , nJ= %d \n",nI,nJ);
				printf("Color(nA, nB, nC) = %d %d %d \n",Color<int>(nA, nB, nC));
				printf("----------------------- \n");
			}
			if((nI==0) && (nJ==nWidth-1)){
				printf("nI= %d, nJ= %d \n",nI,nJ);
				printf("Color(nA, nB, nC) = %d %d %d \n",Color<int>(nA, nB, nC));
				printf("----------------------- \n");
			}
			if((nI==nWidth-1) && (nJ==0)){
				printf("nI= %d, nJ= %d \n",nI,nJ);
				printf("Color(nA, nB, nC) = %d %d %d \n",Color<int>(nA, nB, nC));
				printf("----------------------- \n");
			}
			if((nI==nHeight-1) && (nJ==0)){
				printf("nI=%d, nJ = %d\n",nI,nJ);
				printf("Color(nA, nB, nC) = %d %d %d \n",Color<int>(nA, nB, nC));
				printf("----------------------- \n");
			}
			if((nI==0) && (nJ==nHeight-1)){
				printf("nI=%d, nJ = %d\n",nI,nJ);
				printf("Color(nA, nB, nC) = %d %d %d \n",Color<int>(nA, nB, nC));
				printf("----------------------- \n");
			}
			if((nI==nHeight-1) && (nJ==nWidth-1)){
				printf("nI= %d, nJ= %d\n",nHeight-1,nWidth-1);
				printf("Color(nA, nB, nC) = %d %d %d \n",Color<int>(nA, nB, nC));
				printf("----------------------- \n");
			}
            atblOut[nHeight - nI - 1][nJ] = Color<int>(nA, nB, nC);
			
		}
	}

	delete pifstreamFrom;
}

void write(const char * apchFileName, const COLOR_TBL & atblIn) {

	int nI, nJ;
	string aux; 
	std::string id;
	std::ofstream *to;

	int nHeight = atblIn.size;
	if(nHeight == 0) {
		cout << "Invalid color table detected at line " << __LINE__ << " in file " << __FILE__ << endl;
		exit(-1);
	}
	int nWidth = atblIn[0].size;

	int nMaxColor = 0;
	for(nI = 0; nI < nHeight; nI++) {
		for(nJ = 0; nJ < nWidth; nJ++) {
			nMaxColor = MAX(nMaxColor, MAX(atblIn[nI][nJ].m_R, MAX(atblIn[nI][nJ].m_G, atblIn[nI][nJ].m_B)));
		}
	}

	to = new std::ofstream(apchFileName, ios_base::binary);
	if (to == NULL)
		cout << "could not open file " << apchFileName << endl;
	aux = "P6 ";
	(*to) << aux;
	(*to) << '\n';
	(*to) << nWidth;
	(*to) << " ";
	(*to) << nHeight;
	(*to) << "\n";
	(*to) << nMaxColor;
	(*to) << "\n";

	int nA = 0;
	int nB = 0;
	int nC = 0;
	for(nI = nHeight - 1; nI >= 0; nI--){
	//for(nI = 0; nI < nHeight; nI++) {
		for(nJ = 0; nJ < nWidth; nJ++){
			nA = atblIn[nI][nJ].m_R;
			nB = atblIn[nI][nJ].m_G;
			nC = atblIn[nI][nJ].m_B;
			(*to).put((unsigned char)nA);
			(*to).put((unsigned char)nB);
			(*to).put((unsigned char)nC);
		}
	}
	delete to ;
}