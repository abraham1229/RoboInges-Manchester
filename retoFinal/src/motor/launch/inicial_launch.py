#Importaciones necesarias
import os
from ament_index_python.packages import get_package_share_directory
from launch_ros.actions import Node
from launch import LaunchDescription

def generate_launch_description():

    #Se declara la dirección del launchfile
    config = os.path.join(
        get_package_share_directory('motor'),
        'config',
        'params.yaml'
        )
    
    #Se corre el signal generator
    talker_node = Node(
        package='motor',
        executable='gener',
        output='screen',
        parameters = [config]
    )

    #Se ejecuta el graph
    rqt_graph_node = Node(
        package='rqt_graph',
        executable='rqt_graph',
        output='screen',
    )

    #Se ejecuta el plot
    rqt_plot_node = Node(
        package='rqt_plot',
        executable='rqt_plot',
        output='screen',
        arguments=[{'args': '/ri_Setpoint/data'}],  # Se especifican los tópicos a graficar
    )

    l_d = LaunchDescription([talker_node, rqt_graph_node, rqt_plot_node])
    return l_d
