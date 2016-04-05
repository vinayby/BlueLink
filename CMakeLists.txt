PROJECT(BlueLink)

CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

## C++ options
SET(CMAKE_CXX_STANDARD 11)

SET(CMAKE_LIBRARY_OUTPUT_DIR ${CMAKE_BINARY_DIR}/lib)

## Include the parent of the source dir to get BlueLink/... includes
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/..)


## Unit tests
SET(TESTING ON CACHE BOOL "Build unit tests")
IF(TESTING)
	ENABLE_TESTING()
ENDIF()

FIND_PACKAGE(Bluespec)
FIND_PACKAGE(CAPI)

#FIND_PACKAGE(MODELSIM)

CONFIGURE_FILE(pslse_server.dat.in pslse_server.dat)
CONFIGURE_FILE(shim_host.dat.in shim_host.dat)
CONFIGURE_FILE(pslse.parms.in pslse.parms)

ADD_SUBDIRECTORY(Examples)

ADD_SUBDIRECTORY(Altera)
ADD_SUBDIRECTORY(MemScanChain)
ADD_SUBDIRECTORY(Host)