#Importaciones necesarias
from launch_ros.actions import Node
from launch import LaunchDescription

def generate_launch_description():

    #Se corre el signal generator
    talker_node = Node(
        package='params_reto',
        executable='signal_gener',
        output='screen',
    )

    #Se corre el signal process
    listener_node = Node(
        package='params_reto',
        executable='signal_reconstruction',
        output='screen',
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
        arguments=['/ri_signal/data', '/ri_signal_reconstructed/data'],  # Se especifican los tópicos
    )

    l_d = LaunchDescription([talker_node, listener_node, 
                             rqt_graph_node, rqt_plot_node])
    return l_d
