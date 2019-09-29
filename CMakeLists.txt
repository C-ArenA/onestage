#Go to the build directory and write the following bash commands
#in order to build the program
#the first time or after changes within the cmake file:
    #rm -r *
    #cp -r ../img .
    #cmake ..
#Due to modifications in code:
    #make
    #./mysdl

    cmake_minimum_required(VERSION 3.10.2)
    project(onestage)
    #We can use the following command if we want to debug our program
    #set(CMAKE_BUILD_TYPE Debug)
    
    #Sets the compiler
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
    
    #Bring our headers into the project (if any)
    #include_directories(include)
    
    #the following lines are used to include SDL2
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
    include_directories(include)
    
    #Can manually add the sources using the set command as follows:
    #set(SOURCES src/mainapp.cpp src/Student.cpp)
     
    #file(GLOB...) allows for wildcard additions:
    file(GLOB SOURCES "src/*.cpp")
     
    add_executable(onestage ${SOURCES})
    
    target_link_libraries(onestage ${SDL2_LIBRARIES})
    