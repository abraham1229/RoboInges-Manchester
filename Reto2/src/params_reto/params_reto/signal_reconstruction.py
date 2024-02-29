import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32
from mensaje_personal.msg import Num  
import math


#Se crea el nodo MySignalReconstructor tomando objeto de Node.
class MySignalReconstructor(Node):

    #Se inicializa el nodo
    def __init__(self):
        #Se crear el nodo que será encargado de publicar la señal
        super().__init__('signal_reconstructor')
        #Se hacen las suscripciones pertinentes
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
        #Se crea el publicador para mandar señal reconstruida
        self.publisher = self.create_publisher(Float32, 'ri_signal_reconstructed', 1000)

        self.get_logger().info('Constructor params node initialized')

        #Se declaran las variables globalmente para poderlas usar en diferentes callbacks
        self.type = 0
        self.amplitude = 0.0
        self.freq = 0.0
        self.offset = 0.0
        self.phase_shift = 0.0
        self.time = 0.0


    def params_callback(self, msg):
        #Se asignan los datos obtenidos de mesaje personalizado
        self.type = msg.type
        self.amplitude = msg.amplitude
        self.freq = msg.freq
        self.offset = msg.offset
        self.phase_shift = msg.phase_shift
        self.time = msg.time

    def signal_callback(self, msg):
        reconstructed_signal = 0.0
        #Se hacen condiciones para los tipos de señales y se hacen modificaciones
        #pertinentes de la mismas
        if self.type == 1:
            #Seno
            reconstructed_signal = self.amplitude * math.sin(2 * math.pi * self.time * self.freq + self.phase_shift) + self.offset
        elif self.type == 2:
            # Generar un pulso cuadrado con frecuencia, offset, amplitud y desplazamiento de fase variables
            # Calcula la señal del pulso cuadrado
            signal_value = 1.0 if (math.sin(2 * math.pi * self.freq * self.time + self.phase_shift) > 0) else 0.0
            # Ajusta la amplitud y el offset
            reconstructed_signal = signal_value * self.amplitude + self.offset

        elif self.type == 3:
            #Seno mas coseno
            reconstructed_signal = self.amplitude * math.sin(2 * math.pi * self.time * self.freq + self.phase_shift) + self.offset + math.cos(self.time)
        elif self.type == 4:
            # Coseno
            reconstructed_signal = self.amplitude * math.cos(2 * math.pi * self.time * self.freq + self.phase_shift) + self.offset
        elif self.type == 5:
            # Tangente
            reconstructed_signal = self.amplitude * math.tan(2 * math.pi * self.time * self.freq + self.phase_shift) + self.offset
        else:
            # Seno en cualquier otro caso
            reconstructed_signal = self.amplitude * math.sin(2 * math.pi * self.time * self.freq + self.phase_shift) + self.offset
        
        #Se manda la señal obtenida al topico
        reconstructed_msg = Float32()
        reconstructed_msg.data = reconstructed_signal
        self.publisher.publish(reconstructed_msg)


#La función que será llamada según nuestro setup
def main(args=None):
    #Se inicializa el entorno de ros
    rclpy.init(args=args)
    #Se crea una instancia de la clase creada previamente.
    signal_reconstructor = MySignalReconstructor()
    #Creación del bucle de eventos
    rclpy.spin(signal_reconstructor)
    #Se liberan recursos
    signal_reconstructor.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
