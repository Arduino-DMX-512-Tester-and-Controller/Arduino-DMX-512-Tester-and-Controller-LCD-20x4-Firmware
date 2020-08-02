// ***************************************************************************************************************************
// ***************************************************************************************************************************
// **				                                                                                                        **
// **											Arduino DMX-512 Tester Controller				                            **
// **																	                                                    **
<<<<<<< HEAD
// **	- Firmware v2.1 																									**
=======
// **	- Firmware v2.0 																									**
>>>>>>> master
// **	- Hardware v0.7																										**
// **																														**
// **	- Compilado en Arduino IDE v1.0.6																					**
// **		http://www.arduino.cc/en/Main/OldSoftwareReleases																**
// ** 	- Editado en Sublime Text 3																							**
// **		https://www.sublimetext.com/																					**
// **		Syntax C++																										**
// **		Formato Windows ANSI																							**
// **	- Compilado para Arduino Mega 2560 R3																				**
// **		http://www.arduino.cc/en/Main/ArduinoBoardMega2560																**
// **	- Libreria Arduino cuatro universos DMX v0.3 - Deskontrol.net														**
// **		http://www.deskontrol.net/blog/libreria-arduino-cuatro-universos-dmx/)											**
// **	- Libreria LCD v1.2.1 - Francisco Malpartida																		**
// **		https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home													**
// **	- Libreria Encoder v1.2 - pjrc.com																					**
// **		http://www.pjrc.com/teensy/td_libs_Encoder.html																	**
// **																														**
// **	Autor:																												**
// **	Copyright (C) 2015                                                                                                  **
// **   Daniel Roberto Becerril Angeles																                        **
// **	daniel3514@gmail.com																								**
// **	                                                                                                                    **
// **   Wiki:                                                                                                               **
// **   https://bitbucket.org/daniel3514/0066-arduino-dmx-512-tester-controller/wiki/Home									**
// **																														**
// **	Licenciamiento:																										**
// **																														**
// **	Firmware:																											**
// **		GNU General Pubic Licence Version v3																			**
// **		https://www.gnu.org/copyleft/gpl.html																			**
// **																														**
// **	Hardware:																											**
// **		Open Source Hardware (OSHW) v1.0																				**
// **		http://freedomdefined.org/OSHW#Licenses_and_Hardware															**
// **		http://www.oshwa.org/definition/																				**
// **																														**
// **	Este programa es software libre: usted puede redistribuirlo y / o modificarlo bajo los términos de la 				**
// **	Licencia Pública General GNU publicada por la Free Software Foundation, bien de la versión 3 de la Licencia, 		**
// **	o (A su elección) cualquier versión posterior.																		**
// **																														**
// **	Este programa se distribuye con la esperanza de que sea útil, pero SIN NINGUNA GARANTIA; ni siquiera la garantía 	**
// **	implícita de COMERCIALIZACION o IDONEIDAD PARA UN PROPOSITO PARTICULAR. Vea el GNU General Public License 			**
// **	para más detalles.																									**
// **																														**
// ** 	Esto es software libre, y le invitamos a redistribuirlo bajo ciertas condiciones									**
// **																														**
// **	Deberá haber recibido una copia de la Licencia Pública General GNU													**
// **	junto con este programa. Si no es así, consulte <http://www.gnu.org/licenses/>.										**
// **																														**
// ***************************************************************************************************************************
// ***************************************************************************************************************************

	// Librerias
#include <LiquidCrystal.h>			// libreria para LCD - ttps://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home	
#include <Wire.h>
#include <EEPROM.h>
#include <string.h>
#include <lib_dmx.h>  				// libreria DMX 4 universos deskontrol four universes DMX library  - http://www.deskontrol.net/blog
#include <Encoder.h>				// libreria encoder - http://www.pjrc.com/teensy/td_libs_Encoder.html		

	// DMX Library
#define    DMX512	  		(0)  	// (250 kbaud  - 2 to 512 channels) Standard USITT DMX-512
//#define  DMX1024    		(1)   	// (500 kbaud  - 2 to 1024 channels) Completely non standard - TESTED ok
//#define  DMX2048    		(2)   	// (1000 kbaud - 2 to 2048 channels) called by manufacturers DMX1000K, DMX 4x or DMX 1M ???

	// DMX
int  	DMX_Values 			[515];  // array de valores actuales DMX
int  	Canal_Actual 		= 0;	// canal actual de dmx, valor real del canal, inicia en 1
byte 	Universo_Actual		= 0;	// universo actual de dmx

	// Encoder
byte  	Enc_Center			= 8;	// pin
byte 	Enc_CLK				= 7;	// pin
byte 	Enc_Data 			= 6;	// pin
Encoder myEnc				(Enc_CLK, Enc_Data);	// conexion de encoder

	// Cursor
int  Cursor_Index_Pos 		= 1;	// posicion en tiempo real de lcd
byte Cursor_Index[20][4] 	= 
						{	{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, },
  							{0, 0, 0, 0, }
						};

	// tecleado					
byte Keypad_A				= 30;	// pin 	
byte Keypad_B				= 32;	// pin 	
byte Keypad_C				= 34;	// pin 	
byte Keypad_D				= 36;	// pin 	
byte Keypad_1				= 38;	// pin 	
byte Keypad_2				= 40;	// pin 
byte Keypad_3				= 42;	// pin
byte Keypad_4				= 44;	// pin

	// LCD
byte LCD_RS 				= 43;	// pin
byte LCD_E  				= 45;	// pin
byte LCD_D4 				= 47;	// pin
byte LCD_D5 				= 49;	// pin
byte LCD_D6 				= 51;	// pin
byte LCD_D7					= 53;	// pin
byte Back_Light_PWM			= 13;	// pin, salida para PWM de Back Light de LCD
byte Contrast_PWM			= 12;	// pin, salida para pwm de contraste de LCD
<<<<<<< HEAD
LiquidCrystal 				lcd		(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);  //LCD setup
=======
LiquidCrystal lcd			(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);  //LCD setup
>>>>>>> master
byte Contrast_Value			= 0;	// valor en real time

	// lights
byte Back_Key_Light_On_Off  = 0;	// saber si esta encendida o apagada, back y key
byte External_Light_On_Off  = 0;	// saber si esta encendida o apagada, external
byte Light_Ext_Value		= 0;	// valor en real time
byte Key_Light_Value		= 0;	// valor en real time
byte Back_Light_Value 		= 0;	// valor en real time

	// Caracter de Cursor
byte Caracter_Nav[8] 		= 	{
  									B00000,
  									B01000,
  									B01100,
 									B01110,
  									B01110,
  									B01100,
 									B01000,
  									B00000
								};

	// Caracter de dip switch Off
byte Caracter_Off[8] 		= 	{
  									B11111,
  									B11111,
  									B11111,
 									B11111,
  									B10001,
  									B10001,
 									B10001,
  									B11111
								};

	// Caracter de dip switch On
byte Caracter_On[8] 		= 	{
  									B11111,
  									B10001,
  									B10001,
 									B10001,
  									B11111,
  									B11111,
 									B11111,
  									B11111
								};

	// Caracter de file
byte Caracter_file[8] 		= 	{
  									B00000,
  									B11110,
  									B10011,
 									B10001,
  									B10001,
  									B10001,
 									B11111,
  									B00000
								};

	// Caracter de exit
byte Caracter_exit[8] 		= 	{
  									B11111,
  									B10001,
  									B10100,
 									B10110,
  									B10110,
  									B10100,
 									B10001,
  									B11111
								};
<<<<<<< HEAD

	// Caracter Next
byte Caracter_next[8] 		= 	{
  									B00000,
  									B00000,
  									B10010,
 									B11011,
  									B11011,
  									B10010,
 									B00000,
  									B00000
								};

	// Caracter Back
byte Caracter_back[8] 		= 	{
  									B00000,
  									B00000,
  									B01001,
 									B11011,
  									B11011,
  									B01001,
 									B00000,
  									B00000
								};
=======
>>>>>>> master

	// Key Light
byte Key_Light_PWM			= 11;	// pin

	// Light external
byte Light_PWM 				= 10;	// pin

	// EEPROM
int  BackLight_Add 			= 4094;	// direccion de eeprom
int  Contrast_Add			= 4095;	// direccion de eeprom
int  Bank_Init_Add			= 4093;	// direccion de eeprom
int  Key_Light_Add			= 4092;	// direccion de eeprom
int  Light_Ext_Add			= 4091;	// direccion de eeprom
int  Canal_Actual_1_Add		= 4089;	// canal dmx actual
int  Canal_Actual_2_Add		= 4090;	// canal dmx actual
int  EEPROM_Limit			= 4088;	// limite de espacios en eeprom para universos
byte EEPROM_Def_Jumper		= 9;	// pin

void setup 						()
{
	// Encoder
	pinMode			(Enc_Center,			INPUT_PULLUP);	// no es necesario declarar CLK y data
	
		// Teclado
	pinMode			(Keypad_A, 				OUTPUT);
	pinMode			(Keypad_B, 				OUTPUT);
	pinMode			(Keypad_C, 				OUTPUT);
	pinMode			(Keypad_D, 				OUTPUT);
	pinMode			(Keypad_1, 				INPUT_PULLUP);
	pinMode			(Keypad_2, 				INPUT_PULLUP);
	pinMode			(Keypad_3, 				INPUT_PULLUP);
	pinMode			(Keypad_4, 				INPUT_PULLUP);

	digitalWrite	(Keypad_A, 				HIGH);
	digitalWrite	(Keypad_B, 				HIGH);
	digitalWrite	(Keypad_C, 				HIGH);
	digitalWrite	(Keypad_D, 				HIGH);

		// LCD
	pinMode			(LCD_RS, 				OUTPUT);
	pinMode			(LCD_E,  				OUTPUT);
	pinMode			(LCD_D7, 				OUTPUT);
	pinMode			(LCD_D6, 				OUTPUT);
	pinMode			(LCD_D5, 				OUTPUT);
	pinMode			(LCD_D4, 				OUTPUT);
	pinMode			(Back_Light_PWM,		OUTPUT);
	pinMode			(Contrast_PWM,			OUTPUT);

<<<<<<< HEAD
	lcd.begin								(20, 4);		//tamaño de LCD
=======
	lcd.begin		(20, 					4);				//tamaño de LCD
>>>>>>> master
	lcd.createChar	(0, 					Caracter_Nav); 	//void LCD::createChar(uint8_t location, uint8_t charmap[]) 
	lcd.createChar	(1, 					Caracter_On); 	//void LCD::createChar(uint8_t location, uint8_t charmap[]) 
	lcd.createChar	(2, 					Caracter_Off); 	//void LCD::createChar(uint8_t location, uint8_t charmap[]) 
	lcd.createChar	(3, 					Caracter_file); //void LCD::createChar(uint8_t location, uint8_t charmap[]) 
	lcd.createChar	(4, 					Caracter_exit); //void LCD::createChar(uint8_t location, uint8_t charmap[]) 
<<<<<<< HEAD
	lcd.createChar	(5, 					Caracter_next); //void LCD::createChar(uint8_t location, uint8_t charmap[]) 
	lcd.createChar	(6, 					Caracter_back); //void LCD::createChar(uint8_t location, uint8_t charmap[]) 
=======
>>>>>>> master

		// Key Light
	pinMode 		(Key_Light_PWM,			OUTPUT);

		// Light
	pinMode 		(Light_PWM,				OUTPUT);

		// EEPROM Default
	pinMode 		(EEPROM_Def_Jumper, 	INPUT);		// el pin no tiene pullup fisico

		// DMX
	ArduinoDmx0.set_tx_address				(1);      	// poner aqui la direccion de inicio de DMX
	ArduinoDmx0.set_tx_channels				(512);   	// poner aqui el numero de canales a transmitir
	ArduinoDmx0.init_tx						(DMX512);   // iniciar transmision universo 0, modo estandar DMX512

		// no conectados
	pinMode			(5,   OUTPUT);
	digitalWrite	(5,   LOW);
	pinMode			(20,  OUTPUT);
	digitalWrite	(20,  LOW);
	pinMode			(21,  OUTPUT);
	digitalWrite	(21,  LOW);
	pinMode			(22,  OUTPUT);
	digitalWrite	(22,  LOW);
	pinMode			(23,  OUTPUT);
	digitalWrite	(23,  LOW);
	pinMode			(24,  OUTPUT);
	digitalWrite	(24,  LOW);
	pinMode			(25,  OUTPUT);
	digitalWrite	(25,  LOW);
	pinMode			(26,  OUTPUT);
	digitalWrite	(26,  LOW);
	pinMode			(27,  OUTPUT);
	digitalWrite	(27,  LOW);
	pinMode			(28,  OUTPUT);
	digitalWrite	(28,  LOW);
	pinMode			(29,  OUTPUT);
	digitalWrite	(29,  LOW);
	pinMode			(31,  OUTPUT);
	digitalWrite	(31,  LOW);
	pinMode			(33,  OUTPUT);
	digitalWrite	(33,  LOW);
	pinMode			(35,  OUTPUT);
	digitalWrite	(35,  LOW);
	pinMode			(37,  OUTPUT);
	digitalWrite	(37,  LOW);
	pinMode			(39,  OUTPUT);
	digitalWrite	(39,  LOW);
	pinMode			(41,  OUTPUT);
	digitalWrite	(41,  LOW);
	pinMode			(46,  OUTPUT);
	digitalWrite	(46,  LOW);
	pinMode			(48,  OUTPUT);
	digitalWrite	(48,  LOW);
	pinMode			(50,  OUTPUT);
	digitalWrite	(50,  LOW);
	pinMode			(52,  OUTPUT);
	digitalWrite	(52,  LOW);
	pinMode			(A0,  OUTPUT);
	digitalWrite	(A0,  LOW);
	pinMode			(A1,  OUTPUT);
	digitalWrite	(A1,  LOW);
	pinMode			(A2,  OUTPUT);
	digitalWrite	(A2,  LOW);
	pinMode			(A3,  OUTPUT);
	digitalWrite	(A3,  LOW);
	pinMode			(A4,  OUTPUT);
	digitalWrite	(A4,  LOW);
	pinMode			(A5,  OUTPUT);
	digitalWrite	(A5,  LOW);
	pinMode			(A6,  OUTPUT);
	digitalWrite	(A6,  LOW);
	pinMode			(A7,  OUTPUT);
	digitalWrite	(A7,  LOW);
	pinMode			(A8,  OUTPUT);
	digitalWrite	(A8,  LOW);
	pinMode			(A9,  OUTPUT);
	digitalWrite	(A9,  LOW);
	pinMode			(A10, OUTPUT);
	digitalWrite	(A10, LOW);
	pinMode			(A11, OUTPUT);
	digitalWrite	(A11, LOW);
	pinMode			(A12, OUTPUT);
	digitalWrite	(A12, LOW);
	pinMode			(A13, OUTPUT);
	digitalWrite	(A13, LOW);
	pinMode			(A14, OUTPUT);
	digitalWrite	(A14, LOW);
	pinMode			(A15, OUTPUT);
	digitalWrite	(A15, LOW);
}

void loop 						()
{
<<<<<<< HEAD
	Init_EEPROM_Load();	// valores desde eeprom
	Init_Back_Light	();	// inicializador de Backlight desde eeprom
	Init_Contrast	();	// inicializador de EEPROM desde eeprom
	
		// eeprom defaul
	if (digitalRead(EEPROM_Def_Jumper) == 0)
	{
		EEPROM_Default	();	// jumper para default eeprom
	}

=======
	EEPROM_Load_Init();	// valores desde eeprom
	Back_Light_Init	();	// inicializador de Backlight desde eeprom
	Contrast_Init	();	// inicializador de EEPROM desde eeprom
	EEPROM_Default	();	// jumper para default eeprom
>>>>>>> master
	GUI_About		();	// interface grafica de about
	GUI_Memory_Init	();	// interface grafica de memoria
}

void Canal_Actual_EEPROM_Save	()
{
	int temporal = 0;

	if (Canal_Actual < 256)
	{
		EEPROM.write(Canal_Actual_1_Add, Canal_Actual);
		EEPROM.write(Canal_Actual_2_Add, 0);
	}
	else
	{
		EEPROM.write(Canal_Actual_1_Add, 255);
		temporal = Canal_Actual - 255;
		EEPROM.write(Canal_Actual_2_Add, temporal);
	}
}

void EEPROM_Default 			()	// jumper cerrado, eeprom a default
{
	// valores default
	byte Key_Light_Val_Def	= 255;	// valor default de keylight
	byte Ext_Light_Def		= 255;	// valor default ext light
	byte CH_DMX_Val_Def		= 0;	// valor default de canales DMX
	byte Initial_Bank_Def	= 1;	// banco inicial de memoria a cargar
	byte Canal_Actual_Def 	= 1;
	byte Backlight_Def		= 255;	
	byte Contrast_Def		= 150;

	lcd.clear ();
	lcd.setCursor(1, 1);
	lcd.print("EEPROM Default:");

		// canales DMX
	for (int ch = 0; ch <= EEPROM_Limit; ch ++)
	{
		EEPROM.write(ch, CH_DMX_Val_Def);
		lcd.setCursor(16, 1);
		lcd.print(ch);
	}

		// backlight
	EEPROM.write(BackLight_Add, Backlight_Def);

<<<<<<< HEAD
		// contraste
	EEPROM.write(Contrast_Add,  Contrast_Def);

		// Bank init
	EEPROM.write(Bank_Init_Add, Initial_Bank_Def);

		// Key light
	EEPROM.write(Key_Light_Add, Key_Light_Val_Def);

		// Light Ext
	EEPROM.write(Light_Ext_Add, Ext_Light_Def);

		// canal actual
	EEPROM.write(Canal_Actual_1_Add, Canal_Actual_Def);
	EEPROM.write(Canal_Actual_2_Add, 0);

	lcd.clear ();
	lcd.setCursor(1, 0);
	lcd.print("EEPROM Default ok!");
	lcd.setCursor(3, 2);
	lcd.print("Remove jumper");
	lcd.setCursor(4, 3);
	lcd.print("and reset!");

	while(1);
}

void Init_Back_Light 			()	// lee y aplica el ultimo estado del backlight
=======
			// backlight
		EEPROM.write(BackLight_Add, Backlight_Def);

			// contraste
		EEPROM.write(Contrast_Add,  Contrast_Def);

			// Bank init
		EEPROM.write(Bank_Init_Add, Initial_Bank_Def);

			// Key light
		EEPROM.write(Key_Light_Add, Key_Light_Val_Def);

			// Light Ext
		EEPROM.write(Light_Ext_Add, Ext_Light_Def);

			// canal actual
		EEPROM.write(Canal_Actual_1_Add, Canal_Actual_Def);
		EEPROM.write(Canal_Actual_2_Add, 0);

		lcd.clear ();
		lcd.setCursor(1, 0);
		lcd.print("EEPROM Default ok!");
		lcd.setCursor(3, 2);
		lcd.print("Remove jumper");
		lcd.setCursor(4, 3);
		lcd.print("and reset!");

		while(1);
	}
}

void Back_Light_Init 			()	// lee y aplica el ultimo estado del backlight
>>>>>>> master
{	
	// dimmer de pantalla
	for (int dim = 0; dim <= Back_Light_Value; dim ++)
	{
		analogWrite(Back_Light_PWM, dim);
		delay(3);	// aqui el retardo para el dimmer
	}	

	if (Back_Light_Value == 0)
	{
		Back_Key_Light_On_Off = 0;
	}

	if (Back_Light_Value > 0)
	{
		Back_Key_Light_On_Off = 1;
	}
}

<<<<<<< HEAD
void Init_Contrast 				()	// lee y aplica el ultimo estado del contrast
=======
void Contrast_Init 				()	// lee y aplica el ultimo estado del contrast
>>>>>>> master
{
	if (Contrast_Value < 60)
	{
		Contrast_Value = 150;
	}

	analogWrite(Contrast_PWM, Contrast_Value);
}

void Back_light_Key_light_En 	()	// encender back y key desde teclado
{
	long delay_dimmer = 1;
	
		// encender
	if (Back_Key_Light_On_Off == 0)									// si esta apagada encenderla
	{
			// si el valor es 0 lo encendemos de todos modos
		if (Back_Light_Value == 0)
		{
			for (int contar = 0; contar <= 127; contar ++)
			{
				analogWrite(Back_Light_PWM, contar);		// aqui el valor a encender en el caso que se haya establecido apagado
				delay(delay_dimmer);
			}
		}

		if (Key_Light_Value == 0)
		{
			for (int contar = 0; contar <= 127; contar ++)
			{
				analogWrite(Key_Light_PWM, 127);			// aqui el valor a encender en el caso que se haya establecido apagado
				delay(delay_dimmer);
			}
		}
		
			// solo encender
		if (Back_Light_Value > 0)
		{
			for (int contar = 0; contar <= Back_Light_Value; contar ++)
			{
				analogWrite(Back_Light_PWM, contar);		// encender con el valor de la eeprom
				delay(delay_dimmer);
			}
		}

		if (Key_Light_Value > 0)
		{
			for (int contar = 0; contar <= Back_Light_Value; contar ++)
			{
				analogWrite(Key_Light_PWM, Key_Light_Value);// encender con el valor de la eeprom
				delay(delay_dimmer);
			}
		}

		Back_Key_Light_On_Off = 1;
		goto salida;
	}
	
	// apagar
	if (Back_Key_Light_On_Off == 1)									// si esta encendida apagarla
	{
		for (int contar = Back_Light_Value; contar != 0; contar --)
		{
			analogWrite(Back_Light_PWM, contar);
			delay(delay_dimmer);
		}

		analogWrite(Back_Light_PWM, 0);
		analogWrite(Key_Light_PWM, 0);
		Back_Key_Light_On_Off = 0;
	}

	salida:

	delay(300);												// para impedir repeticion del comando
}

void External_light_En 			()	// encender back y key desde teclado
{
	long delay_dimmer = 1;
	
		// encender
	if (External_Light_On_Off == 0)							// si esta apagada encenderla
	{
			// si el valor es 0 lo encendemos de todos modos
		if (Light_Ext_Value == 0)
		{
			for (int contar = 0; contar <= 127; contar ++)
			{
				analogWrite(Light_PWM, contar);		// aqui el valor a encender en el caso que se haya establecido apagado
				delay(delay_dimmer);
			}
		}
		
			// solo encender
		if (Light_Ext_Value > 0)
		{
			for (int contar = 0; contar <= Light_Ext_Value; contar ++)
			{
				analogWrite(Light_PWM, contar);		// encender con el valor de la eeprom
				delay(delay_dimmer);
			}
		}

		External_Light_On_Off = 1;
		goto salida;
	}
	
	// apagar
	if (External_Light_On_Off == 1)									// si esta encendida apagarla
	{
		for (int contar = Light_Ext_Value; contar != 0; contar --)
		{
			analogWrite(Light_PWM, contar);
			delay(delay_dimmer);
		}

		analogWrite(Light_PWM, 0);
		External_Light_On_Off = 0;
	}
<<<<<<< HEAD

	salida:

	delay(300);												// para impedir repeticion del comando
}

=======

	salida:

	delay(300);												// para impedir repeticion del comando
}

>>>>>>> master
void GUI_Licence 				()	// imprimir licencia LCD
{
	int retardo = 4000;
	
	lcd.clear 		();
	lcd.blink 		();
	lcd.setCursor	(6, 0);
	lcd.print 		("Create by");
	lcd.setCursor	(3, 1);
	lcd.print 		("Daniel Becerril");
	lcd.setCursor 	(4, 2);
	lcd.print 		("goo.gl/7RsKo1");
	lcd.setCursor 	(0, 3);
	lcd.print 		("daniel3514@gmail.com");
	lcd.setCursor 	(19, 0);

		// lectura del boton centro
	while (digitalRead(Enc_Center) == HIGH);

	lcd.clear  		();
	lcd.noBlink		();
	lcd.setCursor 	(0, 0);
	lcd.print 		(" This program is");
	lcd.setCursor 	(0, 1);
	lcd.print 		("distributed in the");
	lcd.setCursor 	(0, 2);
	lcd.print 		("hope that it will be");
	lcd.setCursor 	(0, 3);
	lcd.print 		("useful, but");

	delay(retardo);

	lcd.clear 		();
	lcd.setCursor 	(0, 0);
	lcd.print 		("WITHOUT ANY WARRANTY");
	lcd.setCursor 	(0, 1);
	lcd.print 		("without even the");
	lcd.setCursor 	(0, 2);
	lcd.print 		("implied warranty of");
	lcd.setCursor 	(0, 3);
	lcd.print 		("MERCHANTABILITY of");

	delay(retardo);

	lcd.clear 		();
	lcd.setCursor 	(0, 0);
	lcd.print 		("FITNESS FOR A");
	lcd.setCursor 	(0, 1);
	lcd.print 		("PARTICULAR PORPUSE.");
	lcd.setCursor 	(0, 2);
	lcd.print 		("    This is free ");
	lcd.setCursor 	(0, 3);
	lcd.print 		("software and you are");

	delay(retardo);

	lcd.clear 		();
	lcd.setCursor 	(0, 0);
	lcd.print 		("welcome to");
	lcd.setCursor 	(0, 1);
	lcd.print 		("redistribute it");
	lcd.setCursor 	(0, 2);
	lcd.print 		("under certain");
	lcd.setCursor  	(0, 3);
	lcd.print 		("conditions");

	delay(retardo);

	lcd.clear 		();
	lcd.setCursor 	(0, 0);
	lcd.print 		("See the GNU GENERAL");
	lcd.setCursor 	(0, 1);
	lcd.print 		("PUBLIC LICENCE");
	lcd.setCursor 	(0, 2);
	lcd.print 		("for more details...");

	delay(retardo);
}

void GUI_About 					()	// imprimir about LCD
{
	byte Firm_Ver_Ent = 2;	// version firmware ----------------------------
<<<<<<< HEAD
	byte Firm_Ver_Dec = 1;
=======
	byte Firm_Ver_Dec = 0;
>>>>>>> master
	byte Hard_Ver_Ent = 0;	// version hardware ----------------------------
	byte Hard_Ver_Dec = 7;
	byte Key_Light_Value 	= EEPROM.read(Key_Light_Add);
	byte Back_Light_Value 	= EEPROM.read(BackLight_Add);
	
	lcd.clear ();

	analogWrite(Key_Light_PWM, 0);
	analogWrite(Back_Light_PWM, 0);

	for (int numero = 0; numero <= 512; numero ++)	// efecto binario en lcd
	{
			// binario
		lcd.print (numero, BIN);
			// key light
		if (Key_Light_Value > 0)
		{
			if (numero <= 255)
			{
				if (numero <= Key_Light_Value)
				{
					analogWrite(Key_Light_PWM, numero);
				}
			}
		}
			// back light
		if (Back_Light_Value > 0)
		{
			if (numero <= 255)
			{
				if (numero <= Back_Light_Value)
				{
					analogWrite(Back_Light_PWM, numero);
				}
			}
		}
	}
	
	lcd.clear  		();
	lcd.blink 		();
	lcd.setCursor	(3, 0);
	lcd.print 		("Arduino DMX-512");
	lcd.setCursor 	(1, 1);
	lcd.print 		("Tester & Controller");

		// Firmware
	lcd.setCursor 	(0, 3);
	lcd.print 		("Firm v");
	lcd.print 		(Firm_Ver_Ent);
	lcd.print 		(".");
	lcd.print 		(Firm_Ver_Dec);

		// Hardware
	lcd.setCursor 	(11, 3);
	lcd.print 		("Hard v");
	lcd.print 		(Hard_Ver_Ent);
	lcd.print 		(".");
	lcd.print 		(Hard_Ver_Dec);

		// bank
	lcd.setCursor 	(9, 2);
	lcd.write 		(3);	// carater file

	if (Universo_Actual == 0)
	{
		lcd.print 	("-");
	}
	else
	{
		lcd.print(Universo_Actual);
	}

	lcd.setCursor(10, 2);	// Blink

		// lectura del boton centro
	while (digitalRead(Enc_Center) == HIGH);

	delay (300);			// rebote de boton

	lcd.clear 		();
	lcd.setCursor 	(0, 0);
	lcd.print 		("Open Source License");
	lcd.setCursor 	(0, 1);
	lcd.print 		("Firm: GNU GPL v3");
	lcd.setCursor 	(0, 2);
	lcd.print 		("Hard: OSHW    v1");
	lcd.setCursor 	(0, 3);
	lcd.print 		("Wiki: goo.gl/7RsKo1");
	lcd.setCursor 	(2, 1);
	lcd.setCursor	(19, 1);

		// lectura del boton centro
	while (digitalRead(Enc_Center) == HIGH);

	delay (300);			// rebote de boton
	lcd.noBlink 	();
}

void Multi_Matrix 				(int inicial)	// dibujar matriz de universo dmx
{
	// matrix 1
	Numeric_Write (DMX_Values[inicial], 1, 1);
	Numeric_Write (DMX_Values[inicial + 1], 5, 1);
	Numeric_Write (DMX_Values[inicial + 2], 9, 1);
	Numeric_Write (DMX_Values[inicial + 3], 13, 1);
	Numeric_Write (DMX_Values[inicial + 4], 17, 1);

		// matrix 2
	Numeric_Write (DMX_Values[inicial + 5], 1, 2);
	Numeric_Write (DMX_Values[inicial + 6], 5, 2);
	Numeric_Write (DMX_Values[inicial + 7], 9, 2);
	Numeric_Write (DMX_Values[inicial + 8], 13, 2);
	Numeric_Write (DMX_Values[inicial + 9], 17, 2);

		// matrix 3
	Numeric_Write (DMX_Values[inicial + 10], 1, 3);
	Numeric_Write (DMX_Values[inicial + 11], 5, 3);
	Numeric_Write (DMX_Values[inicial + 12], 9, 3);
	Numeric_Write (DMX_Values[inicial + 13], 13, 3);
	Numeric_Write (DMX_Values[inicial + 14], 17, 3);
}

void GUI_Control_Matrix 		()	// control en matriz
{
	inicio:

	int Inicial = Canal_Actual;

	lcd.clear 		();

	lcd.setCursor 	(0, 0);
	lcd.print 		("c---");

	lcd.setCursor 	(16, 0);
	lcd.print 		("-");

	lcd.setCursor 	(6, 0);
	lcd.write 		(3);	// caracter: 1 on, 2 off, 3 file, 4 exit

	lcd.setCursor 	(10, 0);
	lcd.write 		(4);	// caracter: 1 on, 2 off, 3 file, 4 exit
	
	Numerico_Print(13, 0, Inicial, 512, 1);			// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
	Numerico_Print(17, 0, Inicial + 14, 512, 1);	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)

	lcd.setCursor 	(7, 0);

	if (Universo_Actual == 0)
	{
		lcd.print 	("-");
	}
	else
	{
		lcd.print(Universo_Actual);
	}

		// dibujar matriz
	Multi_Matrix (Inicial);	

		// borrar datos previos en el indice
	Cursor_Index_Clear();

	// establecer el indice

	Cursor_Index[5][0] 	= 1;	// memory
	Cursor_Index[9][0] 	= 2;	// exit

		// col 1
	Cursor_Index[0][1]	= 5;	// y x
	Cursor_Index[0][2] 	= 10;	// y x
	Cursor_Index[0][3] 	= 15;	// y x

		// col 2
	Cursor_Index[4][1] 	= 6;	// y x
	Cursor_Index[4][2] 	= 11;	// y x
	Cursor_Index[4][3] 	= 16;	// y x

		// col 3
	Cursor_Index[8][1] 	= 7;	// y x
	Cursor_Index[8][2] 	= 12;	// y x
	Cursor_Index[8][3] 	= 17;	// y x

		// col 4
	Cursor_Index[12][0] = 3;	// y x
	Cursor_Index[12][1] = 8;	// y x
	Cursor_Index[12][2]	= 13;	// y x
	Cursor_Index[12][3]	= 18;	// y x

		// col 5
	Cursor_Index[16][0] = 4;	// y x
	Cursor_Index[16][1] = 9;	// y x
	Cursor_Index[16][2]	= 14;	// y x
	Cursor_Index[16][3]	= 19;	// y x

	Cursor_Index_Pos = 1;	// posicion inicial

	navegacion:

		// iniciar navegacion y evaluar el index seleccionado
	Navegar(1, Inicial);	// actualiza Cursor_Index_Pos

		// pintar gion de ventana de canales
	lcd.setCursor 	(16, 0);
	lcd.print 		("-");

	int valor_nuevo = 0;

	switch (Cursor_Index_Pos)
	{
			// memoria
		case 1:
			GUI_Memory();
			goto inicio;
			break;

			// Salida
		case 2:
			goto salir;;
			break;

			// banco inicial
		case 3:
			valor_nuevo = Numerico_Write(1, 498, 13, 0, 1, Inicial);				// int  Numerico_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, int num_ant)

				// menor o igual al limites
			if (valor_nuevo <= 498)							// poner limite max
			{
				Inicial = valor_nuevo;
			}

				// encoder
			if (valor_nuevo == 499)							// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(1, 498, 13, 0, 1, Inicial);	// int  Numerico_Enc_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, long num_ant)
					
					if (valor_nuevo > 498)					// poner limite max
					{
						break; 								// enter
					}

					Inicial = valor_nuevo;
						// dibujar matriz
					Multi_Matrix (Inicial);	
					Numerico_Print(17, 0, Inicial + 14, 512, 1);	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
				}

					// acomodar numero 	
				Numerico_Print(13, 0, Inicial, 498, 1);		// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

				// ubicar
			if (valor_nuevo == 500)							// poner limite max + 2
			{
				Numerico_Print(13, 0, Inicial, 512, 1);		// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
				Ubicar(1, 1, DMX_Values[Inicial]);			// void Ubicar(byte y, byte x, byte val_ant)
			}

				// dibujar matriz
			Multi_Matrix (Inicial);	
			Numerico_Print(17, 0, Inicial + 14, 512, 1);	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)

			Canal_Actual = Inicial;

			break;

		case 4:
			valor_nuevo = Numerico_Write(15, 512, 17, 0, 1, Inicial + 14);			// int  Numerico_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, int num_ant)

				// menor o igual al limites
			if (valor_nuevo <= 512)							// poner limite max
			{
				Inicial = valor_nuevo - 14;
			}

				// encoder
			if (valor_nuevo == 513)							// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(15, 512, 17, 0, 1, Inicial + 14);	// int  Numerico_Enc_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, long num_ant)
					
					if (valor_nuevo > 512)					// poner limite max
					{
						break; 								// enter
					}

					Inicial = valor_nuevo - 14;
						// dibujar matriz
					Multi_Matrix (Inicial);	
					Numerico_Print(13, 0, Inicial, 512, 1);	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
				}

					// acomodar numero 	
				Numerico_Print(17, 0, Inicial, 512, 1);		// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

				// ubicar
			if (valor_nuevo == 514)							// poner limite max + 2
			{
				Numerico_Print(17, 0, Inicial + 14, 512, 1);		// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
				Ubicar(17, 3, DMX_Values[Inicial + 14]);			// void Ubicar(byte y, byte x, byte val_ant)
			}

				// dibujar matriz
			Multi_Matrix (Inicial);	
			Numerico_Print(17, 0, Inicial + 14, 512, 1);			// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)

			Canal_Actual = Inicial;

			break;

			// 1
		case 5:
			valor_nuevo = Numerico_Write(0, 255, 1, 1, 1, DMX_Values[Inicial]);

				// menor o igual al limites
			if (valor_nuevo <= 255)					// poner limite max
			{
				ArduinoDmx0.TxBuffer[Inicial - 1] = valor_nuevo;
				DMX_Values[Inicial] = valor_nuevo;
			}

				// encoder
			if (valor_nuevo == 256)					// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(0, 255, 1, 1, 1, DMX_Values[Inicial]);
					
					if (valor_nuevo > 255)			// poner limite max
					{
						break; 						// enter
					}

					ArduinoDmx0.TxBuffer[Inicial - 1] = valor_nuevo;
					DMX_Values[Inicial] = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(1, 1, DMX_Values[Inicial], 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

				// ubicar
			if (valor_nuevo == 257)					// poner limite max + 2
			{
				Ubicar(1, 1, DMX_Values[Inicial]);	// void Ubicar(byte y, byte x, num ant)
			}

			Canal_Actual = Inicial;

			break;

			// 2
		case 6:
			valor_nuevo = Numerico_Write(0, 255, 5, 1, 1, DMX_Values[Inicial + 1]);

				// menor o igual al limites
			if (valor_nuevo <= 255)					// poner limite max
			{
				ArduinoDmx0.TxBuffer[Inicial + 1 - 1] = valor_nuevo;
				DMX_Values[Inicial + 1] = valor_nuevo;
			}

				// encoder
			if (valor_nuevo == 256)					// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(0, 255, 5, 1, 1, DMX_Values[Inicial + 1]);
					
					if (valor_nuevo > 255)			// poner limite max
					{
						break; 						// enter
					}

					ArduinoDmx0.TxBuffer[Inicial + 1 - 1] = valor_nuevo;
					DMX_Values[Inicial + 1] = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(5, 1, DMX_Values[Inicial + 1], 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

				// ubicar
			if (valor_nuevo == 257)					// poner limite max + 2
			{
				Ubicar(5, 1, DMX_Values[Inicial + 1]);	// void Ubicar(byte y, byte x, num ant)
			}

			Canal_Actual = Inicial + 1;

			break;

			// 3
		case 7:
			valor_nuevo = Numerico_Write(0, 255, 9, 1, 1, DMX_Values[Inicial + 2]);

				// menor o igual al limites
			if (valor_nuevo <= 255)					// poner limite max
			{
				ArduinoDmx0.TxBuffer[Inicial + 2 - 1] = valor_nuevo;
				DMX_Values[Inicial + 2] = valor_nuevo;
			}

				// encoder
			if (valor_nuevo == 256)					// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(0, 255, 9, 1, 1, DMX_Values[Inicial + 2]);
					
					if (valor_nuevo > 255)			// poner limite max
					{
						break; 						// enter
					}

					ArduinoDmx0.TxBuffer[Inicial + 2 - 1] = valor_nuevo;
					DMX_Values[Inicial + 2] = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(9, 1, DMX_Values[Inicial + 2], 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

				// ubicar
			if (valor_nuevo == 257)					// poner limite max + 2
			{
				Ubicar(9, 1, DMX_Values[Inicial + 2]);	// void Ubicar(byte y, byte x, num ant)
			}

			Canal_Actual = Inicial + 2;

			break;

			// 4
		case 8:
			valor_nuevo = Numerico_Write(0, 255, 13, 1, 1, DMX_Values[Inicial + 3]);

				// menor o igual al limites
			if (valor_nuevo <= 255)					// poner limite max
			{
				ArduinoDmx0.TxBuffer[Inicial + 3 - 1] = valor_nuevo;
				DMX_Values[Inicial + 3] = valor_nuevo;
			}

				// encoder
			if (valor_nuevo == 256)					// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(0, 255, 13, 1, 1, DMX_Values[Inicial + 3]);
					
					if (valor_nuevo > 255)			// poner limite max
					{
						break; 						// enter
					}

					ArduinoDmx0.TxBuffer[Inicial + 3 - 1] = valor_nuevo;
					DMX_Values[Inicial + 3] = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(13, 1, DMX_Values[Inicial + 3], 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

				// ubicar
			if (valor_nuevo == 257)					// poner limite max + 2
			{
				Ubicar(13, 1, DMX_Values[Inicial + 3]);	// void Ubicar(byte y, byte x, num ant)
			}

			Canal_Actual = Inicial + 3;

			break;

			// 5
		case 9:
			valor_nuevo = Numerico_Write(0, 255, 17, 1, 1, DMX_Values[Inicial + 4]);

				// menor o igual al limites
			if (valor_nuevo <= 255)					// poner limite max
			{
				ArduinoDmx0.TxBuffer[Inicial + 4 - 1] = valor_nuevo;
				DMX_Values[Inicial + 4] = valor_nuevo;
			}

				// encoder
			if (valor_nuevo == 256)					// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(0, 255, 17, 1, 1, DMX_Values[Inicial + 4]);
					
					if (valor_nuevo > 255)			// poner limite max
					{
						break; 						// enter
					}

					ArduinoDmx0.TxBuffer[Inicial + 4 - 1] = valor_nuevo;
					DMX_Values[Inicial + 4] = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(17, 1, DMX_Values[Inicial + 4], 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

				// ubicar
			if (valor_nuevo == 257)					// poner limite max + 2
			{
				Ubicar(17, 1, DMX_Values[Inicial + 4]);	// void Ubicar(byte y, byte x, num ant)
			}

			Canal_Actual = Inicial + 4;

			break;

			// 6
		case 10:
			valor_nuevo = Numerico_Write(0, 255, 1, 2, 1, DMX_Values[Inicial + 5]);

				// menor o igual al limites
			if (valor_nuevo <= 255)					// poner limite max
			{
				ArduinoDmx0.TxBuffer[Inicial + 5 - 1] = valor_nuevo;
				DMX_Values[Inicial + 5] = valor_nuevo;
			}

				// encoder
			if (valor_nuevo == 256)					// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(0, 255, 1, 2, 1, DMX_Values[Inicial + 5]);
					
					if (valor_nuevo > 255)			// poner limite max
					{
						break; 						// enter
					}

					ArduinoDmx0.TxBuffer[Inicial + 5 - 1] = valor_nuevo;
					DMX_Values[Inicial + 5] = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(1, 2, DMX_Values[Inicial + 5], 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

				// ubicar
			if (valor_nuevo == 257)					// poner limite max + 2
			{
				Ubicar(1, 2, DMX_Values[Inicial + 5]);	// void Ubicar(byte y, byte x, num ant)
			}

			Canal_Actual = Inicial + 5;

			break;

			// 7
		case 11:
			valor_nuevo = Numerico_Write(0, 255, 5, 2, 1, DMX_Values[Inicial + 6]);

				// menor o igual al limites
			if (valor_nuevo <= 255)					// poner limite max
			{
				ArduinoDmx0.TxBuffer[Inicial + 6 - 1] = valor_nuevo;
				DMX_Values[Inicial + 6] = valor_nuevo;
			}

				// encoder
			if (valor_nuevo == 256)					// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(0, 255, 5, 2, 1, DMX_Values[Inicial + 6]);
					
					if (valor_nuevo > 255)			// poner limite max
					{
						break; 						// enter
					}

					ArduinoDmx0.TxBuffer[Inicial + 6 - 1] = valor_nuevo;
					DMX_Values[Inicial + 6] = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(5, 2, DMX_Values[Inicial + 6], 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

				// ubicar
			if (valor_nuevo == 257)					// poner limite max + 2
			{
				Ubicar(5, 2, DMX_Values[Inicial + 6]);	// void Ubicar(byte y, byte x, num ant)
			}

			Canal_Actual = Inicial + 6;

			break;

			// 8
		case 12:
			valor_nuevo = Numerico_Write(0, 255, 9, 2, 1, DMX_Values[Inicial + 7]);

				// menor o igual al limites
			if (valor_nuevo <= 255)					// poner limite max
			{
				ArduinoDmx0.TxBuffer[Inicial + 7 - 1] = valor_nuevo;
				DMX_Values[Inicial + 7] = valor_nuevo;
			}

				// encoder
			if (valor_nuevo == 256)					// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(0, 255, 9, 2, 1, DMX_Values[Inicial + 7]);
					
					if (valor_nuevo > 255)			// poner limite max
					{
						break; 						// enter
					}

					ArduinoDmx0.TxBuffer[Inicial + 7 - 1] = valor_nuevo;
					DMX_Values[Inicial + 7] = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(9, 2, DMX_Values[Inicial + 7], 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

				// ubicar
			if (valor_nuevo == 257)					// poner limite max + 2
			{
				Ubicar(9, 2, DMX_Values[Inicial + 7]);	// void Ubicar(byte y, byte x, num ant)
			}

			Canal_Actual = Inicial + 7;

			break;

			// 9
		case 13:
			valor_nuevo = Numerico_Write(0, 255, 13, 2, 1, DMX_Values[Inicial + 8]);

				// menor o igual al limites
			if (valor_nuevo <= 255)					// poner limite max
			{
				ArduinoDmx0.TxBuffer[Inicial + 8 - 1] = valor_nuevo;
				DMX_Values[Inicial + 8] = valor_nuevo;
			}

				// encoder
			if (valor_nuevo == 256)					// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(0, 255, 13, 2, 1, DMX_Values[Inicial + 8]);
					
					if (valor_nuevo > 255)			// poner limite max
					{
						break; 						// enter
					}

					ArduinoDmx0.TxBuffer[Inicial + 8 - 1] = valor_nuevo;
					DMX_Values[Inicial + 8] = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(13, 2, DMX_Values[Inicial + 8], 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

				// ubicar
			if (valor_nuevo == 257)					// poner limite max + 2
			{
				Ubicar(13, 2, DMX_Values[Inicial + 8]);	// void Ubicar(byte y, byte x, num ant)
			}

			Canal_Actual = Inicial + 8;

			break;

			// 10
		case 14:
			valor_nuevo = Numerico_Write(0, 255, 17, 2, 1, DMX_Values[Inicial + 9]);

				// menor o igual al limites
			if (valor_nuevo <= 255)					// poner limite max
			{
				ArduinoDmx0.TxBuffer[Inicial + 9 - 1] = valor_nuevo;
				DMX_Values[Inicial + 9] = valor_nuevo;
			}

				// encoder
			if (valor_nuevo == 256)					// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(0, 255, 17, 2, 1, DMX_Values[Inicial + 9]);
					
					if (valor_nuevo > 255)			// poner limite max
					{
						break; 						// enter
					}

					ArduinoDmx0.TxBuffer[Inicial + 9 - 1] = valor_nuevo;
					DMX_Values[Inicial + 9] = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(17, 2, DMX_Values[Inicial + 9], 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

				// ubicar
			if (valor_nuevo == 257)					// poner limite max + 2
			{
				Ubicar(17, 2, DMX_Values[Inicial + 9]);	// void Ubicar(byte y, byte x, num ant)
			}

			Canal_Actual = Inicial + 9;

			break;

			// 11
		case 15:
			valor_nuevo = Numerico_Write(0, 255, 1, 3, 1, DMX_Values[Inicial + 10]);

				// menor o igual al limites
			if (valor_nuevo <= 255)					// poner limite max
			{
				ArduinoDmx0.TxBuffer[Inicial + 10 - 1] = valor_nuevo;
				DMX_Values[Inicial + 10] = valor_nuevo;
			}

				// encoder
			if (valor_nuevo == 256)					// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(0, 255, 1, 3, 1, DMX_Values[Inicial + 10]);
					
					if (valor_nuevo > 255)			// poner limite max
					{
						break; 						// enter
					}

					ArduinoDmx0.TxBuffer[Inicial + 10 - 1] = valor_nuevo;
					DMX_Values[Inicial + 10] = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(1, 3, DMX_Values[Inicial + 10], 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

				// ubicar
			if (valor_nuevo == 257)					// poner limite max + 2
			{
				Ubicar(1, 3, DMX_Values[Inicial + 10]);	// void Ubicar(byte y, byte x, num ant)
			}

			Canal_Actual = Inicial + 10;

			break;

			// 12
		case 16:
			valor_nuevo = Numerico_Write(0, 255, 5, 3, 1, DMX_Values[Inicial + 11]);

				// menor o igual al limites
			if (valor_nuevo <= 255)					// poner limite max
			{
				ArduinoDmx0.TxBuffer[Inicial + 11 - 1] = valor_nuevo;
				DMX_Values[Inicial + 11] = valor_nuevo;
			}

				// encoder
			if (valor_nuevo == 256)					// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(0, 255, 5, 3, 1, DMX_Values[Inicial + 11]);
					
					if (valor_nuevo > 255)			// poner limite max
					{
						break; 						// enter
					}

					ArduinoDmx0.TxBuffer[Inicial + 11 - 1] = valor_nuevo;
					DMX_Values[Inicial + 11] = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(5, 3, DMX_Values[Inicial + 11], 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

				// ubicar
			if (valor_nuevo == 257)					// poner limite max + 2
			{
				Ubicar(5, 3, DMX_Values[Inicial + 11]);	// void Ubicar(byte y, byte x, num ant)
			}

			Canal_Actual = Inicial + 11;

			break;

			// 13
		case 17:
			valor_nuevo = Numerico_Write(0, 255, 9, 3, 1, DMX_Values[Inicial + 12]);

				// menor o igual al limites
			if (valor_nuevo <= 255)					// poner limite max
			{
				ArduinoDmx0.TxBuffer[Inicial + 12 - 1] = valor_nuevo;
				DMX_Values[Inicial + 12] = valor_nuevo;
			}

				// encoder
			if (valor_nuevo == 256)					// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(0, 255, 9, 3, 1, DMX_Values[Inicial + 12]);
					
					if (valor_nuevo > 255)			// poner limite max
					{
						break; 						// enter
					}

					ArduinoDmx0.TxBuffer[Inicial + 12 - 1] = valor_nuevo;
					DMX_Values[Inicial + 12] = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(9, 3, DMX_Values[Inicial + 12], 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

				// ubicar
			if (valor_nuevo == 257)					// poner limite max + 2
			{
				Ubicar(9, 3, DMX_Values[Inicial + 12]);	// void Ubicar(byte y, byte x, num ant)
			}

			Canal_Actual = Inicial + 12;

			break;

			// 14
		case 18:
			valor_nuevo = Numerico_Write(0, 255, 13, 3, 1, DMX_Values[Inicial + 13]);

				// menor o igual al limites
			if (valor_nuevo <= 255)					// poner limite max
			{
				ArduinoDmx0.TxBuffer[Inicial + 13 - 1] = valor_nuevo;
				DMX_Values[Inicial + 13] = valor_nuevo;
			}

				// encoder
			if (valor_nuevo == 256)					// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(0, 255, 13, 3, 1, DMX_Values[Inicial + 13]);
					
					if (valor_nuevo > 255)			// poner limite max
					{
						break; 						// enter
					}

					ArduinoDmx0.TxBuffer[Inicial + 13 - 1] = valor_nuevo;
					DMX_Values[Inicial + 13] = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(13, 3, DMX_Values[Inicial + 13], 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

				// ubicar
			if (valor_nuevo == 257)					// poner limite max + 2
			{
				Ubicar(13, 3, DMX_Values[Inicial + 13]);	// void Ubicar(byte y, byte x, num ant)
			}

			Canal_Actual = Inicial + 13;

			break;

			// 15
		case 19:
			valor_nuevo = Numerico_Write(0, 255, 17, 3, 1, DMX_Values[Inicial + 14]);

				// menor o igual al limites
			if (valor_nuevo <= 255)					// poner limite max
			{
				ArduinoDmx0.TxBuffer[Inicial + 14 - 1] = valor_nuevo;
				DMX_Values[Inicial + 14] = valor_nuevo;
			}

				// encoder
			if (valor_nuevo == 256)					// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(0, 255, 17, 3, 1, DMX_Values[Inicial + 14]);
					
					if (valor_nuevo > 255)			// poner limite max
					{
						break; 						// enter
					}

					ArduinoDmx0.TxBuffer[Inicial + 14 - 1] = valor_nuevo;
					DMX_Values[Inicial + 14] = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(17, 3, DMX_Values[Inicial + 14], 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

				// ubicar
			if (valor_nuevo == 257)					// poner limite max + 2
			{
				Ubicar(17, 3, DMX_Values[Inicial + 14]);	// void Ubicar(byte y, byte x, num ant)
			}

			Canal_Actual = Inicial + 14;

			break;
	}

	goto navegacion;

	salir:

		// guardar canal actual
  	Canal_Actual_EEPROM_Save();
}

void GUI_Memory_Init 			()	// inicial de memoria
{
	inicio:
	
	int salir = 0;
  	lcd.clear ();

  		// Texto
  	lcd.setCursor 	(0, 0);
  	lcd.print 		("Initial Memory:");
  	lcd.setCursor 	(2, 2);
  	lcd.print 		("Empty");
  	lcd.setCursor 	(9, 2);
  	lcd.print 		("Load");
  	lcd.setCursor 	(15, 2);
  	lcd.print 		("Clear");

  		// bank
  	lcd.setCursor 	(18, 0);
  	lcd.write 		(3);	// carater file

  	if (Universo_Actual == 0)
  	{
    	lcd.print 	("-");
  	}
  	else
  	{
    	lcd.print(Universo_Actual);
  	}

  		// borrar datos previos en el indice
	Cursor_Index_Clear();

		// establecer el indice
	Cursor_Index[1] [2] = 1;		// y x 	// Empty
	Cursor_Index[8] [2] = 2;		// y x 	// Load
	Cursor_Index[14][2]	= 3;		// y x 	// Clear

		// navegacion
	Navegar(0, 0);	// actualiza Cursor_Index_Pos
	
	switch (Cursor_Index_Pos)
	{
		case 1:

			break;

		case 2:
			salir = EEPROM_Load();

    		if (salir == 1)
    		{
      			goto inicio;
    		}

			break;

		case 3:
			salir = EEPROM_Clear();

    		if (salir == 1)
    		{
      			goto inicio;
    		}

			break;
	}

<<<<<<< HEAD
	GUI_Menu_1();
=======
	GUI_Control_Options();
>>>>>>> master
}

int  GUI_Memory_Bank 			(byte Opcion)
{
	// regresa 1 si se selecciona salir, de lo contrario 0
  	// recibe opcion para pintar en la pantalla lo que se selecciono

  	int salir = 0;

  	lcd.clear ();
  	delay (200);	// retardo para no seleccionar inmediatamente la opcion del banco

  		// Texto
  	lcd.setCursor 	(6, 0);
  	lcd.print 		("Memory");

  	lcd.setCursor 	(18, 0);
  	lcd.write 		(byte(3));	// caracter file

  	lcd.setCursor 	(1, 1);
  	lcd.print 		("Bank1  Bank4  Bank7");

  	lcd.setCursor 	(1, 2);
  	lcd.print 		("Bank2  Bank5  Bank8");

  	lcd.setCursor 	(1, 3);
  	lcd.print 		("Bank3  Bank6");

  	lcd.setCursor 	(19, 3);
  	lcd.write 		(byte(4));	// caracter exit

  	switch (Opcion)
  	{
    	case 1:
      		lcd.setCursor (1, 0);
      		lcd.print("Save");
      		break;

    	case 2:
      		lcd.setCursor (1, 0);
      		lcd.print("Load");
      		break;

    	case 3:
      		lcd.setCursor (0, 0);
      		lcd.print("Clear");
      		break;
  	}

  		// Universo Actual
  	lcd.setCursor (19, 0);

  	if (Universo_Actual == 0)
  	{
    	lcd.print("-");
  	}
  	else
  	{
    	lcd.print(Universo_Actual);
  	}

 		// borrar datos previos en el indice
	Cursor_Index_Clear();

  		// establecer el indice
  	Cursor_Index[0][1]   = 1;	// Bank 1 	// y x
  	Cursor_Index[0][2]   = 2;  	// Bank 2
  	Cursor_Index[0][3]   = 3;	// Bank 3
  	Cursor_Index[7][1]   = 4;	// Bank 4
  	Cursor_Index[7][2]   = 5;	// Bank 5
  	Cursor_Index[7][3]   = 6;	// Bank 6
  	Cursor_Index[14][1]  = 7;	// Bank 7
  	Cursor_Index[14][2]  = 8;	// Bank 8
  	Cursor_Index[18][3]  = 9;	// Exit
	
	Cursor_Index_Pos = 1;

		// iniciar navegacion y evaluar el index seleccionado
	Navegar(0, 0);	// actualiza Cursor_Index_Pos
  
  	switch (Cursor_Index_Pos)
	{
			// Bank 1
		case 1:
    		Universo_Actual = 1;
   	 		break;

  			// Bank 2
   	 	case 2:
  			Universo_Actual = 2;
    		break;

	  		// Bank 3
	  	case 3:
  			Universo_Actual = 3;
    		break;

    		// Bank 4
	  	case 4:
  			Universo_Actual = 4;
    		break;

    		// Bank 5
	  	case 5:
  			Universo_Actual = 5;
    		break;

    		// Bank 6
	  	case 6:
  			Universo_Actual = 6;
    		break;

  			// Bank 7
	  	case 7:
  			Universo_Actual = 7;
    		break;

    		// Bank 8
	  	case 8:
  			Universo_Actual = 8;
    		break;

  			// Exit
	  	case 9:
  			salir = 1;
  			Cursor_Index_Pos = 1;
  			break;
  	}

  	return salir;
}

void GUI_Memory 				()
{
	iniciar:

  		// Texto
  	lcd.clear 		();

  	lcd.setCursor 	(0, 0);
  	lcd.print 		("Memory");

  	lcd.setCursor 	(18, 0);
  	lcd.write 		(3);	// caracter: 1 on, 2 off, 3 file, 4 exit

  	if (Universo_Actual == 0)
  	{
    	lcd.print("-");
  	}
  	else
  	{
    	lcd.print(Universo_Actual);
  	}

  	lcd.setCursor 	(1, 1);
  	lcd.print 		("Save");

  	lcd.setCursor 	(1, 2);
  	lcd.print 		("Load");

  	lcd.setCursor 	(1, 3);
  	lcd.print 		("Clear");

  	lcd.setCursor 	(8, 1);
  	lcd.print 		("Clear All");

  	lcd.setCursor 	(8, 2);
  	lcd.print 		("Empty RAM");

  	lcd.setCursor 	(19, 3);
  	lcd.write 		(4);	// caracter: 1 on, 2 off, 3 file, 4 exit

  	lcd.setCursor 	(8, 3);
  	lcd.print 		("BlackOut");

  		// borrar datos previos en el indice
	Cursor_Index_Clear();

  		// Acciones
  	Cursor_Index[0][1]  = 1;		// Save 		// y x
  	Cursor_Index[0][2]  = 2; 		// Load
  	Cursor_Index[0][3]  = 3;		// Clear
  	Cursor_Index[7][1]  = 4;		// Clear All
  	Cursor_Index[7][2]  = 5;		// Blackout
  	Cursor_Index[7][3]  = 6;		// Empty RAM
  	Cursor_Index[18][3] = 7;		// Exit

  	Cursor_Index_Pos = 1;

  		// navegar
	navegacion:

  		// iniciar navegacion y evaluar el index seleccionado
	Navegar(0, 0);	// actualiza Cursor_Index_Pos

	switch (Cursor_Index_Pos)
	{
			// Save 
		case 1:
			if (EEPROM_Save() == 1)
    		{
     			goto iniciar;
    		}

    		goto salida;
			break;

			// Load 
		case 2:
			if (EEPROM_Load() == 1)
    		{
      			goto navegacion;
    		}

    		goto salida;
			break;

			// Clear 
		case 3:
			if (EEPROM_Clear() == 1)
    		{
      			goto iniciar;
    		}

    		goto salida;
			break;

			// Clear All
		case 4:
			EEPROM_Clear_All();
    		goto salida;
			break;

			// Empty RAM
		case 5:
			EEPROM_Empty();
    		goto salida;
			break;

			// Black Out
		case 6:
			Black_Out();
    		goto navegacion;
			break;

			// Exit
		case 7:

			break;
  	}

  	salida:
  	Cursor_Index_Pos = 6;
}

void GUI_Control_Secuencer 		() // secuenciador de bancos guardados en eeprom
{
  	int  Delay_Secuencia 	= 1;
  	int  First_Bank 	 	= 1;
  	int  Final_Bank 	 	= 8;
  	int  valor_nuevo	 	= 0;
  	byte Adelante_Reversa 	= 0;								// 0 Adelante, 1 Reversa
  	byte Bancos [9] 		= {0, 0, 0, 0, 0, 0, 0, 0};
  	byte value 				= 0;
  	long delay_contar		= 0;
  	
  	lcd.clear ();

  		// Texto
  	lcd.setCursor 	(0, 0);
  	lcd.print 		("Secuencer");
<<<<<<< HEAD

  	lcd.setCursor 	(18, 0);
  	lcd.write 		(3);	// caracter: 1 on, 2 off, 3 file, 4 exit
  	lcd.print 		(Universo_Actual);

  	lcd.setCursor 	(4, 1);
  	lcd.print 		("Delay 001x100=mS");

=======

  	lcd.setCursor 	(18, 0);
  	lcd.write 		(3);	// caracter: 1 on, 2 off, 3 file, 4 exit
  	lcd.print 		(Universo_Actual);

  	lcd.setCursor 	(4, 1);
  	lcd.print 		("Delay 001x100=mS");

>>>>>>> master
  	lcd.setCursor 	(0, 2);
  	lcd.print 		("FirstBank 1");

  	lcd.setCursor 	(19, 2);
  	lcd.write 		(4);	// caracter: 1 on, 2 off, 3 file, 4 exit

  	lcd.setCursor 	(0, 3);
  	lcd.print 		("FinalBank 8    Start");

  		// seleccional universo first
  	for (int canal = 0; canal <= 511; canal ++)
    {
        ArduinoDmx0.TxBuffer[canal] = EEPROM.read(canal); 	// salida a DMX
    }      			

  		// borrar datos previos en el indice
	Cursor_Index_Clear();

  		// Acciones
  	Cursor_Index[9][1]  = 1;		// Delay 		// y x
  	Cursor_Index[9][2]  = 2; 		// First
  	Cursor_Index[9][3]  = 3;		// Final
  	Cursor_Index[14][3] = 4;		// Start
  	Cursor_Index[18][2] = 5;		// Exit

  	Cursor_Index_Pos = 1;

  		// navegar
	navegacion:

	lcd.noBlink 	();
	lcd.setCursor 	(15, 3);
  	lcd.print 		("Start");

  		// iniciar navegacion y evaluar el index seleccionado
	Navegar(0, 0);	// actualiza Cursor_Index_Pos

	switch (Cursor_Index_Pos)
	{
			// Delay
		case 1:
			valor_nuevo = Numerico_Write(1, 999, 10, 1, 1, Delay_Secuencia);

				// menor o igual al limites
			if (valor_nuevo <= 999)			// poner limite max
			{
				Delay_Secuencia = valor_nuevo;
			}

				// mayor al limite
			if (valor_nuevo > 999)			// poner limite max
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(1, 999, 10, 1, 1, Delay_Secuencia);
					
					if (valor_nuevo > 999)	// poner limite max
					{
						break; // enter
					}

					Delay_Secuencia = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(10, 1, Delay_Secuencia, 999, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

			goto navegacion;

			break;

			// First
		case 2:
			valor_nuevo = Numerico_Write(1, 8, 10, 2, 1, First_Bank);

				// menor o igual al limites
			if (valor_nuevo <= 8)			// poner limite max
			{
				First_Bank = valor_nuevo;
			}

				// mayor al limite
			if (valor_nuevo > 8)			// poner limite max
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(1, 8, 10, 2, 1, First_Bank);
					
					if (valor_nuevo > 8)	// poner limite max
					{
						break; // enter
					}

					First_Bank = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(10, 2, First_Bank, 8, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

			goto navegacion;

			break;

			// Final
		case 3:
			valor_nuevo = Numerico_Write(1, 8, 10, 3, 1, Final_Bank);

				// menor o igual al limites
			if (valor_nuevo <= 8)			// poner limite max
			{
				Final_Bank = valor_nuevo;
			}

				// mayor al limite
			if (valor_nuevo > 8)			// poner limite max
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(1, 8, 10, 3, 1, Final_Bank);
					
					if (valor_nuevo > 8)	// poner limite max
					{
						break; // enter
					}

					Final_Bank = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(10, 3, Final_Bank, 8, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

			goto navegacion;
			
			break;

			// start
		case 4:
				// validar
    		if (First_Bank == Final_Bank)
    		{
	      		First_Bank = 1;
	      		Numerico_Print(10, 2, First_Bank, 8, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
	      		Final_Bank = 8;
	      		Numerico_Print(10, 3, Final_Bank, 8, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
	      		goto navegacion;
	    	}

	    	lcd.setCursor 	(15, 3);
    		lcd.print 		("Stop ");

			// establecer reversa o adelante

    			// adelante
	    	if (First_Bank < Final_Bank)
	    	{
	      		Adelante_Reversa = 0;
	    	}

	    		// reversa
	    	if (First_Bank > Final_Bank)
	    	{
	      		Adelante_Reversa = 1;
	    	}

	    		// establecer bancos a secuenciar
	    	if (Adelante_Reversa == 0)
	    	{
	      		for (byte Bank = 1; Bank <= 8; Bank ++)
	      		{
	        		if (Bank >= First_Bank && Bank <= Final_Bank)
	        		{
	          			Bancos[Bank] = 1;
	        		}
	      		}
	    	}

	    	if (Adelante_Reversa == 1)
	    	{
	      		for (byte Bank = 8; Bank >= 1; Bank --)
	      		{
	        		if (Bank <= First_Bank && Bank >= Final_Bank)
	        		{
	          			Bancos[Bank] = 1;
	        		}
	      		}
	    	}

	    		//Secuenciar
	    	lcd.blink();

	    		// adelante
	    	if (Adelante_Reversa == 0)
	    	{

				contar:

	      		for (byte conteo = 1; conteo <= 8; conteo ++)
	      		{
	        		if (Bancos [conteo] == 1)
	        		{
	          			lcd.setCursor (19, 0);
	          			lcd.print(conteo);
	          			lcd.setCursor (19, 3);
	          			for (int canal = 0; canal <= 511; canal ++)
	          			{
	            			switch (conteo)
	            			{
	              				case 1:
	                				value = EEPROM.read(canal);
	                				ArduinoDmx0.TxBuffer[canal] = value; 	// salida a DMX
	                				break;

	              				case 2:
	                				value = EEPROM.read(canal + 512);
	                				ArduinoDmx0.TxBuffer[canal] = value; 	// salida a DMX
	                				break;

	              				case 3:
	                				value = EEPROM.read(canal + 1024);
	                				ArduinoDmx0.TxBuffer[canal] = value; 	// salida a DMX
	                				break;

	              				case 4:
	                				value = EEPROM.read(canal + 1536);
	                				ArduinoDmx0.TxBuffer[canal] = value; 	// salida a DMX
	                				break;

	              				case 5:
	                				value = EEPROM.read(canal + 2048);
	                				ArduinoDmx0.TxBuffer[canal] = value; 	// salida a DMX
	                				break;

	              				case 6:
	                				value = EEPROM.read(canal + 2560);
	                				ArduinoDmx0.TxBuffer[canal] = value; 	// salida a DMX
	                				break;

	              				case 7:
	                				value = EEPROM.read(canal + 3072);
	                				ArduinoDmx0.TxBuffer[canal] = value; 	// salida a DMX
	                				break;

	              				case 8:
	                				value = EEPROM.read(canal + 3584);
	                				ArduinoDmx0.TxBuffer[canal] = value; 	// salida a DMX
	                				break;
	            			}
	          			}

	          				//delay
	          			delay_contar = Delay_Secuencia * 100;

	          			while (digitalRead(Enc_Center) == HIGH)		// lectura del boton centro
	          			{
	            			for (long contar = 0; contar <= delay_contar; contar ++)
	            			{
	              				delay(1);
	              				if (digitalRead(Enc_Center) == LOW)
	              				{
	                				goto salida;
	              				}
	            			}

	            			goto Delay_Salir;
	          			}

						salida:

	          			delay(500);									// rebote de boton
	          			goto navegacion;

						Delay_Salir: {}
	        		}
	      		}

	      		goto contar;

	    	}

	    		// reversa
	    	if (Adelante_Reversa == 1)
	    	{
				contar_rev:

	      		for (byte conteo = 8; conteo >= 1; conteo --)
	      		{
	        		if (Bancos [conteo] == 1)
	        		{
	          			lcd.setCursor (19, 0);
	          			lcd.print(conteo);
	          			lcd.setCursor (19, 3);

	          			for (int canal = 0; canal <= 511; canal ++)
	          			{
	            			switch (conteo)
	            			{
	              				case 1:
	                				value = EEPROM.read(canal);
	                				ArduinoDmx0.TxBuffer[canal] = value; 	// salida a DMX
	                				break;

	              				case 2:
	                				value = EEPROM.read(canal + 512);
	                				ArduinoDmx0.TxBuffer[canal] = value; 	// salida a DMX
	                				break;

	              				case 3:
	                				value = EEPROM.read(canal + 1024);
	                				ArduinoDmx0.TxBuffer[canal] = value; 	// salida a DMX
	                				break;

	              				case 4:
	                				value = EEPROM.read(canal + 1536);
	                				ArduinoDmx0.TxBuffer[canal] = value; 	// salida a DMX
	                				break;

	              				case 5:
	                				value = EEPROM.read(canal + 2048);
	                				ArduinoDmx0.TxBuffer[canal] = value; 	// salida a DMX
	                				break;

	              				case 6:
	                				value = EEPROM.read(canal + 2560);
	                				ArduinoDmx0.TxBuffer[canal] = value; 	// salida a DMX
	                				break;

	              				case 7:
	                				value = EEPROM.read(canal + 3072);
	                				ArduinoDmx0.TxBuffer[canal] = value; 	// salida a DMX
	                				break;

	              				case 8:
	                				value = EEPROM.read(canal + 3584);
	                				ArduinoDmx0.TxBuffer[canal] = value; 	// salida a DMX
	                				break;
	            			}
	          			}

	          				//delay
	          			long delay_contar = Delay_Secuencia * 100;

	          			while (digitalRead(Enc_Center) == HIGH)		// lectura del boton centro
	          			{
	            			for (long contar = 0; contar <= delay_contar; contar ++)
	            			{
	              				delay(1);

	              				if (digitalRead(Enc_Center) == LOW)
	              				{
	                				goto salida_rev;
	              				}
	            			}

	            			goto Delay_Salir_Rev;
	          			}

						salida_rev:

	          			delay(500);								// rebote de boton
	          			goto navegacion;

						Delay_Salir_Rev: {}

	        		}
	      		}
	      		goto contar_rev;
	    	}

			break;

				// Exit
			case 5:
				goto salir;
				break;
		}

	salir:

		// restablecer salida dmx como estaba antes de entrar
    for (int Canal = 0; Canal <= 512; Canal ++)
    {
      	ArduinoDmx0.TxBuffer[Canal] = DMX_Values[Canal]; 		// salida a DMX
    }
}

void Black_Out 					()
{
  	lcd.setCursor (7, 3);
  	lcd.blink();

  		// limpiar universo
  	for (int Canal = 1; Canal <= 512; Canal ++)
  	{
    	ArduinoDmx0.TxBuffer[Canal - 1] = 0;
  	}

  		// esperar al boton centro para cancelar
  	while (digitalRead(Enc_Center) == HIGH) {}

  	delay(300);		// retardo de rebote de boton

  		// regresar el universo a su lugar
  	for (int Canal = 1; Canal <= 512; Canal ++)
  	{
    	ArduinoDmx0.TxBuffer[Canal - 1] = DMX_Values[Canal];
  	}

  	lcd.setCursor (7, 2);
  	lcd.noBlink();
}

int  EEPROM_Save 				()	// guarda el universo en la eeprom
{
  	// regresa 1 si se selecciona exit

  	int cancel = 0;				// regresa 1 si se selecciona salir
  	int bank;					// regresa 1 si se selecciona salir
  	int EEPROM_Add = 0;			// direccion de eeprom para universos

  	bank = GUI_Memory_Bank(1);	// seleccinar banco

  	if (bank == 1)
  	{
    	cancel = 1;
    	goto salida;
  	}

  	lcd.clear ();
  	lcd.setCursor (1, 1);
  	lcd.print ("Memory Saving...");
  	lcd.setCursor (1, 2);
  	lcd.print ("Bank: ");
  	lcd.setCursor (7, 2);
  	lcd.print (Universo_Actual);
  	lcd.setCursor (19, 3);
  	lcd.blink();

  	for (int Canal = 0; Canal <= 511; Canal ++)
  	{
    	// Escritura de universo EEPROM
    	switch (Universo_Actual)
    	{
      		case 1:
        		EEPROM_Add = 0 + Canal;
        		break;

      		case 2:
        		EEPROM_Add = 512 + Canal;
        		break;

      		case 3:
        		EEPROM_Add = 1024 + Canal;
        		break;

      		case 4:
        		EEPROM_Add = 1536 + Canal;
        		break;

      		case 5:
        		EEPROM_Add = 2048 + Canal;
        		break;

      		case 6:
        		EEPROM_Add = 2560 + Canal;
        		break;

      		case 7:
        		EEPROM_Add = 3072 + Canal;
        		break;

      		case 8:
        		EEPROM_Add = 3584 + Canal;

        		if (EEPROM_Add > EEPROM_Limit)
        		{
          			EEPROM_Add = EEPROM_Limit;
        		}

        		break;
    	}

    	EEPROM.write(EEPROM_Add, DMX_Values[Canal + 1]);          		// lectura desde EEPROM
  	}

  	lcd.clear 		();
  	lcd.setCursor 	(3, 1);
  	lcd.print 		("Memory Saved!");
  	lcd.setCursor 	(3, 2);
  	lcd.print 		("Bank: ");
  	lcd.print 		(Universo_Actual);
  	lcd.setCursor 	(19, 3);

  	delay (1000);

  	lcd.noBlink		();

	salida:

  	return cancel;
}

int  EEPROM_Load 				() 	// guarda los valores en la eeprom
{
  	// regresa 1 si se selecciona exit

  	int cancel = 0;				// regresa 1 si se selecciona salir
  	int bank;					// regresa 1 si se selecciona salir
  	int EEPROM_Add = 0;			// seleccion de universo

 	bank = GUI_Memory_Bank(2);	// seleccinar banco

  	if (bank == 1)
  	{
    	cancel = 1;
    	goto salida;
  	}

  	lcd.clear ();

  	for (int Canal = 1; Canal <= 512; Canal ++)
  	{
    		// Escritura de universo EEPROM
    	switch (Universo_Actual)
    	{
      		case 1:
        		EEPROM_Add = 0 + Canal - 1;
        		break;

      		case 2:
        		EEPROM_Add = 512 + Canal - 1;
        		break;

      		case 3:
        		EEPROM_Add = 1024 + Canal - 1;
        		break;

      		case 4:
        		EEPROM_Add = 1536 + Canal - 1;
        		break;

      		case 5:
        		EEPROM_Add = 2048 + Canal - 1;
        		break;

      		case 6:
        		EEPROM_Add = 2560 + Canal - 1;
        		break;

      		case 7:
        		EEPROM_Add = 3072 + Canal - 1;
        		break;

      		case 8:
        		EEPROM_Add = 3584 + Canal - 1;

        		if (EEPROM_Add > EEPROM_Limit)
        		{
          			EEPROM_Add = EEPROM_Limit;
        		}

        		break;
   	 	}

    	DMX_Values[Canal] = EEPROM.read(EEPROM_Add);          	// lectura desde EEPROM
    	ArduinoDmx0.TxBuffer[Canal - 1] = DMX_Values[Canal]; 	// salida a DMX
  	}

	lcd.clear 		();
  	lcd.setCursor 	(3, 1);
  	lcd.print 		("Memory Loaded!");
  	lcd.setCursor 	(3, 2);
  	lcd.print 		("Bank: ");
  	lcd.print 		(Universo_Actual);
  	lcd.setCursor 	(19, 3);
  	lcd.blink 		();

  	delay (1000);

  	lcd.noBlink();

	salida:

  	return cancel;
}

<<<<<<< HEAD
void Init_EEPROM_Load 			() // carga los valores de los canales DMX de la eeprom al inicio e inicia el streaming de dmx
=======
void EEPROM_Load_Init 			() // carga los valores de los canales DMX de la eeprom al inicio e inicia el streaming de dmx
>>>>>>> master
{
  	int EEPROM_Add = 0;
  	
  	Universo_Actual 	= EEPROM.read(Bank_Init_Add);
  	Back_Light_Value	= EEPROM.read(BackLight_Add);
  	Light_Ext_Value		= EEPROM.read(Light_Ext_Add);
  	Key_Light_Value		= EEPROM.read(Key_Light_Add);
  	Contrast_Value		= EEPROM.read(Contrast_Add);

  		// canal actual
  	Canal_Actual 		= EEPROM.read(Canal_Actual_1_Add);
  	Canal_Actual 		= Canal_Actual + EEPROM.read(Canal_Actual_2_Add);

  	if (Universo_Actual == 0)
  	{
    	goto salir;
  	}

  	for (int Canal = 1; Canal <= 512; Canal ++)
  	{
    		// Escritura de universo EEPROM
    	switch (Universo_Actual)
    	{
      		case 1:
        		EEPROM_Add = 0 + Canal - 1;
        		break;

      		case 2:
        		EEPROM_Add = 512 + Canal - 1;
        		break;

      		case 3:
        		EEPROM_Add = 1024 + Canal - 1;
        		break;

      		case 4:
        		EEPROM_Add = 1536 + Canal - 1;
        		break;

      		case 5:
        		EEPROM_Add = 2048 + Canal - 1;
        		break;

      		case 6:
        		EEPROM_Add = 2560 + Canal - 1;
        		break;

      		case 7:
       	 		EEPROM_Add = 3072 + Canal - 1;
        		break;

      		case 8:
        		EEPROM_Add = 3584 + Canal - 1;

        		if (EEPROM_Add > EEPROM_Limit)
        		{
          			EEPROM_Add = EEPROM_Limit;
        		}

        		break;
    	}
    	DMX_Values[Canal] = EEPROM.read(EEPROM_Add);          	// lectura desde EEPROM
    	ArduinoDmx0.TxBuffer[Canal - 1] = DMX_Values[Canal]; 	// salida a DMX
  	}

  	lcd.clear 		();
  	lcd.setCursor 	(3, 1);
  	lcd.print 		("Memory Loaded!");
  	lcd.setCursor 	(3, 2);
  	lcd.print 		("Bank: ");
  	lcd.print 		(Universo_Actual);
  	lcd.setCursor 	(10, 2);
  	lcd.blink 		();

  	delay (2000);

  	lcd.noBlink 	();

	salir: {}
}

void EEPROM_Empty 				() // solo borra la ram
{
  	// no hay retorno al menu anterior

  	lcd.clear ();

  	for (int Canal = 1; Canal <= 512; Canal ++)
  	{
    	DMX_Values[Canal] = 0;          		// lectura desde EEPROM
    	ArduinoDmx0.TxBuffer[Canal - 1] = 0; 	// salida a DMX
  	}

  	lcd.clear 		();
  	lcd.setCursor 	(3, 1);
  	lcd.print 		("Memory Emptied!");
  	lcd.setCursor 	(3, 2);
  	lcd.print 		("Bank: RAM");
  	lcd.setCursor 	(19, 3);
  	lcd.blink 		();

  	delay (1000);

  	lcd.noBlink 	();
}

int  EEPROM_Clear 				() // Pone en ceros la memoria EEPROM
{
  	// regresa 1 si se selecciona exit

  	int cancel = 0;				// regresa 1 si se selecciona salir
  	int bank;					// regresa 1 si se selecciona salir
  	int EEPROM_Add = 0;			// direccion de eeprom para universos

  	bank = GUI_Memory_Bank(3);	// seleccinar banco

  	if (bank == 1)				// si se selecciono salir
  	{
    	cancel = 1;
    	goto salida;
  	}

  	lcd.clear 		();
  	lcd.setCursor 	(1, 1);
  	lcd.print 		("Memory Cleaning...");
  	lcd.setCursor 	(1, 2);
  	lcd.print 		("Bank: ");
  	lcd.setCursor 	(7, 2);
  	lcd.print 		(Universo_Actual);
  	lcd.setCursor 	(19, 3);
  	lcd.blink 		();

  	for (int Canal = 0; Canal <= 511; Canal ++)
  	{
    	DMX_Values[Canal] = 0;          		// lectura desde EEPROM
    	ArduinoDmx0.TxBuffer[Canal] = 0; 		// salida a DMX
    		// Escritura de universo EEPROM
    	switch (Universo_Actual)
    	{
      		case 1:
        		EEPROM_Add = 0 + Canal;
        		break;

      		case 2:
        		EEPROM_Add = 512 + Canal;
        		break;

      		case 3:
        		EEPROM_Add = 1024 + Canal;
        		break;

      		case 4:
        		EEPROM_Add = 1536 + Canal;
        		break;

      		case 5:
        		EEPROM_Add = 2048 + Canal;
        		break;

      		case 6:
        		EEPROM_Add = 2560 + Canal;
        		break;

      		case 7:
        		EEPROM_Add = 3072 + Canal;
        		break;

      		case 8:
       			EEPROM_Add = 3584 + Canal;
        		if (EEPROM_Add > EEPROM_Limit)
        		{
          			EEPROM_Add = EEPROM_Limit;
        		}
        		break;
    	}

    	EEPROM.write (EEPROM_Add, 0);		// escritura EEPROM
  	}

  	lcd.clear 		();
  	lcd.setCursor 	(2, 1);
  	lcd.print 		("Memory Cleaned!");
  	lcd.setCursor 	(2, 2);
  	lcd.print 		("Bank: ");
  	lcd.print 		(Universo_Actual);
  	lcd.setCursor 	(19, 3);

  	delay (1000);

  	lcd.noBlink 	();

	salida:

  	return cancel;
}

void EEPROM_Clear_All 			() // Pone en ceros la memoria EEPROM toda
{
  	lcd.clear 		();
  	lcd.setCursor 	(1, 1);
  	lcd.print 		("All");
  	lcd.setCursor 	(1, 2);
  	lcd.print 		("Memory Cleaning...");
  	lcd.setCursor 	(19, 2);
  	lcd.blink 		();

  	for (int Canal = 0; Canal <= EEPROM_Limit; Canal ++)
  	{
    	EEPROM.write (Canal, 0);				// escritura EEPROM

    	if (Canal <= 511)
    	{
     	 	DMX_Values[Canal + 1] = 0;
      		ArduinoDmx0.TxBuffer[Canal] = 0; 	// salida a DMX
    	}
  	}

  	lcd.clear 		();
  	lcd.noBlink		();
  	lcd.setCursor 	(2, 2);
  	lcd.print 		("Memory Cleaned!");
  	lcd.setCursor 	(2, 1);
  	lcd.print 		("All");

  	Universo_Actual = 0;

  	delay (1000);
}

<<<<<<< HEAD
void GUI_Menu_1 				() // menu de opciones
=======
void GUI_Control_Options 		()
>>>>>>> master
{
	inicio:

  		// LCD
  	lcd.clear 		();
<<<<<<< HEAD
=======

  	lcd.setCursor 	(18, 0);
	lcd.write 		(3);	// carater file
>>>>>>> master

  	lcd.setCursor 	(2, 0);
  	lcd.print 		("Convert");

  	lcd.setCursor 	(2, 1);
  	lcd.print 		("Unitary");

	lcd.setCursor 	(2, 2);
	lcd.print 		("Matrix");

	lcd.setCursor 	(2, 3);
	lcd.print 		("Chaser");

	lcd.setCursor 	(11, 3);
	lcd.print 		("Multiply");

	lcd.setCursor 	(11, 2);
	lcd.print 		("Secuencer");

	lcd.setCursor 	(16, 0);
	lcd.write 		(3);	// carater file

	if (Universo_Actual == 0)
  	{
    	lcd.print 	("-");
  	}
  	else
  	{
    	lcd.print (Universo_Actual);
  	}

<<<<<<< HEAD
	lcd.setCursor 	(19, 0);
	lcd.write 		(5);	// carater next
	
=======
  	lcd.setCursor 	(2, 0);
  	lcd.print 		("Convert");
  	lcd.setCursor 	(2, 1);
  	lcd.print 		("Unitary");
	lcd.setCursor 	(2, 2);
	lcd.print 		("Matrix");
	lcd.setCursor 	(2, 3);
	lcd.print 		("Chaser");
	lcd.setCursor 	(11, 3);
	lcd.print 		("Multiply");
	lcd.setCursor 	(11, 0);
	lcd.print 		("Config");
	lcd.setCursor 	(11, 2);
	lcd.print 		("Secuencer");
	lcd.setCursor 	(11, 1);
	lcd.print 		("Memory");

>>>>>>> master
  		// borrar datos previos en el indice
	Cursor_Index_Clear();

  		// establecer el indice
	Cursor_Index[1][0]   = 1; 	// Convert
  	Cursor_Index[1][1]   = 2;	// Unitary		// y x
  	Cursor_Index[1][2]   = 3; 	// Matrix
  	Cursor_Index[1][3]   = 4; 	// Chaser
  	Cursor_Index[10][2]  = 5; 	// Secuencer
  	Cursor_Index[10][3]  = 6; 	// Multiply	
  	Cursor_Index[15][0]  = 7; 	// Memory
  	Cursor_Index[18][0]  = 8; 	// Mext

		// iniciar navegacion y evaluar el index seleccionado
	Navegar(0, 0);	// actualiza Cursor_Index_Pos

  	switch (Cursor_Index_Pos)
	{
			// Convert
		case 1:
			GUI_Convert();
			Cursor_Index_Pos = 1;
			break;

			// Unitary
		case 2:
			GUI_Control_Unit();
			Cursor_Index_Pos = 2;
			break;

			// Matrix
		case 3:
			GUI_Control_Matrix();
			Cursor_Index_Pos = 3;
			break;

			// Chaser
		case 4:
			GUI_Control_Chaser();
			Cursor_Index_Pos = 4;
			break;

			// Secuencer
		case 5:
			GUI_Control_Secuencer();
			Cursor_Index_Pos = 5;
			break;

			// Multiply
		case 6:
			GUI_Control_Multiply();
			Cursor_Index_Pos = 6;
			break;

			// Memory
		case 7:
			GUI_Memory();
			Cursor_Index_Pos = 7;
			break;

		case 8:
			Cursor_Index_Pos = 1;
			GUI_Menu_2();
			Cursor_Index_Pos = 1;
			break;
	}

	goto inicio;
}

void GUI_Menu_2					() // menu de opciones
{
	inicio:

  		// LCD
  	lcd.clear 		();

  	lcd.setCursor 	(2, 0);
  	lcd.print 		("Config");

  	lcd.setCursor 	(2, 1);
  	lcd.print 		("About");

	lcd.setCursor 	(16, 0);
	lcd.write 		(3);	// carater file

	if (Universo_Actual == 0)
  	{
    	lcd.print 	("-");
  	}
  	else
  	{
    	lcd.print (Universo_Actual);
  	}

	lcd.setCursor 	(19, 0);
	lcd.write 		(6);	// carater back
	
  		// borrar datos previos en el indice
	Cursor_Index_Clear();

  		// establecer el indice
	Cursor_Index[1][0]   = 1; 	// Config
  	Cursor_Index[1][1]   = 2;	// About		// y x
  	Cursor_Index[15][0]  = 3; 	// Memory
  	Cursor_Index[18][0]  = 4; 	// Back

		// iniciar navegacion y evaluar el index seleccionado
	Navegar(0, 0);	// actualiza Cursor_Index_Pos

  	switch (Cursor_Index_Pos)
	{
			// Config
		case 1:
			GUI_Config();
			Cursor_Index_Pos = 1;
			break;

			// About
		case 2:
			GUI_About();
			GUI_Licence();
			Cursor_Index_Pos = 2;
			break;

			// Memory
		case 3:
			GUI_Memory();
			Cursor_Index_Pos = 3;
			break;

		case 4:
			Cursor_Index_Pos = 1;
			GUI_Menu_1();
			break;
	}

	goto inicio;
}

void GUI_Convert 				()
{
	int valor 			= 0;								// aqui el valor a calcular
	int valor_temp		= 0;								// aqui el valor temporal para las cuentas
	int valor_resto 	= 0;								// aqui el valor del resto de la divicion
	int valor_Bin [10]	= { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };	// aqui el valor descompuesto en binario
	int valor_nuevo		= 0;

		// LCD
	lcd.clear 		();

	lcd.setCursor 	(0, 0);
	lcd.print 		("Bin:");

	lcd.setCursor 	(16, 0);
	lcd.write 		(byte(1));	// caracter on

	lcd.setCursor 	(17, 0);
	lcd.print 		("On");

	lcd.setCursor 	(16, 1);
	lcd.write 		(byte(2));	// caracter off

	lcd.setCursor 	(5, 1);
	lcd.print 		("124813612");

	lcd.setCursor 	(17, 1);
	lcd.print 		("Off");

	lcd.setCursor 	(9, 2);
	lcd.print  		("62425");

	lcd.setCursor 	(0, 3);
	lcd.print 		("Dec:");

	lcd.setCursor 	(12, 3);
	lcd.print 		("86");

	lcd.setCursor 	(19, 3);
	lcd.write 		(4);	// carater exit
		
		// canal inicial
	Numerico_Print(5, 3, Canal_Actual, 512, 1);	// void Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)

		// calcular binario
    lcd.setCursor (5, 0);
    valor_temp = Canal_Actual;

    for (byte pos = 9; pos >= 1; pos --)
    {
      	valor_resto 		= valor_temp % 2;
      	valor_temp  		= valor_temp / 2;
      	valor_Bin [pos] 	= valor_resto;

      	if (valor_resto == 0)
      	{
      	  lcd.write(byte(2));	// caracter off
      	}
      	else
      	{
      	  lcd.write(byte(1));	// caracter on
      	}
    }

  		// borrar datos previos en el indice
	Cursor_Index_Clear();

  		// establecer el indice
  	Cursor_Index[4][0]   = 1;	// Bin		// y x
  	Cursor_Index[4][3]   = 2; 	// Dec
  	Cursor_Index[18][3]  = 3; 	// Exit

  	navegacion:

		// iniciar navegacion y evaluar el index seleccionado
	Navegar(0, 0);	// actualiza Cursor_Index_Pos

	long Enc_read	= 0;
	long Enc_ant 	= 0;
	byte Cursor 	= 1;
	byte bit_ant	= 0;

  	switch (Cursor_Index_Pos)
	{
			// Bin
		case 1:
			lcd.setCursor (5, 1);

			seguir:
			lcd.blink();

				// navegar cursor
			while(digitalRead(Enc_Center) == 1)
			{
				Enc_read = myEnc.read() / 4;

					// izquierda
				if (Enc_read < Enc_ant)
				{
					Enc_ant = Enc_read;
					Cursor = Cursor - 1;

						// limites
					if(Cursor < 1)
					{
						Cursor = 10;
						lcd.setCursor (4, 0);
					}
					else
					{
							// dibujar cursor
						lcd.setCursor (Cursor + 4, 1);
					}
					
				}

					// derecha
				if (Enc_read > Enc_ant)		
				{
					Enc_ant = Enc_read;
					Cursor = Cursor + 1;

						// limites
					if(Cursor == 10)
					{
						// dibujar cursor
						lcd.setCursor (4, 0);
					}
					else
					{
						if(Cursor > 10)
						{
							Cursor = 1;
						}

							// dibujar cursor
						lcd.setCursor (Cursor + 4, 1);
					}
				}
			}

			delay(300); // rebote de centro encoder

				// insertar valor
			switch (Cursor)
			{
				case 1:
					bit_ant = valor_Bin [9];

					valor_Bin [9] = Numerico_Write(0, 1, 5, 0, 1, bit_ant);	//int  Numerico_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, int num_ant)

					lcd.setCursor (5, 0);

					if (valor_Bin [9] == 1)
					{
						lcd.write(byte(1));
					}

					if (valor_Bin [9] == 0)
					{
						lcd.write(byte(2));
					}

					break;

				case 2:
					bit_ant = valor_Bin [8];

					valor_Bin [8] = Numerico_Write(0, 1, 6, 0, 1, bit_ant);	//int  Numerico_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, int num_ant)

					lcd.setCursor (6, 0);

					if (valor_Bin [8] == 1)
					{
						lcd.write(byte(1));
					}

					if (valor_Bin [8] == 0)
					{
						lcd.write(byte(2));
					}

					break;

				case 3:
					bit_ant = valor_Bin [7];

					valor_Bin [7] = Numerico_Write(0, 1, 7, 0, 1, bit_ant);	//int  Numerico_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, int num_ant)

					lcd.setCursor (7, 0);

					if (valor_Bin [7] == 1)
					{
						lcd.write(byte(1));
					}

					if (valor_Bin [7] == 0)
					{
						lcd.write(byte(2));
					}

					break;

				case 4:
					bit_ant = valor_Bin [6];

					valor_Bin [6] = Numerico_Write(0, 1, 8, 0, 1, bit_ant);	//int  Numerico_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, int num_ant)

					lcd.setCursor (8, 0);

					if (valor_Bin [6] == 1)
					{
						lcd.write(byte(1));
					}

					if (valor_Bin [6] == 0)
					{
						lcd.write(byte(2));
					}

					break;

				case 5:
					bit_ant = valor_Bin [5];

					valor_Bin [5] = Numerico_Write(0, 1, 9, 0, 1, bit_ant);	//int  Numerico_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, int num_ant)

					lcd.setCursor (9, 0);

					if (valor_Bin [5] == 1)
					{
						lcd.write(byte(1));
					}

					if (valor_Bin [5] == 0)
					{
						lcd.write(byte(2));
					}

					break;

				case 6:
					bit_ant = valor_Bin [4];

					valor_Bin [4] = Numerico_Write(0, 1, 10, 0, 1, bit_ant);	//int  Numerico_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, int num_ant)

					lcd.setCursor (10, 0);

					if (valor_Bin [4] == 1)
					{
						lcd.write(byte(1));
					}

					if (valor_Bin [4] == 0)
					{
						lcd.write(byte(2));
					}

					break;

				case 7:
					bit_ant = valor_Bin [3];

					valor_Bin [3] = Numerico_Write(0, 1, 11, 0, 1, bit_ant);	//int  Numerico_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, int num_ant)

					lcd.setCursor (11, 0);

					if (valor_Bin [3] == 1)
					{
						lcd.write(byte(1));
					}

					if (valor_Bin [3] == 0)
					{
						lcd.write(byte(2));
					}

					break;

				case 8:
					bit_ant = valor_Bin [2];

					valor_Bin [2] = Numerico_Write(0, 1, 12, 0, 1, bit_ant);	//int  Numerico_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, int num_ant)

					lcd.setCursor (12, 0);

					if (valor_Bin [2] == 1)
					{
						lcd.write(byte(1));
					}

					if (valor_Bin [2] == 0)
					{
						lcd.write(byte(2));
					}

					break;

				case 9:
					bit_ant = valor_Bin [1];

					valor_Bin [1] = Numerico_Write(0, 1, 13, 0, 1, bit_ant);	//int  Numerico_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, int num_ant)

					lcd.setCursor (13, 0);

					if (valor_Bin [1] == 1)
					{
						lcd.write(byte(1));
					}

					if (valor_Bin [1] == 0)
					{
						lcd.write(byte(2));
					}

					break;

				case 10:
					goto salida_menu;
					break;
			}

				// calcular valor de binario a decimal
	        valor = 0;
	        if (valor_Bin [9] == 1)
	        {
				valor = valor + 1;
	        }

	        if (valor_Bin [8] == 1)
	        {
				valor = valor + 2;
	        }

	        if (valor_Bin [7] == 1)
	        {
				
				valor = valor + 4;
	        }

	        if (valor_Bin [6] == 1)
	        {
				valor = valor + 8;
	        }

	        if (valor_Bin [5] == 1)
	        {
				valor = valor + 16;
	        }

	        if (valor_Bin [4] == 1)
	        {
				valor = valor + 32;
	        }

	        if (valor_Bin [3] == 1)
	        {
				valor = valor + 64;
	        }

	        if (valor_Bin [2] == 1)
	        {
				valor = valor + 128;
	        }

	        if (valor_Bin [1] == 1)
	        {
				valor = valor + 256;
	        }

	        	// escribir el valor en decimal
	       	Numerico_Print(5, 3, valor, 511, 1);		// void Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)

	       		// posicionar cursor
	       	switch (Cursor)
	       	{
	       		case 1:
	       			lcd.setCursor (5, 1);
	       			break;

	       		case 2:
	       			lcd.setCursor (6, 1);
	       			break;

	       		case 3:	
	       			lcd.setCursor (7, 1);
	       			break;

	       		case 4:
	       			lcd.setCursor (8, 1);
	       			break;

	       		case 5:
	       			lcd.setCursor (9, 1);
	       			break;

	       		case 6:
	       			lcd.setCursor (10, 1);
	       			break;

	       		case 7:
	       			lcd.setCursor (11, 1);
	       			break;

	       		case 8:
	       			lcd.setCursor (12, 1);
	       			break;

	       		case 9:
	       			lcd.setCursor (13, 1);
	       			break;
	       	}

			goto seguir;

			salida_menu:
			lcd.noBlink();

			break;

			// Dec
		case 2:
			valor_nuevo = Numerico_Write(1, 511, 5, 3, 1, Canal_Actual);				// int  Numerico_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, int num_ant)

				// menor o igual al limites
			if (valor_nuevo <= 511)					// poner limite max
			{
				Canal_Actual = valor_nuevo;

						// calcular binario
    				lcd.setCursor (5, 0);
					valor_temp = Canal_Actual;

				    for (byte pos = 9; pos >= 1; pos --)
				    {
				      	valor_resto 		= valor_temp % 2;
				      	valor_temp  		= valor_temp / 2;
				      	valor_Bin [pos] 	= valor_resto;

				      	if (valor_resto == 0)
				      	{
				      	  lcd.write(byte(2));
				      	}
				      	else
				      	{
				      	  lcd.write(byte(1));
				      	}
				    }
			}

				// encoder
			if (valor_nuevo == 512)					// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(1, 511, 5, 3, 1, Canal_Actual);	// int  Numerico_Enc_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, long num_ant)
					
					if (valor_nuevo > 511)			// poner limite max
					{
						break; 						// enter
					}

					Canal_Actual = valor_nuevo;

						// calcular binario
    				lcd.setCursor (5, 0);
					valor_temp = Canal_Actual;

				    for (byte pos = 9; pos >= 1; pos --)
				    {
				      	valor_resto 		= valor_temp % 2;
				      	valor_temp  		= valor_temp / 2;
				      	valor_Bin [pos] 	= valor_resto;
				      	if (valor_resto == 0)
				      	{
				      	  lcd.write(byte(2));
				      	}
				      	else
				      	{
				      	  lcd.write(byte(1));
				      	}
				    }
				}
					// acomodar numero 	
				Numerico_Print(5, 3, Canal_Actual, 511, 1);				// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

				// ubicar
			if (valor_nuevo == 513)										// poner limite max + 2
			{
				Numerico_Print(5, 2, Canal_Actual, 511, 1);				// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
				Ubicar(5, 3, DMX_Values[Canal_Actual]);					// void Ubicar(byte y, byte x, byte val_ant)
				lcd.setCursor (5, 2);
				lcd.print ("   ");
				Numerico_Print(5, 3, Canal_Actual, 511, 1);				// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

			break;

			// salida
		case 3:
			goto salir;
			break;
	}

  	goto navegacion;

  	salir:

  		// guardar canal actual
  	Canal_Actual_EEPROM_Save();
}

void GUI_Config 				()
{
	Cursor_Index_Pos = 1;

	Inicio:

		// GUI
	lcd.clear 		();
<<<<<<< HEAD

	lcd.setCursor 	(0, 0);
	lcd.print 		("Config");

	lcd.setCursor 	(1, 1);
	lcd.print 		("Key");
	Numeric_Write 	(Key_Light_Value, 5, 1);

	lcd.setCursor 	(0, 2);
	lcd.print 		("Back");
	Numeric_Write 	(Back_Light_Value, 5, 2);

	lcd.setCursor 	(1, 3);
	lcd.print 		("Ext");
	Numeric_Write 	(Light_Ext_Value, 5, 3);

	lcd.setCursor 	(9, 1);
	lcd.print 		("Cont");
	Numeric_Write 	(Contrast_Value, 14, 1);

	lcd.setCursor 	(9, 2);
	lcd.write 		(3);	// caracter: 1 on, 2 off, 3 file, 4 exit
	lcd.print 		("ini ");

	if (Universo_Actual < 1)
	{
		lcd.print 	("-");
	}
	else
	{
		lcd.print(Universo_Actual);
	}

	lcd.setCursor 	(14, 3);
	lcd.print 		("EEdef");

	lcd.setCursor 	(16, 0);
	lcd.write 		(3);	// caracter: 1 on, 2 off, 3 file, 4 exit
=======

	lcd.setCursor 	(0, 0);
	lcd.print 		("Config");

	lcd.setCursor 	(1, 1);
	lcd.print 		("Key:");
	Numeric_Write 	(Key_Light_Value, 6, 1);

	lcd.setCursor 	(0, 2);
	lcd.print 		("Back:");
	Numeric_Write 	(Back_Light_Value, 6, 2);

	lcd.setCursor 	(1, 3);
	lcd.print 		("Ext:");
	Numeric_Write 	(Light_Ext_Value, 6, 3);

	lcd.setCursor 	(10, 0);
	lcd.write 		(3);	// caracter: 1 on, 2 off, 3 file, 4 exit
	lcd.print 		("Ini:");
>>>>>>> master

	lcd.setCursor 	(16, 0);
	if (Universo_Actual < 1)
	{
		lcd.print 	("-");
	}
	else
	{
		lcd.print(Universo_Actual);
	}

<<<<<<< HEAD
	lcd.setCursor 	(19, 0);
=======
	lcd.setCursor 	(10, 1);
	lcd.print 		("Cont:");
	Numeric_Write 	(Contrast_Value, 16, 1);

	lcd.setCursor 	(11, 3);
	lcd.print 		("About");

	lcd.setCursor 	(19, 3);
>>>>>>> master
	lcd.write 		(4);	// caracter: 1 on, 2 off, 3 file, 4 exit

		// borrar datos previos en el indice
	Cursor_Index_Clear();

		// establecer el indice
<<<<<<< HEAD
	Cursor_Index[4][1]  = 1;	// Key Light Value  	// y x
	Cursor_Index[4][2]  = 2;	// Back Light Value 
	Cursor_Index[4][3]  = 3;	// External Light Value 
	Cursor_Index[13][1] = 4;	// Contrast Value 
	Cursor_Index[13][2] = 5;	// Bank init Value
	Cursor_Index[13][3] = 6;	// EEPROM default
	Cursor_Index[15][0] = 7;	// memory
	Cursor_Index[18][0] = 8;	// Exit
=======
	Cursor_Index[5][1]  = 1;	// Key Light Value  	// y x
	Cursor_Index[5][2]  = 2;	// Back Light Value 
	Cursor_Index[5][3]  = 3;	// External Light Value 
	Cursor_Index[15][0] = 4;	// Bank init Value
	Cursor_Index[15][1] = 5;	// Contrast Value 
	Cursor_Index[10][3] = 6;	// About
	Cursor_Index[18][3] = 7;	// Exit
>>>>>>> master

	navegacion:

	int valor_nuevo = 0;

		// iniciar navegacion y evaluar el index seleccionado
	Navegar(0, 0);	// actualiza Cursor_Index_Pos

	switch (Cursor_Index_Pos)
<<<<<<< HEAD
	{			
		case 1:	// Key Light Value
			valor_nuevo = Numerico_Write(0, 255, 5, 1, 1, Key_Light_Value); 
=======
	{
			// Key Light Value
		case 1:
			valor_nuevo = Numerico_Write(0, 255, 6, 1, 1, Key_Light_Value); 
>>>>>>> master

				// menor o igual al limites
			if (valor_nuevo <= 255)			// poner limite max
			{
				analogWrite(Key_Light_PWM, valor_nuevo);
				Key_Light_Value = valor_nuevo;
			}

				// mayor al limite
			if (valor_nuevo > 255)			// poner limite max
			{
				while(1)
				{
<<<<<<< HEAD
					valor_nuevo = Numerico_Enc_Write(0, 255, 5, 1, 1, Key_Light_Value);
=======
					valor_nuevo = Numerico_Enc_Write(0, 255, 6, 1, 1, Key_Light_Value);
>>>>>>> master
					
					if (valor_nuevo > 255)	// poner limite max
					{
						break; // enter
					}

					analogWrite(Key_Light_PWM, valor_nuevo);	// accion
					Key_Light_Value = valor_nuevo;
		
				}
					// acomodar numero 	
<<<<<<< HEAD
				Numerico_Print(5, 1, Key_Light_Value, 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
=======
				Numerico_Print(6, 1, Key_Light_Value, 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
>>>>>>> master
			}

			EEPROM.write(Key_Light_Add, Key_Light_Value);

			break;
<<<<<<< HEAD
			
		case 2:	// Back Light Value 
			valor_nuevo = Numerico_Write(1, 255, 5, 2, 1, Back_Light_Value);
=======

			// Back Light Value 
		case 2:
			valor_nuevo = Numerico_Write(1, 255, 6, 2, 1, Back_Light_Value);
>>>>>>> master

				// menor o igual al limites
			if (valor_nuevo <= 255)			// poner limite max
			{
				analogWrite(Back_Light_PWM, valor_nuevo);
				Back_Light_Value = valor_nuevo;
			}

				// mayor al limite
			if (valor_nuevo > 255)			// poner limite max
			{
				while(1)
				{
<<<<<<< HEAD
					valor_nuevo = Numerico_Enc_Write(1, 255, 5, 2, 1, Back_Light_Value);
=======
					valor_nuevo = Numerico_Enc_Write(1, 255, 6, 2, 1, Back_Light_Value);
>>>>>>> master
					
					if (valor_nuevo > 255)	// poner limite max
					{
						break; // enter
					}

					analogWrite(Back_Light_PWM, valor_nuevo);	// accion
					Back_Light_Value = valor_nuevo;
		
				}
					// acomodar numero 	
<<<<<<< HEAD
				Numerico_Print(5, 2, Back_Light_Value, 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
=======
				Numerico_Print(6, 2, Back_Light_Value, 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
>>>>>>> master
			}

			EEPROM.write(BackLight_Add, Back_Light_Value);
			break;

<<<<<<< HEAD
		case 3: // External Light
			valor_nuevo = Numerico_Write(1, 255, 5, 3, 1, Light_Ext_Value);	// (int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, int num_ant) // regresa el numero tecleado

				// menor o igual al limites
			if (valor_nuevo <= 255)			// poner limite max
			{
				analogWrite(Light_PWM, valor_nuevo);
				Light_Ext_Value = valor_nuevo;
			}

				// mayor al limite
			if (valor_nuevo > 255)			// poner limite max
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(1, 255, 5, 3, 1, Light_Ext_Value); // (int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, int num_ant) // regresa el numero tecleado
					
					if (valor_nuevo > 255)	// poner limite max
					{
						break; // enter
					}

					analogWrite(Light_PWM, valor_nuevo);	// accion
					Light_Ext_Value = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(5, 3, Light_Ext_Value, 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

			EEPROM.write(Light_Ext_Add, Light_Ext_Value);
			break;

		case 4: // Contrast Value
			valor_nuevo = Numerico_Write(1, 255, 14, 1, 1, Contrast_Value);
=======
			// Contrast Value
		case 5:
			valor_nuevo = Numerico_Write(1, 255, 16, 1, 1, Contrast_Value);
>>>>>>> master

				// menor o igual al limites
			if (valor_nuevo <= 255)			// poner limite max
			{
				analogWrite(Contrast_PWM, valor_nuevo);
				Contrast_PWM = valor_nuevo;
			}

				// mayor al limite
			if (valor_nuevo > 255)			// poner limite max
			{
				while(1)
				{
<<<<<<< HEAD
					valor_nuevo = Numerico_Enc_Write(1, 255, 14, 1, 1, Contrast_Value);
=======
					valor_nuevo = Numerico_Enc_Write(1, 255, 16, 1, 1, Contrast_Value);
>>>>>>> master
					
					if (valor_nuevo > 255)	// poner limite max
					{
						break; // enter
					}

					analogWrite(Contrast_PWM, valor_nuevo);	// accion
					Contrast_Value = valor_nuevo;
		
				}
					// acomodar numero 	
<<<<<<< HEAD
				Numerico_Print(14, 1, Contrast_Value, 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
=======
				Numerico_Print(16, 1, Contrast_Value, 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
>>>>>>> master
			}

			EEPROM.write(Contrast_Add, Contrast_Value);
			break;

<<<<<<< HEAD
		case 5: // Bank init Value
			valor_nuevo = Numerico_Write(1, 8, 14, 2, 1, Universo_Actual);
=======
			// Bank init Value
		case 4:
			valor_nuevo = Numerico_Write(0, 8, 16, 0, 1, Universo_Actual);
>>>>>>> master

				// menor o igual al limites
			if (valor_nuevo <= 8)			// poner limite max
			{
				Universo_Actual = valor_nuevo;
			}

				// mayor al limite
			if (valor_nuevo > 8)			// poner limite max
			{
				while(1)
				{
<<<<<<< HEAD
					valor_nuevo = Numerico_Enc_Write(1, 8, 14, 2, 1, Universo_Actual);
=======
					valor_nuevo = Numerico_Enc_Write(0, 8, 16, 0, 1, Universo_Actual);
>>>>>>> master
					
					if (valor_nuevo > 8)	// poner limite max
					{
						break; // enter
					}

					Universo_Actual = valor_nuevo;
		
				}
					// acomodar numero 	
<<<<<<< HEAD
				Numerico_Print(14, 2, Universo_Actual, 8, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
=======
				Numerico_Print(16, 0, Universo_Actual, 8, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
>>>>>>> master
			}

			EEPROM.write(Bank_Init_Add, Universo_Actual);
			break;

<<<<<<< HEAD
		case 6: // EEPROM default
			EEPROM_Default();
			break;
		
		case 7: // memory
			GUI_Memory();
			Cursor_Index_Pos = 7;
			goto Inicio;
			break;

		case 8: // exit
=======
			// About
		case 6:
			GUI_About();
			GUI_Licence();
			Cursor_Index_Pos = 5;
			goto Inicio;
			break;

			// External Light
		case 3:
			valor_nuevo = Numerico_Write(1, 255, 6, 3, 1, Light_Ext_Value);	// (int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, int num_ant) // regresa el numero tecleado

				// menor o igual al limites
			if (valor_nuevo <= 255)			// poner limite max
			{
				analogWrite(Light_PWM, valor_nuevo);
				Light_Ext_Value = valor_nuevo;
			}

				// mayor al limite
			if (valor_nuevo > 255)			// poner limite max
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(1, 255, 6, 3, 1, Light_Ext_Value); // (int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, int num_ant) // regresa el numero tecleado
					
					if (valor_nuevo > 255)	// poner limite max
					{
						break; // enter
					}

					analogWrite(Light_PWM, valor_nuevo);	// accion
					Light_Ext_Value = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(6, 3, Light_Ext_Value, 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

			EEPROM.write(Light_Ext_Add, Light_Ext_Value);
			break;
		
			// Exit
		case 7:
>>>>>>> master
			goto salida;
			break;
	}
	
	goto navegacion;

	salida:

	Cursor_Index_Pos = 1;
}

void GUI_Control_Multiply 		()
{
  	int  First_Channel = 1;
  	long Multiply 	   = 1;
  	long Quantity 	   = 512;
  	int  Value         = 255;

	iniciar:

  		// LCD
  	lcd.clear 		();

  	lcd.setCursor 	(3, 0);
  	lcd.print 		("Value");

  	lcd.setCursor 	(18, 2);
  	lcd.write 		(3);	// caracter: 1 on, 2 off, 3 file, 4 exit

  	if (Universo_Actual == 0)
  	{
    	lcd.print 	("-");
  	}
  	else
  	{
    	lcd.print(Universo_Actual);
  	}

  	lcd.setCursor	(0, 1);
  	lcd.print 		("First CH");

  	lcd.setCursor 	(0, 2);
  	lcd.print 		("Multiply");

  	lcd.setCursor 	(0, 3);
  	lcd.print 		("Quantity      Apply");

  	lcd.setCursor 	(19, 1);
  	lcd.write 		(4);	// caracter: 1 on, 2 off, 3 file, 4 exit

  	Numerico_Print(9, 0, Value, 		255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
  	Numerico_Print(9, 1, First_Channel, 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
  	Numerico_Print(9, 2, Multiply, 		255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
  	Numerico_Print(9, 3, Quantity, 		255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)

		// borrar datos previos en el indice
	Cursor_Index_Clear();

		// establecer el indice
	Cursor_Index[8][0]   = 1;	// Value  	// y x
	Cursor_Index[8][1]   = 2;	// First Channel
	Cursor_Index[8][2]   = 3;	// Multiply
	Cursor_Index[8][3]   = 4;	// Quantity
	Cursor_Index[18][1]  = 7;	// Exit
	Cursor_Index[17][2]  = 6;	// Memory
	Cursor_Index[13][3]  = 5;	// Apply

	int  valor_nuevo 	= 0;
	long valid 			= 0;
	long canal 			= 0;

	Cursor_Index_Pos = 1;

	navegacion:

		// iniciar navegacion y evaluar el index seleccionado
	Navegar(0, 0);	// actualiza Cursor_Index_Pos

	switch (Cursor_Index_Pos)
	{
			// Value
		case 1:
			valor_nuevo = Numerico_Write(1, 255, 9, 0, 1, Value);

				// menor o igual al limites
			if (valor_nuevo <= 255)			// poner limite max
			{
				Value = valor_nuevo;
			}

				// mayor al limite
			if (valor_nuevo > 255)			// poner limite max
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(1, 255, 9, 0, 1, Value);
					
					if (valor_nuevo > 255)	// poner limite max
					{
						break; // enter
					}

					Value = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(9, 0, Value, 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

			break;

			// First Channel
		case 2:
			valor_nuevo = Numerico_Write(1, 512, 9, 1, 1, First_Channel);

				// menor o igual al limites
			if (valor_nuevo <= 512)			// poner limite max
			{
				First_Channel = valor_nuevo;
			}

				// mayor al limite
			if (valor_nuevo > 512)			// poner limite max
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(1, 512, 9, 1, 1, First_Channel);
					
					if (valor_nuevo > 512)	// poner limite max
					{
						break; // enter
					}

					First_Channel = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(9, 1, First_Channel, 512, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

			break;

			// Multiply
		case 3:
			valor_nuevo = Numerico_Write(1, 512, 9, 2, 1, Multiply);

				// menor o igual al limites
			if (valor_nuevo <= 512)			// poner limite max
			{
				Multiply = valor_nuevo;
			}

				// mayor al limite
			if (valor_nuevo > 512)			// poner limite max
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(1, 512, 9, 2, 1, Multiply);
					
					if (valor_nuevo > 512)	// poner limite max
					{
						break; // enter
					}

					Multiply = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(9, 2, Multiply, 512, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

			break;

			// Quantity
		case 4:
			valor_nuevo = Numerico_Write(1, 512, 9, 3, 1, Quantity);

				// menor o igual al limites
			if (valor_nuevo <= 512)			// poner limite max
			{
				Quantity = valor_nuevo;
			}

				// mayor al limite
			if (valor_nuevo > 512)			// poner limite max
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(1, 512, 9, 3, 1, Quantity);
					
					if (valor_nuevo > 512)	// poner limite max
					{
						break; // enter
					}

					Quantity = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(9, 3, Quantity, 512, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}
			break;

			// Apply
		case 5:
				// Validar datos
	    	valid = Multiply * Quantity;
	    
	    	if (valid > 512)	// si no es valido
	    	{
	      		lcd.setCursor 	(13, 0);
	      		lcd.print 		("Error! ");
	      		break;
	    	}

	    		// calcular
	    	lcd.setCursor 		(13, 0);
	    	lcd.print 			("       ");
	    	lcd.setCursor 		(14, 3);
	    	lcd.print 			("Calc..");

	    	for (long conteo = 1; conteo <= Quantity; conteo++)
	    	{
	      		if (conteo == 1)
	      		{
	        		canal = First_Channel;
	      		}

	      		if (conteo != 1)
	      		{
	        		canal = canal + Multiply;
	      		}

	      		if (canal > 512)
	      		{
	        		canal = canal - Multiply;
	       	 		conteo = Quantity;
	      		}

	      		lcd.setCursor(17, 0);
	      		lcd.print(canal);
	      		delay (5);
	      		ArduinoDmx0.TxBuffer[canal - 1] = Value;
	      		DMX_Values[canal] = Value;
	    	}

	    	lcd.setCursor 	(13, 0);
	    	lcd.print 		("Ok!");
	    	lcd.setCursor 	(14, 3);
	    	lcd.print 		("Apply ");

			break;

			// Memory
		case 6:
			GUI_Memory();
			Cursor_Index_Pos = 6;
			goto iniciar;
			break;

			// Exit
		case 7:
			goto salir;

			break;
	}

	goto navegacion;

	salir: {}
}

void GUI_Control_Chaser 		()
{
  	long Delay   		= 1;
  	int  First 			= Canal_Actual;
  	int  Final 	 		= 512;
  	long ciclo_longitud = 1300;						// numero multiplicador aprox para 1 seg
    long ciclo 			= 0;
	long Delay_Cont		= 0;
	int  canal 			= First;

  		// LCD
  	lcd.clear 		();

  	lcd.setCursor 	(0, 0);
  	lcd.print 		("Chaser");

  	lcd.setCursor 	(13, 0);
  	lcd.print 		("Ch:");

  	lcd.setCursor 	(2, 1);
  	lcd.print 		("Delay:");

  	lcd.setCursor 	(12, 1);
  	lcd.print 		("x10=mS");

  	lcd.setCursor 	(0, 2);
  	lcd.print 		("FirstCh:");

  	lcd.setCursor 	(19, 2);
  	lcd.write 		(4);	// caracter: 1 on, 2 off, 3 file, 4 exit

  	lcd.setCursor 	(0, 3);
  	lcd.print 		("FinalCh:");

  	lcd.setCursor 	(15, 3);
  	lcd.print 		("Start");

  	Numerico_Print(9, 1, Delay, 100, 1);	//void Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
  	Numerico_Print(9, 2, First, 100, 1);	//void Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
  	Numerico_Print(9, 3, Final, 100, 1);	//void Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)

  	// first channel
  		// borrar canales previos
	for (int Canales = 0; Canales <= 511; Canales ++)
	{	
	    ArduinoDmx0.TxBuffer[Canales] = 0; 			// salida a DMX
	}

		// dibujar numero
	Numerico_Print(17, 0, Canal_Actual, 512, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
	ArduinoDmx0.TxBuffer[Canal_Actual - 1] = 255; 	// salida a DMX

  		// borrar datos previos en el indice
	Cursor_Index_Clear();

		// establecer el indice
	Cursor_Index[14][3] = 4;	// start 		//y x
	Cursor_Index[8] [1] = 1;	// delay		//y x	
	Cursor_Index[8] [2] = 2;	// first chanel	//y x
	Cursor_Index[8] [3] = 3;	// final chanel	//y x
	Cursor_Index[18][2] = 6;	// exit			//y x
	Cursor_Index[16][0] = 5;	// Ch			//y x

	navegacion:

		// iniciar navegacion y evaluar el index seleccionado
	Navegar(0, 0);	// actualiza Cursor_Index_Pos

	int valor_nuevo = 0;
	int ch_ant = 0;

	switch (Cursor_Index_Pos)
	{
			// start
		case 4:
	    	lcd.setCursor 	(15, 3);
	    	lcd.print 		("Stop ");

	    		// borrar canales previos
	    	for (int Canales = 0; Canales <= 511; Canales ++)
	    	{	
	     	 	ArduinoDmx0.TxBuffer[Canales] = 0; 			// salida a DMX
	    	}

	    	while (digitalRead(Enc_Center) == HIGH)			// lectura del boton centro
	    	{
	      		ciclo = ciclo + 1;
	      		if (ciclo == ciclo_longitud)
	      		{
	        		Delay_Cont = Delay_Cont + 1;
	        		if (Delay_Cont == Delay)
	        		{
	          			if (canal > Final)
	          			{
	            			canal = First;
	          			}
	          			Numerico_Print(17, 0, canal, 512, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)

	          				// apagar lo anterior
	          			for (long contar = First; contar <= Final; contar ++)
	          			{
	            			ArduinoDmx0.TxBuffer[contar - 1] = 0;
	          			}

	          				// encender el siguiente
	          			ArduinoDmx0.TxBuffer[canal - 1] = 255;
	          			Delay_Cont = 0;
	          			canal = canal + 1;
	        		}
	        		ciclo = 0;
	      		}
	    	}

	    	lcd.setCursor 	(15, 3);
	    	lcd.print 		("Start");

	    	delay (300); 		// evita que le gane la descarga del capacitor

			break;

			// delay
		case 1:
			valor_nuevo = Numerico_Write(1, 999, 9, 1, 1, Delay);

				// menor o igual al limites
			if (valor_nuevo <= 999)			// poner limite max
			{
				Delay = valor_nuevo;
			}

				// mayor al limite
			if (valor_nuevo > 999)			// poner limite max
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(1, 999, 9, 1, 1, Delay);
					
					if (valor_nuevo > 999)	// poner limite max
					{
						break; // enter
					}

					Delay = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(9, 1, Delay, 999, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

			break;

			// first
		case 2:
			valor_nuevo = Numerico_Write(1, 512, 9, 2, 1, First);

				// menor o igual al limites
			if (valor_nuevo <= 512)			// poner limite max
			{
				First = valor_nuevo;
			}

				// mayor al limite
			if (valor_nuevo > 512)			// poner limite max
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(1, 512, 9, 2, 1, First);
					
					if (valor_nuevo > 512)	// poner limite max
					{
						break; // enter
					}

					First = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(9, 2, First, 512, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}
			break;

			// final
		case 3:
			valor_nuevo = Numerico_Write(1, 512, 9, 3, 1, Final);

				// menor o igual al limites
			if (valor_nuevo <= 512)			// poner limite max
			{
				Final = valor_nuevo;
			}

				// mayor al limite
			if (valor_nuevo > 512)			// poner limite max
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(1, 512, 9, 3, 1, Final);
					
					if (valor_nuevo > 512)	// poner limite max
					{
						break; // enter
					}

					Final = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(9, 3, Final, 512, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}
			break;

			// channel
		case 5:
			ch_ant = First;

			lcd.setCursor(17, 0);
			lcd.print("   ");

				// borrar canales previos
	    	for (int Canales = First; Canales <= Final; Canales ++)
	    	{	
	     	 	ArduinoDmx0.TxBuffer[Canales - 1] = 0; 			// salida a DMX
	    	}

	    		// encender canal inicial
	    	ArduinoDmx0.TxBuffer[First - 1] = 255; 				// salida a DMX

			while(1)
			{
				valor_nuevo = Numerico_Enc_Write(First, Final, 17, 0, 1, ch_ant);

					// borrar canales previos
	    		for (int Canales = First; Canales <= Final; Canales ++)
	    		{	
	     	 		ArduinoDmx0.TxBuffer[Canales - 1] = 0; 			// salida a DMX
	    		}

					// encender canal
				ArduinoDmx0.TxBuffer[valor_nuevo - 1] = 255; 		// salida a DMX
				
				if (valor_nuevo > Final)	// poner limite max
				{
					break; // enter
				}

				ch_ant = valor_nuevo;
		
			}
				// acomodar numero 	
			Numerico_Print(17, 0, First, 512, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)

				// borrar canales previos
	    	for (int Canales = First; Canales <= Final; Canales ++)
	    	{	
	     	 	ArduinoDmx0.TxBuffer[Canales - 1] = 0; 			// salida a DMX
	    	}

	    		// encender canal inicial
	    	ArduinoDmx0.TxBuffer[First - 1] = 255; 				// salida a DMX

			break;

			// exit
		case 6:
			goto salir;
			break;
	}		

	goto navegacion;

	salir:

		// regresar el universo a su lugar
    for (int Canal = 1; Canal <= 512; Canal ++)
    {
      	ArduinoDmx0.TxBuffer[Canal - 1] = DMX_Values[Canal];
    }
}

void GUI_Control_Unit 			()
{
	int CH_1 = 0;
	int CH_2 = 0;
	int CH_3 = 0;
	int CH_4 = 0;
	int CH_5 = 0;
	int CH_6 = 0;
	int CH_7 = 0;
	int CH_8 = 0;

	Cursor_Index_Pos =  1;

	inicio:

	lcd.clear();

		// establecer valores
	if (Canal_Actual > 504)
	{
		CH_1 = 505;
	}
	else
	{
		CH_1 = Canal_Actual;
	}

	CH_2 = CH_1 + 1;
	CH_3 = CH_1 + 2;
	CH_4 = CH_1 + 3;
	CH_5 = CH_1 + 4;
	CH_6 = CH_1 + 5;
	CH_7 = CH_1 + 6;
	CH_8 = CH_1 + 7;

  		// universo actual
  	lcd.setCursor 	(18, 0);
  	lcd.write 		(3);	// caracter: 1 on, 2 off, 3 file, 4 exit

  	if (Universo_Actual == 0)
  	{
    	lcd.print 	("-");
  	}
  	else
  	{
    	lcd.print(Universo_Actual);
  	}

  	lcd.setCursor 	(19, 3);
  	lcd.write 		(4);	// caracter: 1 on, 2 off, 3 file, 4 exit

  		// borrar datos previos en el indice
	Cursor_Index_Clear();
		// establecer el indice
	Cursor_Index[0][0] 	= 1;	// ch 1 	//y x
	Cursor_Index[0][1] 	= 2;	// CH 1 	//y x	
	Cursor_Index[4][0] 	= 3;	// ch 2		//y x
	Cursor_Index[4][1] 	= 4;	// ch 2		//y x
	Cursor_Index[8][0] 	= 5;	// ch 3		//y x
	Cursor_Index[8][1] 	= 6;	// ch 3 	//y x
	Cursor_Index[12][0] = 7;	// ch 4 	//y x
	Cursor_Index[12][1] = 8;	// ch 4		//y x
	Cursor_Index[0][2] 	= 9;	// ch 5		//y x
	Cursor_Index[0][3] 	= 10;	// ch 5		//y x
	Cursor_Index[4][2] 	= 11;	// ch 6		//y x
	Cursor_Index[4][3] 	= 12;	// ch 6		//y x
	Cursor_Index[8][2] 	= 13;	// ch 7		//y x
	Cursor_Index[8][3] 	= 14;	// ch 7		//y x
	Cursor_Index[12][2] = 15;	// ch 8		//y x
	Cursor_Index[12][3] = 16;	// ch 8		//y x
	Cursor_Index[17][0] = 17;	// mem		//y x
	Cursor_Index[18][3] = 18;	// exit 	//y x

	navegacion:

		// canal 1
  	Numeric_Write(CH_1, 1, 0);
  	Numeric_Write(DMX_Values[CH_1], 1, 1);

  		// canal 2
  	Numeric_Write(CH_2, 5, 0);
  	Numeric_Write(DMX_Values[CH_2], 5, 1);

  		// canal 3
  	Numeric_Write(CH_3, 9, 0);
  	Numeric_Write(DMX_Values[CH_3], 9, 1);

  		// canal 4
  	Numeric_Write(CH_4, 13, 0);
  	Numeric_Write(DMX_Values[CH_4], 13, 1);

  		// canal 5
  	Numeric_Write(CH_5, 1, 2);
  	Numeric_Write(DMX_Values[CH_5], 1, 3);

  		// canal 6
  	Numeric_Write(CH_6, 5, 2);
  	Numeric_Write(DMX_Values[CH_6], 5, 3);

  		// canal 7
  	Numeric_Write(CH_7, 9, 2);
  	Numeric_Write(DMX_Values[CH_7], 9, 3);

  		// canal 8
  	Numeric_Write(CH_8, 13, 2);
  	Numeric_Write(DMX_Values[CH_8], 13, 3);

		// iniciar navegacion y evaluar el index seleccionado
	Navegar(0, 0);	// actualiza Cursor_Index_Pos

	int valor_nuevo = 0;

	switch (Cursor_Index_Pos)
	{
			// 1 Channel
		case 1:
			valor_nuevo = Numerico_Write(1, 512, 1, 0, 1, CH_1);				// int  Numerico_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, int num_ant)

				// menor o igual al limites
			if (valor_nuevo <= 512)					// poner limite max
			{
				CH_1 = valor_nuevo;
			}

				// encoder
			if (valor_nuevo == 513)					// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(1, 512, 1, 0, 1, CH_1);	// int  Numerico_Enc_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, long num_ant)
					
					if (valor_nuevo > 512)			// poner limite max
					{
						break; 						// enter
					}

					CH_1 = valor_nuevo;
					Numeric_Write(DMX_Values[CH_1], 1, 1);
				}

					// acomodar numero 	
				Numerico_Print(1, 0, CH_1, 512, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

			Canal_Actual = CH_1;

				// ubicar
			if (valor_nuevo == 514)					// poner limite max + 2
			{
				Numeric_Write(CH_1, 1, 0);			// escribir canal
				Ubicar(1, 1, DMX_Values[CH_1]);		// void Ubicar(byte y, byte x, num ant)
			}

			break;

			// 1 Value
		case 2:
			valor_nuevo = Numerico_Write(0, 255, 1, 1, 1, DMX_Values[CH_1]);

				// menor o igual al limites
			if (valor_nuevo <= 255)					// poner limite max
			{
				ArduinoDmx0.TxBuffer[CH_1 - 1] = valor_nuevo;
				DMX_Values[CH_1] = valor_nuevo;
			}

				// encoder
			if (valor_nuevo == 256)					// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(0, 255, 1, 1, 1, DMX_Values[CH_1]);
					
					if (valor_nuevo > 255)			// poner limite max
					{
						break; 						// enter
					}

					ArduinoDmx0.TxBuffer[CH_1 - 1] = valor_nuevo;
					DMX_Values[CH_1] = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(1, 1, DMX_Values[CH_1], 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

				// ubicar
			if (valor_nuevo == 257)					// poner limite max + 2
			{
				Ubicar(1, 1, DMX_Values[CH_1]);		// void Ubicar(byte y, byte x, num ant)
			}

			break;

			// 2 Channel
		case 3:
			valor_nuevo = Numerico_Write(1, 512, 5, 0, 1, CH_2);				// int  Numerico_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, int num_ant)

				// menor o igual al limites
			if (valor_nuevo <= 512)					// poner limite max
			{
				CH_2 = valor_nuevo;
			}

				// encoder
			if (valor_nuevo == 513)					// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(1, 512, 5, 0, 1, CH_2);	// int  Numerico_Enc_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, long num_ant)
					
					if (valor_nuevo > 512)			// poner limite max
					{
						break; 						// enter
					}

					CH_2 = valor_nuevo;
					Numeric_Write(DMX_Values[CH_2], 5, 1);
				}

					// acomodar numero 	
				Numerico_Print(5, 0, CH_2, 512, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

			Canal_Actual = CH_2;

				// ubicar
			if (valor_nuevo == 514)					// poner limite max + 2
			{
				Numeric_Write(CH_2, 5, 0);			// escribir canal
				Ubicar(5, 1, DMX_Values[CH_2]);		// void Ubicar(byte y, byte x, num ant)
			}

			break;

			// 2 Value
		case 4:
			valor_nuevo = Numerico_Write(0, 255, 5, 1, 1, DMX_Values[CH_2]);

				// menor o igual al limites
			if (valor_nuevo <= 255)					// poner limite max
			{
				ArduinoDmx0.TxBuffer[CH_2 - 1] = valor_nuevo;
				DMX_Values[CH_2] = valor_nuevo;
			}

				// encoder
			if (valor_nuevo == 256)					// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(0, 255, 5, 1, 1, DMX_Values[CH_2]);
					
					if (valor_nuevo > 255)			// poner limite max
					{
						break; 						// enter
					}

					ArduinoDmx0.TxBuffer[CH_2 - 1] = valor_nuevo;
					DMX_Values[CH_2] = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(5, 1, DMX_Values[CH_2], 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

				// ubicar
			if (valor_nuevo == 257)					// poner limite max + 2
			{
				Ubicar(5, 1, DMX_Values[CH_2]);		// void Ubicar(byte y, byte x, num ant)
			}

			break;

			// 3 Channel
		case 5:
			valor_nuevo = Numerico_Write(1, 512, 9, 0, 1, CH_3);				// int  Numerico_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, int num_ant)

				// menor o igual al limites
			if (valor_nuevo <= 512)					// poner limite max
			{
				CH_3 = valor_nuevo;
			}

				// encoder
			if (valor_nuevo == 513)					// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(1, 512, 9, 0, 1, CH_3);	// int  Numerico_Enc_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, long num_ant)
					
					if (valor_nuevo > 512)			// poner limite max
					{
						break; 						// enter
					}

					CH_3 = valor_nuevo;
					Numeric_Write(DMX_Values[CH_3], 9, 1);
				}

					// acomodar numero 	
				Numerico_Print(9, 0, CH_3, 512, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

			Canal_Actual = CH_3;

				// ubicar
			if (valor_nuevo == 514)					// poner limite max + 2
			{
				Numeric_Write(CH_3, 9, 0);			// escribir canal
				Ubicar(9, 1, DMX_Values[CH_3]);		// void Ubicar(byte y, byte x, num ant)
			}

			break;

			// 3 Value
		case 6:
			valor_nuevo = Numerico_Write(0, 255, 9, 1, 1, DMX_Values[CH_3]);

				// menor o igual al limites
			if (valor_nuevo <= 255)					// poner limite max
			{
				ArduinoDmx0.TxBuffer[CH_3 - 1] = valor_nuevo;
				DMX_Values[CH_3] = valor_nuevo;
			}

				// encoder
			if (valor_nuevo == 256)					// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(0, 255, 9, 1, 1, DMX_Values[CH_3]);
					
					if (valor_nuevo > 255)			// poner limite max
					{
						break; 						// enter
					}

					ArduinoDmx0.TxBuffer[CH_3 - 1] = valor_nuevo;
					DMX_Values[CH_3] = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(9, 1, DMX_Values[CH_3], 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

				// ubicar
			if (valor_nuevo == 257)					// poner limite max + 2
			{
				Ubicar(9, 1, DMX_Values[CH_3]);		// void Ubicar(byte y, byte x, num ant)
			}

			break;

			// 4 Channel
		case 7:
			valor_nuevo = Numerico_Write(1, 512, 13, 0, 1, CH_4);				// int  Numerico_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, int num_ant)

				// menor o igual al limites
			if (valor_nuevo <= 512)					// poner limite max
			{
				CH_4 = valor_nuevo;
			}

				// encoder
			if (valor_nuevo == 513)					// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(1, 512, 13, 0, 1, CH_4);	// int  Numerico_Enc_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, long num_ant)
					
					if (valor_nuevo > 512)			// poner limite max
					{
						break; 						// enter
					}

					CH_4 = valor_nuevo;
					Numeric_Write(DMX_Values[CH_4], 13, 1);
				}

					// acomodar numero 	
				Numerico_Print(13, 0, CH_4, 512, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

			Canal_Actual = CH_4;

				// ubicar
			if (valor_nuevo == 514)					// poner limite max + 2
			{
				Numeric_Write(CH_4, 13, 0);			// escribir canal
				Ubicar(13, 1, DMX_Values[CH_4]);		// void Ubicar(byte y, byte x, num ant)
			}

			break;

			// 4 Value
		case 8:
			valor_nuevo = Numerico_Write(0, 255, 13, 1, 1, DMX_Values[CH_4]);

				// menor o igual al limites
			if (valor_nuevo <= 255)					// poner limite max
			{
				ArduinoDmx0.TxBuffer[CH_4 - 1] = valor_nuevo;
				DMX_Values[CH_4] = valor_nuevo;
			}

				// encoder
			if (valor_nuevo == 256)					// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(0, 255, 13, 1, 1, DMX_Values[CH_4]);
					
					if (valor_nuevo > 255)			// poner limite max
					{
						break; 						// enter
					}

					ArduinoDmx0.TxBuffer[CH_4 - 1] = valor_nuevo;
					DMX_Values[CH_4] = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(13, 1, DMX_Values[CH_4], 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

				// ubicar
			if (valor_nuevo == 257)					// poner limite max + 2
			{
				Ubicar(13, 1, DMX_Values[CH_4]);	// void Ubicar(byte y, byte x, num ant)
			}

			break;

			// 5 Channel
		case 9:
			valor_nuevo = Numerico_Write(1, 512, 1, 2, 1, CH_5);				// int  Numerico_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, int num_ant)

				// menor o igual al limites
			if (valor_nuevo <= 512)					// poner limite max
			{
				CH_5 = valor_nuevo;
			}

				// encoder
			if (valor_nuevo == 513)					// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(1, 512, 1, 2, 1, CH_5);	// int  Numerico_Enc_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, long num_ant)
					
					if (valor_nuevo > 512)			// poner limite max
					{
						break; 						// enter
					}

					CH_5 = valor_nuevo;
					Numeric_Write(DMX_Values[CH_5], 1, 3);
				}

					// acomodar numero 	
				Numerico_Print(1, 2, CH_5, 512, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

			Canal_Actual = CH_5;

				// ubicar
			if (valor_nuevo == 514)					// poner limite max + 2
			{
				Numeric_Write(CH_5, 1, 2);			// escribir canal
				Ubicar(1, 3, DMX_Values[CH_5]);		// void Ubicar(byte y, byte x, num ant)
			}

			break;

			// 5 Value
		case 10:
			valor_nuevo = Numerico_Write(0, 255, 1, 3, 1, DMX_Values[CH_5]);

				// menor o igual al limites
			if (valor_nuevo <= 255)					// poner limite max
			{
				ArduinoDmx0.TxBuffer[CH_5 - 1] = valor_nuevo;
				DMX_Values[CH_5] = valor_nuevo;
			}

				// encoder
			if (valor_nuevo == 256)					// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(0, 255, 1, 3, 1, DMX_Values[CH_5]);
					
					if (valor_nuevo > 255)			// poner limite max
					{
						break; 						// enter
					}

					ArduinoDmx0.TxBuffer[CH_5 - 1] = valor_nuevo;
					DMX_Values[CH_5] = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(1, 3, DMX_Values[CH_5], 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

				// ubicar
			if (valor_nuevo == 257)					// poner limite max + 2
			{
				Ubicar(1, 3, DMX_Values[CH_5]);	// void Ubicar(byte y, byte x, num ant)
			}

			break;

			// 6 Channel
		case 11:
			valor_nuevo = Numerico_Write(1, 512, 5, 2, 1, CH_6);				// int  Numerico_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, int num_ant)

				// menor o igual al limites
			if (valor_nuevo <= 512)					// poner limite max
			{
				CH_6 = valor_nuevo;
			}

				// encoder
			if (valor_nuevo == 513)					// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(1, 512, 5, 2, 1, CH_6);	// int  Numerico_Enc_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, long num_ant)
					
					if (valor_nuevo > 512)			// poner limite max
					{
						break; 						// enter
					}

					CH_6 = valor_nuevo;
					Numeric_Write(DMX_Values[CH_6], 5, 3);
				}

					// acomodar numero 	
				Numerico_Print(5, 2, CH_6, 512, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

			Canal_Actual = CH_6;

				// ubicar
			if (valor_nuevo == 514)					// poner limite max + 2
			{
				Numeric_Write(CH_6, 5, 2);			// escribir canal
				Ubicar(5, 3, DMX_Values[CH_6]);		// void Ubicar(byte y, byte x, num ant)
			}

			break;

			// 6 Value
		case 12:
			valor_nuevo = Numerico_Write(0, 255, 5, 3, 1, DMX_Values[CH_6]);

				// menor o igual al limites
			if (valor_nuevo <= 255)					// poner limite max
			{
				ArduinoDmx0.TxBuffer[CH_6 - 1] = valor_nuevo;
				DMX_Values[CH_6] = valor_nuevo;
			}

				// encoder
			if (valor_nuevo == 256)					// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(0, 255, 5, 3, 1, DMX_Values[CH_6]);
					
					if (valor_nuevo > 255)			// poner limite max
					{
						break; 						// enter
					}

					ArduinoDmx0.TxBuffer[CH_6 - 1] = valor_nuevo;
					DMX_Values[CH_6] = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(5, 3, DMX_Values[CH_6], 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

				// ubicar
			if (valor_nuevo == 257)					// poner limite max + 2
			{
				Ubicar(5, 3, DMX_Values[CH_6]);	// void Ubicar(byte y, byte x, num ant)
			}

			break;

			// 7 Channel
		case 13:
			valor_nuevo = Numerico_Write(1, 512, 9, 2, 1, CH_7);				// int  Numerico_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, int num_ant)

				// menor o igual al limites
			if (valor_nuevo <= 512)					// poner limite max
			{
				CH_7 = valor_nuevo;
			}

				// encoder
			if (valor_nuevo == 513)					// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(1, 512, 9, 2, 1, CH_7);	// int  Numerico_Enc_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, long num_ant)
					
					if (valor_nuevo > 512)			// poner limite max
					{
						break; 						// enter
					}

					CH_7 = valor_nuevo;
					Numeric_Write(DMX_Values[CH_7], 9, 3);
				}

					// acomodar numero 	
				Numerico_Print(9, 2, CH_7, 512, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

			Canal_Actual = CH_7;

				// ubicar
			if (valor_nuevo == 514)					// poner limite max + 2
			{
				Numeric_Write(CH_7, 9, 2);			// escribir canal
				Ubicar(9, 3, DMX_Values[CH_7]);		// void Ubicar(byte y, byte x, num ant)
			}

			break;

			// 7 Value
		case 14:
			valor_nuevo = Numerico_Write(0, 255, 9, 3, 1, DMX_Values[CH_7]);

				// menor o igual al limites
			if (valor_nuevo <= 255)					// poner limite max
			{
				ArduinoDmx0.TxBuffer[CH_7 - 1] = valor_nuevo;
				DMX_Values[CH_7] = valor_nuevo;
			}

				// encoder
			if (valor_nuevo == 256)					// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(0, 255, 9, 3, 1, DMX_Values[CH_7]);
					
					if (valor_nuevo > 255)			// poner limite max
					{
						break; 						// enter
					}

					ArduinoDmx0.TxBuffer[CH_7 - 1] = valor_nuevo;
					DMX_Values[CH_7] = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(9, 3, DMX_Values[CH_7], 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

				// ubicar
			if (valor_nuevo == 257)					// poner limite max + 2
			{
				Ubicar(9, 3, DMX_Values[CH_7]);	// void Ubicar(byte y, byte x, num ant)
			}

			break;

			// 8 Channel
		case 15:
			valor_nuevo = Numerico_Write(1, 512, 13, 2, 1, CH_8);				// int  Numerico_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, int num_ant)

				// menor o igual al limites
			if (valor_nuevo <= 512)					// poner limite max
			{
				CH_8 = valor_nuevo;
			}

				// encoder
			if (valor_nuevo == 513)					// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(1, 512, 13, 2, 1, CH_8);	// int  Numerico_Enc_Write(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, long num_ant)
					
					if (valor_nuevo > 512)			// poner limite max
					{
						break; 						// enter
					}

					CH_8 = valor_nuevo;
					Numeric_Write(DMX_Values[CH_8], 13, 3);
				}

					// acomodar numero 	
				Numerico_Print(13, 2, CH_8, 512, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

			Canal_Actual = CH_8;

				// ubicar
			if (valor_nuevo == 514)					// poner limite max + 2
			{
				Numeric_Write(CH_8, 13, 2);			// escribir canal
				Ubicar(13, 3, DMX_Values[CH_8]);		// void Ubicar(byte y, byte x, num ant)
			}

			break;

			// 8 Value
		case 16:
			valor_nuevo = Numerico_Write(0, 255, 13, 3, 1, DMX_Values[CH_8]);

				// menor o igual al limites
			if (valor_nuevo <= 255)					// poner limite max
			{
				ArduinoDmx0.TxBuffer[CH_8 - 1] = valor_nuevo;
				DMX_Values[CH_8] = valor_nuevo;
			}

				// encoder
			if (valor_nuevo == 256)					// poner limite max + 1
			{
				while(1)
				{
					valor_nuevo = Numerico_Enc_Write(0, 255, 13, 3, 1, DMX_Values[CH_8]);
					
					if (valor_nuevo > 255)			// poner limite max
					{
						break; 						// enter
					}

					ArduinoDmx0.TxBuffer[CH_8 - 1] = valor_nuevo;
					DMX_Values[CH_8] = valor_nuevo;
		
				}
					// acomodar numero 	
				Numerico_Print(13, 3, DMX_Values[CH_8], 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
			}

				// ubicar
			if (valor_nuevo == 257)					// poner limite max + 2
			{
				Ubicar(13, 3, DMX_Values[CH_8]);	// void Ubicar(byte y, byte x, num ant)
			}

			break;

			// memoria
		case 17:
			GUI_Memory();
			Cursor_Index_Pos = 17;
			goto inicio;
			break;

			// salida
		case 18:
			goto salir;
			break;
	}

  	goto navegacion;

  	salir:
  		// guardar canal actual
  	Canal_Actual_EEPROM_Save();
}

void Ubicar 					(byte y, byte x, byte val_ant)	// parpadea el canal actual
{
  	digitalWrite(Keypad_C, LOW);

  	delay(300);
  
  	while (digitalRead(Keypad_4) == HIGH && digitalRead(Enc_Center) == HIGH)
  	{
    	ArduinoDmx0.TxBuffer[Canal_Actual - 1] = 255;
    	Numeric_Write (255, y, x);		// void Numeric_Write (int valor, int col, int row)
    	delay (100);
    	ArduinoDmx0.TxBuffer[Canal_Actual - 1] = 0;
    	lcd.setCursor (y, x);
    	lcd.print ("   ");
    	delay (100);
  	}

  	delay(300); 	// rebote de boton enter

  	lcd.noBlink();
  	digitalWrite(Keypad_C, HIGH);
  	ArduinoDmx0.TxBuffer[Canal_Actual - 1] = val_ant;

  		// acomodar anterior
  	Numerico_Print(y, x, val_ant, 255, 1);	// poner max 	// Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
}

// ----------------------------- Navegacion LCD - Encoder - Keypad v0.0 -----------------------------

void Numeric_Write 				(int valor, int col, int row)	// posicionar el valor en los campos 000
{
	lcd.setCursor 	(col, row);
	lcd.print 		("000");

	if (valor < 10)
	{
		lcd.setCursor (col + 2, row);
	}

	if (valor > 9 && valor < 100)
	{
		lcd.setCursor (col + 1, row);
	}

	if (valor > 99)
	{
		lcd.setCursor (col, row);
	}

	lcd.print (valor);
}

void Numerico_Print 			(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
{
	// valor: numero a acomodar
	// max: numero maximo, para el espaciado
	// Dec_Hex: Dec 1, Hex 2
	// LCD_x: cursor
	// LCD_y: cursor

	// calcular tamaño
	lcd.noBlink 	();						// no parpadear cursor
	lcd.setCursor	(LCD_x, LCD_y);

		// Dec
	if (Dec_Hex == 1)				
	{
		if (max < 10)						// 1 cifra
		{
			lcd.print(valor);
			goto salir;
		}

		if (max > 9 && max < 100)			// 2 cifras
		{
			if (valor < 10)
			{
				lcd.print(0);
				lcd.print(valor);
			}
			else
			{
				lcd.print(valor);
			}

			goto salir;
		}

		if (max > 99 && max < 1000)			// 3 cifras
		{
			if (valor < 10)
			{
				lcd.print("00");
				lcd.print(valor);
			}

			if (valor > 9 && valor < 100)
			{
				lcd.print("0");
				lcd.print(valor);
			}

			if (valor > 99)
			{
				lcd.print(valor);
			}

			goto salir;
		}

		if (max > 999)						// 4 cifras
		{
			if (valor < 10)
			{
				lcd.print("000");
				lcd.print(valor);
			}

			if (valor > 9 && valor < 100)
			{
				lcd.print("00");
				lcd.print(valor);
			}

			if (valor > 99)
			{
				lcd.print("0");
				lcd.print(valor);
			}

			if (valor > 999)
			{
				lcd.print(valor);
			}

			goto salir;
		}
	}
		// hexadecimal
	if (Dec_Hex == 2)				
	{
		if (valor < 16)
		{
			lcd.print("0");
			lcd.print(valor, HEX);
			goto salir;
		}

		if (valor > 15)
		{
			lcd.print(valor, HEX);
		}
	}

	salir: {}
}

void Navegar_Matrix 			(byte Y, byte X, int Canal_init)
{
	// posicion del canal
	lcd.setCursor(1, 0);

		// memory
	if (Y == 4 && X == 0)
	{
		lcd.setCursor 	(1, 0);
		lcd.print 		("---");
		goto salida;
	}

		// Exit
	if (Y == 8 && X == 0)
	{
		lcd.setCursor 	(1, 0);
		lcd.print 		("---");
		goto salida;
	}

		// inicial
	if (Y == 12 && X == 0)
	{
		Numerico_Print(1, 0, Canal_init, 512, 1);			// void Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
		goto salida;
	}

		// final
	if (Y == 16 && X == 0)
	{
		Numerico_Print(1, 0, Canal_init + 14, 512, 1);		// void Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
		goto salida;
	}

		// 1
	if (Y == 0 && X == 1)
	{
		Numerico_Print(1, 0, Canal_init, 512, 1);			// void Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
		goto salida;
	}

		// 2
	if (Y == 4 && X == 1)
	{
		Numerico_Print(1, 0, Canal_init + 1, 512, 1);		// void Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
		goto salida;
	}

		// 3
	if (Y == 8 && X == 1)
	{
		Numerico_Print(1, 0, Canal_init + 2, 512, 1);		// void Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
		goto salida;
	}

		// 4
	if (Y == 12 && X == 1)
	{
		Numerico_Print(1, 0, Canal_init + 3, 512, 1);		// void Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
		goto salida;
	}

		// 5
	if (Y == 16 && X == 1)
	{
		Numerico_Print(1, 0, Canal_init + 4, 512, 1);		// void Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
		goto salida;
	}

		// 6
	if (Y == 0 && X == 2)
	{
		Numerico_Print(1, 0, Canal_init + 5, 512, 1);		// void Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
		goto salida;
	}

		// 7
	if (Y == 4 && X == 2)
	{
		Numerico_Print(1, 0, Canal_init + 6, 512, 1);		// void Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
		goto salida;
	}

		// 8
	if (Y == 8 && X == 2)
	{
		Numerico_Print(1, 0, Canal_init + 7, 512, 1);		// void Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
		goto salida;
	}

		// 9
	if (Y == 12 && X == 2)
	{
		Numerico_Print(1, 0, Canal_init + 8, 512, 1);		// void Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
		goto salida;
	}

		// 10
	if (Y == 16 && X == 2)
	{
		Numerico_Print(1, 0, Canal_init + 9, 512, 1);		// void Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
		goto salida;
	}

		// 11
	if (Y == 0 && X == 3)
	{
		Numerico_Print(1, 0, Canal_init + 10, 512, 1);		// void Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
		goto salida;
	}

		// 12
	if (Y == 4 && X == 3)
	{
		Numerico_Print(1, 0, Canal_init + 11, 512, 1);		// void Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
		goto salida;
	}

		// 13
	if (Y == 8 && X == 3)
	{
		Numerico_Print(1, 0, Canal_init + 12, 512, 1);		// void Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
		goto salida;
	}

		// 14
	if (Y == 12 && X == 3)
	{
		Numerico_Print(1, 0, Canal_init + 13, 512, 1);		// void Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
		goto salida;
	}

		// 15
	if (Y == 16 && X == 3)
	{
		Numerico_Print(1, 0, Canal_init + 14, 512, 1);		// void Numerico_Print(byte LCD_x, byte LCD_y, int valor, int max, byte Dec_Hex)
		goto salida;
	}

	salida: {}
}

void Navegar 					(byte matrix, byte matrix_ch_init) // actualiza Cursor_Index_Pos
{
	// matrix 1, para gui matrix, 0 normal

	byte Index_Final = 0;	// saber cual es el ultimo indice

		// buscar donde poner el cursor y ultimo indice
	for (byte Conteo_Y = 0; Conteo_Y <= 19; Conteo_Y ++)
	{
		for (byte Conteo_X = 0; Conteo_X <= 3; Conteo_X ++)
		{
				// posicionar cursor
			if (Cursor_Index[Conteo_Y][Conteo_X] == Cursor_Index_Pos)
			{
				lcd.setCursor (Conteo_Y, Conteo_X);
				lcd.write(byte(0));	// caracter cursor

					// matrix
				if (matrix == 1)
				{
					Navegar_Matrix(Conteo_Y, Conteo_X, matrix_ch_init);
				}
			}
				// saber ultimo indice
			if (Cursor_Index[Conteo_Y][Conteo_X] > Index_Final)
			{
				Index_Final = Cursor_Index[Conteo_Y][Conteo_X];
			}
		}
	} 

	long Enc_ant 				= myEnc.read() / 4;
	long Enc_read				= 0;
	int  Cursor_Index_Pos_ant 	= 0;
	byte giro 					= 0;

		// Lectura de encoder
	while(digitalRead(Enc_Center) == 1)
	{
		Enc_read = myEnc.read() / 4;
		Cursor_Index_Pos_ant = Cursor_Index_Pos;
		giro = 0;

			// lectura de teclado para lights
		digitalWrite(Keypad_D, LOW);

			// * - External Light
		if (digitalRead(Keypad_1) == 0)
		{
			External_light_En();
		}
		
			// # - Back light y Key Light
		if (digitalRead(Keypad_3) == 0)
		{
			Back_light_Key_light_En();
		}

		digitalWrite(Keypad_D, HIGH);

			// izquierda
		if (Enc_read < Enc_ant)
		{
			Enc_ant = Enc_read;

				// restar Cursor_Index_Pos
			Cursor_Index_Pos = Cursor_Index_Pos - 1;

				// limites
			if(Cursor_Index_Pos < 1)
			{
				Cursor_Index_Pos = Index_Final;
			}

			giro = 1;
		}

			// derecha
		if (Enc_read > Enc_ant)		
		{
			Enc_ant = Enc_read;

				// sumar Cursor_Index_Pos
			Cursor_Index_Pos = Cursor_Index_Pos + 1;

					// limites
			if(Cursor_Index_Pos > Index_Final)
			{
				Cursor_Index_Pos = 1;
			}

			giro = 1;
		}

			// si se giro...
		if (giro == 1)
		{
			// posicionar cursor
			for (byte Conteo_Y = 0; Conteo_Y <= 19; Conteo_Y ++)
			{
				for (byte Conteo_X = 0; Conteo_X <= 3; Conteo_X ++)
				{
						// posicionar cursor
					if (Cursor_Index[Conteo_Y][Conteo_X] == Cursor_Index_Pos)
					{
						lcd.setCursor (Conteo_Y, Conteo_X);
						lcd.write(byte(0));	// caracter cursor

							// matrix
						if (matrix == 1)
						{
							Navegar_Matrix(Conteo_Y, Conteo_X, matrix_ch_init);
						}
					}

						// borrar cursor anterior
					if (Cursor_Index[Conteo_Y][Conteo_X] == Cursor_Index_Pos_ant)
					{
						lcd.setCursor (Conteo_Y, Conteo_X);
						lcd.print(" ");
					}
				}
			}
		}
	}

	delay(300); // rebote de centro encoder
}

void Cursor_Index_Clear			() // borrar el indice
{	
	for (byte Conteo_Y = 0; Conteo_Y <= 19; Conteo_Y ++)
	{
		for (byte Conteo_X = 0; Conteo_X <= 3; Conteo_X ++)
		{
			Cursor_Index[Conteo_Y][Conteo_X] = 0;
		}
	}
}

int  Numerico_Enc_Write 		(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, long num_ant) // regresa el numero generado por el encoder
{
	// numero minimo a escribir - numero maximo a escribir - x y de pantalla donde se escribe
	// num_ant, el numero que estaba impreso
	// Dec_Hex decimal 1, hexadecimal 2
	// enter: encoder centro
	// hexadecimal max 2 digitos
	// si regresa numero max + 1 se presiono enter en encoder

	long Enc_ant 		= myEnc.read() / 4;
	long Enc_read		= 0;
	int  numero_lenght 	= 0;
	int  Enc_Real_Time  = 0;

	Enc_Real_Time 		= num_ant;

	lcd.setCursor 	(LCD_x, LCD_y);
	lcd.blink 		();					// parpadear cursor
	lcd.setCursor 	(LCD_x, LCD_y);
	lcd.print 		(num_ant);
	lcd.setCursor 	(LCD_x, LCD_y);
	
		// esperar giro
	while(1)
	{
		Enc_read = myEnc.read() / 4;
			
		// incrementar
		if (Enc_read > Enc_ant)	
		{
			Enc_Real_Time = Enc_Real_Time + 1;

			// limites
			if (Enc_Real_Time > max)
			{
				Enc_Real_Time = min;
				goto calculo;
			}

			goto calculo;
		}

			// decrementar
		else if (Enc_read < Enc_ant)	
		{
			Enc_Real_Time = Enc_Real_Time - 1;

				// limites
			if (Enc_Real_Time < min)
			{
				Enc_Real_Time = max;
				goto calculo;
			}

			goto calculo;
		}

		if (digitalRead(Enc_Center) == 0)
		{
			delay(300);		// rebote
			
			return max + 1;
		}
	}
	
	calculo:

	// calcular tamaños maximos del numero

		// decimal
	if (Dec_Hex == 1)				
	{
		if (max < 10)
		{
			numero_lenght = 1;
		}

		if (max > 9)
		{
			numero_lenght = 2;
		}

		if (max > 99)
		{
			numero_lenght = 3;
		}

		if (max > 999)
		{
			numero_lenght = 4;
		}
	}

		// hexadecimal
	if (Dec_Hex == 2)				
	{
		if (max < 16)
		{
			numero_lenght = 1;
		}

		if (max > 15)
		{
			numero_lenght = 2;
		}
	}
	
	// borrar numeros anteriores

	lcd.setCursor(LCD_x, LCD_y);

	if (numero_lenght == 2)
	{
		lcd.print("  ");
	}

	if (numero_lenght == 3)
	{
		lcd.print("   ");
	}

	if (numero_lenght == 4)
	{
		lcd.print("    ");
	}

	// dibujar numero
	
	lcd.setCursor(LCD_x, LCD_y);

		// dec
	if (Dec_Hex == 1)
	{
		lcd.print(Enc_Real_Time);
	}

		// hex
	if (Dec_Hex == 2)
	{
		lcd.print(Enc_Real_Time, HEX);
	}

	return Enc_Real_Time;
}

int  Numerico_Write 			(int min, int max, byte LCD_x, byte LCD_y, byte Dec_Hex, int num_ant) // regresa el numero tecleado
{
	// regresa max + 1 cuando se selecciona D para encoder
	// regresa max + 2 para ubicacion
	// A regresa max
	// B regresa min
	// numero minimo a escribir - numero maximo a escribir - x y de pantalla donde se escribe
	// el calculo del tamaño del numero lo hace en automatico
	// num_ant, el numero que estaba impreso
	// Dec_Hex decimal 1, hexadecimal 2
	// enter: encoder centro
	// cancelar y poner numero default: *
	// hexadecimal max 2 digitos
	// entrada desde encoder: D
	// si regresa numero max + 1 se presiono D para encoder
	
	int 	numero_lenght 		= 0;
	int 	retardo_lecturas 	= 300;
	byte 	numero_1			= 0;
	byte	numero_2			= 0;
	byte	numero_3			= 0;
	byte	numero_4			= 0;
	byte 	lectura 			= 0;
	byte 	numero_unidades		= 0;
	int 	numero 				= 0;
	
	lcd.blink();	// parpadear cursor
	
	// calcular tamaño de numero de espacios que ve a utilizar el numero maximo

		// decimal
	if (Dec_Hex == 1)				
	{
		if (max < 10)
		{
			numero_lenght = 1;
		}

		if (max > 9)
		{
			numero_lenght = 2;
		}

		if (max > 99)
		{
			numero_lenght = 3;
		}

		if (max > 999)
		{
			numero_lenght = 4;
		}
	}
		// hexadecimal
	if (Dec_Hex == 2)				
	{
		if (max < 16)
		{
			numero_lenght = 1;
		}

		if (max > 15)
		{
			numero_lenght = 2;
		}
	}
	
		// LCD posicionar cursor	
	lcd.setCursor(LCD_x, LCD_y);
	if (numero_lenght == 1)
	{
		lcd.print 		("_");
		lcd.setCursor	(LCD_x, LCD_y);
	}
	if (numero_lenght == 2)
	{
		lcd.print 		("__");
		lcd.setCursor 	(LCD_x + 1, LCD_y);
	}
	if (numero_lenght == 3)
	{
		lcd.print 		("___");
		lcd.setCursor 	(LCD_x + 2, LCD_y);
	}
	if (numero_lenght == 4)
	{
		lcd.print 		("____");
		lcd.setCursor 	(LCD_x + 3, LCD_y);
	}
	
	dibujar_numero_1:

	lectura = Numerico_Key(); // A = 10, B = 11, C = 12, D = 13, # = 14, * = 15, encoder center = 16
		
		// D - lectura desde encoder
	if (lectura == 13)	
	{
		lcd.noBlink();
		return max + 1;
	}

		// A - numero maximo
	if (lectura == 10)	
	{
		numero = max;
		goto numero_max_min;
	}

		// B - numero minimo
	if (lectura == 11)	
	{
		numero = min;
		goto numero_max_min;
	}

		// C - ubicar
	if (lectura == 12)	
	{
		lcd.noBlink();
		return max + 2;
	}

		// reglas decimal
	if (Dec_Hex == 1)
	{
		if (lectura == 16)					// enter, sin numero
		{
			goto numero_ant;
		}

		if (lectura > 9 && lectura < 16)	// tecla no valida
		{
			goto dibujar_numero_1;
		}
	}
	
		// reglas hexadecimal
	if (Dec_Hex == 2)
	{
		if (lectura == 16)					// enter, sin numero
		{
			goto numero_ant;
		}
	}
	
	// dibujar numero
	lcd.setCursor(LCD_x, LCD_y);

		// decimal
	if (Dec_Hex == 1)
	{
		if (numero_lenght == 1)
		{
			lcd.print(lectura);
			numero_1 = lectura;
			goto salida;
		}

		if (numero_lenght == 2)
		{
			lcd.setCursor(LCD_x + 1, LCD_y);
			lcd.print(lectura);
			lcd.setCursor(LCD_x + 1, LCD_y);
		}

		if (numero_lenght == 3)
		{
			lcd.setCursor(LCD_x + 2, LCD_y);
			lcd.print(lectura);
			lcd.setCursor(LCD_x + 2, LCD_y);
		}

		if (numero_lenght == 4)
		{
			lcd.setCursor(LCD_x + 3, LCD_y);
			lcd.print(lectura);
			lcd.setCursor(LCD_x + 3, LCD_y);
		}
	}

		// hexadecimal
	if (Dec_Hex == 2)
	{
		if (numero_lenght == 1)
		{
			lcd.print(lectura, HEX);
			numero_1 = lectura;
			goto salida;
		}

		if (numero_lenght ==  2)
		{
			lcd.setCursor(LCD_x + 1, LCD_y);
			lcd.print(lectura, HEX);
			lcd.setCursor(LCD_x + 1, LCD_y);
		}
	}
	
		// continuar
	numero_1 = lectura;

	dibujar_numero_2:

	delay(retardo_lecturas);
	lectura = Numerico_Key();
	
		// reglas decimal
	if (Dec_Hex == 1)
	{
		if (lectura == 16 || lectura == 14)	// enter, numero 1
		{
			lcd.setCursor(LCD_x, LCD_y);
			lcd.print("0");
			numero_2 = 0;
			numero_unidades = 1;
			goto salida;
		}

		if (lectura > 9 && lectura < 16)	// tecla no valida
		{
			goto dibujar_numero_2;
		}

		if (lectura == 15)					// cancelar
		{
			goto numero_ant;
		}
	}
		// reglas hexadecimal
	if (Dec_Hex == 2)
	{
		if (lectura == 16)					// enter encoder, solo numero 1
		{
			lcd.setCursor(LCD_x, LCD_y);
			lcd.print("0");
			numero_2 = 0;
			numero_unidades = 1;
			goto salida;
		}
	}
	
	// dibujar numero
		// decimal
	if (Dec_Hex == 1)
	{
		lcd.setCursor(LCD_x, LCD_y);
		if (numero_lenght == 2)
		{
			lcd.print(numero_1);
			lcd.print(lectura);
			numero_2 = lectura;
			goto salida;
		}

		if (numero_lenght == 3)
		{
			lcd.setCursor(LCD_x + 1, LCD_y);
			lcd.print(numero_1);
			lcd.print(lectura);
			lcd.setCursor(LCD_x + 2, LCD_y);
		}

		if (numero_lenght == 4)
		{
			lcd.setCursor(LCD_x + 2, LCD_y);
			lcd.print(numero_1);
			lcd.print(lectura);
			lcd.setCursor(LCD_x + 3, LCD_y);
		}
	}
		// hexadecimal
	if (Dec_Hex == 2)
	{
		lcd.setCursor(LCD_x, LCD_y);
		lcd.print(numero_1, HEX);
		lcd.print(lectura, HEX);
		numero_2 = lectura;
		goto salida;
	}		
	
	numero_2 = lectura;

	dibujar_numero_3:

	delay(retardo_lecturas);
	
	lectura = Numerico_Key();
	
		// reglas
	if (lectura == 16)	// enter, numero 2
	{
		numero_3 = 0;
		numero_unidades = 2;
		goto salida;
	}

	if (lectura > 9 && lectura < 16)	// tecla no valida
	{
		goto dibujar_numero_3;
	}

	if (lectura == 15)					// cancelar
	{
		goto numero_ant;
	}	

		// dibujar numero
	lcd.setCursor(LCD_x, LCD_y);
	if (numero_lenght == 3)
	{
		lcd.print(numero_1);
		lcd.print(numero_2);
		lcd.print(lectura);
		numero_3 = lectura;
		goto salida;
	}

	if (numero_lenght == 4)
	{
		lcd.setCursor 	(LCD_x + 1, LCD_y);
		lcd.print 		(numero_1);
		lcd.print 		(numero_2);
		lcd.print 		(lectura);
		lcd.setCursor 	(LCD_x + 3, LCD_y);
	}

	numero_3 = lectura;	
	
	dibujar_numero_4:

	delay(retardo_lecturas);
	
	lectura = Numerico_Key();
	
		// reglas
	if (lectura == 16)	// enter, numero 3
	{
		numero_4 = 0;
		numero_unidades = 3;
		goto salida;
	}

	if (lectura > 9 && lectura < 16)	// tecla no valida
	{
		goto dibujar_numero_4;
	}

	if (lectura == 15)					// cancelar
	{
		goto numero_ant;
	}	

		// dibujar numero
	lcd.setCursor 	(LCD_x, LCD_y);
	lcd.print 		(numero_1);
	lcd.print 		(numero_2);
	lcd.print 		(numero_3);
	lcd.print 		(lectura);
	
	numero_4 = lectura;
		
	goto salida;	

	numero_max_min:
	
	lcd.noBlink();

		// inicial
	lcd.setCursor(LCD_x, LCD_y);

		// 2 digitos
	if (numero_lenght == 2)
	{
			// decimal
		if (Dec_Hex == 1)
		{
			if (numero < 10)
			{
				lcd.print("0");
			}
		}
			// hexadecimal
		if (Dec_Hex == 2)
		{
			if (numero < 16)
			{
				lcd.print("0");
			}
		}
	}
		// 3 digitos
	if (numero_lenght == 3)
	{
		if (numero < 10)
		{
			lcd.print("00");
		}

		if (numero > 9 && numero < 100)
		{
			lcd.print("0");
		}
	}
		// 4 digitos
	if (numero_lenght == 4)
	{
		if (numero < 10)
		{
			lcd.print("000");
		}

		if (numero > 9 && numero< 100)
		{
			lcd.print("00");
		}

		if (numero > 99 && numero < 1000)
		{
			lcd.print("0");
		}		
	}
		// dibujar numero
	if (Dec_Hex == 1)	// decimal
	{
		lcd.print(numero);
	}

	if (Dec_Hex == 2)	// hexadecimal
	{
		lcd.print(numero, HEX);
	}

	return numero;
	
	numero_ant:
	
	lcd.noBlink();

		// inicial
	lcd.setCursor(LCD_x, LCD_y);

		// 2 digitos
	if (numero_lenght == 2)
	{
			// decimal
		if (Dec_Hex == 1)
		{
			if (num_ant < 10)
			{
				lcd.print("0");
			}
		}

			// hexadecimal
		if (Dec_Hex == 2)
		{
			if (num_ant < 16)
			{
				lcd.print("0");
			}
		}
	}

		// 3 digitos
	if (numero_lenght == 3)
	{
		if (num_ant < 10)
		{
			lcd.print("00");
		}

		if (num_ant > 9 && num_ant < 100)
		{
			lcd.print("0");
		}
	}

		// 4 digitos
	if (numero_lenght == 4)
	{
		if (num_ant < 10)
		{
			lcd.print("000");
		}

		if (num_ant > 9 && num_ant < 100)
		{
			lcd.print("00");
		}

		if (num_ant > 99 && num_ant < 1000)
		{
			lcd.print("0");
		}		
	}

		// dibujar numero
	if (Dec_Hex == 1)	// decimal
	{
		lcd.print(num_ant);
	}

	if (Dec_Hex == 2)	// hexadecimal
	{
		lcd.print(num_ant, HEX);
	}

	return num_ant;
	
	salida:

		// agrupar numeros para enviar de vuelta
	lcd.noBlink();
	int numero_total = 0;
	int numero_temp  = 0;
	
		// 1 digito
	if (numero_lenght == 1)
	{
			// limites
		lcd.setCursor(LCD_x, LCD_y);
		if (numero_1 > max)
		{
			numero_1 = max;
			if (Dec_Hex == 1)	// decimal
			{
				lcd.print(max);
			}

			if (Dec_Hex == 2)	// hexadecimal
			{
				lcd.print(max, HEX);
			}
		}
		if (numero_1 < min)
		{
			numero_1 = min; 
			if (Dec_Hex == 1)	// decimal
			{
				lcd.print(min);
			}

			if (Dec_Hex == 2)	// hexadecimal
			{
				lcd.print(min, HEX);
			}
		}
		
		return numero_1;
	}
		// 2 digitos
	if (numero_lenght == 2)
	{
		// cncatenar numero
			// decimal
		if (Dec_Hex == 1)
		{
			if (numero_unidades == 0)
			{
				numero_total 	= numero_1 * 10;
				numero_total 	= numero_total + numero_2;
			}
			else
			{
				numero_total 	= numero_1;
			}
		
		}
			// hexadecimal
		if (Dec_Hex == 2)
		{
			if (numero_unidades == 0)
			{
				numero_total 	= numero_1 * 16;
				numero_total 	= numero_total + numero_2;
			}
			else
			{
				numero_total 	= numero_1;
			}
			
		}

			// limites
		if (numero_total > max)
		{
			numero_total = max;
		}

		if (numero_total < min)
		{
			numero_total = min;
		}

			// escribir numero
		lcd.setCursor(LCD_x, LCD_y);
		if (numero_total < 10)
		{
			lcd.print("0");
			if (Dec_Hex == 1)	// decimal
			{
				lcd.print(numero_total);
			}

			if (Dec_Hex == 2)	// hexadecimal
			{
				lcd.print(numero_total, HEX);
			}
		}

		if (numero_total > 9)
		{
			if (Dec_Hex == 1)	// decimal
			{
				lcd.print(numero_total);
			}

			if (Dec_Hex == 2)	// hexadecimal
			{
				if (numero_total > 15)
				{
					lcd.print(numero_total, HEX);
				}
				else
				{
					lcd.print("0");
					lcd.print(numero_total, HEX);
				}
				
			}
		}
		
		return numero_total;
	}
		// 3 digitos
	if (numero_lenght == 3)
	{
		// concatenar numero
			// 1 digitos
		if (numero_unidades == 1)
		{
			numero_total 	= numero_1;
		}
			// 2 digitos
		if (numero_unidades == 2)
		{
			numero_total 	= numero_1 * 10;
			numero_total	= numero_total + numero_2;
		}
			// 3 digitos
		if (numero_unidades == 0)
		{
			numero_total 	= numero_1 * 100;
			numero_temp		= numero_2 * 10; 
			numero_total	= numero_total + numero_temp + numero_3;
		}
		
		// limites
		if (numero_total > max)
		{
			numero_total = max;
		}

		if (numero_total < min)
		{
			numero_total = min;
		}
			// escribir numero
		lcd.setCursor(LCD_x, LCD_y);
		if (numero_total < 10)
		{
			lcd.print("00");
			lcd.print(numero_total);
		}

		if (numero_total > 9 && numero_total < 100)
		{
			lcd.print("0");
			lcd.print(numero_total);
		}

		if (numero_total > 99)
		{
			lcd.print(numero_total);
		}
		
		return numero_total;
	}
		// 4 digitos
	if (numero_lenght == 4)
	{
			// concatenar numeros
		if (numero_unidades == 1)
		{
			numero_total 	= numero_1;
		}

		if (numero_unidades == 2)
		{
			numero_total 	= numero_1 * 10;
			numero_total	= numero_total + numero_2;
		}

		if (numero_unidades == 3)
		{
			numero_total 	= numero_1 * 100;
			numero_temp		= numero_2 * 10;
			numero_total	= numero_total + numero_temp + numero_3;
		}

		if (numero_unidades == 0)
		{
			numero_total 	= numero_1 * 1000;
			numero_temp		= numero_2 * 100; 
			numero_total	= numero_total + numero_temp;
			numero_temp		= numero_3 * 10;
			numero_total	= numero_total + numero_temp + numero_4;
		}
			// limites
		if (numero_total > max)
		{
			numero_total = max;
		}

		if (numero_total < min)
		{
			numero_total = min;
		}
		
			// escribir numero
		lcd.setCursor(LCD_x, LCD_y);

		if (numero_total < 10)
		{
			lcd.print("000");
			lcd.print(numero_total);
		}

		if (numero_total > 9 && numero_total < 100)
		{
			lcd.print("00");
			lcd.print(numero_total);
		}

		if (numero_total > 99 && numero_total < 1000)
		{
			lcd.print("0");
			lcd.print(numero_total);
		}

		if (numero_total > 999)
		{
			lcd.print(numero_total);
		}
		
		return numero_total;
	}
}

int  Numerico_Key 				() // devuelve el numero de la tecla precionada o el centro del encoder
{
	// A = 10, B = 11, C = 12, D = 13, # = 14, * = 15, encoder center = 16
	
	byte numero = 17;			// 17 para valor sin tecla
	
	// puertos a ceros
	digitalWrite(Keypad_A, HIGH);
	digitalWrite(Keypad_B, HIGH);
	digitalWrite(Keypad_C, HIGH);
	digitalWrite(Keypad_D, HIGH);
	
	while (numero == 17)
	{
		// encoder
		if (digitalRead(Enc_Center) == 0)
		{
			delay(300);
			numero = 16;
			break;
		}
		
		// A-1 - 1
		digitalWrite(Keypad_A, LOW);
		if (digitalRead(Keypad_1) == 0)
		{
			numero = 1;
			break;
		}
		
		// A-2 - 2
		if (digitalRead(Keypad_2) == 0)
		{
			numero = 2;
			break;
		}
		
		// A-3 - 3
		if (digitalRead(Keypad_3) == 0)
		{
			numero = 3;
			break;
		}
		
		// A-4 - A
		if (digitalRead(Keypad_4) == 0)
		{
			numero = 10;
			break;
		}

		digitalWrite(Keypad_A, HIGH);
		
		// B-1 - 4
		digitalWrite(Keypad_B, LOW);

		if (digitalRead(Keypad_1) == 0)
		{
			numero = 4;
			break;
		}
		
		// B-2 - 5
		if (digitalRead(Keypad_2) == 0)
		{
			numero = 5;
			break;
		}
		
		// B-3 - 6
		if (digitalRead(Keypad_3) == 0)
		{
			numero = 6;
			break;
		}
		
		// B-4 - B
		if (digitalRead(Keypad_4) == 0)
		{
			numero = 11;
			break;
		}
		digitalWrite(Keypad_B, HIGH);
		
		// C-1 - 7
		digitalWrite(Keypad_C, LOW);

		if (digitalRead(Keypad_1) == 0)
		{
			numero = 7;
			break;
		}
		
		// C-2 - 8
		if (digitalRead(Keypad_2) == 0)
		{
			numero = 8;
			break;
		}
		
		// C-3 - 9
		if (digitalRead(Keypad_3) == 0)
		{
			numero = 9;
			break;
		}
		
		// C-4 - C
		if (digitalRead(Keypad_4) == 0)
		{
			numero = 12;
			break;
		}
		digitalWrite(Keypad_C, HIGH);
		
		// D-1 - *
		digitalWrite(Keypad_D, LOW);

		if (digitalRead(Keypad_1) == 0)
		{
			numero = 15;
			break;
		}
		
		// D-2 - 0
		if (digitalRead(Keypad_2) == 0)
		{
			numero = 0;
			break;
		}
		
		// D-3 - #
		if (digitalRead(Keypad_3) == 0)
		{
			numero = 14;
			break;
		}
		
		// D-4 - D
		if (digitalRead(Keypad_4) == 0)
		{
			numero = 13;
			break;
		}
		digitalWrite(Keypad_D, HIGH);
	}
	
		// puertos a ceros
	digitalWrite(Keypad_A, HIGH);
	digitalWrite(Keypad_B, HIGH);
	digitalWrite(Keypad_C, HIGH);
	digitalWrite(Keypad_D, HIGH);
	
	return numero;
}
