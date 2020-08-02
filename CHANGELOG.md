# **Notas sobre la versión**

***

- Compilado en Arduino IDE v1.0.6
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

### **v2.2**

- Hardware v0.7 - v0.8
- Tamaño binario del Sketch: 41.998 bytes (de un máximo de 258.048 bytes)
- **CORREGIDO** - se agregó a serial.print, F() para que cadena se guarde en la flash y no en la RAM

***

### **v2.1**

- Hardware v0.7 - v0.8
- Tamaño binario del Sketch: 41,590 bytes (de un máximo de 258,048 bytes)
- **CORREGIR**  - void Numeric_Write, lo remplazo void Numerico_Print, esta función ya no se utiliza
- **AGREGADO**  - a menú config, eeprom default
- **CAMBIADO**  - menú config, reorganización de items
- **AGREGADO**  - a menú 2, about
- **AGREGADO**  - a menú 2, config
- **AGREGADO**  - a menú 2, botón de back
- **AGREGADO**  - menú 2
- **AGREGADO**  - menú 1, botón de next
- **CAMBIADO**  - menú 1, reubicación de items
- **CAMBIADO**  - Config ya no tiene la opción de About, about, queda en el menú principal
- **CORREGIDO** - GUI_Control_Options a GUI_Menu_1, se agregaron más menús de funciones
- **CORREGIDO** - Contrast_Init a Init_Contrast, se busca más rápido
- **CORREGIDO** - Back_Light_Init a Init_Back_Light, se busca más rápido
- **CORREGIDO** - EEPROM_Load_Init a Init_EEPROM_Load, se busca más rápido
- **AGREGADO**  - carácter next
- **AGREGADO**  - carácter back 

***

### **v2.0**

- Hardware v0.7 - v0.8
- **AGREGADO**  - a config, external light
- **CAMBIADO**  - en config, redistribución de menú
- **ELIMINADO** - interruptores de lights, los sustituye teclado
- **AGREGADO**  - en teclado *, on off de external light
- **AGREGADO**  - en teclado #, on off de backlight y key light
- **AGREGADO**  - en Navegar, la lectura de * y # para lights
- **CORREGIDO** - en GUI_Memory_Init, la llamada a GUI_Control_Options(), era redundante
- **CORREGIDO** - en Multiply, espaciado
- **CAMBIADO**  - en Secuencer por caracteres nuevos
- **CORREGIDO** - en Memory, espaciado
- **CAMBIADO**  - en Memory por caracteres nuevos
- **CAMBIADO**  - en config por caracteres nuevos
- **CAMBIADO**  - en control chaser por caracteres nuevos
- **CORREGIDO** - en control matrix, el índice empieza en opción 1 y no en 3
- **CAMBIADO**  - en control matrix por caracteres nuevos
- **CAMBIADO**  - en control unitary por caracteres nuevos
- **CAMBIADO**  - en convert por caracteres nuevos
- **CAMBIADO**  - en control options por caracteres nuevos
- **CAMBIADO**  - en about por caracteres nuevos
- **CAMBIADO**  - en menú memory init por caracteres nuevos
- **CAMBIADO**  - en menú memory bank por caracteres nuevos
- **AGREGADO**  - carácter para LCD de exit
- **AGREGADO**  - carácter para LCD de archivo
- **ELIMINADO** - a numeric write, * y # como control de números 
- **AGREGADO**  - tabuladores al código
- **CORREGIDO** - Link de about de wiki al de Bitbucket https://goo.gl/7RsKo1
- **CORREGIDO** - about, versión de firmware de 1.9 a 2.0
- **AGREGADO**  - a inicio, Load Bank:-, se quita b-
- **AGREGADO**  - a Memory, Bank:-, se quita b-
- **CORREGIDO** - en Memory Bank, la leyenda Bank esta recorrida
- **CORREGIDO** - en Initial Memory, faltaba:
- **CORREGIDO** - en Memory, espacios y :
- **CORREGIDO** - en Secuencer, faltaba:
- **CORREGIDO** - DMX_Controller.ino:5747: warning: 'numero_total' may be used uninitialized in this function, se corrigió poniendo = 0

***

## **[v1.9 - Stable - Hardware v0.7 - v0.8](https://bitbucket.org/daniel3514/0066-arduino-dmx-512-tester-controller/src/03ac9d7d01c0ac0785e2351d8d0e76eea3e9af66/Firmware/v1.9/?at=master)**
- **PENDIENTE,** - funciones en teclado back light, agregar a lectura numerico write
- **PENDIENTE,** - sacar numérico write y remplazar por numérico print
- **PENDIENTE,** - Convert, cambiar cursor de navegación de binarios
- **PENDIENTE,** - tecla *, para backlight y key light, en esta versión no está activa
- **PENDIENTE,** - tecla #, quitarla de enter, no se usa, sustituye encoder center
- **PENDIENTE,** - DMX_Controller.ino: In function 'int Numerico_Write(int, int, byte, byte, byte, int)':
	- DMX_Controller.ino:5971: warning: control reaches end of non-void function
- **PENDIENTE,** - DMX_Controller.ino:5747: warning: 'numero_total' may be used uninitialized in this function
- **PENDIENTE,** - link de repositorio a bitbucket https://goo.gl/7RsKo1
- **AGREGADO,**  - modelo de programación de LCD - Encoder - keypad
	- https://github.com/daniel3514/Arduino-LCD-Encoder-KeyPad-Examples/tree/master/Examples/LCD%20-%20Encoder%20-%20Key%20Pad/v0.0
- **AGREGADO,** canal actual a eeprom
- **AGREGADO,** canal actual salvar en eeprom cuando se sale de algún control
- **AGREGADO,** Control Unit, función para escribir valores repetidos en la matriz, ejemplo si hay dos unos ambos se actualizan
- **AGREGADO,** Control Matrix, Ubicar, valor anterior al final
- **AGREGADO,** Control Matrix, ubicar a inicial y final
- **AGREGADO,** Control Matrix, mostrar canal a inicial y final
- **CORREGIDO,** menú, memoria, cambio de orden de items
- **CORREGIDO,** menú, Config, límites y vista
- **CORREGIDO,** Control Unitary, rediseño de GUI
- **AGREGADO,** Control Unitary, 8 unitarios distintos no consecutivos
- **AGREGADO,** Convert, opción de ubicar canal
- **CORREGIDO,** Convert, rediseño de interface gráfica
- **CORREGIDO,** Convert, modelo de navegación de binarios
- **CORREGIDO,** Control Chaser, rediseño de interface gráfica
- **AGREGADO,** Control Chaser. canal actual como first
- **AGREGADO,** Control Chaser, canal actual inicia encendido
- **AGREGADO,** Control Chaser, repasar canales desde encoder
- **CORREGIDO,** Control Secuencer, rediseño de GUI
- **CORREGIDO,** Config, la ventana de acción del contraste se queda en los límites de 0 a 255
- **AGREGADO,** Secuencer, el universo inicial siempre es 1
- **AGREGADO,** Multiply, valores preestablecidos
***

## **[v1.8 - beta - Hardware v0.7 - v0.8](https://bitbucket.org/daniel3514/0066-arduino-dmx-512-tester-controller/src/03ac9d7d01c0ac0785e2351d8d0e76eea3e9af66/Firmware/v1.8/?at=master)**
- **CORREGIR,** cambiar delay por interrupciones de timer
- **CORREGIDO,** Pin Out para hardware v0.7
- **CORREGIDO,** Pin encoder center al 6
- **CORREGIDO,** Quitar la programación del potenciómetro
- **CORREGIDO,** Quitar la programación de los cursores
- **CORREGIDO,** pin 6 de encoder center a pull-up
- **CORREGIDO,** pin key light a 11
- **CORREGIDO,** pin contraste a 12
- **AGREGAR,** en multiplicador, el valor en tiempo real desde el potenciómetro o teclado
- **AGREGAR,** control chaser desde el potenciómetro, al girar recorre los canales
- **AGREGAR,** EEPROM Default en pin 9 como pull-up
- **AGREGAR,** dimmer para luz led como lámpara en pin 10
- **AGREGADO,** a EEPROM, espacio para Ext Light
- **AGREGADO,** función para jumper de eeprom default
- **AGREGADO,** dimmer de pantalla al inicio
- **AGREGADO,** índices a posiciones de LCD en el Excel
***

## **[v1.7 - Stable - Hardware v0.3 - v0.5](https://bitbucket.org/daniel3514/0066-arduino-dmx-512-tester-controller/src/03ac9d7d01c0ac0785e2351d8d0e76eea3e9af66/Firmware/v1.7/?at=master)**
- **CORREGIDO,** se separa la lectura desde el encoder como función
- **CORREGIDO,** en analogy read "a" cambia por encoder read "e"
- **AGREGADO,** control desde encoder a value de dmx
- **AGREGADO,** control desde encoder a config contraste 
- **AGREGADO,** control desde encoder a config backlight
- **AGREGADO,** control desde encoder a config bank init
***

## **[v1.6 - Stable - Hardware v0.3 - v0.5](https://bitbucket.org/daniel3514/0066-arduino-dmx-512-tester-controller/src/03ac9d7d01c0ac0785e2351d8d0e76eea3e9af66/Firmware/v1.6/?at=master)**
- **CORREGIDO,** se agrega un encoder KEYES Rotary encoder module KY-040 para remplazar el potenciómetro
- **AGREGADO,** el botón del centro es el mismo del encoder
- **AGREGADO,** encoder CLK en 6 DT en 7
- **CORREGIDO,** el pin del potenciómetro se elimina
- **AGREGADO,** encoder library 
	- https://www.pjrc.com/teensy/td_libs_Encoder.html
- **CORREGIDO,** lectura análoga de valor, se agrega el valor anterior en la escritura del LCD
- **CORREGIDO,** lectura análoga en valor el cursor blink se queda en la "a" y no sobre el numero
***

## **[v1.5 - Stable - Hardware v0.3 - v0.4](https://bitbucket.org/daniel3514/0066-arduino-dmx-512-tester-controller/src/03ac9d7d01c0ac0785e2351d8d0e76eea3e9af66/Firmware/v1.5/?at=master)**
- Ultima versión con potenciómetro
- **CORREGIDO,** el cursor en el análogo se mostraba el blink fuera del numero y se encimaba
***

## **[v1.4 - Stable - Hardware v0.3 - v0.4](https://bitbucket.org/daniel3514/0066-arduino-dmx-512-tester-controller/src/03ac9d7d01c0ac0785e2351d8d0e76eea3e9af66/Firmware/v1.4/?at=master)**
- **CORREGIDO,** en about la versión actual
- **CORREGIDO,** las leyendas Ctrl cambian por Exit, el menú control ya no tiene la leyenda
- **CORREGIDO,** en control unitary Ctrl cambia por Exit
- **CORREGIDO,** en control Matrix Ctr cambia por Exi
- **CORREGIDO,** en control chaser Ctrl por Exit
- **CORREGIDO,** en control secuencer Ctrl por Exit
- **CORREGIDO,** en control multiply Ctrl por Exit
- **CORREGIDO,** en control options se quitó la leyenda Control:
- **AGREGADO,** Convert, convierte entre binario y decimal para address dip switch
- **AGREGADO,** a control options la opción Convert
- **AGREGADO,** a Convert binario a decimal botón de centro para salir, botón de lados para navegar, botón arriba abajo para cambiar valor
***

## **[v1.3 - Stable - Hardware v0.3 - v0.4](https://bitbucket.org/daniel3514/0066-arduino-dmx-512-tester-controller/src/03ac9d7d01c0ac0785e2351d8d0e76eea3e9af66/Firmware/v1.3/?at=master)**
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

## **[v1.2 - Stable - Hardware v0.3 - v0.4](https://bitbucket.org/daniel3514/0066-arduino-dmx-512-tester-controller/src/03ac9d7d01c0ac0785e2351d8d0e76eea3e9af66/Firmware/v1.2/?at=master)**
- **AGREGADO,** al arranque toma el banco de la eeprom previamente elegido desde config
- **AGREGADO,** a config el banco que lee a arranque
- **AGREGADO,** al about el banco actual
- **AGREGADO,** a about reacomodo de datos
- **AGREGADO,** a about licencias open source
- **AGREGADO,** a initial memory el bank actual
- **AGREGADO,** en EEPROM add 4093 para guardar banco a correr al inicio
- **AGREGADO,** Bank 8 solo tiene 509 canales disponibles
- **AGREGADO,** a EEPROM Load el límite en bank 8 de 4092
- **AGREGADO,** a EEPROM Save el límite en bank 8 de 4092
- **CORREGIDO,** GUI Config de LCD config solo a config
- **CORREGIDO,** GUI Config de Control a exit
- **AGREGADO,** a GUI Config opción bank init
- **AGREGADO,** EEPROM_Load_Init para cargar el universo pre configurado al inicio
- **CORREGIDO,** GUI about cambio de disposición y url por wiki
- **AGREGADO,** GUI_Licence a config
***

## **[v1.1 - Beta - Hardware v0.3 - v0.4](https://bitbucket.org/daniel3514/0066-arduino-dmx-512-tester-controller/src/03ac9d7d01c0ac0785e2351d8d0e76eea3e9af66/Firmware/v1.1/?at=master)**
- **AGREGADO,** memory a control options
- **AGREGADO,** a memory gui ClearAll para borrar todos los bancos de la eeprom
- **AGREGADO,** a memory gui reacomodo de menús
***

## **[v1.0 - Beta - Hardware v0.3 - v0.4](https://bitbucket.org/daniel3514/0066-arduino-dmx-512-tester-controller/src/03ac9d7d01c0ac0785e2351d8d0e76eea3e9af66/Firmware/v1.0/?at=master)**
- **CORREGIDO,** seceuncer no tiene reversa
- **CORREGIDO,** secuencer no tiene salida de dmx, el uso de memoria eeprom descartaba valores
- **CORREGIDO,** GUI_Secuencer se cambió el método de lectura de memoria, se hace en tiempo real, evita over flow
- **CORREGIDO,** GUI_Secuencer se cambió a GUI_Control_Secuencer
- **CORREGIDO,** tabulacion
- **CORREGIDO,** manejo de memoria EEPROM al guardar y leer el conteo es en 1 y no en 0
- **CORREGIDO,** GUI_Chasser el cursor blink no se mostraba después de stop 
- **CORREGIDO,** GUI_Control_Options, el cursor no se mostraba en unitary
- **CORREGIDO,** disminución de tiempo mensaje final de opciones de acceso a eeprom
- **AGREGADO,** lectura de botón "center" en el about
- **AGREGADO,** a GUI_Secuencer límite de delay a 100
- **AGREGADO,** a GUI_Secuencer en la salida a control regresa al dmx los datos desde la RAM
- **AGREGADO,** a GUI_Unitary el canal anterior y siguiente en el gui
***

## **[v0.9 - Beta - Hardware v0.3 - v0.4](https://bitbucket.org/daniel3514/0066-arduino-dmx-512-tester-controller/src/03ac9d7d01c0ac0785e2351d8d0e76eea3e9af66/Firmware/v0.9/?at=master)**
- **CORREGIR,** GUI_Secuencer provoca over flow y se reinicia, demasiada RAM usada
- **CORREGIDO,** GUI_Navegar se cambió la variable Boton_Delay_Cursor de long a int
- **CORREGIDO,** Contrast_Init se limita a no menor de 150 el valor del pwm
- **CORREGIDO,** GUI_Config solo en control options
- **CORREGIDO,** esta encimado en control options unitary
- **CORREGIDO,** GUI Control Options se quitó iniciar:, no se usa
- **CORREGIDO,** se agregó variable global BackLight_Add para dirección de EEPROM
- **CORREGIDO,** se agregó variable global Contrast_Add para dirección de EEPROM
- **CORREGIDO,** Se quitó el efecto binario cuando se usa la memoria EEPROM
- **AGREGADO,** GUI_Secuencer limitado delay entre 0 y 999 x 100 mS
- **AGREGADO,** GUI_Secuencer limitado final y first entre 1 y 8
- **AGREGADO,** a GUI_About bink del cursor
- **AGREGADO,** GUI_Memory_Bank
- **AGREGADO,** GUI_Memory_Bank, regresa 1 si se selecciona salir para regresar al menú anterior
- **AGREGADO,** a GUI_Memory_Bank, retardo cuando entra al banco de memoria
- **AGREGADO,** a matrix el número de banco actual, si el banco no se seleccionó muestra "-"
- **AGREGADO,** a memory options el número de banco actual, si el banco no se seleccionó muestra "-"
- **AGREGADO,** a unitary control el número de banco actual, si el banco no se seleccionó muestra "-"
- **AGREGADO,** a multiply control el número de banco actual, si el banco no se seleccionó muestra "-"
- **AGREGADO,** a GUI Memory la configuración
- **AGREGADO,** a GUI Control Options el número de banco actual, si el banco no se seleccionó muestra "-"
- **AGREGADO,** a GUI Control Options la configuración
- **AGREGADO,** a GUI_EEPROM_Empty la leyenda del banco que se está modificando "RAM"
- **AGREGADO,** a GUI_EEPROM_Empty el blink del lcd para saber que está trabajando
- **AGREGADO,** a EEPROM_Clear control de universos guardados
- **AGREGADO,** a EEPROM_Clear al final y al principio el número de banco
- **AGREGADO,** a EEPROM_Clear el blink del lcd para saber que está trabajando
- **AGREGADO,** a EEPROM_Clear regresa 1 si se selecciona exit
- **AGREGADO,** a EEPROM_Clear más tiempo para mensaje final
- **AGREGADO,** a EEPROM_Load control de universos guardados
- **AGREGADO,** a EEPROM_Load, regresa 1 si se selecciona exit
- **AGREGADO,** a EEPROM_Load al final el número de banco
- **AGREGADO,** a EEPROM_Load el blink del lcd para saber que está trabajando
- **AGREGADO,** a EEPROM_Load más tiempo para mensaje final
- **AGREGADO,** a EEPROM_Save control de universos guardados
- **AGREGADO,** a EEPROM_Save al final el número de banco
- **AGREGADO,** a EEPROM_Save, regresa 1 si se selecciona exit
- **AGREGADO,** a EEPROM_Save el blink del lcd para saber que está trabajando
- **AGREGADO,** a EEPROM_Save más tiempo para mensaje final
- **AGREGADO,** a GUI_Memory_Init control de universos
- **AGREGADO,** a GUI_Memory_Init manejo cuando se selecciona exit en los bancos de memoria
- **AGREGADO,** a GUI_Memory control de salida desde bancos de memoria
- **AGREGADO,** a GUI_Memory salida inmediata después de la lectura de opción
- **AGREGADO,** a GUI_About la leyenda open hardware
- **AGREGADO,** a GUI_About más tiempo para mostrar
- **AGREGADO,** GUI Secuencer
- **AGREGADO,** el banco 8 solo llegaría a 500 por el contraste y el backlight
- **AGREGADO,** Los bancos de memoria no aplican a memory empty
- **AGREGADO,** GUI_Memory_Bank solo activa en cambios de EEPROM
***

## **[v0.8 - Stable - Hardware v0.3 - v0.4](https://bitbucket.org/daniel3514/0066-arduino-dmx-512-tester-controller/src/03ac9d7d01c0ac0785e2351d8d0e76eea3e9af66/Firmware/v0.8/?at=master)**
- **AGREGADO,** compatibilidad con Hardware v0.3 - v0.4
***

## **[v0.7 - Stable - Hardware v0.0 - v0.2](https://bitbucket.org/daniel3514/0066-arduino-dmx-512-tester-controller/src/03ac9d7d01c0ac0785e2351d8d0e76eea3e9af66/Firmware/v0.7/?at=master)**
- **AGREGADO,** en chaser el cursor en blink cuando hace la secuencia
- **AGREGADO,** función de Black Out desde el menú de Memory, pone todos los canales en 0 y los regresa a lo que tenían, para salir dar en center
- **CORREGIDO,** en config contraste el límite inferior no se mostraba
- **CORREGIDO,** en gui about se retiró variable id, no se usa
- **CORREGIDO,** en chaser se quitó el label iniciar, no se usa
- **CORREGIDO,** en numérico calc se quitó la variable salida, no se usa
- **CORREGIDO,** en numérico calc se quitó la variable Num_Val_Temp_3, no se usa
- **CORREGIDO,** en chaser ya no guarda los valores de los cambios aplicados, al salir los regresa a su lugar
- **CORREGIDO,** en multiply cuando hace en calculó se cambia apply por calc..
- **CORREGIDO,** en ubicar se agrega cancelar con center
- **CORREGIDO,** se cambió la url del about apuntando al Wiki
***

## **[v0.6 - Stable - Hardware v0.0 - v0.2](https://bitbucket.org/daniel3514/0066-arduino-dmx-512-tester-controller/src/03ac9d7d01c0ac0785e2351d8d0e76eea3e9af66/Firmware/v0.6/?at=master)**
- **CORREGIDO,** los valores limites superiores de config se escribían un carácter después
- **CORREGIDO,** hacer a partir de 155 el dimmer del contraste
- **CORREGIDO,** botón * de back light funciona errático - faltaba delay para evitar repetición
- **CORREGIDO,** quitar en config el dimmer 0-255, no aplica al contraste
- **CORREGIDO,** las io no usadas son salidas low
- **CORREGIDO,** no inicializa el contraste
- **CORREGIDO,** en matrix no se aplican los cambios en los bancos
- **CORREGIDO,** en matrix el valor final del banco se pasa de 512
- **CORREGIDO,** en config backlight el valor no se guardaba en eeprom
- **CORREGIDO,** en config backlight se recorrían todas las opciones de botones, se agregó mecanismo para sacar del bucle
- **CORREGIDO,** se bajó el delay de la lectura análoga para evitar pasos escalonados
- **AGREGADO,** potenciómetro para valores DMX con tecla "D" solo en valores, para detenerlo presionar # o center
- **AGREGADO,** análogo a unitary
- **AGREGADO,** análogo a matrix
- **AGREGADO,** análogo a config back light
- **AGREGADO,** an-alogo a config contrast
- **AGREGADO,** en la lectura análogo mecanismo para escribir el valor solo cuando cambia y no todo el tiempo
***

## **[v0.5 - Stable - Hardware v0.0 - v0.2](https://bitbucket.org/daniel3514/0066-arduino-dmx-512-tester-controller/src/03ac9d7d01c0ac0785e2351d8d0e76eea3e9af66/Firmware/v0.5/?at=master)**
- **AGREGADO,** la función para cuando se da enter en un numero para cambiarlo, si de da enter de nuevo se quede el número que estaba

## **[v0.4 - Stable - Hardware v0.0 - v0.2](https://bitbucket.org/daniel3514/0066-arduino-dmx-512-tester-controller/src/03ac9d7d01c0ac0785e2351d8d0e76eea3e9af66/Firmware/v0.4/?at=master)**
- **CORREGIDO,** se retira del about el ID
- **CORREGIDO,** se cambia en config el menú exit por Ctrl
- **AGREGADO,** void Back_Light_En() para encender o apagar el back light desde el teclado numúrico
- **AGREGADO,** void Back_Light_Init() para encender o apagar el back light desde la última configuración
- **AGREGADO,** a Control Options el menú Config
- **AGREGADO,** void GUI_Config() con las opciones de la configuración, el LCD y la salida al pwm
- **AGREGADO,** control del back light a gui_navegar, siempre está activo
- **AGREGADO,** se actualiza el about con el nombre del proyecto
- **AGREGADO,** al config el about
- **AGREGADO,** al about desde config espera a que se presione center para salir
- **AGREGADO,** al config mas info sobre el backlight
- **AGREGADO,** a control options Memory options
- **AGREGADO,** en matrix la opción de poner el valor final de la matriz
- **AGREGADO,** a la lectura numúrica centro como enter
***

## ** [v0.3 - Stable - Hardware v0.0 - v0.2](https://bitbucket.org/daniel3514/0066-arduino-dmx-512-tester-controller/src/03ac9d7d01c0ac0785e2351d8d0e76eea3e9af66/Firmware/v0.3/?at=master)**
- **CORREGIDO,** retirar de setup las variables de la versión y pasarlas directamente a su void (no hay razón para que sean globales)
- **CORREGIDO,** en gui about retirar el delay en el efecto binario
- **CORREGIDO,** eeprom save, load empty y clear retirar delay de efecto (se retiró en todos los casos)
- **CORREGIDO,** agregar al inicio del programa .ino un about
- **CORREGIDO,** en control chaser se quitó el espacio entre delay el número y x10=mS, parece que fuera una opción
***

## **[v0.2 - Stable - Hardware v0.0 - v0.2](https://bitbucket.org/daniel3514/0066-arduino-dmx-512-tester-controller/src/03ac9d7d01c0ac0785e2351d8d0e76eea3e9af66/Firmware/v0.2/?at=master)**
- **CORREGIR,** retirar del setup las variables de la versión y pasarlas directamente a su void
- **CORREGIR,** en GUI_About se retirar el delay en el efecto binario
- **CORREGIR,** eeprom save, load empty y clear retirar el delay de efecto binario
- **CORREGIR,** agregar al inicio del programa un about
- **CORREGIR,** checar el tema del puerto de data flux, no se asigna
- **CORREGIDO,** se cambió gui_init por gui_about
- **CORREGIDO,** se cambia en unitary control, matrix por control y apunta a gui control options
- **CORREGIDO,** se cambia en matrix control, ubi por con y apunta a gui control options
- **CORREGIDO,** se quita la opción about es muy repetitiva
- **AGREGADO,** control options about
- **AGREGADO,** control options Chaser
- **AGREGADO,** control options multiply
- **AGREGADO,** actualización del texto "about"
- **AGREGADO,** actualización del texto "memory initial"
- **AGREGADO,** al GUI_Memory "empty" para borrar la RAM
- **AGREGADO,** el control multiply
- **AGREGADO,** a about al inicio el efecto del binario corriendo
***

## **[v0.1 - Stable - Hardware v0.0 - v0.2](https://bitbucket.org/daniel3514/0066-arduino-dmx-512-tester-controller/src/03ac9d7d01c0ac0785e2351d8d0e76eea3e9af66/Firmware/v0.1/DMX_Controller/?at=master)**
- **CORREGIDO,** cambiar en gui unit a "Unitary"
- **CORREGIDO,** cambiar en GUI multi a "Matrix"
- **CORREGIDO,** hacer los barridos de la memoria más rápidos, se agrega efecto de carga y no baja la velocidad
- **CORREGIDO,** agregar al menú memory "Cancel"
- **CORREGIDO,** se agrega 100ms mas a la lectura de los cursores
- **CORREGIDO,** cuando se escribe un numero en la matriz o en unit, mayor o menor al límite la variable funciona pero el visual no
- **CORREGIR,** en GUI_Multi no hay vista de posición
- **AGREGADO,** líneas bajas cuando se está escribiendo un número, se quitaron los ceros
- **AGREGADO,** se implementa para el caso de los valores "A" para 255 y "B" para 000
- **AGREGADO,** se implementa para los valores la tecla "C" para ubicar la lámpara, parpadea y deja de hacerlo al volverla a presionar
- **AGREGADO,** se implementa en la matriz el valor "C" que indica el canal donde está posicionado el cursor
***

## **v0.0 - Beta - Hardware v0.0 - v0.2**
- **AGREGADO,** Hello World !!
***