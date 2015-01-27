#include "BasicStringDefinitions.h"
#include <QDataStream>

#include "VRAppData.h"

#include <iostream>
#include <fstream>

#include "VRServerClientCommands.h"

#include "VRAvatarManagerServer.h"
#include "VRUserAccount.h"
#include "VRUserAccountManager.h"
#include "VRProductManagerServer.h"
#include "VRCashierManagerServer.h"
#include "VRCashierServer.h"
#include "VRVisitorManagerServer.h"

#include "VRBasketServer.h"

#include "VRCashierServerReport.h"

#include "VRDatabaseNetworkManager.h"

using namespace VR;
using namespace std;

//=====================================================================

QByteArray DatabaseNetworkManager::databaseRequest(QByteArray & aData)	{
	string strPFileError = AppData::getFPathLog() + "errors.txt";
	ofstream outFileError;
	outFileError.open(strPFileError,ios::app);

	//Request
	QDataStream in(&aData,QIODevice::ReadOnly);
	in.setVersion(QDataStream::Qt_4_8);

	//Initialize parameters
	quint8 nType;
	in >> nType;

	//Respond
	QByteArray output;
	QDataStream out(&output, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_8);


	out << quint64(0) << nType;	//Size of the package

	switch (nType)	{
	case ServerClientCommands::NEW_USER_REGISTER:
		{
			QString qstrIP;
			int nUserID;

			in >> qstrIP >> nUserID;

			VisitorManagerServer vms;
			vms.registerVisitor(qstrIP.toStdString(), nUserID);

			break;
		}
	case ServerClientCommands::PRODUCT_REQUEST:
		{
			QString qstrRequest;
			in >> qstrRequest;

			ProductManagerServer pms;
			QString qstrProductData = pms.getProductDataFromDB(qstrRequest.toStdString()).c_str();

			out << qstrProductData;
			break;
		}
	case ServerClientCommands::PRODUCT_TO_BASKET_REQUEST:
		{
			QString qstrProductName;
			QString qstrUserIDName;
			float flProductQuantity;

			in >> qstrUserIDName >> qstrProductName >> flProductQuantity;

			ProductManagerServer pms;
			ProductManagerServer::ProductManagerServerParams pmsp;
			pmsp.m_strUserIDName = qstrUserIDName.toStdString();
			pmsp.m_strProductName = qstrProductName.toStdString();
			pmsp.m_flProductQuantity = flProductQuantity;

			float flQuantity = pms.tryAddProduct2Basket(pmsp);	//Returns approved quantities

			out << flQuantity;

			//Give allocated products to the "OrdersReserved" table in the Cashier DB
			CashierManagerServer cms;
			CashierManagerServer::CashierManagerServerParams cmsp;
			cmsp.m_strUserIDName = qstrUserIDName.toStdString();
			cmsp.m_strProductName = qstrProductName.toStdString();
			cmsp.m_flProductQuantity = flQuantity;

			bool bRes = cms.addProduct2OrdersReserved(cmsp);

			break;
		}
	case ServerClientCommands::REMOVE_PRODUCT_REQUEST:
	case ServerClientCommands::REMOVE_FROM_CASHIER_REQUEST:
		{
			QString qstrUserIDName;
			QString qstrProductName;
			float flProductQuantity;

			in >> qstrUserIDName >> qstrProductName >> flProductQuantity;

			ProductManagerServer pms;
			ProductManagerServer::ProductManagerServerParams pmsp;
			pmsp.m_strUserIDName = qstrUserIDName.toStdString();
			pmsp.m_strProductName = qstrProductName.toStdString();
			pmsp.m_flProductQuantity = flProductQuantity;

			bool bRes = pms.removeProduct(pmsp);

			out << bRes;

			//Remove from "Reserved" list
			CashierManagerServer cms;
			CashierManagerServer::CashierManagerServerParams cmsp;
			cmsp.m_strUserIDName = qstrUserIDName.toStdString();
			cmsp.m_strProductName = qstrProductName.toStdString();

			bRes = cms.removeProductFromOrdersReserved(cmsp);

			break;
		}
	case ServerClientCommands::MODIFY_PRODUCT_REQUEST:
		{
			QString qstrUserIDName;
			QString qstrProductName;
			float flProductQuantity;
			float flProductNewQuantity;

			in >> qstrUserIDName >> qstrProductName >> flProductQuantity >> flProductNewQuantity;

			ProductManagerServer pms;
			ProductManagerServer::ProductManagerServerParams pmsp;
			pmsp.m_strUserIDName = qstrUserIDName.toStdString();
			pmsp.m_strProductName = qstrProductName.toStdString();
			pmsp.m_flProductQuantity = flProductQuantity;
			pmsp.m_flProductNewQuantity = flProductNewQuantity;

			float flNewQuantity = pms.modifyProductQuantity(pmsp);

			out << flNewQuantity;

			//Update the quantity from the "Reserved" list
			CashierManagerServer cms;
			CashierManagerServer::CashierManagerServerParams cmsp;
			cmsp.m_strUserIDName = qstrUserIDName.toStdString();
			cmsp.m_strProductName = qstrProductName.toStdString();
			cmsp.m_flProductQuantity = flNewQuantity;

			bool bRes = cms.removeProductFromOrdersReserved(cmsp);

			break;
		}
	case ServerClientCommands::AVATAR_REGISTER:
		{
			QString qstrAvatarName;
			QString qstrAvatarMatrix;
			in >> qstrAvatarName >> qstrAvatarMatrix;

			AvatarManagerServer ams;
			ams.registerAvatar(qstrAvatarName.toStdString(), qstrAvatarMatrix.toStdString());
			break;
		}
	case ServerClientCommands::AVATAR_UPDATE:
		{
			QString qstrAvatarName;
			QString qstrAvatarMatrix;
			in >> qstrAvatarName >> qstrAvatarMatrix;

			AvatarManagerServer ams;
			ams.updateAvatarData(qstrAvatarName.toStdString(), qstrAvatarMatrix.toStdString());
			break;
		}
	case ServerClientCommands::OTHER_AVATARS_REQUEST:
		{
			QString qstrAvatarNames;
			in >> qstrAvatarNames;

			AvatarManagerServer ams;
			list<string> lstOtherAvatarsData = ams.getAvatarsDataFromDB();
			string strResult;

			if (lstOtherAvatarsData == list<string>())	{
				strResult = "";
			} else {
				list<string>::iterator it = lstOtherAvatarsData.begin();
				for (it; it != lstOtherAvatarsData.end(); it++)	{
					strResult += (*it) + ";";
				}
				strResult.pop_back();
			}

			QString qstrResult = strResult.c_str();
			out << qstrResult;
			break;
		}
	case ServerClientCommands::SIGN_IN_REQUEST:
		{
			QString qstrUser;
			QString qstrPsw;
			QString qstrUserID;
			in >> qstrUser >> qstrPsw >> qstrUserID;

			UserAccount ua;
			int nRes = ua.trySignIn(qstrUser.toStdString(), qstrPsw.toStdString(), qstrUserID.toStdString()) 
				? ServerClientCommands::PASSED : ServerClientCommands::FAILED;

			//Update AddressBook's temporary UserID value

			out << nRes;
			break;
		}
	case ServerClientCommands::SIGN_UP_REQUEST:
		{
			QString qstrEMail;
			QString qstrPsw;
			QString qstrFirstName;
			QString qstrLastName;
			QString qstrUserID;

			in >> qstrFirstName >> qstrLastName >> qstrEMail >> qstrPsw >> qstrUserID;

			UserAccount::UserAccountParams uap;
			uap.m_strEMail = qstrEMail.toStdString();
			uap.m_strFirstName = qstrFirstName.toStdString();
			uap.m_strLastName = qstrLastName.toStdString();
			uap.m_strPsw = qstrPsw.toStdString();
			uap.m_strUserIDName = qstrUserID.toStdString();

			UserAccount ua;
			int nRes = ua.trySignUp(uap) ? ServerClientCommands::PASSED : ServerClientCommands::FAILED;

			out << nRes;
			break;
		}
	case ServerClientCommands::SIGN_OUT_REQUEST: 
		{
			QString qstrUser;
			in >> qstrUser;

			UserAccount ua;
			ua.trySignOut(qstrUser.toStdString());
			int nRes = 1;
			out << nRes;
			break;
		}
	case ServerClientCommands::MODIFY_USER_ACCOUNT_REQUEST: 
		{
			QString qstrEMail;
			QString qstrPsw;
			QString qstrFirstName;
			QString qstrLastName;
			QString qstrUserIDName;
			in >> qstrFirstName >> qstrLastName >> qstrEMail >> qstrPsw >> qstrUserIDName;

			UserAccount::UserAccountParams uap;
			uap.m_strEMail = qstrEMail.toStdString();
			uap.m_strFirstName = qstrFirstName.toStdString();
			uap.m_strLastName = qstrLastName.toStdString();
			uap.m_strPsw = qstrPsw.toStdString();

			UserAccount ua;
			int nRes = ua.tryModifyUserAccount(uap) ? ServerClientCommands::PASSED : ServerClientCommands::FAILED;
			out << nRes;

			break;
		}
	case ServerClientCommands::PURCHASE_REQUEST:
		{
			QString qstrVisitorName;
			QString qstrBasketProdQty;
			in >> qstrVisitorName >> qstrBasketProdQty;

			//User checked
			bool bAccountValid = UserAccount::checkUserAccountValidity(qstrVisitorName.toStdString());

			if (bAccountValid==false)	{
				int nRes = ServerClientCommands::AUTHENTICATION_FAILED;
				out << nRes;
				break;
			}

			//Basket checked
			ProductManagerServer productMgr;
			bool bCanMeetRequest = productMgr.canFullfilRequest(qstrBasketProdQty.toStdString());
			if (bCanMeetRequest==false)	{
				//REPORT THAT QUANTITIES ARE LIMITED
				break;
			}

			//PREPARE INFORMATIONAL RECEIPT; SEND IT INTO CONFIRMATION
			//REAL RECEIPT IS SENT ALONG WITH THE GOODS
			CashierServer cashier;
//			cashier.prepareReceipt(qstrVisitorName);

			break;
		}
	case ServerClientCommands::USER_CONFIRMS_PURCHASE:
		{
			CashierServer cashier;


			//NOT YET IMPLEMENTED

			break;
		}
	case ServerClientCommands::PRODUCT_INFO_REQUEST:
		{
			QString qstrRequest;
			in >> qstrRequest;

			ProductManagerServer pms;
			QString qstrProductData = pms.getProductInfo(qstrRequest.toStdString()).c_str();

			out << qstrProductData;
			break;
		}
	case ServerClientCommands::USER_PERSONAL_DATA:
		{
			QString qstrFirstName;
			QString qstrMiddleName;
			QString qstrLastName;
			QString qstrAddress;
			QString qstrCity;
			QString qstrCountry;
			QString qstrPostalCode;
			QString qstrState;
			QString qstrUserID;

			in >> qstrFirstName >> qstrMiddleName >> qstrLastName >> qstrAddress >> qstrCity >> qstrPostalCode 
				>> qstrState >> qstrCountry >> qstrUserID;

			UserAccount::UserPersonalData upd;
			upd.m_strAddress = qstrAddress.toStdString();
			upd.m_strCity = qstrCity.toStdString();
			upd.m_strCountry = qstrCountry.toStdString();
			upd.m_strFirstName = qstrFirstName.toStdString();
			upd.m_strLastName = qstrLastName.toStdString();
			upd.m_strMiddleName = qstrMiddleName.toStdString();
			upd.m_strPostalCode = qstrPostalCode.toStdString();
			upd.m_strState = qstrState.toStdString();
			upd.m_strUserID = UserAccountManager::getUserAccountID(qstrUserID.toStdString());
			upd.m_strUserID.pop_back();

			UserAccount ua;
			int nRes = ua.insertUserPersonalData(upd);

			CashierManagerServer cms;
			cms.orderConfirmed(qstrUserID.toStdString());

			out << nRes;

			break;
		}
	}

	outFileError.close();

	return output;
}

//==================================================================================

void DatabaseNetworkManager::checkDatabaseTables()	{
	UserAccountManager::createDB();
	AvatarManagerServer::createAvatarDB();
	CashierManagerServer::createDB();
	VisitorManagerServer::createDB();
}

//----------------------------------------------------------------------------------

void DatabaseNetworkManager::checkAvatarActivity()	{
	AvatarManagerServer::checkAvatarActivity();
}

//----------------------------------------------------------------------------------

void DatabaseNetworkManager::printOrderList()	{
	list<string> strlstOrderList = CashierManagerServer::getActiveOrdersList();

	if (strlstOrderList.empty())	{
		cout << "Order list is empty" << endl;
		return;
	}

	ofstream outputFile;
	string strFileName = AppData::getFPathVRShop() + "OrderList.txt";
	outputFile.open(strFileName);

	CashierServerReport::createOrdersReportHeader(strlstOrderList, outputFile);

	int nOrderID;
	int nUserID;
	string strProduct;
	float flQuantity;

	int nCurrentTop=0;

	list<string>::iterator it;
	for (it = strlstOrderList.begin(); it != strlstOrderList.end(); it++)	{
		vector<string> vecstrData = splitString(*it,";");

		vector<string>::iterator itt = vecstrData.begin();
		nOrderID = stoi(itt[0]);
		nUserID = stoi(itt[1]);
		
		if (nUserID>nCurrentTop)	{
			nCurrentTop = nUserID;

			//NEW CUSTOMER - BROWSE USERACCOUNT DB FOR DATA
			string strUserData = UserAccountManager::getUserAddress(nUserID);
			CashierServerReport::createOrdersReportCustomer(strUserData, outputFile);
		}

		strProduct = (itt[2]);
		flQuantity = stof(itt[3]);

		outputFile << "\t" << nOrderID << " " << strProduct << " " << flQuantity << endl;
	}

	outputFile.close();
}

//----------------------------------------------------------------------------------

void DatabaseNetworkManager::clientQuitApplication(const int & anUserID)	{
	string strUserID = tostr(anUserID);

	//Unregister visitor from the visitor DB
	VisitorManagerServer::unregisterVisitor(strUserID);

	UserAccount ua;
	ua.trySignOut(strUserID);

	//cashier.db: Orders reserved
	CashierManagerServer::clearProductsReserved(strUserID);

	//HERE ADD FUNCTIONS THAT NEEDS TO BE EXECUTED ON THE SERVER SIDE
}