#ifndef VR_BASIC_OSG_OPERATIONS_H
#define VR_BASIC_OSG_OPERATIONS_H

#include <osg/Matrix>
#include <string>
#include <vector>

osg::Matrixd vecstr2Matrix(std::vector<std::string> & avecstrMatrixData);
double distanceL2Matrixd(const osg::Matrixd & amtrxA, const osg::Matrixd & amtrxB);
std::string matrix2String(osg::Matrixd & amtrxMatrixData, char achDelimiter=(' '));

#endif //VR_BASIC_OSG_OPERATIONS_H