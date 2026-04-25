cmake_minimum_required(VERSION 3.15)
project(AuraVisionEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include Directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Source Files
set(SOURCES
    src/main.cpp
    src/Core/TaskScheduler.cpp
    src/Core/PoolAllocator.cpp
    src/Renderer/VisualEngine.cpp
)

# Header Files (for IDE visibility)
set(HEADERS
    include/Aura/Core/Base.hpp
    include/Aura/Core/TaskScheduler.hpp
    include/Aura/Math/Vector3.hpp
    include/Aura/Math/Matrix4.hpp
    include/Aura/Camera/Camera.hpp
    include/Aura/Renderer/VisualEngine.hpp
    include/Aura/Vision/ImageProcessor.hpp
)

# Executable
add_executable(AuraEngine ${SOURCES} ${HEADERS})

# Optimization flags for "Heavy" performance
if(MSVC)
    target_compile_options(AuraEngine PRIVATE /W4 /O2 /Oi /Ot /GL)
else()
    target_compile_options(AuraEngine PRIVATE -Wall -Wextra -O3)
endif()
