# --- Add header files
file (GLOB_RECURSE HEADER_FILES
	${PROJECT_SOURCE_DIR}/inc/*.h
	${PROJECT_SOURCE_DIR}/inc/*.hpp
)

add_compile_definitions (PLATFORM=${PLATFORM})
add_compile_definitions (_CRT_SECURE_NO_WARNINGS)

if ( ${PROFILE} EQUAL 0 ) 

	message ("Debug Compilation.")
	add_compile_definitions (DEBUG_TOKEN)
	
elseif ( ${PROFILE} EQUAL 0 )

	message ("Release Compilation.")
	
endif ()


set (WIN_RESOURCES ${CMAKE_SOURCE_DIR}/project/res/main.rc)
add_executable (
	${PROJECT_NAME} WIN32 ${HEADER_FILES} 

	src/io.cpp
	src/dialogWindow.cpp
	src/main.cpp

	${WIN_RESOURCES}
)


target_include_directories (${PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/inc
)


# --- DLLS - WINDOWS ONLY
target_link_libraries (${PROJECT_NAME} kernel32 user32 gdi32 winspool shell32 ole32 oleaut32 uuid comdlg32 advapi32 hid)

# --- Creation of a symlink to res inside build folder.
add_custom_command(
	TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E create_symlink
		${CMAKE_SOURCE_DIR}/project/res
		${CMAKE_CURRENT_BINARY_DIR}/res
	COMMENT "Creating a symling to 'res' folder."
)

# --- Addition of MANIFEST file (It is neccesery to make controls look the way intended).
add_custom_command (
	TARGET ${PROJECT_NAME} POST_BUILD 
	COMMAND "${MT}" -manifest "${CMAKE_CURRENT_BINARY_DIR}/res/main.manifest" -outputresource:"${CMAKE_CURRENT_BINARY_DIR}/NewFile.exe"
	COMMENT "Adding manifest file."
)
