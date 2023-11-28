import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.actions import IncludeLaunchDescription
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution

from launch_ros.actions import Node


def generate_launch_description():
    # Configure ROS nodes for launch

    # Setup project paths
    pkg_project_bringup = get_package_share_directory('ign_template')
    pkg_project_gazebo = get_package_share_directory('ign_template')
    pkg_ros_gz_sim = get_package_share_directory('ros_gz_sim')

    # Setup to launch the simulator and Gazebo world
    gz_sim = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_ros_gz_sim, 'launch', 'gz_sim.launch.py')),
        launch_arguments={'gz_args': PathJoinSubstitution([
            pkg_project_gazebo,
            'worlds',
            'basic_world1.sdf'
        ])}.items(),
    )

    rosnode1 =  Node(
                package='ign_template',
                executable='teleop_node',
                output='screen',
                prefix="xterm -e"
                )

    # Bridge ROS topics and Gazebo messages for establishing communication
    bridge = Node(
        package='ros_gz_bridge',
        executable='parameter_bridge',
        arguments=[
          '/teleop@geometry_msgs/msg/Twist@gz.msgs.Twist',
        ],
        output='screen'
    )

    return LaunchDescription([
        gz_sim,
        bridge,
        rosnode1
    ])