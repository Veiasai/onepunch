add_library(ctp_info_lib_${CTP_LIB_VERSION} SHARED IMPORTED GLOBAL)
set_target_properties(ctp_info_lib_${CTP_LIB_VERSION}
                PROPERTIES
                IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libthostmduserapi_${CTP_LIB_VERSION}.so
                IMPORTED_NO_SONAME true
                INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/../inc)

add_library(ctp_exec_lib_${CTP_LIB_VERSION} SHARED IMPORTED GLOBAL)
set_target_properties(ctp_exec_lib_${CTP_LIB_VERSION}
                PROPERTIES
                IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libthosttraderapi_${CTP_LIB_VERSION}.so
                IMPORTED_NO_SONAME true
                INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/../inc)

add_library(ctp_data_collect_lib_${CTP_LIB_VERSION} SHARED IMPORTED GLOBAL)
set_target_properties(ctp_data_collect_lib_${CTP_LIB_VERSION}
                PROPERTIES
                IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libLinuxDataCollect_${CTP_LIB_VERSION}.so
                IMPORTED_NO_SONAME true
                INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/../inc)
