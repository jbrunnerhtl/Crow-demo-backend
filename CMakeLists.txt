cmake_minimum_required(VERSION 3.28)
project(crow-backend)

include(FetchContent)

FetchContent_Declare (
    Crow
    GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
    GIT_TAG v1.3.3
)

FetchContent_MakeAvailable(Crow)

set(PROJECT_FILES
    src/main.cpp
    src/InMemoryDeviceRepository.cpp
    src/Laptop.cpp
    src/Server.cpp
    src/Device.cpp
)


add_executable(${PROJECT_NAME} ${PROJECT_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE Crow::Crow)