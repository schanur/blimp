# directory: blimp__atmega_mc/io/

MCC=avr-gcc

MCU_TARGET = atmega168
MC_OPTIMIZE = -Os

MC_CFLAGS = -g -Wall -Werror $(MC_OPTIMIZE) -mmcu=$(MCU_TARGET)

all : ports uart i2cmaster i2c protocol_packet_handler

ports : ports.c
		$(MCC) $(MC_CFLAGS) -c ports.c

ring_buffer :
		$(MCC) $(MC_CFLAGS) -c ring_buffer.c

uart_buffer : ring_buffer
		$(MCC) $(MC_CFLAGS) -c uart_buffer.c

uart : uart_buffer
		$(MCC) $(MC_CFLAGS) -c uart.c
		avr-ar -crs libuart.a uart.o uart_buffer.o ring_buffer.o

i2cmaster : twimaster.c
		$(MCC) $(MC_CFLAGS) -c twimaster.c -o i2cmaster.o

i2c : i2cmaster
		$(MCC) $(MC_CFLAGS) -c i2c.c

protocol_packet_handler :
		$(MCC) $(MC_CFLAGS) -c protocol_packet_handler.c

clean :
		rm -fv *.o
		rm -fv *.a
