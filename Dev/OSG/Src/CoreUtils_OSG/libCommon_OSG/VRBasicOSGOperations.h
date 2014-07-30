#ifndef VR_BASIC_OSG_OPERATIONS_H
#define VR_BASIC_OSG_OPERATIONS_H

#include <osg/Matrix>
#include <string>
#include <vector>


namespace VR	{
	class BasicOSGOperations	{
	public:
		osg::Matrixd vecstr2Matrix(std::vector<std::string> & avecstrMatrixData);
	};
}
#endif //VR_BASIC_OSG_OPERATIONS_H