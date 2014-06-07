#ifndef VR_ANIMATED_AVATAR_H
#define VR_ANIMATED_AVATAR_H

#include <QObject>

namespace VR {
	class Avatar;

	class AnimatedAvatar : public Avatar	{
		Q_OBJECT

	public:
		AnimatedAvatar(QObject * parent=0);
		~AnimatedAvatar();

		virtual const char* className() const;
	};
}
#endif //VR_ANIMATED_AVATAR_H