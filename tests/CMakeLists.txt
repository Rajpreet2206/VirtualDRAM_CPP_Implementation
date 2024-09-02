find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(test_pim_simulator
    test_virtual_dram.cpp
    test_pim_operations.cpp
    test_pim_controller.cpp
)

target_link_libraries(test_pim_simulator
    PRIVATE
    GTest::GTest
    GTest::Main
    pim_simulator_lib
)

gtest_discover_tests(test_pim_simulator)