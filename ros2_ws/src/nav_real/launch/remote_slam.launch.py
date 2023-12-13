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
    share_pkg_dir = get_package_share_directory('nav_real')
    lidar_launch = os.path.join(get_package_share_directory('urg_node2'),"launch","urg_node2.launch.py")

    #joint_state_pubの起動
    states_pub_node = Node(
                package='nav_real',
                executable='states_pub_node',
                output='screen',
                parameters=[os.path.join(share_pkg_dir,'config','params.yaml')]
                )
    
    dammy_enc_node = Node(
            package='nav_real',
            executable='dammy_encorder_node',
            output='screen',
            parameters=[os.path.join(share_pkg_dir,'config','params.yaml')]
            )
    
    joy_node = Node(
                package='joy',
                executable='joy_node',
                output='screen'
                )
    joy_transrate_node = Node(
                package='nav_real',
                executable='joy_transrate_node',
                output='screen',
                parameters=[os.path.join(share_pkg_dir,'config','params.yaml')]
                )

    diff_drive_node = Node(
                package='nav_real',
                executable='diff_drive_node',
                output='screen',
                parameters=[os.path.join(share_pkg_dir,'config','params.yaml')]
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
    
    #slam_toolboxの起動オプション設定
    slam_params_file = LaunchConfiguration('slam_params_file')
    declare_slam_params_file_cmd = DeclareLaunchArgument(
        'slam_params_file',
        default_value=os.path.join(get_package_share_directory("nav_dev"),
                                   'params', 'slam_param.yaml'),
        description='Full path to the ROS2 parameters file to use for the slam_toolbox node')

    #slam_toolboxの起動設定
    start_async_slam_toolbox_node = Node(
        parameters=[
          slam_params_file,
        ],
        package='slam_toolbox',
        executable='async_slam_toolbox_node',
        name='slam_toolbox',
        output='screen')
    
    return LaunchDescription([
        states_pub_node,
        dammy_enc_node,
        robot_state_publisher,

        joy_node,
        joy_transrate_node,
        diff_drive_node,

        rviz2,

        declare_slam_params_file_cmd,
        start_async_slam_toolbox_node,
    ])
