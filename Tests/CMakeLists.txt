include_directories(../Src)

add_executable(testbench testbench.cpp)

target_link_libraries(testbench PPLIB)

add_test(NAME Test1 COMMAND  testbench /home/matttax/CLionProjects/PathPlanningProject/TestData/0_test.xml)
add_test(NAME Test2 COMMAND  testbench /home/matttax/CLionProjects/PathPlanningProject/TestData/1_test.xml)
add_test(NAME Test3 COMMAND  testbench /home/matttax/CLionProjects/PathPlanningProject/TestData/2_test.xml)
add_test(NAME Test4 COMMAND  testbench /home/matttax/CLionProjects/PathPlanningProject/TestData/3_test.xml)
add_test(NAME Test5 COMMAND  testbench /home/matttax/CLionProjects/PathPlanningProject/TestData/4_test.xml)
add_test(NAME Test6 COMMAND  testbench /home/matttax/CLionProjects/PathPlanningProject/TestData/5_test.xml)
add_test(NAME Test7 COMMAND  testbench /home/matttax/CLionProjects/PathPlanningProject/TestData/6_test.xml)
add_test(NAME Test8 COMMAND  testbench /home/matttax/CLionProjects/PathPlanningProject/TestData/7_test.xml)
add_test(NAME Test9 COMMAND  testbench /home/matttax/CLionProjects/PathPlanningProject/TestData/8_test.xml)
add_test(NAME Test10 COMMAND testbench /home/matttax/CLionProjects/PathPlanningProject/TestData/9_test.xml)
add_test(NAME Test11 COMMAND testbench /home/matttax/CLionProjects/PathPlanningProject/TestData/A_test.xml)
add_test(NAME Test12 COMMAND testbench /home/matttax/CLionProjects/PathPlanningProject/TestData/B_test.xml)