#importaciones necesarias
import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32
import math

#Se crea el nodo My_publisher tomando objeto de Node.
class My_Publisher(Node):

    #Se inicializa el nodo
    def __init__(self):
        #Se crear el nodo que será encargado de publicar la señal
        super().__init__('wave_publisher')
        #Se crean los tópicos de la senial y del tiempo para la senoidal.
        self.publisher_signal = self.create_publisher(Float32, 'signal', 10)
        self.publisher_time = self.create_publisher(Float32, 'time', 10)
        self.timer_period = 0.1  # Frecuencia de 10 Hz
        #Se le llamará al timer_callback cada que se cumpla el periodo
        self.timer = self.create_timer(self.timer_period, self.timer_callback)
        #Es un mensaje de inicio para mostrar que la creación ha sido exitosa
        self.get_logger().info('Wave Publisher node successfully initialized!!!')
        #Se inicializa el tiempos
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

#La función que será llamada según nuestro setup
def main(args=None):
    #Se inicializa el entorno de ros
    rclpy.init(args=args)
    #Se crear una instancia de la clase creada previamente
    wave_publisher = My_Publisher()
    #Creación de bucle de eventos ros2
    rclpy.spin(wave_publisher)
    #Se liberan recursos como buena práctica
    wave_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
