cmake_minimum_required (VERSION 2.6)
project (Project_Zero)

set(OXYGINE_ROOT ../../../Programs/oxygine-framework/)

add_subdirectory(${OXYGINE_ROOT} oxygine-framework)
add_definitions(${OXYGINE_DEFINITIONS})
include_directories(${OXYGINE_INCLUDE_DIRS})
link_directories(${OXYGINE_LIBRARY_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OXYGINE_CXX_FLAGS}")

set(SOURCES_LIST ../src/main ../src/MainActor ../src/Application ../src/Creature) 

add_executable(Project_Zero ${SOURCES_LIST})
target_link_libraries(Project_Zero ${OXYGINE_CORE_LIBS})

if (WIN32) #disable console mode for VC++
	set_target_properties(Project_Zero PROPERTIES WIN32_EXECUTABLE TRUE)
endif(WIN32)
