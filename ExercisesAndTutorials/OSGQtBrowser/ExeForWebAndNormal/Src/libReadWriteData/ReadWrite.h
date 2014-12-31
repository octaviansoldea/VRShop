#ifndef READ_WRITE_H
#define READ_WRITE_H

#include <string>
#include <fstream>

namespace VR	{
	class ReadWrite	{
	public:
		ReadWrite();
		~ReadWrite();
		
		int readFileData(std::string & astrFileName);
		void writeFileData(std::string & astrFileName);
	};
}
#endif //READ_WRITE_H