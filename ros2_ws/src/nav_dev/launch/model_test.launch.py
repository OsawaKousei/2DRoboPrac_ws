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
    use_sim_time = LaunchConfiguration('use_sim_time', default='true')
    world_name = LaunchConfiguration('world_name', default='nav_slam_world')
    pkg_share_dir = get_package_share_directory('nav_dev')
    model_path = os.path.join(pkg_share_dir, "models")

    #ignition gazeboがモデルにアクセスできるように設定
    ign_resource_path = SetEnvironmentVariable(
        name='IGN_GAZEBO_RESOURCE_PATH',value=[
        os.path.join("/opt/ros/humble", "share"),
        ":" +
        model_path])

    #ロボットをスポーンさせる設定
    ignition_spawn_entity = Node(
        package='ros_ign_gazebo',
        executable='create',
        output='screen',
        arguments=['-entity', 'LidarRobo4',
                   '-name', 'LidarRobo4',
                   #ロボットのsdfファイルを指定
                   '-file', PathJoinSubstitution([
                        pkg_share_dir,
                        "models", "LidarRobo4", "model.sdf"]),
                    #ロボットの位置を指定
                   '-allow_renaming', 'true',
                   '-x', '0.2',
                   '-y', '0.2',
                   '-z', '0.075'],
        )
    
    #フィールドをスポーンさせる設定
    ignition_spawn_world = Node(
        package='ros_ign_gazebo',
        executable='create',
        output='screen',
            #フィールドのsdfファイルを指定
        arguments=['-file', PathJoinSubstitution([
                        pkg_share_dir,
                        "models", "field", "model.sdf"]),
                   '-allow_renaming', 'false'],
        )
    
    #ワールドのsdfファイルを設定(worldタグのあるsdfファイル)
    world = os.path.join(pkg_share_dir, "models", "worlds", "nav_slam.sdf")

    #ignition gazeboの起動設定
    ign_gz = IncludeLaunchDescription(
            PythonLaunchDescriptionSource(
                [os.path.join(get_package_share_directory('ros_ign_gazebo'),
                              'launch', 'ign_gazebo.launch.py')]),
            launch_arguments=[('ign_args', [' -r -v 3 ' +
                              world
                             ])])
    
    return LaunchDescription([
        ign_resource_path,
        ignition_spawn_entity,
        ignition_spawn_world,
        ign_gz,
    ])
