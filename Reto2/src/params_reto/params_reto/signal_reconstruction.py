#importaciones necesarias
import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32
from mensaje_personal.msg import Num 

#Se crea el nodo SignalProcessor tomando objeto de Node.
class SignalProcessor(Node):

    #Se inicializa el nodo
    def __init__(self):
        #Se crear el nodo que será encargado del proceso de la senial
        super().__init__('reconstruction')
        #Se hace la subscripcion a el topico signal
        self.subscription_signal = self.create_subscription(
            Float32,
            'ri_signal_params',
            self.signal_callback,
            10)
        # Crear publicador para proc_signal
        self.publisher_proc_signal = self.create_publisher(Float32, 'ri_signal_reconstructed', 10)  
        self.alpha = 10.0  # Valor inicial del offset
        self.phase_shift = 20.0  # Valor inicial del cambio de fase
        #Se manda mensaje de creación exitosa
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

#La función que será llamada según nuestro setup
def main(args=None):
    #Se inicializa el entorno de ros
    rclpy.init(args=args)
    #Se crear una instancia de la clase creada previamente
    signal_processor = SignalProcessor()
    #Creación de bucle de eventos ros2
    rclpy.spin(signal_processor)
    #Se liberan recursos como buena práctica
    signal_processor.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
