#cmake file for project association
#author: liuwenjun
#created:2014/02/20

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

## 添加项目
set(CMAKE_SHARED_LIBRARY_SUFFIX ".passoa")
SET(CMAKE_SHARED_LIBRARY_PREFIX "")

include_directories(${PROJECT_SOURCE_DIR}/stage/include)
LINK_DIRECTORIES (${PROJECT_SOURCE_DIR}/stage/lib)
if(PASSOA_COMPILER_MSVC)

add_library(img SHARED
${PROJECT_SOURCE_DIR}/src/export.def
${PROJECT_SOURCE_DIR}/src/jpeg.cpp
)
install(FILES ${PROJECT_SOURCE_DIR}/stage/bin/turbojpeg.dll DESTINATION node_modules/img)

else()

add_library(img SHARED
${PROJECT_SOURCE_DIR}/src/jpeg.cpp
)
install(FILES ${PROJECT_SOURCE_DIR}/stage/lib/libturbojpeg.so DESTINATION node_modules/img)

endif()

target_link_libraries(img
	turbojpeg
)

install(TARGETS img
	RUNTIME DESTINATION  node_modules/img
	LIBRARY DESTINATION  node_modules/img
	ARCHIVE DESTINATION  node_modules/img
)
# install(DIRECTORY ${PROJECT_SOURCE_DIR}/modules/ DESTINATION node_modules)
