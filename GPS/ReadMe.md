SISTEMA DE NAVEGACION AUTONOMA DEL ROVER.

UNAM SPACE
  
  Equipo de camaras y sensores.
  
   Explicacion del primer codigo (Prueba_GPS)
      
      Este codigo es el mas basico que vas an encontrar para el GPS ya que este te da toda la informacion que el mismo GPS llega ah 
      recavar, pero de toda esa informacion solo nos importa una simple linea que nos la dara en el puerto serial de la IDE.
      
   [![GPS-Coordenadapng.png](https://i.postimg.cc/Tw3PBdq9/GPS-Coordenadapng.png)](https://postimg.cc/CZ9YqV2B)
             
   - Esta simple linea nos da mucha informacion como:
      
   [![GPS-Fecha.png](https://i.postimg.cc/s2XXNfJJ/GPS-Fecha.png)](https://postimg.cc/pmwR9H49)- Representa la hora GMT (En el meridiano de GreenWich).
      
   [![GPS-Valor.png](https://i.postimg.cc/mZMrq57K/GPS-Valor.png)](https://postimg.cc/HjYH83Zt) - Es la indicación de que el dato de posición está fijado y es correcto. “V” sería no válido.
      
   [![GPS-Longitud.png](https://i.postimg.cc/gJL0GMQX/GPS-Longitud.png)](https://postimg.cc/bD8PTRzp) - Representa la longitud (8º 24.5210´)
      
   [![GPS-Norte.png](https://i.postimg.cc/wTpBdQVM/GPS-Norte.png)](https://postimg.cc/jCMTHNBY) - Representa el Norte
      
   [![GPS-Latitud.png](https://i.postimg.cc/VvykvqP7/GPS-Latitud.png)](https://postimg.cc/njkJwQz7) - Representa la latitud (8º 24.5210´)
      
   [![GPS-Oeste.png](https://i.postimg.cc/Ghxm3T7Q/GPS-Oeste.png)](https://postimg.cc/w73p0Mdy) - Representa el Oeste
      
   [![GPS-Velocidad.png](https://i.postimg.cc/0jp2wz89/GPS-Velocidad.png)](https://postimg.cc/p5LHNXhS) - Representa la velocidad en nudos
            
   [![GPS-Hora.png](https://i.postimg.cc/nLPzb8Rf/GPS-Hora.png)](https://postimg.cc/B82sHzfm) - Representa la fecha
      
      
  Explicacion del Segundo codigo (simple_test)
      
      Este codigo es un simplificado del codigo anterior ya que te da toda la informacion que el mismo GPS llega ah recavar, pero de 
      toda esa informacion solo nos imprimira en el puerto serial de la IDE la longuitud y la latitud.
      
   [![Simple-Coordenadas.png](https://i.postimg.cc/3JpQ3k1w/Simple-Coordenadas.png)](https://postimg.cc/GHc5QhZ0)
      
      Cabe recalcar que este codigo viene en la librerias del GPS (Tiny GPS) y viene justamente con el mismo nombre que con el que se 
      encuentra en el repositorio.
      
      Una cosa mas este codigo para que funcione si es que lo sacas de las liberias tiene que un fallo que es el siguiente:
      
  [![SS-DE-GIT.png](https://i.postimg.cc/qq9fq65M/SS-DE-GIT.png)](https://postimg.cc/GTJgStRZ) 
      
      En la linea 16 en ss.begin en lugar de 4800 es 9600 para que te aparezca en lo que se tiene que imprimir en el puerto serial de
      la IDE.
      
      
      
      
