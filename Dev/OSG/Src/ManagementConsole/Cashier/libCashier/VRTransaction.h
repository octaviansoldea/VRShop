    /* 
    	This class is called when the basket formation is finished
    	(no changes to selected products can be done).
    	
    	It should accommodate for buyer specific params, e.g. applying special discounts,
    	or any other general "special" events, e.g. general discounts
    
    	The user has to sign-in and his identity be approved, if not done earlier.
    
    
    */
    
    #ifndef VR_TRANSACTION_H
    #define VR_TRANSACTION_H
    
    #include <vector>
    
    namespace VR	{
    	class AbstractUser;
  	class ProductShopClient;
    
    	class Transaction	{
    	public:
    		Transaction();
 		Transaction(const std::vector<ProductShopClient> & avecProduct, const AbstractUser & aAbstractUser);
    
    		void applyGeneralDiscount(float & aflDiscountRate);
    
    		// 1.) authenticate the user (our server); => 2.) literally asking for validation via bank (bank's server)
    		void isApproved() const;
    
    		bool tryExecute();
    	protected:
    		bool isUserAccountApproved(const AbstractUser & aAbstractUser);
    
    		std::string getSQLInterogationCommand();//check if the shop can satisfy the request.
    
  		std::vector<ProductShopClient> m_vecProduct;
    	};
    }
    #endif //VR_TRANSACTION_H
