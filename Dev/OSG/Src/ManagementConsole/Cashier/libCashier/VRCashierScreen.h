#ifndef VR_CASHIER_SCREEN_H
#define VR_CASHIER_SCREEN_H

namespace VR	{
	class CashierScreen	{
	public:
		typedef enum {MAIN_MENU = 0, DISPLAY_PRODUCTS, PURCHASE, CLOSE, HELP, EXIT_STORE} SCREEN_OPTIONS;

		CashierScreen();
		CashierScreen(const SCREEN_OPTIONS & aSelectOption = MAIN_MENU);

	};
}
#endif //VR_CASHIER_SCREEN_H