import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.actions import IncludeLaunchDescription
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution

from launch_ros.actions import Node
import xacro


def generate_launch_description():
    # Configure ROS nodes for launch

    # Setup project paths
    pkg_project_bringup = get_package_share_directory('rviz_test')
    model_path = os.path.join(get_package_share_directory('rviz_test'), 'model', '01-first.urdf')

    robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='both',
        arguments=[model_path]
    )

    # Visualize in RViz
    rviz = Node(
       package='rviz2',
       executable='rviz2',
       arguments=['-d', os.path.join(pkg_project_bringup, 'config', 'urdf.rviz')]
    )

    return LaunchDescription([
        robot_state_publisher,
        rviz
    ])