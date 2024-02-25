import rclpy
from rclpy.node import Node
from std_msgs.msg import String, Int32

class My_Talker_Params(Node):
    def __init__(self):
        super().__init__('ri_signal_generator')
        self.declare_parameter('ri_type', 1)
        self.pub = self.create_publisher(Int32, 'ri_signal', 10)
        timer_period = 1.0
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.get_logger().info('Talker params node initialized')
        self.msg = Int32()

    def timer_callback(self):
        ri_type = self.get_parameter('ri_type').get_parameter_value().integer_value
        self.msg.data = ri_type
        self.pub.publish(self.msg)

def main(args = None):
    rclpy.init(args=args)
    m_t_p = My_Talker_Params()
    rclpy.spin(m_t_p)
    m_t_p.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()