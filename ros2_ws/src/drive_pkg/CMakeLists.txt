cmake_minimum_required(VERSION 3.8)
project(drive_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

file(GLOB ${PROJECT_NAME}_msg_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} msg/*)
#file(GLOB ${PROJECT_NAME}_srv_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} srv/*)


rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/DiffDrive.msg"
)


ament_auto_add_executable(
diff_drive_node src/diff_drive_node.cpp
)


ament_auto_package()
