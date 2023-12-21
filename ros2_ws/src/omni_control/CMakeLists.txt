cmake_minimum_required(VERSION 3.8)
project(omni_control)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

#依存関係を自動で解決
find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()



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

#omni_joy_nodeを実行ファイルとしてビルド
ament_auto_add_executable(
omni_joy_node src/omni_joy_node.cpp
)

#omni_drive_nodeを実行ファイルとしてビルド
ament_auto_add_executable(
omni_drive_node src/omni_drive_node.cpp
)

#omni_raspi_nodeを実行ファイルとしてビルド
ament_auto_add_executable(
omni_raspi_node src/omni_raspi_node.cpp
)

#omni_hardware_nodeを実行ファイルとしてビルド
ament_auto_add_executable(
omni_hardware_node src/omni_hardware_node.cpp
)

#omni_states_nodeを実行ファイルとしてビルド
ament_auto_add_executable(
omni_states_node src/omni_states_node.cpp
)

#実行ファイルのビルド、共有ファイルのインストール
ament_auto_package(
  INSTALL_TO_SHARE
    config
    launch
)
