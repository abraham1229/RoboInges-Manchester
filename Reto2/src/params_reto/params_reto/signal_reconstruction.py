import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32
from mensaje_personal.msg import Num  


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

        self.amplitude = 0.0
        self.offset = 0.0

    def params_callback(self, msg):
        self.amplitude = msg.amplitude
        self.offset = msg.offset

    def signal_callback(self, msg):
        reconstructed_signal = self.amplitude * msg.data + self.offset
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
