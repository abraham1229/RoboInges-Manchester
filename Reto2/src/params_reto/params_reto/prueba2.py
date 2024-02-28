import rclpy
from rclpy.node import Node

from mensaje_personal.msg import Num                        # CHANGE


class MinimalSubscriber(Node):

    def __init__(self):
        super().__init__('minimal_subscriber')
        self.subscription = self.create_subscription(
            Num,                                               # CHANGE
            'ri_signal_params',
            self.listener_callback,
            1000)
        self.subscription

    def listener_callback(self, msg):
        self.get_logger().info('Reading: "%d" and "%d"' % (msg.num, msg.num2)) 


def main(args=None):
    rclpy.init(args=args)

    minimal_subscriber = MinimalSubscriber()

    rclpy.spin(minimal_subscriber)

    minimal_subscriber.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()