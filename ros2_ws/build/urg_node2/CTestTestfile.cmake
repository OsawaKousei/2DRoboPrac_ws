# CMake generated Testfile for 
# Source directory: /home/kousei/2DRoboPrac_ws/ros2_ws/src/urg_node2
# Build directory: /home/kousei/2DRoboPrac_ws/ros2_ws/build/urg_node2
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(urg_node2_test "/usr/bin/python3.10" "-u" "/opt/ros/humble/share/ament_cmake_test/cmake/run_test.py" "/home/kousei/2DRoboPrac_ws/ros2_ws/build/urg_node2/test_results/urg_node2/urg_node2_test.gtest.xml" "--package-name" "urg_node2" "--output-file" "/home/kousei/2DRoboPrac_ws/ros2_ws/build/urg_node2/ament_cmake_gtest/urg_node2_test.txt" "--command" "/home/kousei/2DRoboPrac_ws/ros2_ws/build/urg_node2/urg_node2_test" "--gtest_output=xml:/home/kousei/2DRoboPrac_ws/ros2_ws/build/urg_node2/test_results/urg_node2/urg_node2_test.gtest.xml")
set_tests_properties(urg_node2_test PROPERTIES  LABELS "gtest" REQUIRED_FILES "/home/kousei/2DRoboPrac_ws/ros2_ws/build/urg_node2/urg_node2_test" TIMEOUT "200" WORKING_DIRECTORY "/home/kousei/2DRoboPrac_ws/ros2_ws/build/urg_node2" _BACKTRACE_TRIPLES "/opt/ros/humble/share/ament_cmake_test/cmake/ament_add_test.cmake;125;add_test;/opt/ros/humble/share/ament_cmake_gtest/cmake/ament_add_gtest_test.cmake;86;ament_add_test;/opt/ros/humble/share/ament_cmake_gtest/cmake/ament_add_gtest.cmake;93;ament_add_gtest_test;/home/kousei/2DRoboPrac_ws/ros2_ws/src/urg_node2/CMakeLists.txt;64;ament_add_gtest;/home/kousei/2DRoboPrac_ws/ros2_ws/src/urg_node2/CMakeLists.txt;0;")
subdirs("gtest")
