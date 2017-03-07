cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include("gate/cmake/HunterGate.cmake")
HunterGate(
    URL  "https://github.com/designerror/hunter/archive/v0.18.4.20.tar.gz"
    SHA1 "94e3314bfe952db1510ca644d2a8e0b55e9ebc8b"
)

project(ydclient)

set(YDCLIENT_VERSION_MAJOR 0)
set(YDCLIENT_VERSION_MINOR 1)
set(YDCLIENT_VERSION_PATCH 1)
set(YDCLIENT_VERSION ${YDCLIENT_VERSION_MAJOR}.${YDCLIENT_VERSION_MINOR}.${YDCLIENT_VERSION_PATCH})
set(YDCLIENT_VERSION_STRING "v${YDCLIENT_VERSION}")

option(BUILD_TESTS "Build tests" ON)

hunter_add_package(Boost COMPONENTS system filesystem)
find_package(Boost CONFIG REQUIRED system filesystem)

hunter_add_package(puffin-stream)
find_package(puffin-stream REQUIRED)

hunter_add_package(puffin-buffer)
find_package(puffin-buffer REQUIRED)

hunter_add_package(OpenSSL)
find_package(OpenSSL REQUIRED)

hunter_add_package(CURL)
find_package(CURL CONFIG REQUIRED)

hunter_add_package(nlohmann-json)
find_package(nlohmann-json REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB ${PROJECT_NAME}_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/sources/*) 

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})

target_link_libraries(${PROJECT_NAME} 
	Boost::filesystem Boost::system 
	OpenSSL::SSL OpenSSL::Crypto 
	CURL::libcurl 
	nlohmann-json::nlohmann-json
	puffin-stream::puffin-stream
	puffin-buffer::puffin-buffer)

if(BUILD_TESTS)
	enable_testing()
	hunter_add_package(Catch)
	find_package(Catch CONFIG REQUIRED)
	file(GLOB TESTS_${PROJECT_NAME}_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tests/*/*.cpp)
	add_executable(check ${TESTS_${PROJECT_NAME}_SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/tests/main.cpp)
	target_link_libraries(check ${PROJECT_NAME} Catch::Catch)
	add_test(NAME check COMMAND check "-s" "-r" "compact" "--use-colour" "yes")	
endif()
