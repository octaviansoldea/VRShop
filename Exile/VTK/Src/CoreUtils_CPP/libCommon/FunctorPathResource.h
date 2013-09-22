#ifndef FUNCTOR_PATH_RESOURCE_H
#define FUNCTOR_PATH_RESOURCE_H

#include <iostream>
#include <string>

class FunctorPathResource	{
public:
	FunctorPathResource() {
		m_qstrPathResources = "C:/Projekti/VRShop/Dev/Resources/"
				 			//"D:/Octavian/Companies/VirtualShop/GitHub/VRShop/Dev/Resources/"
						  ;
	}
	std::string operator()(const std::string& aqstrPathFile) const	{
		return (m_qstrPathResources + aqstrPathFile);
	}
private:
	std::string m_qstrPathResources;
};
#endif //FUNCTOR_PATH_RESOURCE_H