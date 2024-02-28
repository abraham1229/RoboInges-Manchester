import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32
from mensaje_personal.msg import Num  
import math

class My_Talker_Params(Node):
    def __init__(self):
        super().__init__('ri_signal_generator')
        self.declare_parameters(
            namespace='',
            parameters=[
                ('ri_type', 1),
                ('ri_amplitude', 1.5),
                ('ri_freq', 2.0),
                ('ri_offset', 1.0),
                ('ri_phase_shift', 1.0)
            ])
        self.pub = self.create_publisher(Float32, 'ri_signal', 1000)  # Frecuencia de publicación de 1kHz
        timer_period = 0.001  # Período de temporizador para 1kHz
        self.timer = self.create_timer(timer_period, self.timer_callback)

        self.pub_info = self.create_publisher(Num, 'ri_signal_params', 1000)  # Frecuencia de publicación de 1kHz

        self.get_logger().info('Talker params node initialized')

    def timer_callback(self):
        ri_type = self.get_parameter('ri_type').get_parameter_value().integer_value
        ri_amplitude = self.get_parameter('ri_amplitude').get_parameter_value().double_value
        time = self.get_clock().now().to_msg().nanosec / 1e9  # Convertir a segundos
        ri_freq = self.get_parameter('ri_freq').get_parameter_value().double_value
        ri_offset = self.get_parameter('ri_offset').get_parameter_value().double_value
        ri_phase_shift =  self.get_parameter('ri_phase_shift').get_parameter_value().double_value
        if ri_type == 1:
            # Generar una señal senoidal con frecuencia y desplazamiento de fase variables
            signal_value = math.sin(2 * math.pi * ri_freq * time + ri_phase_shift)
        elif ri_type == 2:
            # Generar un pulso cuadrado con frecuencia y desplazamiento de fase variables
            signal_value = 1.0 if (math.sin(2 * math.pi * ri_freq * time + ri_phase_shift) > 0) else 0.0
        elif ri_type == 3:
            # Generar una señal de diente de sierra con frecuencia y desplazamiento de fase variables
            signal_value = (time * ri_freq + ri_phase_shift) % (2)
        elif ri_type == 4:
            # Generar una señal coseno con frecuencia y desplazamiento de fase variables
            signal_value = math.cos(2 * math.pi * ri_freq * time + ri_phase_shift)
        elif ri_type == 5:
            # Generar una señal tangente con frecuencia y desplazamiento de fase variables
            signal_value = math.tan(time + ri_phase_shift)
        else:
            # Si el tipo no es reconocido, generar una señal senoidal de 2 Hz y amplitud de 0.5 por defecto
            signal_value = math.sin(2 * math.pi * ri_freq * time + ri_phase_shift)

        # Publicar el valor de la señal
        msg = Float32()
        msg.data = signal_value
        self.pub.publish(msg)
        msgDato = Num()
        msgDato.amplitude = ri_amplitude
        msgDato.offset = ri_offset
        self.pub_info.publish(msgDato)
        # self.get_logger().info('Publishing: "%f" and "%f"' % (msgDato.amplitude, msgDato.offset)) 
        # amp = Float32()
        # amp.data = ri_amplitude
        # self.pub_datos.publish([amp,amp])


def main(args=None):
    rclpy.init(args=args)
    m_t_p = My_Talker_Params()
    rclpy.spin(m_t_p)
    m_t_p.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
