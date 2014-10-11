CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")

SUBDIRS(
  DatabaseNetworkManager
  Cashier
  Product
  Agent
  ServerClient
)