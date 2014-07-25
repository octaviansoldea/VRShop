    #ifndef VR_PRODUCT_MANAGER_H
    #define VR_PRODUCT_MANAGER_H
    
    #include <string>
    #include <vector>
    #include <list>
    
    #include <osg/Group>
    
    namespace VR	{
    	class ProductSettings_GUI;
    	class RemoveProduct_GUI;
    	class ProductController;
  	class ProductShopEditor;
    	class AbstractObject;
    
    	class ProductManager {
    	public:
    		ProductManager();
    		~ProductManager();
    
    		const char* className() const;
    
    		osg::Node * getProductsRepresentation();
    
    		osg::Node * getChild(const std::string & astrChildName);
            //inline Node* getChild( unsigned  int i ) { return _children[i].get(); }
            //inline const Node* getChild( unsigned  int i ) const { return _children[i].get(); }
    
  		ProductShopEditor * getProduct(const AbstractObject * apAbstractObject);
    
    		void addNewProduct();
  		void addNewProduct(ProductShopEditor * apProductShopEditor);
    //		void removeProduct();
  		void removeProduct(ProductShopEditor * apProductShopEditor);
  
  		bool modifyProduct(ProductShopEditor * apProductShopEditor);
  
  		void preparedObjectData(std::vector<std::string> &avecItems, std::string & astrParent);
  		void initFromSQLData(std::vector<std::string> & avecstrSQLData);
    
    	private:
    		osg::ref_ptr<osg::Group> m_pgrpProductsRepresentation;
    
    		ProductSettings_GUI * m_pProductSettings_GUI;
    		RemoveProduct_GUI * m_pRemoveProduct_GUI;
    
  		std::list<ProductShopEditor*> m_lstProducts;
    
    
    		void createDBTableProduct() const;	//Let be Manufacturers in a separate table
  		void productViewed(const ProductShopEditor & aProductShopEditor /* User & aUser*/);
    	};
    }
    #endif //VR_PRODUCT_MANAGER_H