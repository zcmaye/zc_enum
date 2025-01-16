
add_executable(zc_enumAllTests
        AllTestsMain.cpp
    "HttpStatus.h" "HttpStatus.cpp")
#set_target_source_groups(zc_enumAllTests STRIP_PREFIX "zc_enum")


#target_link_libraries(zc_enumAllTests PRIVATE zc_enum PRIVATE zc_enum-test)

set_target_properties(zc_enumAllTests PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON
)
if (MSVC)
    target_compile_options(zc_enumAllTests PRIVATE /permissive-)
endif()

target_include_directories(zc_enumAllTests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_test(zc_enumAllTests zc_enumAllTests)