#importaciones necesarias
import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32

class SignalProcessor(Node):

    def __init__(self):
        super().__init__('process')
        self.subscription_signal = self.create_subscription(
            Float32,
            'signal',
            self.signal_callback,
            10)
        self.subscription_time = self.create_subscription(
            Float32,
            'time',
            self.time_callback,
            10)
        self.publisher_proc_signal = self.create_publisher(Float32, 'proc_signal', 10)  # Crear publicador para proc_signal
        self.alpha = 10.0  # Valor inicial del offset
        self.phase_shift = 20.0  # Valor inicial del cambio de fase
        self.get_logger().info('Signal Processor node successfully initialized!!!')

    def signal_callback(self, msg):
        # Procesar la señal recibida
        processed_signal = msg.data + self.alpha  # Aplicar offset
        processed_signal /= 2  # Reducir la amplitud a la mitad
        processed_signal *= self.phase_shift  # Aplicar cambio de fase
        # Publicar la señal procesada en el nuevo tópico proc_signal
        msg_proc_signal = Float32()
        msg_proc_signal.data = processed_signal
        self.publisher_proc_signal.publish(msg_proc_signal)
        # Imprimir la señal procesada en la terminal
        self.get_logger().info('Processed Signal: %f' % processed_signal)

    def time_callback(self, msg):
        # No es necesario hacer nada con el tiempo en este nodo
        pass

def main(args=None):
    rclpy.init(args=args)
    signal_processor = SignalProcessor()
    rclpy.spin(signal_processor)
    signal_processor.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
