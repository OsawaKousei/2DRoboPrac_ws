import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.actions import IncludeLaunchDescription
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.actions import IncludeLaunchDescription, SetEnvironmentVariable
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution

from launch_ros.actions import Node
import xacro


def generate_launch_description():
    # Configure ROS nodes for launch

    # Setup project paths
    pkg_project_bringup = get_package_share_directory('nav_dev')
    pkg_project_gazebo = get_package_share_directory('nav_dev')
    pkg_ros_gz_sim = get_package_share_directory('ros_gz_sim')

    use_sim_time = LaunchConfiguration('use_sim_time', default='true')
    world_name = LaunchConfiguration('world_name', default='nav_dev_world')

    launch_file_dir = os.path.join(get_package_share_directory('nav_dev'), 'launch')

    ign_resource_path = SetEnvironmentVariable(
        name='IGN_GAZEBO_RESOURCE_PATH',value=[
        os.path.join("/opt/ros/humble", "share"),
        ":" +
        os.path.join(get_package_share_directory('nav_dev'), "models")])

    # Load the SDF file from "description" package
    sdf = os.path.join(
        get_package_share_directory('nav_dev'),
        'models', 'LidarRobo', 'model.sdf')

    doc = xacro.parse(open(sdf))
    xacro.process_doc(doc)

    # Spawn robot
    ignition_spawn_entity = Node(
        package='ros_ign_gazebo',
        executable='create',
        output='screen',
        arguments=['-entity', "waffle",
                   '-name', "waffle",
                   '-file', PathJoinSubstitution([
                        get_package_share_directory('nav_dev'),
                        "models", "turtlebot3", "model.sdf"]),
                   '-allow_renaming', 'true',
                   '-x', '-2',
                   '-y', '0.5',
                   '-z', '0.01'],
        )
    
    # Spawn world
    ignition_spawn_world = Node(
        package='ros_ign_gazebo',
        executable='create',
        output='screen',
        arguments=['-file', PathJoinSubstitution([
                        get_package_share_directory('nav_dev'),
                        "models", "worlds", "model.sdf"]),
                   '-allow_renaming', 'false'],
        )
    
    world_only = os.path.join(get_package_share_directory('nav_dev'), "models", "worlds", "world_only.sdf")

    # Setup to launch the simulator and Gazebo world
    gz_sim = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_ros_gz_sim, 'launch', 'gz_sim.launch.py')),
        launch_arguments={'gz_args': PathJoinSubstitution([
            pkg_project_gazebo,
            'worlds',
            'world_only.sdf'
        ])}.items()
    )

    ign_gz = IncludeLaunchDescription(
            PythonLaunchDescriptionSource(
                [os.path.join(get_package_share_directory('ros_ign_gazebo'),
                              'launch', 'ign_gazebo.launch.py')]),
            launch_arguments=[('ign_args', [' -r -v 3 ' +
                              world_only
                             ])])

    robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='both',
        parameters=[
            {'use_sim_time': True},
            {'robot_description': doc.toxml()},
        ]
    )

    # Visualize in RViz
    rviz = Node(
       package='rviz2',
       executable='rviz2',
       name="rviz2",
       arguments=['-d', os.path.join(pkg_project_bringup, 'config', 'slam.rviz')],
       parameters=[{'use_sim_time': use_sim_time}],
       condition=IfCondition(LaunchConfiguration('rviz')),
       output='screen'
    )

    # Bridge ROS topics and Gazebo messages for establishing communication
    bridge = Node(
        package='ros_ign_bridge',
        executable='parameter_bridge',
        parameters=[{
            'config_file': os.path.join(pkg_project_bringup, 'config', 'lidar_bridge.yaml'),
            'qos_overrides./tf_static.publisher.durability': 'transient_local',
        },{'use_sim_time': use_sim_time}],
        #/odom/tfをtfとして再発行
        remappings=[
            ("/odom/tf", "tf"),
        ]
    )

    map_static_tf = Node(package='tf2_ros',
                        executable='static_transform_publisher',
                        name='static_transform_publisher',
                        output='log',
                        arguments=['0.0', '0.0', '0.0', '0.0', '0.0', '0.0', 'map', 'odom'])
 
    map_dir = LaunchConfiguration(
        'map',
        default=os.path.join(
            get_package_share_directory('nav_dev'),
            'maps',
            'turtlebot3_world.yaml'))

    param_file_name = 'waffle.yaml'

    param_dir = LaunchConfiguration(
        'params_file',
        default=os.path.join(
            get_package_share_directory('nav_dev'),
            'params',
            param_file_name))
    
    nav2_launch_file_dir = os.path.join(get_package_share_directory('nav2_bringup'), 'launch')

    rviz_config_dir = os.path.join(
        get_package_share_directory('nav2_bringup'),
        'rviz',
        'nav2_default_view.rviz')



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
        
        DeclareLaunchArgument('rviz', default_value='true',description='Open RViz.'),
        
        bridge,
        map_static_tf,

        DeclareLaunchArgument(
            'use_sim_time',
            default_value=use_sim_time,
            description='If true, use simulated clock'),
        
        DeclareLaunchArgument(
            'use_sim_time',
            default_value=use_sim_time,
            description='If true, use simulated clock'),

        robot_state_publisher,

        DeclareLaunchArgument(
            'map',
            default_value=map_dir,
            description='Full path to map file to load'),

        DeclareLaunchArgument(
            'params_file',
            default_value=param_dir,
            description='Full path to param file to load'),

        DeclareLaunchArgument(
            'use_sim_time',
            default_value='true',
            description='Use simulation (Gazebo) clock if true'),
        
        DeclareLaunchArgument(
            'use_sim_time',
            default_value='true',
            description='Use simulation (Gazebo) clock if true'),

        IncludeLaunchDescription(
            PythonLaunchDescriptionSource([nav2_launch_file_dir, '/bringup_launch.py']),
            launch_arguments={
                'map': map_dir,
                'use_sim_time': use_sim_time,
                'params_file': param_dir}.items(),
        ),

        Node(
            package='rviz2',
            executable='rviz2',
            name='rviz2',
            arguments=['-d', rviz_config_dir],
            parameters=[{'use_sim_time': use_sim_time}],
            output='screen'),

    ])