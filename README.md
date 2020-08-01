# **Arduino DMX-512 Tester and Controller**

## **Firmware - LCD 20x4**

[![version](https://img.shields.io/badge/version-1.3_release-brightgreen.svg)](CHANGELOG.md)
[![license](https://img.shields.io/badge/licence-GNU_GPL_v3.0-blue)](https://github.com/Arduino-DMX-512-Tester-and-Controller/Arduino-DMX-512-Tester-and-Controller-LCD-20x4-Firmware/blob/master/LICENCE.md)

![GitHub issues](https://img.shields.io/github/issues/Arduino-DMX-512-Tester-and-Controller/Arduino-DMX-512-Tester-and-Controller-LCD-20x4-Firmware)
![GitHub forks](https://img.shields.io/github/forks/Arduino-DMX-512-Tester-and-Controller/Arduino-DMX-512-Tester-and-Controller-LCD-20x4-Firmware)
![GitHub stars](https://img.shields.io/github/stars/Arduino-DMX-512-Tester-and-Controller/Arduino-DMX-512-Tester-and-Controller-LCD-20x4-Firmware)

***

Herramienta Open Hardware, para pruebas y control de iluminación de espectáculos a través del protocolo [DMX-512](http://es.wikipedia.org/wiki/Digital_Multiplex), ideal para hacer pruebas rápidas en instalaciones fijas o temporales de iluminación, sin la necesidad de instalar consolas de iluminación, interfaces o computadoras en ambientes al intemperie, hostiles o de difícil acceso.

***

### **Basado en:**

- [Arduino Mega 2560 Rev-3](http://www.arduino.cc/en/Main/ArduinoBoardMega2560)
- [Librería Arduino cuatro universos DMX v0.3 - Deskontrol](http://www.deskontrol.net/blog/libreria-arduino-cuatro-universos-dmx/)
- [Libreria LCD v1.2.1 - Francisco Malpartida](https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home)
- [Simulación en Proteus de Arduino - Microcontrolandos](http://microcontrolandos.blogspot.mx/2012/12/arduino-componentes-para-o-proteus.html)
- [Encoder](http://www.robodosis.net/2013/01/encoder-rotativo-mecanico-con-pic16f877a_2.html)

***

- Navegación desde cursor de fácil acceso e intuitivo
- Inserción rápida de valores desde el teclado numérico
- Inserción de valores desde potenciómetro análogo
- Función para ubicar luminaria desde el canal seleccionado
- Acceso rápido a opciones de memoria
- Función de Black Out desde el menú Memory Options
- 4 modos de control DMX:
    - Unitary
    - Matrix
    - Multiply
    - Chaser
    - Config
- Control de iluminación de LCD back light desde el menu Config
- Control de contraste de LCD desde desde el menu Config
- Acceso rápido desde el teclado al LCD back light
- Compilado en [Arduino IDE v1.0.6](http://www.arduino.cc/en/Main/OldSoftwareReleases)
- Librería Arduino cuatro universos DMX v0.3 - [Deskontrol.net](http://www.deskontrol.net/blog/libreria-arduino-cuatro-universos-dmx/)
- Libreria LCD v1.2.1 - [Francisco Malpartida](https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home)

***

- Instalación de librerías DMX:
	- Instalar Arduino IDE v1.0.6 (carpeta .../Software/) (Windows 10 64 bits, ok!)
	- Instalar la librería del encoder:
		- Menú Sketch, Importar librería, Add Library
		- Seleccionar el archivo Encoder.zip (carpeta .../Firmware/Documentacion/Librerias/)
		- Abrir
		- Mensaje: Library added to you libraries
	- Instalar la librería del LCD:
		- Menú Sketch, Importar librería, Add Library
		- Seleccionar el archivo LiquidCrystal_V1.2.1.zip (carpeta .../Firmware/Documentacion/Librerias/)
		- Abrir
		- Mensaje: Library added to you libraries
	- Instalar la librería del DMX:
		- Copiar la carpeta DMX desde .../Firmware/Documentacion/Librerias/DMX/Dmx/
		- Pegarla en la carpeta de .../Arduino/libraries/ el los archivos de programa (para el caso de Windows 10 64 bits, C:\Program Files (x86)\Arduino\libraries)
		- Reiniciar Arduino IDE
		- Revisar el menú Sketch, Importar librería..., Dmx
- Cargando el Firmware:
	- Seleccionar el firmware que vamos a cargar
	- Lo abrimos desde Arduino IDE
	- Menú Herramientas, Tarjeta, Arduino Mega 2560 or Mega ADK
	- Conectar el Arduino Mega al PC
	- Verificar que Windows lo dé de alta correctamente:
		- Panel de control\Sistema y seguridad\Sistema
		- Administrador de dispositivos
		- Puertos (COM y LPT)
		- Arduino Mega 2560 (COMx)
	- En Arduino IDE seleccionamos nuestro Arduino Mega:
		- Menú Herramientas, Puerto Serial, COMx
	- Clic en el icono Cargar...
	- Salen estos errores:
		- avrdude: stk500v2_recv(): checksum error
		- avrdude: stk500v2_recv(): checksum error
		- avrdude: stk500v2_recv(): checksum error
		- avrdude: stk500v2_recv(): checksum error
		- avrdude: stk500v2_recv(): checksum error
		- avrdude: stk500v2_recv(): checksum error
		- avrdude: verification error, first mismatch at byte 0x0b60 0x50 != 0xd7
		- avrdude: verification error; content mismatch
    
***

### ![**Changelog**](CHANGELOG.md)

- **CORREGIR,** en control matrix cuando se selecciona un canal de la esquina el cursor parpadeando queda fuera de lugar
- **AGREGADO,** Control de iluminación para teclado
- **AGREGADO,** a EEPROM la posición 4092 para guardar key light
- **AGREGADO,** la variable global int EEPROM_Limit para controlar el límite de escritura de eeprom de universos
- **AGREGADO,** EEPROM_Limit a todas las funciones de memoria EEPROM
- **AGREGADO,** el control * en el teclado controla el back light y el key light 
- **AGREGADO,** variable global Light_On_Off para control desde tecla * de la iluminacion de teclado y back
- **AGREGADO,** al about un dimmer en key y back durante el efecto binario
- **AGREGADO,** a la tecla de light * un dimmer de on y off para key y back
- **CORREGIDO,** en Back_Light_En, byte Back_Light_Value = EEPROM.read(513); el valor esta fuera de rango
- **CORREGIDO,** unused variable 'EEPROM_Add'
- **CORREGIDO,** en about "open hardware!" por "Open Source License:"

***

### ![**Hardware**](https://github.com/Arduino-DMX-512-Tester-and-Controller/Arduino-DMX-512-Tester-and-Controller-LCD-20x4-Hardware)

- v0.3 a v0.4

***

### **Entrada de Usuario**

- Al arranque presenta las opciones de Initial Memory, para establecer los valores iniciales de la memoria RAM
- El símbolo ">" indica el lugar donde se está posicionado en el menú
- El símbolo “+” y el cursor parpadeante, indica que se espera la entrada numérica del usuario
- La navegación entre los menús, se hace a partir de las teclas del cursor arriba, abajo, derecha, izquierda y centro que aplica como "enter"
- Cuando se da "enter" en un menú que requiere entrada del usuario aparece "+___" y el cursor parpadeante indicando la entrada del usuario, para este caso se utiliza el teclado numérico, si el numero escrito es menor de 3 dígitos presionar "#" que funciona como un "enter" del teclado numérico
- Si se trata de una entrada de usuario en donde se indica el valor de un canal DMX, se puede presionar (después de dar “enter”) la tecla "A" que escribe directamente "255" (el valor máximo de un canal) o la tecla "B" que escribe directamente "000" (el valor mínimo de un canal)
- La tecla "C" funciona como un medio para ubicar una luminaria o un canal en específico, solo basta con seleccionar un canal, posicionarse en el valor, dar "enter" y presionar "C", el valor del canal secuenciara entre "000" y "255", para detenerlo volver a presionar nuevamente "C"
- Las tecla "*" enciende o apaga el backlight
- Las tecla "D" activa solo para los valores el potenciometro análogo, con el se puede ingresar el valor al girarlo
- La opción "Ctrl" regresa al menú de Control Options

![Teclado](https://raw.githubusercontent.com/Arduino-DMX-512-Tester-and-Controller/Arduino-DMX-512-Tester-and-Controller-LCD-20x4-Firmware/master/Documentacion/Teclado/Teclado.JPG)

***

### **Initial Memory:**

Establece los valores iniciales de la memoria RAM, leídos desde la EEPROM:

- Empty (dejar la EEPROM intacta sin modificar, todos los canales estan en "000")
- Load (cargar los valores guardados en la EEPROM del universo DMX)
- Clear (borrar los valores guardados en la EEPROM y dejar los canales en "000")

![Initial Memory](https://raw.githubusercontent.com/Arduino-DMX-512-Tester-and-Controller/Arduino-DMX-512-Tester-and-Controller-LCD-20x4-Firmware/master/media/Initial%20Memory.JPG)

***

### **Control Options**

El usuario selecciona el método de control de los distintos canales DMX

- Memory   - acceso a las opciones de memoria
- Unitary  - acceso rápido a un canal en específico
- Matrix   - visualizar una matriz de 3 x 5 con los valores actuales de los diferentes canales
- Chaser   - hacer una secuencia entre canales específicos
- Multiply - asignar un valor a un número de canales específico, con un salto numérico especifico
- Config   - accede a la configuración del sistema

***

### **Unitary Control**

Permite el acceso rápido a un canal en específico

- Channel - acceso al canal
- Value   - acceso al valor del canal
- Ctrl    - acceso al menu Control Options
- Memory  - acceso al menú de Memory Options

![Unitary Control](https://github.com/Arduino-DMX-512-Tester-and-Controller/Arduino-DMX-512-Tester-and-Controller-LCD-20x4-Firmware/blob/master/media/Control%20Unitary.JPG)

***

### **Matrix Control**

Permite visualizar una matriz de 3 x 5 con los valores actuales de los diferentes canales DMX

- c---    - muestra el numero del canal seleccionado desde los cursores
- Mem     - acceso a Memory Options
- Ctrl    - acceso a Control Options
- 001-015 - acceso al numero de canales a mostrar en la matriz de 3 x 5, el primer numero representa el primer canal y el segundo el ultimo canal

![Matrix](https://raw.githubusercontent.com/Arduino-DMX-512-Tester-and-Controller/Arduino-DMX-512-Tester-and-Controller-LCD-20x4-Firmware/master/media/Control%20Matrix.JPG)

***

### **Chaser Control**

Permite hacer una secuencia entre canales específicos

- ChaserCH -  muestra el valor actual secuenciado (una vez iniciada la secuencia)
- Delay    - selecciona la cantidad de tiempo en mS (mili Segundos) entre cada paso, el valor es aproximado a el numero por 10 = la cantidad de mS
- First CH - selecciona el primer canal de la secuencia
- Final CH - selecciona el ultimo canal de la secuencia
- Ctrl     - acceso a Control Options, los valores secuenciados no afectan al salir la memoria RAM con los valores anteriores
- Start    - Inicia la secuencia y cambia a "Stop", aqui se puede detener la secuencia

**Ejemplo:**

Selecciono "Delay" de 100 (100x10= 1000 mS), "First CH" 001 y "Final CH" 512
El resultado es una secuencia desde el canal 1 hasta el 512 y el paso entre los canales lo hace cada segundo

![Chaser Control](https://raw.githubusercontent.com/Arduino-DMX-512-Tester-and-Controller/Arduino-DMX-512-Tester-and-Controller-LCD-20x4-Firmware/master/media/Control%20Chaser.JPG)

***

### **Multiply Control**

Permite asignar un valor a un número de canales específico, con un salto numérico especifico

- Value    - selecciona el valor que se va a escribir (000 - 255)
- First CH - selecciona el primer canal
- Multiply - selecciona el numero de canales a multiplicar
- Quantity - selecciona la cantidad de veces a multiplicar
- Ctrl     - Acceso a Control Options, si afecta la memoria RAM de los canales
- Memory   - Acceso a Memory Options
- Apply    - Evalúa la petición, de no ser posible la solicitud, muestra el mensaje "Error", de lo contrario aplica la multiplicación a los canales y pone el valor seleccionado

**Ejemplo:**

Seleccionamos: "Value" = 255, "First CH" = 001, "Multiply" = 003, "Quantity" = 170 y "Apply"

El resultado es: 170 canales a partir del canal 1 hasta el 510, de 3 en 3 con el valor 255

![Control Multiply](https://github.com/Arduino-DMX-512-Tester-and-Controller/Arduino-DMX-512-Tester-and-Controller-LCD-20x4-Firmware/blob/master/media/Control%20Multiply.JPG)

***

### **Memory Options**

Acceso fácil a las opciones de la memoria EEPROM

- Save   - guarda el universo DMX con los valores actuales
- Load   - carga desde la memoria EEPROM los valores del universo DMX anteriormente guardado
- Empty  - Borrar la memoria RAM con los valores DMX actuales sin afectar la memoria EEPROM
- Clear  - Borrar el universo DMX guardado en la EEPROM
- Black  - Opcion "Black Out", pone todos los canales del universo DMX con valor "000", sin afectar la memoria, para salir presionar "enter" o "central" y regresa los valores anteriores 
- Cancel - regresar al menú anterior sin cambios

![Memory Options](https://raw.githubusercontent.com/Arduino-DMX-512-Tester-and-Controller/Arduino-DMX-512-Tester-and-Controller-LCD-20x4-Firmware/master/media/Memory%20Options.JPG)

***

### **Config**

Configuración general del sistema

- Ubicado en Control Options
- BackLight - Selecciona el valor entre 000-255 del dimmer de la luz trasera del LCD
- Contrast  - Selecciona el valor entre 150-255 del dimmer del contraste del LCD (liite inferior de 150, para evitar que el LCD no se vea)
- Exit      - regresa al menú anterior
- Los valores modificados se guardan en automático en la memoria EEPROM

***

### **About**

Muestra el "Acerca de.." del proyecto y las versiones de hardware y firmware instaladas

- Ubicado en Config
- Para salir presionar "enter" o "center"

***

## **Licenciamiento:**

![](https://raw.githubusercontent.com/Arduino-DMX-512-Tester-and-Controller/Arduino-DMX-512-Tester-and-Controller-LCD-20x4-Hardware/master/Social/Logos/GPLv3.png)

[GNU General Public License v3.0](https://github.com/Arduino-DMX-512-Tester-and-Controller/Arduino-DMX-512-Tester-and-Controller-LCD-20x4-Firmware/blob/master/LICENCE.md)

***

## **Autor:**

- Daniel Becerril
- Copyright (C) 2015

[![Email](https://raw.githubusercontent.com/Arduino-DMX-512-Tester-and-Controller/Arduino-DMX-512-Tester-and-Controller-LCD-20x4-Hardware/master/Social/Logos/email%2050x50.jpg)](mailto:daniel3514@gmail.com)
[![Facebook](https://raw.githubusercontent.com/Arduino-DMX-512-Tester-and-Controller/Arduino-DMX-512-Tester-and-Controller-LCD-20x4-Hardware/master/Social/Logos/Facebook%2050x50.png)](https://www.facebook.com/daniel.3514)
[![Facebook](https://raw.githubusercontent.com/Arduino-DMX-512-Tester-and-Controller/Arduino-DMX-512-Tester-and-Controller-LCD-20x4-Hardware/master/Social/Logos/Facebook%20Pages%2050x50.jpg)](https://www.facebook.com/ArduinoDMX512TesterController)
[![Twitter](https://raw.githubusercontent.com/Arduino-DMX-512-Tester-and-Controller/Arduino-DMX-512-Tester-and-Controller-LCD-20x4-Hardware/master/Social/Logos/Twitter%2050x50.png)](https://twitter.com/daniel3514)
[![Instructables](https://raw.githubusercontent.com/Arduino-DMX-512-Tester-and-Controller/Arduino-DMX-512-Tester-and-Controller-LCD-20x4-Hardware/master/Social/Logos/Instructables%2050x50.jpg)](http://www.instructables.com/id/Arduino-DMX-512-Tester-and-Controller/)
[![Hack a Day](https://raw.githubusercontent.com/Arduino-DMX-512-Tester-and-Controller/Arduino-DMX-512-Tester-and-Controller-LCD-20x4-Hardware/master/Social/Logos/hackaday%2050x50.jpg)](https://hackaday.io/project/5342-arduino-dmx-512-tester-and-controller)
[![Youtube](https://raw.githubusercontent.com/Arduino-DMX-512-Tester-and-Controller/Arduino-DMX-512-Tester-and-Controller-LCD-20x4-Hardware/master/Social/Logos/Youtube%2050x50.png)](https://www.youtube.com/watch?v=TxBHMpAWDSY)
[![Tech Inside](https://raw.githubusercontent.com/Arduino-DMX-512-Tester-and-Controller/Arduino-DMX-512-Tester-and-Controller-LCD-20x4-Hardware/master/Social/Logos/techinside%2045x45.png)](https://techinsideblog.wordpress.com/)
[![GitHub](https://raw.githubusercontent.com/Arduino-DMX-512-Tester-and-Controller/Arduino-DMX-512-Tester-and-Controller-LCD-20x4-Hardware/master/Social/Logos/github%2050x50.png)](https://github.com/Arduino-DMX-512-Tester-and-Controller)
[![Hackster](https://raw.githubusercontent.com/Arduino-DMX-512-Tester-and-Controller/Arduino-DMX-512-Tester-and-Controller-LCD-20x4-Hardware/master/Social/Logos/hackster%2050x50.png)](https://www.hackster.io/daniel3514/arduino-dmx-512-tester-controller-977c89)

***
