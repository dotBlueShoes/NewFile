set_property (GLOBAL PROPERTY USE_FOLDERS ON)
set_property (GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

set (CMAKE_CXX_STANDARD 23)
set (CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set (CMAKE_DISABLE_SOURCE_CHANGES ON)

# --- Turn on reloading for XAML code on hot for MSVC compilators it it's available.
if (POLICY CMP0141)
	cmake_policy (SET CMP0141 NEW)
	set (CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif ()

#set (PLATFORM_WIN 1)
#set (PLATFORM_LINUX 2)
#set (PLATFORM_MAC 3)

# if ( PLATFORM EQUAL ${PLATFORM_WIN} ) {
# 	message("-- Platform Type WINDOWS")
# } elseif ( ${PLATFORM} EQUAL ${PLATFORM_LINUX} ) {
# 	message("-- Platform Type LINUX")
# } elseif ( ${PLATFORM} EQUAL ${PLATFORM_MAC} ) {
# 	message("-- Platform Type MAC")
# }


# --- BUILD TYPES
# --- set(BUILD_TYPE_AGN 0)
# --- set(BUILD_TYPE_WIN 1)
# --- if (CMAKE_BUILD_TYPE STREQUAL "Debug")
# --- 
# ---     # SET DEBUG LEVEL (PROJECT VARIABLE)
# ---     add_compile_definitions(DEBUG_LEVEL=3)
# --- 
# ---     if (BUILD_TYPE EQUAL ${BUILD_TYPE_WIN})
# ---         message("-- Build Type WINDOWS DEBUG")
# ---     else()
# ---         message("-- Build Type AGNOSTIC DEBUG")
# ---     endif()
# --- else() # Release
# --- 
# --- 	# SET DEBUG LEVEL (PROJECT VARIABLE)
# ---     add_compile_definitions(DEBUG_LEVEL=0)
# --- 
# ---     if (BUILD_TYPE EQUAL ${BUILD_TYPE_WIN})
# ---         message("-- Build Type WINDOWS RELEASE")
# ---     else()
# ---         message("-- Build Type AGNOSTIC RELEASE")
# ---     endif()
# --- endif()