#importaciones necesarias
from setuptools import find_packages, setup

#Se le pone el nombre de paquete para concatenar.
package_name = 'courseworks'

#Se agrega el setup para poder trabajar con los archivos.
setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    #Archivos de datos
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='abraham',
    maintainer_email='abrahamortizcastro1229@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    #Se agregan archivos necesarios.
    entry_points={
        'console_scripts': [
            'signal_generator = courseworks.signal_generator:main',
            'signal_process = courseworks.signal_process:main'
        ],
    },
)
