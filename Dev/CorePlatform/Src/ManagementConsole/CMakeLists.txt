CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")

SUBDIRS(
  CentralControl
  DatabaseNetworkManager
  Cashier
  Product
  Agent
  ServerClient
)