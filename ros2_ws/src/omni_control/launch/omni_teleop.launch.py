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
    nav_dev_dir = get_package_share_directory('nav_dev')
    pkg_dir = get_package_share_directory('omni_control')
    lidar_launch = os.path.join(get_package_share_directory('urg_node2'),"launch","urg_node2.launch.py")

    #joint_state_pubの起動
    states_pub_node = Node(
                package='omni_control',
                executable='omni_states_node',
                output='screen',
                parameters=[os.path.join(pkg_dir,'config','omni_params.yaml')]
                )
    #joyの起動   
    joy_node = Node(
                package='joy',
                executable='joy_node',
                output='screen'
                )
    #omni_joyの起動
    omni_joy_node = Node(
                package='omni_control',
                executable='omni_joy_node',
                output='screen',
                parameters=[os.path.join(pkg_dir,'config','omni_params.yaml')]
                )
    #omni_driveの起動
    omni_drive_node = Node(
                package='omni_control',
                executable='omni_drive_node',
                output='screen'
                )
    
    #omni_hardwareの起動
    omni_hardware_node = Node(
                package='omni_control',
                executable='omni_hardware_node',
                output='screen',
                parameters=[os.path.join(pkg_dir,'config','omni_params.yaml')]
                )

    
    #ロボットのsdfファイルのパスを取得
    sdf = os.path.join(
        get_package_share_directory('nav_dev'),
        'models', 'LidarRobo', 'model.sdf')

    #xacroでsdfファイルをurdfに変換
    doc = xacro.parse(open(sdf))
    xacro.process_doc(doc)
    
    #robot_state_publsherの起動設定
    robot_state_publisher = Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            name='robot_state_publisher',
            output='both',
            parameters=[{'robot_description': doc.toxml()}]) # type: ignore
     
    #rviz2の設定フィルのパスを取得
    rviz_config_dir = os.path.join(
        nav_dev_dir,
        'config',
        'nav_slam.rviz')
    
    #rviz2の起動設定
    rviz2 = Node(
            package='rviz2',
            executable='rviz2',
            name='rviz2',
            arguments=['-d', rviz_config_dir],
            output='screen')
    
    return LaunchDescription([
        joy_node,
        omni_joy_node,
        omni_drive_node,
        #omni_hardware_node,
        states_pub_node,
        robot_state_publisher,
        rviz2,
    ])
