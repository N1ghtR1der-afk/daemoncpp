cmake_minimum_required(VERSION 3.13)
project(crypt_daemon VERSION 0.9 LANGUAGES CXX)



set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.45.0 COMPONENTS *boost libraries here*) 

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(crypt_daemon main.cpp) 
    target_link_libraries(crypt_daemon ${Boost_LIBRARIES})
endif()

set(SOURCE main.cpp ./libs/aes256.cpp)

add_executable(main main.cpp)	