import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32
import math

class My_Talker_Params(Node):
    def __init__(self):
        super().__init__('ri_signal_generator')
        self.declare_parameter('ri_type', 1)
        self.declare_parameter('ri_amplitude', 1)
        self.declare_parameter('ri_freq', 1)
        self.declare_parameter('ri_offset', 1)
        self.pub = self.create_publisher(Float32, 'ri_signal', 1000)  # Frecuencia de publicación de 1kHz
        timer_period = 0.001  # Período de temporizador para 1kHz
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.get_logger().info('Talker params node initialized')

    def timer_callback(self):
        ri_type = self.get_parameter('ri_type').get_parameter_value().integer_value
        time = self.get_clock().now().to_msg().nanosec / 1e9  # Convertir a segundos
        if ri_type == 1:
            # Generar una señal senoidal de 2 Hz y amplitud de 0.5
            signal_value = 0.5 * math.sin(2 * math.pi * 2 * time)
        elif ri_type == 2:
            # Generar un pulso cuadrado
            signal_value = 1.0 if (self.get_clock().now().to_msg().sec % 2) < 1 else 0.0
        elif ri_type == 3:
            # Generar una señal de diente de sierra
            signal_value = (time % 10) / 10.0
        elif ri_type == 4:
            # Generar una señal coseno de 2 Hz y amplitud de 0.5
            signal_value = 0.5 * math.cos(2 * math.pi * 2 * time)
        elif ri_type == 5:
            # Generar una señal tangente
            signal_value = math.tan(time)
        else:
            # Si el tipo no es reconocido, generar una señal senoidal de 2 Hz y amplitud de 0.5 por defecto
            signal_value = 0.5 * math.sin(2 * math.pi * 2 * time)

        # Publicar el valor de la señal
        msg = Float32()
        msg.data = signal_value
        self.pub.publish(msg)

def main(args=None):
    rclpy.init(args=args)
    m_t_p = My_Talker_Params()
    rclpy.spin(m_t_p)
    m_t_p.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
