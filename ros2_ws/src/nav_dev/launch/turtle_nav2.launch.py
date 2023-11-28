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
    #よく使う変数を設定
    use_sim_time = LaunchConfiguration('use_sim_time', default='true')
    world_name = LaunchConfiguration('world_name', default='nav_dev_world')
    pkg_share_dir = get_package_share_directory('nav_dev')
    model_path = os.path.join(get_package_share_directory('nav_dev'), "models")

    #gazeboがモデルにアクセスできるようにするための設定
    ign_resource_path = SetEnvironmentVariable(
        name='IGN_GAZEBO_RESOURCE_PATH',value=[
        os.path.join("/opt/ros/humble", "share"),
        ":" + model_path])

    #ロボットをスポーンさせる
    ignition_spawn_entity = Node(
        package='ros_ign_gazebo',
        executable='create',
        output='screen',
        arguments=['-entity', 'waffle',
                   '-name', 'waffle',
                   #ロボットのsdfファイルを指定
                   '-file', PathJoinSubstitution([model_path, "turtlebot3", "model.sdf"]),
                   '-allow_renaming', 'true',
                   #ロボットをスポーンさせる位置を指定
                   '-x', '-2.0',
                   '-y', '-0.5',
                   '-z', '0.01'],
        )
    
    #フィールドをスポーンさせる
    ignition_spawn_world = Node(
        package='ros_ign_gazebo',
        executable='create',
        output='screen',
        arguments=['-file', PathJoinSubstitution([model_path, "worlds", "model.sdf"]),#フィールドのsdfファイルを指定
                   '-allow_renaming', 'false'],
        )
    
    #シミュレーション環境のsdfファイルを指定(worldタグを持つsdfファイル)
    world_only = os.path.join(model_path, "worlds", "world_only.sdf")

    #ign gazeboの起動
    ign_gz = IncludeLaunchDescription(
            PythonLaunchDescriptionSource(
                [os.path.join(get_package_share_directory('ros_ign_gazebo'),
                              'launch', 'ign_gazebo.launch.py')]),
            launch_arguments=[('ign_args', [' -r -v 3 ' +
                              world_only
                             ])])
    #ros_ign_bridgeの起動
    bridge = Node(
        package='ros_ign_bridge',
        executable='parameter_bridge',
        parameters=[{
            #brigdeのcofigファイルを指定
            'config_file': os.path.join(pkg_share_dir, 'config', 'lidar_bridge.yaml'),
            'qos_overrides./tf_static.publisher.durability': 'transient_local',
        },{'use_sim_time': use_sim_time}],
        #topicの名前を変更
        remappings=[
            ("/odom/tf", "tf"),
        ],
        output='screen'
    )

    #mapトピックの発行？
    map_static_tf = Node(package='tf2_ros',
                        executable='static_transform_publisher',
                        name='static_transform_publisher',
                        output='log',
                        arguments=['0.0', '0.0', '0.0', '0.0', '0.0', '0.0', 'map', 'odom'])
    
    #ロボットのsdfファイルを指定
    sdf = os.path.join(
        model_path, 'turtlebot3', 'model.sdf')

    #xacroでsdfファイルをurdfファイルに変換
    doc = xacro.parse(open(sdf))
    xacro.process_doc(doc)

    #robot_state_publisherを起動
    robot_state_publisher = Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            name='robot_state_publisher',
            output='both',
            parameters=[{'use_sim_time': use_sim_time,
                         'robot_description': doc.toxml()}])
    
    #nav2のマップファイルを指定
    map_dir = LaunchConfiguration(
        'map',
        default=os.path.join(
            pkg_share_dir,
            'maps',
            'turtlebot3_world.yaml'))

    #nav2のパラメータファイルを指定
    param_file_name = 'waffle.yaml'
    param_dir = LaunchConfiguration(
        'params_file',
        default=os.path.join(
            pkg_share_dir,
            'params',
            param_file_name))

    #nav2の起動ファイルの位置を指定
    nav2_launch_file_dir = os.path.join(get_package_share_directory('nav2_bringup'), 'launch')

    #rviz2の設定ファイルを指定(今回はnav2用に提供された設定を使用)
    rviz_config_dir = os.path.join(
        get_package_share_directory('nav2_bringup'),
        'rviz',
        'nav2_default_view.rviz')
    
    #nav2の起動
    nav2 = IncludeLaunchDescription(
            PythonLaunchDescriptionSource([nav2_launch_file_dir, '/bringup_launch.py']),
            launch_arguments={
                'map': map_dir,
                'use_sim_time': use_sim_time,
                'params_file': param_dir}.items(),
        )
    
    #rviz2の起動
    rviz2 = Node(
            package='rviz2',
            executable='rviz2',
            name='rviz2',
            arguments=['-d', rviz_config_dir],
            parameters=[{'use_sim_time': use_sim_time}],
            output='screen')

    return LaunchDescription([
        ign_resource_path,
        ignition_spawn_entity,
        ignition_spawn_world,
        ign_gz,
        DeclareLaunchArgument(
            'use_sim_time',
            default_value=use_sim_time,
            description='If true, use simulated clock'),

        DeclareLaunchArgument(
            'world_name',
            default_value=world_name,
            description='World name'),
        
        bridge,
        map_static_tf,
       
        robot_state_publisher,

        DeclareLaunchArgument(
            'map',
            default_value=map_dir,
            description='Full path to map file to load'),

        DeclareLaunchArgument(
            'params_file',
            default_value=param_dir,
            description='Full path to param file to load'),
        nav2,
        rviz2,
    ])
