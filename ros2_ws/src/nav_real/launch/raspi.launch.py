import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.actions import IncludeLaunchDescription, SetEnvironmentVariable
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
import xacro

def generate_launch_description():
    lidar_launch = os.path.join(get_package_share_directory('urg_node2'),"launch","urg_node2.launch.py")
    
    raspi_node = Node(
                package='nav_real',
                executable='raspi_node',
                output='screen'
                )
    
    return LaunchDescription([       
        IncludeLaunchDescription(PythonLaunchDescriptionSource([lidar_launch])),

        raspi_node,
    ])
