    #ifndef VR_CASHIER_H
    #define VR_CASHIER_H
    
    #include <vector>
    
    namespace VR	{
    	class Basket;
  	class CashierScreen;
    
    	class Cashier	{
    	public:
    		Cashier();
    		~Cashier();
    
    		void init(Basket * apBasket);
    
    		void displayMainMenu();
    
    		void getCurrentSubTotal() const;
    
    		void performPurchase(Basket * apBasket);
    		void abort();
    
    	protected:
    		typedef enum {STORE = 0, HOME} DELIVERY_TYPE;
    		typedef enum {CREDIT_CARD = 0, CASH} PAYMENT_TYPE;
    
    
    	private:
    		CashierScreen * m_pCashierScreen;
    		Basket * m_pBasket;
    	};
    }
    #endif //VR_CASHIER_H
