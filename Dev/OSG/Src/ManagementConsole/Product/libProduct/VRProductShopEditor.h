    #ifndef VR_PRODUCT_SHOP_EDITOR_H
    #define VR_PRODUCT_SHOP_EDITOR_H
    
    #include "VRAbstractProduct.h"
    
    namespace VR	{
    	struct ProductShopEditorParams : public AbstractProductParams	{
    		std::string m_strProductCategory;
    		std::string m_strProductName;
    		unsigned long m_nProductCode;
    		std::string m_strProductManufacturer;
    		std::string m_strProductShortDescription;
    		std::string m_strProductDescription;
    		std::string m_strManufacturerName;
    		std::string m_strManufacturerOrigin;
    		std::string m_strProductUnit;
    		std::string m_strProductUnitMeasure;
    		float m_flQuantity;
    		float m_flPricePerUnit;
    		float m_flTaxRate;
    		int m_nCurrency;
    		std::string m_strDateAdded;
    		std::string m_strDateLastModified;
    
    		ProductShopEditorParams();
    	};
    
    	class ProductShopEditor : public AbstractProduct	{
    	public:
    		ProductShopEditor();
    		ProductShopEditor(osg::ref_ptr <AbstractObject> apRepresentation, const ProductShopEditorParams & aProductShopEditorParams);
  		virtual ~ProductShopEditor();
    
    		void createRepresentation(const std::string & astrRepresentation);
    		osg::ref_ptr<AbstractObject> getRepresentation() const;
    
    		void setColor(const std::vector < float > & aarrflColor);
    		void setTexture(const std::string & astrFileName);
    
    		void setParams(const ProductShopEditorParams & aProductShopEditorParams);
    		void getParams(ProductShopEditorParams & aProductShopEditorParams) const;
    
    		std::string prepareRowData(const std::string & astrParentName="");
    
  		virtual void initFromSQLData(std::string & astrSQLData);
    	
    	private:
    		osg::ref_ptr<AbstractObject> m_pRepresentation;
    		ProductShopEditorParams m_ProductShopEditorParams;
    	};
    }
    #endif //VR_PRODUCT_SHOP_EDITOR_H
