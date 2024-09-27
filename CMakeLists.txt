cmake_minimum_required(VERSION 3.13...3.22)

project(app)

# Enable verbose output for the generated makefile
# set(CMAKE_VERBOSE_MAKEFILE ON)
# --no-print-directory

set(CMAKE_CXX_STANDARD 17)
add_definitions(-DICE_CPP11_MAPPING)
set(XMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(RLIB --docroot ../ -c ../wt_config.xml --http-address 0.0.0.0 --http-port 9010)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src/)
# set(SOURCE_DIR_MY_WT ${PROJECT_SOURCE_DIR}/../1000-MyWt/)

include_directories(${SOURCE_DIR})
# include_directories(${SOURCE_DIR_MY_WT})
# include_directories(${SOURCE_DIR}/101-Interface)

# Add App.cpp to the list of source files
set(SOURCES
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/001-App/App.cpp
    ${SOURCE_DIR}/002-Dbo/Session.cpp
    ${SOURCE_DIR}/002-Dbo/UserFormModel.cpp
    ${SOURCE_DIR}/002-Dbo/UserFormView.cpp
    ${SOURCE_DIR}/003-Auth/AuthWidget.cpp
    ${SOURCE_DIR}/003-Auth/PasswordPromptDialog.cpp
    ${SOURCE_DIR}/003-Auth/RegistrationView.cpp
    ${SOURCE_DIR}/004-Settings/Settings.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

# Link the required libraries
target_link_libraries(${PROJECT_NAME} 
    wthttp
    wt
    wtdbo
    wtdbosqlite3
    # laws-cpp-sdk-s3
    # laws-cpp-sdk-core
    # boost_filesystem
    # boost_regex
    # Ice++11
)

# Runtime library options

add_custom_target(run
    COMMAND ${PROJECT_NAME} ${RLIB}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/static
#     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources
#     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/xml-templates
#     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/wt_config.xml
#     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
