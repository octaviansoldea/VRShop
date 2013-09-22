#ifndef TRACE_H
#define TRACE_H

#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include "Log.h"

/*class Trace{
#ifdef _DEBUG
	FILE * m_fp;
#endif
public:
    Trace(){
#ifdef _DEBUG
		m_fp = fopen("Trace.txt", "wb");
		if(m_fp == NULL){
			printf("Error: Could not open the trace file\n");
			exit(-1);
		}
#endif
	}
    ~Trace(){
#ifdef _DEBUG
		fclose(m_fp);
#endif
	}
    //FILE * getFP() { return(m_fp); }
	void printNormalMessage(const char * astrMessage) const;
	void printWarningMessage(const char * astrMessage) const;
	void printErrorMessage(const char * astrMessage) const;
};*/

class Trace : public CFileLog {
	CFileLog * m_pLog;
public:
	Trace() : m_pLog(NULL) {}
	~Trace() { if(m_pLog != NULL) delete(m_pLog); }
	void init(std::string astrLogFileName);
	void printNormalMessage(const char * astrMessage);
	void printWarningMessage(const char * astrMessage);
	void printErrorMessage(const char * astrMessage);
};

#endif //TRACE_H