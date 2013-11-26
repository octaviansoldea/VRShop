#ifndef VR_ABSTRACT_OBJECT_H
#define VR_ABSTRACT_OBJECT_H

#include <string>

namespace VR	{
	struct AbstractObjectParams	{
	};

	class AbstractObject {
	public:
		virtual std::string getSQLFormat() const;

		virtual std::string getSQLCommand() const = 0;
		virtual void initFromSQLData(const std::string & astrSQLData) = 0;

	private:
		static std::string m_strSQLFormat;
	};
}
#endif //VR_ABSTRACT_OBJECT_H