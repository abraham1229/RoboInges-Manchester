import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32
from scipy import signal
import math


#Se crea el nodo My_Talker_Params tomando objeto de Node.
class My_Talker_Params(Node):
    #Se inicializa el nodo
    def __init__(self):
        #Se crear el nodo que será encargado de publicar la señal
        super().__init__('ri_Setpoint')
        #Se declara la lista de parámetros a utilizar
        self.declare_parameters(
            namespace='',
            parameters=[
                ('ri_type', rclpy.Parameter.Type.INTEGER),
                ('ri_sine.amplitude', rclpy.Parameter.Type.DOUBLE),
                ('ri_sine.frequency', rclpy.Parameter.Type.DOUBLE),
                ('ri_sine.offset', rclpy.Parameter.Type.DOUBLE),
                ('ri_sine.phase', rclpy.Parameter.Type.DOUBLE),
                ('ri_sine.time', rclpy.Parameter.Type.DOUBLE),
                ('ri_square.amplitude', rclpy.Parameter.Type.DOUBLE),
                ('ri_square.frequency', rclpy.Parameter.Type.DOUBLE),
                ('ri_square.offset', rclpy.Parameter.Type.DOUBLE),
                ('ri_square.phase', rclpy.Parameter.Type.DOUBLE),
                ('ri_square.time', rclpy.Parameter.Type.DOUBLE),
                ('ri_sawtooth.amplitude', rclpy.Parameter.Type.DOUBLE),
                ('ri_sawtooth.frequency', rclpy.Parameter.Type.DOUBLE),
                ('ri_sawtooth.offset', rclpy.Parameter.Type.DOUBLE),
                ('ri_sawtooth.phase', rclpy.Parameter.Type.DOUBLE),
                ('ri_sawtooth.time', rclpy.Parameter.Type.DOUBLE),
                ('ri_constant.amplitude', rclpy.Parameter.Type.DOUBLE),
            ])
        
        # Frecuencia de publicación de 10Hz
        self.pub = self.create_publisher(Float32, 'ri_setpoint', 1000)  
        # Período de temporizador para 10Hz
        timer_period = 0.1 
        #Se declara el timer que llamará al callback
        self.timer = self.create_timer(timer_period, self.timer_callback)
        #Se notifica que ha sido creado correctamente
        self.get_logger().info('Talker params node initialized')

    def timer_callback(self):

        time = self.get_clock().now().to_msg().nanosec / 1e9  # Convertir a segundos
        #Se hace la lectura del parámetro type
        ri_type = self.get_parameter('ri_type').get_parameter_value().integer_value
        #Se generan condiciones para las 5 señales y lectura de sus params 
        if ri_type == 0:
            #Señal de seno
            amplitude = self.get_parameter('ri_sine.amplitude').get_parameter_value().double_value
            freq = self.get_parameter('ri_sine.frequency').get_parameter_value().double_value
            offset = self.get_parameter('ri_sine.offset').get_parameter_value().double_value
            phase =  self.get_parameter('ri_sine.phase').get_parameter_value().double_value
            signal_value = amplitude * math.sin(2 * math.pi * time * freq + phase) + offset
        elif ri_type == 1:
            #Señal de seno pulso cuadrado
            amplitude = self.get_parameter('ri_square.amplitude').get_parameter_value().double_value
            freq = self.get_parameter('ri_square.frequency').get_parameter_value().double_value
            offset = self.get_parameter('ri_square.offset').get_parameter_value().double_value
            phase =  self.get_parameter('ri_square.phase').get_parameter_value().double_value
            signal_value = amplitude * signal.square(2 * math.pi * time * freq + phase) + offset
        elif ri_type == 2:
            #Señal de seno mas coseno
            amplitude = self.get_parameter('ri_sawtooth.amplitude').get_parameter_value().double_value
            freq = self.get_parameter('ri_sawtooth.frequency').get_parameter_value().double_value
            offset = self.get_parameter('ri_sawtooth.offset').get_parameter_value().double_value
            phase =  self.get_parameter('ri_sawtooth.phase').get_parameter_value().double_value
            signal_value = amplitude * signal.sawtooth(2 * math.pi * time * freq + phase) + offset
        elif ri_type == 3:
            #Señal de seno mas coseno
            amplitude = self.get_parameter('ri_constant.amplitude').get_parameter_value().double_value
            signal_value = amplitude
        else:
            #Señal de sen (en cualquier otro caso)
            amplitude = self.get_parameter('ri_sine.amplitude').get_parameter_value().double_value
            freq = self.get_parameter('ri_sine.frequency').get_parameter_value().double_value
            offset = self.get_parameter('ri_sine.offset').get_parameter_value().double_value
            phase =  self.get_parameter('ri_sine.phase').get_parameter_value().double_value
            signal_value = amplitude * math.sin(2 * math.pi * time * freq + phase) + offset

        # Publicar el valor de la señal
        msg = Float32()
        msg.data = signal_value
        self.pub.publish(msg)

#La función que será llamada según nuestro setup
def main(args=None):
    #Se inicializa el entorno de ros
    rclpy.init(args=args)
    #Se crea una instancia de la clase creada previamente.
    m_t_p = My_Talker_Params()
    #Creación del bucle de eventos
    rclpy.spin(m_t_p)
    #Se liberan recursos
    m_t_p.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
