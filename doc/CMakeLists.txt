include(GNUInstallDirs)

add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/changelog.gz"
    COMMAND gzip -cn9 "${CMAKE_CURRENT_SOURCE_DIR}/changelog" > "${CMAKE_CURRENT_BINARY_DIR}/changelog.gz"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/changelog"
    COMMENT "Compressing changelog ${CMAKE_CURRENT_SOURCE_DIR}/changelog > ${CMAKE_CURRENT_BINARY_DIR}/changelog.gz"
)

add_custom_target(changelog ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/changelog.gz")

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/changelog.gz"
    DESTINATION "${CMAKE_INSTALL_DOCDIR}"
)