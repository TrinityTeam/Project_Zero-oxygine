cmake_minimum_required (VERSION 2.6)
project (Project_Zero)

if (NOT OXYGINE_ROOT AND DEFINED ENV{OXYGINE_ROOT})
	file(TO_CMAKE_PATH "$ENV{OXYGINE_ROOT}" OXYGINE_ROOT)

elseif(NOT OXYGINE_ROOT AND NOT DEFINED ENV{OXYGINE_ROOT})
	message(FATAL_ERROR "Oxygine has not been found; Please specify OXYGINE_ROOT environment variable")

endif()

add_subdirectory(${OXYGINE_ROOT} oxygine-framework)
add_definitions(${OXYGINE_DEFINITIONS})
include_directories(${OXYGINE_INCLUDE_DIRS})
link_directories(${OXYGINE_LIBRARY_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OXYGINE_CXX_FLAGS}")

set(SOURCES_LIST ../src/main ../src/Scene ../src/Application ../src/Creature)

add_executable(Project_Zero ${SOURCES_LIST})

if(MINGW)
	set(ADDITIONAL_LIBRARIES psapi)
endif()

target_link_libraries(${PROJECT_NAME} ${OXYGINE_CORE_LIBS} ${ADDITIONAL_LIBRARIES})

if (WIN32)
	set_target_properties(Project_Zero PROPERTIES WIN32_EXECUTABLE TRUE)
endif()
