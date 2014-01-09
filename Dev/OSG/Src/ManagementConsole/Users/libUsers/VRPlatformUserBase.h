#ifndef VR_PLATFORM_USER_BASE_H
#define VR_PLATFORM_USER_BASE_H

namespace VR	{
	struct PlatformUserBaseParams	{
		int m_nUserID;

		PlatformUserBaseParams();
	};

	class PlatformUserBase	{
	public:
		PlatformUserBase();

		virtual ~PlatformUserBase() = 0;

	private:
		int m_nNumberOfPlatformUsers;
	};
}
#endif //VR_PLATFORM_USER_BASE_H