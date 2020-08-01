// ***************************************************************************************************************************
// ***************************************************************************************************************************
// **																														**
// ** 	Ejemplo de funciones gráficas con Adafruit GFX Library, Arduino Mega, Adafruit HXD8357D TFT 320x480, 8 bit Mode		**
// **																														**
// **	Escrito en Notepad++																								**
// **	Compilado en Arduino v1.0.6																							**
// **																														**
// **	Hardware:																											**
// **	https://learn.adafruit.com/adafruit-3-5-color-320x480-tft-touchscreen-breakout										**
// **																														**
// **	Video:																												**
// **	http://youtu.be/Y8XBOiMS-KI																							**
// **																														**
// **	Libreria Adafruit GFX:																								**
// **	https://github.com/adafruit/Adafruit-GFX-Library																	**
// **																														**
// **	Libreria Adafruit TFTLCD:																							**
// **	https://github.com/adafruit/TFTLCD-Library																			**
// **																														**
// **	Repositorio:																										**
// **	https://github.com/daniel3514/Adafruit-GFX-Library-Example-Arduino-Mega-HXD8357D-and-STMPE610						**
// **																														**
// **	Autores:																											**
// **	Daniel Alejandro Becerril Hernandez																					**
// **	Daniel Roberto Becerril Angeles																						**
// **																														**
// **	daniel3514@gmail.com																								**
// **																														**
// **	Licenciamiento:																										**
// **	GNU GENERAL PUBLIC LICENSE Version 3																				**
// **																														**
// ****************************************************************************************************************************
// ****************************************************************************************************************************

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
// For the Arduino Uno, Duemilanove, Diecimila, etc.:
//   D0 connects to digital pin 8  (Notice these are
//   D1 connects to digital pin 9   NOT in order!)
//   D2 connects to digital pin 2
//   D3 connects to digital pin 3
//   D4 connects to digital pin 4
//   D5 connects to digital pin 5
//   D6 connects to digital pin 6
//   D7 connects to digital pin 7
// For the Arduino Mega, use digital pins 22 through 29
// (on the 2-row header at the end of the board).

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

void setup() 
{
	// inicializador de pantalla
	tft.reset();
	tft.begin(tft.readID());	// readID, el valor ID que lee la libreria desde la pantalla
}

void loop() 
{
	// retardo entre tests
	int retardo = 1000;
	
	Pantalla_Fondo();			// fillScreen
	delay(retardo);
	
	Pantalla_Tamano();			// width height
	delay(retardo);
	
	Pantalla_ID();			 	//readID
	delay(retardo);
	
	Pantalla_Rotacion();		// setRotation getRotation
	delay(retardo);
	
	Cursor();					// getCursorX getCursorY setCursor
	delay(retardo);
	
	Texto_Tamano();				// setTextSize
	delay(retardo);
	
	Texto_Color();				// setTextColor
	delay(retardo);
	
	Texto_Ajuste();				// setTextWrap
	delay(retardo);
		
	Linea();					// drawLine
	delay(retardo);
	
	Linea_Rapida_X_Y();			// drawFastVLine drawFastHLine
	delay(retardo);
	
	Rectangulo_Contorno();		// drawRect
	delay(retardo);
	
	Rectangulo_Relleno();		// fillRect
	delay(retardo);
	
	Rectangulo_Redondeado();	// drawRoundRect
	delay(retardo);
	
	Rectangulo_Redondeado_Relleno();		// fillRoundRect
	delay(retardo);
	
	Circulo_Contorno();			// drawCircle
	delay(retardo);
	
	Circulo_Relleno();			// fillCircle
	delay(retardo);
	
	Circulo_Seccion();			// drawCircleHelper
	delay(retardo);
	
	Circulo_Seccion_Relleno_Estirar();	// fillCircleHelper
	delay(retardo);
	
	Triangulo();				// drawTriangle
	delay(retardo);
	
	Triangulo_Relleno();		// fillTriangle
	delay(retardo);
	
	Caracteres();				// drawChar
	delay(retardo);
}

void Caracteres()
{
	// dibuja caracteres
	
	// void Adafruit_GFX::drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size)
	
	tft.fillScreen(BLACK);		// fondo negro
	tft.setCursor(0, 0);		// posicion del cursor
	tft.setTextSize(3);			// tamaño de texto, lo probamos 1 hasta 100 y funciona
	tft.setTextColor(WHITE);	// color de texto
	tft.println("drawChar");	// texto
	tft.println(" ");	       	// texto
	
	for(int contar = 0; contar <= 255; contar ++)
	{
		tft.setCursor(0, 40);		// posicion del cursor
		tft.setTextColor(WHITE, BLACK);	// color de texto
		tft.println(contar);	       	// texto
		tft.drawChar(100, 100, contar, BLUE, WHITE, 10);
		delay(200);
	}
}

void Triangulo_Relleno()
{
	// Dibuja un triangulo relleno
	
	// void Adafruit_GFX::fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
	tft.fillScreen(BLACK);			// fondo negro
	tft.fillTriangle(100, 100, 200, 100, 150, 150, MAGENTA); // dibuja un triangulo relleno, fillTriangle(x0, y0, x1, y1, x2, y2, color)
	
	tft.setCursor(0, 0);			// posicion del cursor
	tft.setTextSize(3);				// tamaño de texto, lo probamos 1 hasta 100 y funciona
	tft.setTextColor(WHITE);		// color de texto
	tft.println("fillTriangle");	// texto
}
void Triangulo()
{
	// Dibuja un triangulo
	
	// void Adafruit_GFX::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
	tft.fillScreen(BLACK);			// fondo negro
	tft.drawTriangle(100, 100, 200, 100, 150, 150, MAGENTA); // dibuja un triangulo, drawTriangle(x0, y0, x1, y1, x2, y2, color)
	
	tft.setCursor(0, 0);			// posicion del cursor
	tft.setTextSize(3);				// tamaño de texto, lo probamos 1 hasta 100 y funciona
	tft.setTextColor(WHITE);		// color de texto
	tft.println("drawTriangle");	// texto
}
void Rectangulo_Redondeado_Relleno()
{
	// Dibuja un rectángulo redondeado relleno
	
	// fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color)
	
	tft.fillScreen(BLACK);			// fondo negro
	tft.setTextSize(3);				// tamaño de texto, lo probamos 1 hasta 100 y funciona
	tft.setTextColor(WHITE);		// color de texto
	
	for (int radio = 0; radio <= 100; radio ++)
	{
		tft.fillScreen(BLACK);		// fondo negro
		tft.setCursor(0, 0);			// posicion del cursor
		tft.println("drawRoundRect");	// texto
		tft.setCursor(0, 30);		// posicion del cursor
		tft.println("radio: ");		// texto
		tft.println(radio);			// texto
		
		tft.fillRoundRect(100, 100, 40, 40, radio, YELLOW); // rectangulo redondeado con relleno, drawRoundRect(X, Y, ancho, alto, radio, color)
	}
}

void Rectangulo_Redondeado()
{
	// Dibuja un rectángulo redondeado
	// drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color)
	
	tft.fillScreen(BLACK);			// fondo negro
	tft.setTextSize(2);				// tamaño de texto, lo probamos 1 hasta 100 y funciona
	tft.setTextColor(WHITE);		// color de texto
	
	for (int radio = 0; radio <= 100; radio ++)
	{
		tft.fillScreen(BLACK);		// fondo negro
		tft.setCursor(0, 0);			// posicion del cursor
		tft.println("drawRoundRect");	// texto
		tft.setCursor(0, 30);		// posicion del cursor
		tft.println("radio: ");		// texto
		tft.println(radio);			// texto
		
		tft.drawRoundRect(100, 100, 40, 40, radio, YELLOW);	// rectangulo redondeado, drawRoundRect(X, Y, ancho, alto, radio, color)
	}
	
	tft.fillScreen(BLACK);		// fondo negro
	
	for (int radio = 0; radio <= 100; radio ++)
	{
		
		tft.setCursor(0, 0);			// posicion del cursor
		tft.println("drawRoundRect");	// texto
		tft.setCursor(0, 30);			// posicion del cursor
		tft.setTextColor(WHITE, BLACK);	// color de texto
		tft.println("radio: ");			// texto
		tft.println(radio);				// texto
		
		tft.drawRoundRect(100, 100, 40, 40, radio, YELLOW); // rectangulo redondeado, drawRoundRect(X, Y, ancho, alto, radio, color)
	}
}

void Rectangulo_Relleno()
{
	// dibuja un rectangulo con relleno de color
	
	// void Adafruit_GFX::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
	
	tft.fillScreen(BLACK);		// fondo negro
	tft.setTextSize(2);			// tamaño de texto, lo probamos 1 hasta 100 y funciona
	tft.setTextColor(WHITE);	// color de texto
	tft.setCursor(0, 0);		// posicion del cursor
	tft.println("fillRect");	// texto
	
	tft.fillRect(100, 100, 50, 100, GREEN);	// rectangulo, 	tft.fillRect(X, Y, alto, ancho, color de fondo);	
}

void Linea_Rapida_X_Y()
{
	// dibuja una linea rapida solo con x, y, sentido y color sobre X o Y
	
	// void Adafruit_GFX::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
	
	tft.fillScreen(BLACK);			// fondo negro
	tft.setTextSize(2);				// tamaño de texto, lo probamos 1 hasta 100 y funciona
	tft.setTextColor(WHITE);		// color de texto
	
	tft.setCursor(0, 0);			// posicion del cursor
	tft.println("drawFastVLine");	// texto
	
	tft.drawFastVLine(100, 100, 50, WHITE);		// linea rapida, tft.drawFastVLine(X, Y, sobre x, color);
	
	delay(1000);
	
	tft.fillScreen(BLACK);			// fondo negro
	tft.setCursor(0, 0);			// posicion del cursor
	tft.println("drawFastHLine");	// texto
	
	tft.drawFastHLine(100, 100, 50, WHITE);		// linea rapida, tft.drawFastVLine(X, Y, sobre Y, color);
}

void Rectangulo_Contorno()
{
	// dibuja un rectangulo
	
	// void Adafruit_GFX::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
	
	tft.fillScreen(BLACK);		// fondo negro
	tft.setTextSize(2);			// tamaño de texto, lo probamos 1 hasta 100 y funciona
	tft.setTextColor(WHITE);	// color de texto
	tft.setCursor(0, 0);		// posicion del cursor
	tft.println("drawRect");	// texto
	
	tft.drawRect(100, 100, 50, 100, YELLOW);	// rectangulo, 	tft.drawRect(X, Y, alto, ancho, color);	
}

void Linea()
{
	// dibuja una linea
	
	// void Adafruit_GFX::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color)
	
	tft.fillScreen(BLACK);		// fondo negro
	tft.setTextSize(2);			// tamaño de texto, lo probamos 1 hasta 100 y funciona
	tft.setTextColor(WHITE);	// color de texto
	tft.setCursor(0, 0);		// posicion del cursor
	tft.println("     drawLine");	// texto
	
	tft.drawLine(0, 0, 320, 480, GREEN);	// dibuja linea, tft.drawLine(X0, Y0, X1, Y1, color);
}

void Circulo_Seccion_Relleno_Estirar()
{
	// dibuja un circulo en secciones con corner name de 1 a 3, y lo estira sobre Y y lo reduce sobre X con delta de 0 a x
	
	// void Adafruit_GFX::fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color) {
	 
	for (int cornername = 1; cornername <= 3; cornername ++)
	{
		for (int delta = 1; delta <= 10; delta ++)
		{
			tft.fillScreen(BLACK);			// fondo negro
			tft.setCursor(0, 0);			// posicion del cursor
			tft.setTextColor(WHITE);		// color de texto
			tft.setTextSize(2);				// tamaño de texto, lo probamos 1 hasta 100 y funciona
			tft.println("fillCircleHelper");// texto
			tft.println(" ");				// texto
			tft.println("delta:");			// texto
			tft.println(delta * 10);		// texto
			tft.println(" ");				// texto
			tft.println("corner name:");	// texto
			tft.println(cornername);		// texto
			tft.fillCircleHelper(150, 150, 50, cornername, delta * 10, MAGENTA);	// tft.fillCircleHelper(X, Y, radio, cornername seccion 1 a 3, delta estirar 0 a x, color);
			delay(500);
		}
	}
}

void Circulo_Relleno()
{
	// dibuja un circulo con color de relleno
	
	// void Adafruit_GFX::fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
		
	tft.fillScreen(BLACK);		// fondo negro
	tft.setCursor(0, 0);		// posicion del cursor
	tft.setTextSize(2);			// tamaño de texto, lo probamos 1 hasta 100 y funciona
	tft.setTextColor(WHITE);	// color de texto
	tft.println("fillCircle");	// texto
			
	tft.fillCircle(150, 150, 100, GREEN);	// circulo con relleno, tft.fillCircle(X, Y, radio, color de relleno); 
}

void Circulo_Seccion()
{
	// dibuja el contorno de un circulo en secciones, lo parte en 4 y cuenta como si fueran las secciones del circulo en binario
	
	// void Adafruit_GFX::drawCircleHelper( int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color) {
	
	for (int cornername = 1; cornername <= 15; cornername ++)
	{
		tft.fillScreen(BLACK);			// fondo negro
		tft.setCursor(0, 0);			// posicion del cursor
		tft.setTextSize(2);				// tamaño de texto, lo probamos 1 hasta 100 y funciona
		tft.setTextColor(WHITE);		// color de texto
		tft.println("drawCircleHelper");// texto
		tft.println(" ");				// texto
		tft.println("corner name:");	// texto
		tft.println(cornername);		// texto
		tft.drawCircleHelper(150, 150, 100, cornername, WHITE);		// contorno de un circulo en secciones, 1 a 15
		delay(1500);
	}	
}

void Circulo_Contorno()
{
	// dibuja un contorno de linea
	
	// void Adafruit_GFX::drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
		
	tft.fillScreen(BLACK);			// fondo negro
	tft.setCursor(0, 0);			// posicion del cursor
	tft.setTextSize(2);				// tamaño de texto, lo probamos 1 hasta 100 y funciona
	tft.setTextColor(WHITE);		// color de texto
	tft.println("drawCircle");		// texto
		
	tft.drawCircle(150, 150, 100, RED);	// dibuja el contorno de un circulo, drawCircle(X, Y, radio, color)
}

void Pantalla_Rotacion()
{
	// setRotation establece la rotacion de la pantalla, 0 = 0*, 1 = 90*, 2 = 180*, 3 = 270*
	// getRotation devuelve el valor de la rotacion de pantalla actual
	
	// void Adafruit_GFX::setRotation(uint8_t x)
	
	// uint8_t Adafruit_GFX::getRotation(void) const {
	// return rotation;
	// }
	
	tft.fillScreen(BLACK);			// fondo negro
	tft.setCursor(0, 0);			// posicion del cursor
	tft.setTextColor(WHITE);		// color de texto
	tft.setTextSize(3);				// tamaño de texto, lo probamos 1 hasta 100 y funciona
	
	tft.setRotation(0);				// rotacion de pantalla 0 = 0*, 1 = 90*, 2 = 180*, 3 = 270*
	tft.setCursor(0, 0);			// posicion del cursor
	tft.println("setRotation:");		// texto
	tft.println(tft.getRotation());	// devuelve el valor de rotacion de pantalla
	delay(2000);
	
	tft.setRotation(1);				// rotacion de pantalla 0 = 0*, 1 = 90*, 2 = 180*, 3 = 270*
	tft.setCursor(0, 0);			// posicion del cursor
	tft.println("setRotation:");		// texto
	tft.println(tft.getRotation());	// devuelve el valor de rotacion de pantalla
	delay(2000);
	
	tft.setRotation(2);				// rotacion de pantalla 0 = 0*, 1 = 90*, 2 = 180*, 3 = 270*
	tft.setCursor(0, 0);			// posicion del cursor
	tft.println("setRotation:");		// texto
	tft.println(tft.getRotation());	// devuelve el valor de rotacion de pantalla
	delay(2000);
	
	tft.setRotation(3);				// rotacion de pantalla 0 = 0*, 1 = 90*, 2 = 180*, 3 = 270*
	tft.setCursor(0, 0);			// posicion del cursor
	tft.println("setRotation:");		// texto
	tft.println(tft.getRotation());	// devuelve el valor de rotacion de pantalla
	delay(2000);
	
	tft.setRotation(0);
}

void Pantalla_ID()
{
	// devuelve el ID de la pantalla
	
	tft.fillScreen(BLACK);			// fondo negro
	tft.setCursor(0, 0);			// posicion del cursor
	tft.setTextColor(WHITE);		// color de texto
	tft.setTextSize(3);				// tamaño de texto, lo probamos 1 hasta 100 y funciona
	tft.println("readID");			// texto
	tft.println(" ");				// texto
	tft.println(tft.readID());		// texto
}

void Texto_Ajuste()
{
	// Ajusta el texto al tamaño de la pantalla
	
	// void Adafruit_GFX::setTextWrap(boolean w) {
	// wrap = w;
	// }
	
	tft.fillScreen(BLACK);			// fondo negro
	tft.setCursor(0, 0);			// posicion del cursor
	tft.setTextColor(WHITE);		// color de texto
	tft.setTextSize(2);				// tamaño de texto, lo probamos 1 hasta 100 y funciona
	
	tft.println("setTextWrap");	// texto 
	tft.println(" ");	// texto
	
	tft.setTextWrap(false);			// ajuste de texto
	tft.println("Esto es un texto sin ajuste setTextWrap");	// texto
	tft.println(" ");	// texto
	
	tft.setTextWrap(true);			// ajuste de texto
	tft.println("Esto es un texto con ajuste setTextWrap");	// texto
	
}

void Pantalla_Fondo()
{
	// fondo de pantalla
	
	// void Adafruit_GFX::fillScreen(uint16_t color)
	
	tft.setTextSize(3);				// tamaño de texto, lo probamos 1 hasta 100 y funciona

	tft.fillScreen(BLUE);			// fondo azul
	tft.setCursor(0, 0);			// posicion del cursor
	tft.setTextColor(BLUE, WHITE);	// color de texto
	tft.println("fillScreen");		// texto 
	delay(1000);
	
	tft.fillScreen(RED);			// fondo rojo
	tft.setCursor(0, 0);			// posicion del cursor
	tft.setTextColor(BLUE, WHITE);	// color de texto
	tft.println("fillScreen");		// texto 
	delay(1000);
	
	tft.fillScreen(GREEN);			// fondo verde
	tft.setCursor(0, 0);			// posicion del cursor
	tft.setTextColor(BLUE, WHITE);	// color de texto
	tft.println("fillScreen");		// texto 
	delay(1000);
	
	tft.fillScreen(CYAN);			// fondo cian
	tft.setCursor(0, 0);			// posicion del cursor
	tft.setTextColor(BLUE, WHITE);	// color de texto
	tft.println("fillScreen");		// texto
	delay(1000);	
	
	tft.fillScreen(MAGENTA);		// fondo magenta
	tft.setCursor(0, 0);			// posicion del cursor
	tft.setTextColor(BLUE, WHITE);	// color de texto
	tft.println("fillScreen");		// texto 
	delay(1000);
	
	tft.fillScreen(YELLOW);			// fondo amarillo
	tft.setCursor(0, 0);			// posicion del cursor
	tft.setTextColor(BLUE, WHITE);	// color de texto
	tft.println("fillScreen");		// texto 
	delay(1000);
	
	tft.fillScreen(WHITE);			// fondo blanco
	tft.setCursor(0, 0);			// posicion del cursor
	tft.setTextColor(BLUE, WHITE);	// color de texto
	tft.println("fillScreen");		// texto 
	delay(1000);
	
	tft.fillScreen(BLACK);			// fondo negro
	tft.setCursor(0, 0);			// posicion del cursor
	tft.setTextColor(BLUE, WHITE);	// color de texto
	tft.println("fillScreen");		// texto 
}

void Texto_Tamano()
{
	// tamaño de texto
	
	// void Adafruit_GFX::setTextSize(uint8_t s)

	tft.fillScreen(BLACK);			// fondo negro
	tft.setCursor(0, 0);			// posicion del cursor
	
	tft.setTextColor(WHITE);		// color de texto
	tft.setTextSize(1);				// tamaño de texto, lo probamos 1 hasta 100 y funciona
	tft.println("setTextSize 1");	// texto
	tft.println(" ");				// texto
	
	tft.setTextColor(BLUE);			// color de texto
	tft.setTextSize(2);				// tamaño de texto, lo probamos 1 hasta 100 y funciona
	tft.println("setTextSize 2");	// texto
	tft.println(" ");				// texto
	
	tft.setTextColor(RED);			// color de texto
	tft.setTextSize(3);				// tamaño de texto, lo probamos 1 hasta 100 y funciona
	tft.println("setTextSize 3");	// texto
	tft.println(" ");				// texto
	
	tft.setTextColor(MAGENTA);		// color de texto
	tft.setTextSize(4);				// tamaño de texto, lo probamos 1 hasta 100 y funciona
	tft.println("setTextSize 4");	// texto
	tft.println(" ");				// texto
	
	tft.setTextColor(GREEN);		// color de texto
	tft.setTextSize(5);				// tamaño de texto, lo probamos 1 hasta 100 y funciona
	tft.println("setTextSize 5");	// texto
	tft.println(" ");				// texto
	
	tft.setTextColor(YELLOW);		// color de texto
	tft.setTextSize(6);				// tamaño de texto, lo probamos 1 hasta 100 y funciona
	tft.println("setTextSize 6");	// texto
}

void Texto_Color()
{
	// texto con color de fondo
	
	// void Adafruit_GFX::setTextColor(uint16_t c, uint16_t b)
	// textcolor   = c;
	// textbgcolor = b; 

	tft.fillScreen(BLACK);			// fondo negro
	
	tft.setTextColor(BLUE);			// color de texto
	tft.setTextSize(2);				// tamaño de texto, lo probamos 1 hasta 100 y funciona
	tft.println("setTextColor(color)");	// texto
	
	tft.setCursor(0, 0);			// posicion del cursor
	tft.setTextColor(BLUE, WHITE);	// color de texto
	tft.setTextSize(2);				// tamaño de texto, lo probamos 1 hasta 100 y funciona
	tft.println("setTextColor(color, fondo)");		// texto
}

void Cursor()
{
	// posicion de cursor
	
	// int16_t Adafruit_GFX::getCursorX(void) const {
	// return cursor_x;
	// }
	
	// int16_t Adafruit_GFX::getCursorY(void) const {
	// return cursor_y;
	// }
	
	// void Adafruit_GFX::setCursor(int16_t x, int16_t y) {
	// cursor_x = x;
	// cursor_y = y;
	// }
	
	tft.fillScreen(BLACK);			// fondo negro
	tft.setCursor(0, 0);			// posicion del cursor X, Y
	tft.setTextSize(2);				// tamaño de texto, lo probamos 1 hasta 100 y funciona
	tft.setTextColor(GREEN);		// color de texto
	tft.println("setCursor");		// texto
	tft.println(" ");				// texto
	tft.println("X = ");			// texto
	tft.println(tft.getCursorX());	// texto, tft.getCursorX() devuelve la posicion del cursor
	tft.println(" ");				// texto
	tft.println("Y = ");			// texto
	tft.println(tft.getCursorY());	// texto, tft.getCursorY() devuelve la posicion del cursor
}

void Pantalla_Tamano()
{
	// tamaño de pantalla
	
	// int16_t Adafruit_GFX::width(void) const {
	// return _width;
 
	// int16_t Adafruit_GFX::height(void) const {
	// return _height;

	tft.fillScreen(BLACK);			// fondo negro
	tft.setCursor(0, 0);			// posicion del cursor
	tft.setTextColor(BLUE);			// color de texto
	tft.setTextSize(3);				// tamaño de texto, lo probamos 1 hasta 100 y funciona
	
	tft.println("width");			// texto,
	tft.println(tft.width());		// texto, tft.width() alto
	
	tft.println(" ");				// texto,
	
	tft.println("height");			// texto
	tft.println(tft.height());		// texto, tft.height() ancho
}