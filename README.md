# piMusicBox

# Descripción general

Hoy en día los microcontroladores (μC) suponen más del 50% de los Circuitos
Integrados existentes. Basta analizar un hogar cualquiera para encontrar al menos una
o dos docenas de microcontroladores distribuidos entre los diferentes dispositivos
presentes en el mismo: lavadoras, frigoríficos, hornos, microondas, teléfonos, mandos
inalámbricos, teclados, automóviles, etc. Casi cualquier dispositivo electrónico cuenta
con un μC como elemento esencial para la toma de decisiones o para la supervisión del
sistema.
Un buen ejemplo de su creciente importancia e interés son los juguetes electrónicos
interactivos. Estos juguetes, cada vez más comunes en nuestra vida cotidiana,
contienen, en su gran mayoría, microcontroladores. La integración del μC en la industria
del juguete ha significado, para fabricantes y consumidores, la posibilidad de disfrutar
de juguetes cada vez más divertidos e incluso ha logrado transformar el juguete en una
plataforma educativa de enorme potencial para los niños. Mini-robots, coches,
helicópteros y aviones a control remoto son sólo algunos de los ejemplos de productos
que hacen uso de microcontroladores.
Otro de los ámbitos en el que los microcontroladores han cobrado singular protagonismo
es el musical. En particular, son una pieza importante dentro de los sintetizadores de
música para generar señales de diferentes frecuencias. Estos equipos son capaces de
generar una gran variedad de sonidos y ritmos que en muchos casos superan las
capacidades de los músicos tocando instrumentos tradicionales.
En este proyecto se propone la implementación de un sintetizador de melodías de
bajo coste orientado a su integración en un juguete infantil basado en la lectura de
diferentes tarjetas RFID. Dado que nuestro propósito es docente (enfocado a la
interacción entre HW y SW y a los requisitos de tiempo real) no implementaremos un
sintetizador de gran calidad sino una versión simplificada que nos permitirá conocer las
principales dificultades que conlleva la implementación de estos equipos. En este
documento se proporciona una guía para su diseño e implementación.

El funcionamiento de nuestro juguete es sencillo. El usuario dispondrá de diversas
tarjetas RFID (los alumnos podrán emplear sus correspondientes carnets de alumno
UPM) que podrán ser sucesivamente insertadas en una ranura habilitada en nuestra
caja musical. La inserción de cada tarjeta en dicha ranura será oportunamente detectada
por el sistema leyéndose su correspondiente identificador y dando comienzo a la
reproducción de la melodía asociada a la tarjeta en cuestión. Igualmente, la posterior
extracción de la tarjeta dará por finalizada la reproducción de la melodía en curso.
En el presente proyecto supondremos que un cliente (el Departamento de Ingeniería
Electrónica) nos ha contratado para desarrollar un prototipo del juguete de bajo coste.
Para ello, contaremos con la ventaja de disponer de una Raspberry Pi, un
microcontrolador de referencia y con altas prestaciones. Dado que el propósito de este
laboratorio es eminentemente docente (con especial énfasis en la interacción HW-SW,
así como en los requisitos de tiempo real), el objetivo será implementar un prototipo
funcional completo. No obstante, aunque dicho prototipo estará inspirado en el
funcionamiento anteriormente detallado, a diferencia del modelo facilitado a modo de
ejemplo (ver Ilustración 1), en el que sus creadores hicieron un esfuerzo extra por
acercar el prototipo a lo que podría ser una primera versión del consiguiente producto
haciendo uso de herramientas de diseño e impresión 3D, es preciso hacer notar que el
alumno no está obligado a construir la caja como tal aunque su diseño y montaje sí que
serán considerados como posibles mejoras.
Este enunciado constituye una guía para su diseño e implementación. Adicionalmente,
el alumno dispone de un vídeo demostrativo sobre este proyecto en YouTube: https://youtu.be/BhlKW1HB3Oc 

# Objetivo general

El objetivo del proyecto es mostrar la viabilidad de la idea de diseño básica desarrollando
un prototipo plenamente funcional. El programa que ejecutará el micro se realizará en
lenguaje C. El sistema digital basado en un microcontrolador será la plataforma
ENT2004CF disponible en el laboratorio B-043 (construida en torno a una Raspberry Pi). Para más detalles relacionados con el sistema de desarrollo (utilización, pines de
conexión, elementos disponibles), consulte la publicación [1].
En los apartados siguientes se detallarán las arquitecturas HW y SW, haciendo énfasis
en la descomposición modular del sistema, tarea clave para abordar con éxito el diseño
de cualquier sistema HW o SW medianamente complejo.
El objetivo general se resume en desarrollar un “sistema digital basado en la plataforma
ENT2004CF” que reúna obligatoriamente las siguientes características:

• El sistema deberá mantener informado al usuario en todo momento
haciéndole notar mediante mensajes que se mostrarán en la pantalla del
ordenador, a través de la ventana de terminal del entorno de desarrollo Eclipse
(que actuará como display de visualización), el estado en el que éste se
encuentra (e.g. reproduciendo melodía) y la ocurrencia de los diferentes eventos
de relevancia para el funcionamiento del mismo (e.g. se ha detectado tarjeta).

• La inserción de una tarjeta será motivo suficiente para comenzar la
reproducción de una melodía.

• La posterior retirada o extracción de la tarjeta será motivo suficiente para
detener la reproducción de la melodía.

• El sistema deberá contar con el HW necesario para la detección tanto de la
inserción como de la extracción de la tarjeta, distinguiendo claramente una
acción de otra. Para ello deberá emplearse un optoacoplador de encapsulado
ranurado usado a modo de interruptor óptico o sensor final de carrera que nos
permitirá detectar ambas acciones.

• En caso de que la tarjeta permaneciese insertada por más tiempo del necesario
para completar la reproducción de la melodía, la versión básica del sistema
simplemente comunicará sin más tal situación al usuario a través de la ventana
de terminal siendo necesario volver a insertar la tarjeta para comenzar
nuevamente la reproducción.

• El sistema deberá ser capaz de reproducir al menos una melodía. En este
sentido, la plataforma ENT2004CF, y por extensión la propia Raspberry Pi, será
la encargada de generar una señal cuadrada con la frecuencia de la nota a
reproducir durante un tiempo determinado. Para percibir la melodía (con
fuerte distorsión) bastará con aplicar dicha señal directamente sobre unos
auriculares.

• En la versión final, los retardos debidos a, por ejemplo, escribir por la terminal o
gestionar la detección y lectura de las diferentes tarjetas, no deben afectar a la
correcta reproducción de las melodías (requisitos de concurrencia y tiempo
real).

• Será, igualmente, competencia del sistema SW, generar y procesar las señales
necesarias para gobernar el HW externo.

• Los posibles rebotes originados por el HW de detección de tarjetas se
suprimirán por SW. En particular, la inserción de la tarjeta debe significar una
única lectura de la misma sin que le afecten los posibles rebotes en la señal
que se reciba del HW de detección (la eliminación defectuosa de tales rebotes
se pondrá típicamente de manifiesto en un comportamiento anómalo por parte del sistema que reaccionará como si hubiésemos insertado y extraído
repetidamente la tarjeta).

Adicionalmente, y con carácter opcional, los alumnos podrán mejorar su diseño
incorporando al mismo las siguientes especificaciones:

• El sistema contará con las etapas HW de filtrado y amplificación necesarias
para el adecuado acondicionamiento de las señales generadas para la
reproducción de las melodías.

• El sistema será capaz de identificar al menos dos tarjetas distintas (i.e. con
identificadores diferentes) asociadas a su vez a la reproducción de otras tantas
melodías necesariamente distintas.

• El sistema podrá leer las tarjetas (en adelante también referidas como etiquetas
o tags) haciendo uso del dispositivo Mifare MFRC522 [7], disponible en el
laboratorio, que consiste en un lector de tarjetas RFID (Identificación por Radio
Frecuencia) con comunicación por bus Serial Peripheral Interface o SPI
(también incorpora comunicación vía bus I2C y UART). En este sentido, el
alumno deberá:

o Desde el punto de vista HW, establecer las correspondientes
conexiones físicas con la Raspberry Pi empleando para ello las
entradas y salidas digitales disponibles en los conectores de la placa
TL04 y conforme a la correspondiente Tabla de distribución de pines
(disponible, por ejemplo, en el Tutorial sobre "Iniciación al Manejo de las
Entradas/Salidas del BCM 2835"). A este respecto, se hace notar al
alumno que el lector MFRC522 funciona necesariamente con una tensión
de alimentación de 3,3V por lo que será necesario intercalar un
conversor de niveles bidireccional, también facilitado en el propio
laboratorio, para acomodar dicho valor a los 5V propios de las entradas
y salidas digitales disponibles en la TL04 y viceversa.

o Desde el punto de vista SW, incorporar a su propio sistema una librería
escrita en lenguaje C y facilitada en el propio laboratorio que
implementará la funcionalidad de control básica necesaria para la
configuración e inicialización de la comunicación SPI y de la consiguiente
lectura de los identificadores de las tarjetas.

