

target_include_directories (${TARGET_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_sources(${TARGET_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/SN74HC161N.cpp
)
