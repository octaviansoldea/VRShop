#ifndef VR_ABSTRACT_OBJECT_H
#define VR_ABSTRACT_OBJECT_H

#include <string>

namespace VR	{
	class AbstractObject {
	public:
		virtual std::string getSQLFormat() const;

		virtual ~AbstractObject() = 0;
	private:
		static std::string m_strSQLFormat;
	};
}
#endif //VR_ABSTRACT_OBJECT_H