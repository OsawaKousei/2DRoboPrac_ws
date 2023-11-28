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
    pkg_project_bringup = get_package_share_directory('nav_dev')
    pkg_project_gazebo = get_package_share_directory('nav_dev')
    pkg_ros_gz_sim = get_package_share_directory('ros_gz_sim')

    use_sim_time = LaunchConfiguration('use_sim_time', default='true')
    world_name = LaunchConfiguration('world_name', default='nav_dev_world')

    launch_file_dir = os.path.join(get_package_share_directory('nav_dev'), 'launch')

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
        arguments=['-entity', "LiadarRobo",
                   '-name', "Lidarrobo",
                   '-file', PathJoinSubstitution([
                        get_package_share_directory('nav_dev'),
                        "models", "lidarRobo", "model.sdf"]),
                   '-allow_renaming', 'true',
                   '-x', '0.1',
                   '-y', '0.1',
                   '-z', '0.075'],
        )
    
    # Spawn world
    ignition_spawn_world = Node(
        package='ros_ign_gazebo',
        executable='create',
        output='screen',
        arguments=['-file', PathJoinSubstitution([
                        get_package_share_directory('nav_dev'),
                        "models", "field", "model.sdf"]),
                   '-allow_renaming', 'false'],
        )

    # Setup to launch the simulator and Gazebo world
    gz_sim = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_ros_gz_sim, 'launch', 'gz_sim.launch.py')),
        launch_arguments={'gz_args': PathJoinSubstitution([
            pkg_project_gazebo,
            'worlds',
            'world_only.sdf'
        ])}.items(),
    )

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
        package='ros_gz_bridge',
        executable='parameter_bridge',
        parameters=[{
            'config_file': os.path.join(pkg_project_bringup, 'config', 'lidar_bridge.yaml'),
            'qos_overrides./tf_static.publisher.durability': 'transient_local',
        }],
        #/odom/tfをtfとして再発行
        remappings=[
            ("/odom/tf", "tf"),
        ]
    )

    lidar_node =  Node(
                package='nav_dev',
                executable='lidar_node',
                prefix="xterm -e"
                )
    
    teleop_node =  Node(
                package='nav_dev',
                executable='teleop_node',
                prefix="xterm -e"
                )

    return LaunchDescription([
        ignition_spawn_entity,
        ignition_spawn_world,
        gz_sim,
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
        robot_state_publisher,
        rviz,
        lidar_node
    ])