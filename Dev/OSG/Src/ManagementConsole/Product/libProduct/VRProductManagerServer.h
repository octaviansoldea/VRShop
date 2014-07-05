#ifndef VR_PRODUCT_MANAGER_SERVER_H
#define VR_PRODUCT_MANAGER_SERVER_H

#include <string>
#include <list>

#include <QObject>

namespace VR	{
	class DatabaseManager;

	class ProductManagerServer : public QObject	{
		Q_OBJECT
	public:
		ProductManagerServer();
		~ProductManagerServer();

		const char* className() const;

		std::string getProductDataFromDB(const std::string astrProductName);

	private:
		DatabaseManager * m_pDb;
	};
}
#endif //VR_PRODUCT_MANAGER_SERVER_H