import os

from sympy import diff
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.actions import IncludeLaunchDescription, SetEnvironmentVariable
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node

def generate_launch_description():
    pkg_share_dir = get_package_share_directory('drive_pkg')

    diff_drive_node = Node(
                package='drive_pkg',
                executable='diff_drive_node',
                output='screen',
                parameters=[os.path.join(pkg_share_dir,'config','params.yaml')]
                )
    
    return LaunchDescription([
        diff_drive_node,
    ])