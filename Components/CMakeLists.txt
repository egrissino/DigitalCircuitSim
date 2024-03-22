
target_include_directories (${TARGET_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

add_subdirectory(Bus)
add_subdirectory(Buffer)
add_subdirectory(Clock)
add_subdirectory(Counter)
add_subdirectory(Decoder)
add_subdirectory(EEPROM)
add_subdirectory(Latch)
add_subdirectory(Logic)
