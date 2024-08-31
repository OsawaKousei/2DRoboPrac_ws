import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.actions import IncludeLaunchDescription, SetEnvironmentVariable
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node

def generate_launch_description():
    pkg_dir = get_package_share_directory('omni_control')
    lidar_launch = os.path.join(get_package_share_directory('urg_node2'),"launch","urg_node2.launch.py")

    hardware_node = Node(
                package='omni_control',
                executable='omni_hardware_node',
                output='screen',
                parameters=[os.path.join(pkg_dir,'config','omni_params.yaml')]
                )
    
    return LaunchDescription([       
        IncludeLaunchDescription(PythonLaunchDescriptionSource([lidar_launch])),
        hardware_node
    ])
