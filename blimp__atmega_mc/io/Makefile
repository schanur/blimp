MCC=avr-gcc

MCU_TARGET = atmega168
MC_OPTIMIZE = -Os

MC_CFLAGS = -g -Wall $(MC_OPTIMIZE) -mmcu=$(MCU_TARGET)

all : ports uart 

ports : ports.c
		$(MCC) $(MC_CFLAGS) -c ports.c

ring_buffer :
		$(MCC) $(MC_CFLAGS) -c ring_buffer.c

uart_buffer : ring_buffer
		$(MCC) $(MC_CFLAGS) -c uart_buffer.c

uart : uart_buffer
		$(MCC) $(MC_CFLAGS) -c uart.c

clean :
		rm -fv *.o
