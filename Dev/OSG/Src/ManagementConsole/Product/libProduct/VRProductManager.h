#ifndef VR_PRODUCT_MANAGER_H
#define VR_PRODUCT_MANAGER_H

#include <string>
#include <vector>

#include <osg/Group>

namespace VR	{
	class ProductSettings_GUI;
	class RemoveProduct_GUI;
	class ProductController;
	class Product;
	class AbstractObject;

	class ProductManager : public osg::Group	{
	public:
		ProductManager();
		~ProductManager();

		const char* className() const;
		
		Node * getChild(const std::string & astrChildName);
        inline Node* getChild( unsigned  int i ) { return _children[i].get(); }
        inline const Node* getChild( unsigned  int i ) const { return _children[i].get(); }

		Product * getProduct(const AbstractObject * apAbstractObject);

		void addNewProduct();
		void removeProduct();
		void removeProduct(Product * apProduct);

		void modifyProduct(Product * apProduct);

	private:
		ProductSettings_GUI * m_pProductSettings_GUI;
		RemoveProduct_GUI * m_pRemoveProduct_GUI;

		Product * m_pProduct;
		std::vector<Product*> m_pvecProducts;
	};
}
#endif //VR_PRODUCT_MANAGER_H