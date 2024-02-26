import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32
import math

class My_Talker_Params(Node):
    def __init__(self):
        super().__init__('ri_signal_generator')
        self.declare_parameter('ri_type', 1)
        self.pub = self.create_publisher(Float32, 'ri_signal', 10)
        timer_period = 0.02
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.get_logger().info('Talker params node initialized')

    def timer_callback(self):
        ri_type = self.get_parameter('ri_type').get_parameter_value().integer_value
        signal_value = 0.0
        if ri_type == 1:
            # Generar una señal senoidal con frecuencia de 1 Hz y amplitud de 1.0
            signal_value = math.sin(self.get_clock().now().to_msg().sec)
        elif ri_type == 2:
            # Generar un pulso cuadrado
            signal_value = 1.0 if (self.get_clock().now().to_msg().sec % 2) < 1 else 0.0
        elif ri_type == 3:
            # Generar una señal de diente de sierra
            signal_value = (self.get_clock().now().to_msg().sec % 10) / 10.0
        elif ri_type == 4:
            # Generar una señal coseno con frecuencia de 1 Hz y amplitud de 1.0
            signal_value = math.cos(self.get_clock().now().to_msg().sec)
        elif ri_type == 5:
            # Generar una señal tangente
            signal_value = math.tan(self.get_clock().now().to_msg().sec)
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
