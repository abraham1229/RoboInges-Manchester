import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32
from mensaje_personal.msg import Num  
import math


class MySignalReconstructor(Node):

    def __init__(self):
        super().__init__('signal_reconstructor')
        self.subscription_signal = self.create_subscription(
            Float32,
            'ri_signal',
            self.signal_callback,
            1000)
        self.subscription_params = self.create_subscription(
            Num,
            'ri_signal_params',
            self.params_callback,
            1000)
        self.publisher = self.create_publisher(Float32, 'ri_signal_reconstructed', 1000)

        self.get_logger().info('Constructor params node initialized')

        self.type = 0
        self.amplitude = 0.0
        self.freq = 0.0
        self.offset = 0.0
        self.phase_shift = 0.0
        self.time = 0.0


    def params_callback(self, msg):
        self.type = msg.type
        self.amplitude = msg.amplitude
        self.freq = msg.freq
        self.offset = msg.offset
        self.phase_shift = msg.phase_shift
        self.time = msg.time

    def signal_callback(self, msg):
        reconstructed_signal = 0.0
        if self.type == 1:
            reconstructed_signal = self.amplitude * math.sin(2 * math.pi * self.time * self.freq + self.phase_shift) + self.offset
        elif self.type == 2:
            reconstructed_signal = 1.0 if (math.sin(2 * math.pi * self.time ) > 0) else 0.0
            reconstructed_signal = reconstructed_signal *self.amplitude +self.offset
        elif self.type == 2:
            reconstructed_signal = self.amplitude * math.sin(2 * math.pi * self.time * self.freq + self.phase_shift) + self.offset + math.cos(self.time)
        elif self.type == 4:
            # Generar una señal coseno con frecuencia y desplazamiento de fase variables
            reconstructed_signal = self.amplitude * math.cos(2 * math.pi * self.time * self.freq + self.phase_shift) + self.offset
        elif self.type == 5:
            # Generar una señal tangente con frecuencia y desplazamiento de fase variables
            reconstructed_signal = self.amplitude * math.tan(2 * math.pi * self.time * self.freq + self.phase_shift) + self.offset
        else:
            # Si el tipo no es reconocido, generar una señal senoidal de 2 Hz y amplitud de 0.5 por defecto
            
            reconstructed_signal = self.amplitude * math.sin(2 * math.pi * self.time * self.freq + self.phase_shift) + self.offset
        reconstructed_msg = Float32()
        reconstructed_msg.data = reconstructed_signal
        self.publisher.publish(reconstructed_msg)


def main(args=None):
    rclpy.init(args=args)
    signal_reconstructor = MySignalReconstructor()
    rclpy.spin(signal_reconstructor)
    signal_reconstructor.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
