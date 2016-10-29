
message(STATUS "Prep for addon: CEF")

SET(CEF_PATH ${CMAKE_CURRENT_LIST_DIR})

macro(ADDON_CEF_PROJECT ADDON_BUILD)
    message(STATUS "Adding project with build folder of ${ADDON_BUILD}")
    add_subdirectory (${CEF_PATH} "${ADDON_BUILD}/CEF_build")
endmacro(ADDON_CEF_PROJECT)

macro(ADDON_CEF_INCLUDES)
    include_directories(${CEF_PATH}/include/)
    include_directories(${CEF_PATH}/include/include/)
endmacro(ADDON_CEF_INCLUDES)

macro(ADDON_CEF APPLICATION_TARGET FOLDER)
    message(STATUS "Function call for CEF")
    message(STATUS "Adding include directory to: ${${APPLICATION_TARGET}} ${CEF_PATH}/include/")
	
	SET(CEF_lib "${CEF_PATH}/bin/x64/CEF-vc130-mtd.lib")
	
    SET(CEF_dll "${CEF_PATH}/bin/x64/libcef.dll")
	SET(d3dcompiler_43 "${CEF_PATH}/bin/x64/d3dcompiler_43.dll")
	SET(d3dcompiler_47 "${CEF_PATH}/bin/x64/d3dcompiler_47.dll")
	SET(libEGL "${CEF_PATH}/bin/x64/libEGL.dll")
	SET(libGLESv2 "${CEF_PATH}/bin/x64/libGLESv2.dll")
	SET(widevinecdmadapter "${CEF_PATH}/bin/x64/widevinecdmadapter.dll")
	SET(natives_blob "${CEF_PATH}/bin/x64/natives_blob.bin")
	SET(snapshot_blob "${CEF_PATH}/bin/x64/snapshot_blob.bin")
	SET(cefpak "${CEF_PATH}/bin/x64/cef.pak")
	SET(cef_100_percent "${CEF_PATH}/bin/x64/cef_100_percent.pak")
	SET(cef_200_percent "${CEF_PATH}/bin/x64/cef_200_percent.pak")
	SET(cef_extensions "${CEF_PATH}/bin/x64/cef_extensions.pak")
	SET(devtools_resources "${CEF_PATH}/bin/x64/devtools_resources.pak")
	SET(icudtl "${CEF_PATH}/bin/x64/icudtl.dat")
	
    if(${OPIFEX_OPTION_RELEASE})
      SET(BINARY_RELEASE_MODE "release")
    else()
      SET(BINARY_RELEASE_MODE "debug")
    endif()

    message(STATUS "COPY TO: ${PROJECT_BINARY_DIR}/${FOLDER}")
    add_custom_command(TARGET ${APPLICATION_TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CEF_dll}" ${PROJECT_BINARY_DIR}/${FOLDER})
    add_custom_command(TARGET ${APPLICATION_TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${d3dcompiler_43}" ${PROJECT_BINARY_DIR}/${FOLDER})
    add_custom_command(TARGET ${APPLICATION_TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${d3dcompiler_47}" ${PROJECT_BINARY_DIR}/${FOLDER})
    add_custom_command(TARGET ${APPLICATION_TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${libEGL}" ${PROJECT_BINARY_DIR}/${FOLDER})
    add_custom_command(TARGET ${APPLICATION_TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${libGLESv2}" ${PROJECT_BINARY_DIR}/${FOLDER})
    add_custom_command(TARGET ${APPLICATION_TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${widevinecdmadapter}" ${PROJECT_BINARY_DIR}/${FOLDER})
    add_custom_command(TARGET ${APPLICATION_TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${natives_blob}" ${PROJECT_BINARY_DIR}/${FOLDER})
    add_custom_command(TARGET ${APPLICATION_TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${snapshot_blob}" ${PROJECT_BINARY_DIR}/${FOLDER})
    add_custom_command(TARGET ${APPLICATION_TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${cefpak}" ${PROJECT_BINARY_DIR}/${FOLDER})
    add_custom_command(TARGET ${APPLICATION_TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${cef_100_percent}" ${PROJECT_BINARY_DIR}/${FOLDER})
    add_custom_command(TARGET ${APPLICATION_TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${cef_200_percent}" ${PROJECT_BINARY_DIR}/${FOLDER})
    add_custom_command(TARGET ${APPLICATION_TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${cef_extensions}" ${PROJECT_BINARY_DIR}/${FOLDER})
    add_custom_command(TARGET ${APPLICATION_TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${devtools_resources}" ${PROJECT_BINARY_DIR}/${FOLDER})
    add_custom_command(TARGET ${APPLICATION_TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${icudtl}" ${PROJECT_BINARY_DIR}/${FOLDER})
	
    add_custom_command(TARGET ${APPLICATION_TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CEF_PATH}/bin/x64/locales/en-US.pak" ${PROJECT_BINARY_DIR}/${FOLDER}/locales)
	
endmacro(ADDON_CEF)

macro(ADDON_CEF_DEFINES TEMP_RESULT)
endmacro(ADDON_CEF_DEFINES)

macro(ADDON_CEF_LINK TEMP_RESULT)
    SET(TEMP_RESULT "cef")
endmacro(ADDON_CEF_LINK)

macro(ADDON_CEF_ASSETS TEMP_RESULT)
	SET(TEMP_RESULT "")
endmacro(ADDON_CEF_ASSETS)