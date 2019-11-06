#include <wiringPi.h>

#include <stdio.h>
#include <unistd.h>			//Used for UART
#include <fcntl.h>			//Used for UART
#include <termios.h>		//Used for UART

#include <sys/time.h>
#include <pthread.h>
#include "lcd.h"


// Eigenschaften->C/C++->Allgemein->zus�tzliche include verzeichnisse-> C:\Users\thoma\source\repos\Blink1\src;C:\Users\thoma\source\repos\Blink1\inc;%(AdditionalIncludeDirectories)

#include "CPPTimerInterface.h"

// LED-PIN - wiringPi-PIN 0 ist BCM_GPIO 17.
// Wir m�ssen bei der Initialisierung mit wiringPiSetupSys die BCM-Nummerierung verwenden.
// Wenn Sie eine andere PIN-Nummer w�hlen, verwenden Sie die BCM-Nummerierung, und
// aktualisieren Sie die Eigenschaftenseiten � Buildereignisse � Remote-Postbuildereignisbefehl 
// der den GPIO-Export f�r die Einrichtung f�r wiringPiSetupSys verwendet.
#define	LED17	17
// text zur n�chste zeile
#define LED18 22

int main(void) 
{
	wiringPiSetupSys();

	// ACHTUNG Projekt->Blink1 Eigenschaften->Buildereignisse_>  gpio export 22 out;gpio export 17 out  !!!!
	pinMode(LED17, OUTPUT); 
	pinMode(LED18, OUTPUT);

	// projekt->Eigenschaften->Linker->zus�tzliche Optiornen-> -lwiringPiDev 
	int fd = lcdInit(2, 16, 4, 1, 2, 3, 4, 5, 6, 0, 0, 0, 0); //see /usr/local/include/lcd.h
	printf("%d", fd);
	if (fd == -1) {
		printf("lcdInit 1 failed\n");
		return 1;
	}
	sleep(1);
	lcdClear(fd);
	lcdPosition(fd, 0, 0);
	lcdPuts(fd, "Welcome To--->");

	lcdPosition(fd, 0, 1);
	lcdPuts(fd, "    raspberry pi");



	//-------------------------
	//----- SETUP USART 0 -----
	//-------------------------
	//At bootup, pins 8 and 10 are already set to UART0_TXD, UART0_RXD (ie the alt0 function) respectively
	int uart0_filestream = -1;

	//OPEN THE UART
	//The flags (defined in fcntl.h):
	//	Access modes (use 1 of these):
	//		O_RDONLY - Open for reading only.
	//		O_RDWR - Open for reading and writing.
	//		O_WRONLY - Open for writing only.
	//
	//	O_NDELAY / O_NONBLOCK (same function) - Enables nonblocking mode. When set read requests on the file can return immediately with a failure status
	//											if there is no input immediately available (instead of blocking). Likewise, write requests can also return
	//											immediately with a failure status if the output can't be written immediately.
	//
	//	O_NOCTTY - When set and path identifies a terminal device, open() shall not cause the terminal device to become the controlling terminal for the process.
	uart0_filestream = open("/dev/serial0", O_RDWR | O_NOCTTY | O_NDELAY);		//Open in non blocking read/write mode
	if (uart0_filestream == -1)
	{
		//ERROR - CAN'T OPEN SERIAL PORT
		printf("Error - Unable to open UART.  Ensure it is not in use by another application\n");
	}

	//CONFIGURE THE UART
	//The flags (defined in /usr/include/termios.h - see http://pubs.opengroup.org/onlinepubs/007908799/xsh/termios.h.html):
	//	Baud rate:- B1200, B2400, B4800, B9600, B19200, B38400, B57600, B115200, B230400, B460800, B500000, B576000, B921600, B1000000, B1152000, B1500000, B2000000, B2500000, B3000000, B3500000, B4000000
	//	CSIZE:- CS5, CS6, CS7, CS8
	//	CLOCAL - Ignore modem status lines
	//	CREAD - Enable receiver
	//	IGNPAR = Ignore characters with parity errors
	//	ICRNL - Map CR to NL on input (Use for ASCII comms where you want to auto correct end of line characters - don't use for bianry comms!)
	//	PARENB - Parity enable
	//	PARODD - Odd parity (else even)
	struct termios options;
	tcgetattr(uart0_filestream, &options);
	options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;		//<Set baud rate
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	tcflush(uart0_filestream, TCIFLUSH);
	tcsetattr(uart0_filestream, TCSANOW, &options);


	TimerTask tt = 9;
	//tt.Init();

	tt.TimerStart();


	CPPTimerInterface cc;
	//cc.Init();


	
	
	while (true)
	{
		digitalWrite(LED17, !digitalRead(LED17));  
		digitalWrite(LED18, !digitalRead(LED18));
		delay(500); // ms
	

		//----- TX BYTES -----
		//unsigned char tx_buffer[20];
		//unsigned char* p_tx_buffer;

		//p_tx_buffer = &tx_buffer[0];
		//*p_tx_buffer++ = 'H';
		//*p_tx_buffer++ = 'e';
		//*p_tx_buffer++ = 'l';
		//*p_tx_buffer++ = 'l';
		//*p_tx_buffer++ = 'o';

		//if (uart0_filestream != -1)
		//{
		//	int count = write(uart0_filestream, &tx_buffer[0], (p_tx_buffer - &tx_buffer[0]));		//Filestream, bytes to write, number of bytes to write
		//	if (count < 0)
		//	{
		//		printf("UART TX error\n");
		//	}
		//	else
		//	{
		//		
		//		printf("\n");
		//	}
		//}

		//----- CHECK FOR ANY RX BYTES -----
		//if (uart0_filestream != -1)
		//{

		//	// Read up to 255 characters from the port if they are there
		//	unsigned char rx_buffer[256];
		//	int rx_length = read(uart0_filestream, (void*)rx_buffer, 255);		//Filestream, buffer to store in, number of bytes to read (max)
		//	if (rx_length < 0)
		//	{
		//		//An error occured (will occur if there are no bytes)
		//	}
		//	else if (rx_length == 0)
		//	{
		//		//No data waiting
		//	}
		//	else
		//	{
		//		digitalWrite(LED18, !digitalRead(LED18));
		//		//Bytes received
		///*		rx_buffer[rx_length] = '\0';
		//		printf("%i bytes read : %s\n", rx_length, rx_buffer);*/

		//	}
		//}
	}

	//----- CLOSE THE UART -----
	//close(uart0_filestream);

	return 0;
}