import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32
import math

class My_Publisher(Node):

    def __init__(self):
        super().__init__('wave_publisher')
        self.publisher_signal = self.create_publisher(Float32, 'signal', 10)
        self.publisher_time = self.create_publisher(Float32, 'time', 10)
        self.timer_period = 0.1  # Frecuencia de 10 Hz
        self.timer = self.create_timer(self.timer_period, self.timer_callback)
        self.get_logger().info('Wave Publisher node successfully initialized!!!')
        self.time = 0.0

    def timer_callback(self):
        # Calcular el valor de la onda sinusoidal
        wave_value = math.sin(self.time)
        
        # Publicar el valor de la onda sinusoidal en el topic 'signal'
        msg_signal = Float32()
        msg_signal.data = wave_value
        self.publisher_signal.publish(msg_signal)

        # Publicar el tiempo actual en el topic 'time'
        msg_time = Float32()
        msg_time.data = self.time
        self.publisher_time.publish(msg_time)

        # Incrementar el tiempo para el próximo ciclo
        self.time += self.timer_period


def main(args=None):
    rclpy.init(args=args)
    wave_publisher = My_Publisher()
    rclpy.spin(wave_publisher)
    wave_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
