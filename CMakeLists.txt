cmake_minimum_required(VERSION 3.15)
project(AuraVisionEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include Directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Base Source Files
set(SOURCES
    src/Core/TaskScheduler.cpp
    src/Core/PoolAllocator.cpp
    src/Renderer/VisualEngine.cpp
)

# Platform Specific Logic
if(ANDROID)
    # Add JNI Bridge for Android
    list(APPEND SOURCES android/app/src/main/cpp/native-lib.cpp)
    add_library(aura_engine SHARED ${SOURCES})
    target_link_libraries(aura_engine log) # Link Android logging
else()
    # Desktop Executable
    list(APPEND SOURCES src/main.cpp)
    add_executable(AuraEngine ${SOURCES})
endif()

# Optimization flags
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /O2 /Oi /Ot /GL)
else()
    # Using PROJECT_NAME to target either the library or the executable
    if(ANDROID)
        target_compile_options(aura_engine PRIVATE -Wall -Wextra -O3)
    else()
        target_compile_options(AuraEngine PRIVATE -Wall -Wextra -O3)
    endif()
endif()
