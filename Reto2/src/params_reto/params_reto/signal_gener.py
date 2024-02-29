import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32
from mensaje_personal.msg import Num  
import math


#Se crea el nodo My_Talker_Params tomando objeto de Node.
class My_Talker_Params(Node):
    #Se inicializa el nodo
    def __init__(self):
        #Se crear el nodo que será encargado de publicar la señal
        super().__init__('ri_signal_generator')
        #Se declara la lista de parámetros a utilizar
        self.declare_parameters(
            namespace='',
            parameters=[
                ('ri_type', 1),
                ('ri_amplitude', 1.5),
                ('ri_freq', 2.0),
                ('ri_offset', 1.0),
                ('ri_phase_shift', 1.0)
            ])
        # Frecuencia de publicación de 1kHz
        self.pub = self.create_publisher(Float32, 'ri_signal', 1000)  
        # Período de temporizador para 1kHz
        timer_period = 0.001 
        #Se declara el timer que llamará al callback
        self.timer = self.create_timer(timer_period, self.timer_callback)
        #Se crea el publicador que mandará mensaje personalizado
        self.pub_info = self.create_publisher(Num, 'ri_signal_params', 1000)  # Frecuencia de publicación de 1kHz
        #Se notifica que ha sido creado correctamente
        self.get_logger().info('Talker params node initialized')

    def timer_callback(self):
        #Se hace la lectura de los parámetros a utilizar
        ri_type = self.get_parameter('ri_type').get_parameter_value().integer_value
        ri_amplitude = self.get_parameter('ri_amplitude').get_parameter_value().double_value
        time = self.get_clock().now().to_msg().nanosec / 1e9  # Convertir a segundos
        ri_freq = self.get_parameter('ri_freq').get_parameter_value().double_value
        ri_offset = self.get_parameter('ri_offset').get_parameter_value().double_value
        ri_phase_shift =  self.get_parameter('ri_phase_shift').get_parameter_value().double_value
        #Se generan condiciones para las 5 señales
        if ri_type == 1:
            #Señal de seno
            signal_value = math.sin(2 * math.pi * time)
        elif ri_type == 2:
            #Señal de seno pulso cuadrado
            signal_value = 1.0 if (math.sin(2 * math.pi * time ) > 0) else 0.0
        elif ri_type == 3:
            #Señal de seno mas coseno
            signal_value = math.sin(2 * math.pi * time)+math.cos(time)
        elif ri_type == 4:
            #Señal de coseno
            signal_value = math.cos(2 * math.pi * time )
        elif ri_type == 5:
            #Señal de tangente
            signal_value = math.tan(time)
        else:
            #Señal de sen (en cualquier otro caso)
            signal_value = math.sin(2 * math.pi * time)

        # Publicar el valor de la señal
        msg = Float32()
        msg.data = signal_value
        self.pub.publish(msg)
        #Publicar los parámetros obtenidos con ayuda de msg personalizado.
        msgDato = Num()
        msgDato.type = ri_type
        msgDato.amplitude = ri_amplitude
        msgDato.freq = ri_freq
        msgDato.offset = ri_offset
        msgDato.phase_shift = ri_phase_shift
        msgDato.time = time
        self.pub_info.publish(msgDato)
        # self.get_logger().info('Publishing: "%f" and "%f"' % (msgDato.amplitude, msgDato.offset)) 
        # amp = Float32()
        # amp.data = ri_amplitude
        # self.pub_datos.publish([amp,amp])

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
