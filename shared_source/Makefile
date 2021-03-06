MCC=avr-gcc
PCC=g++

MCU_TARGET = atmega168

MC_OPTIMIZE = -Os
PC_OPTIMIZE = -O3
MC_WARNINGS = -std=c99 -Wall -pedantic -Werror
PC_WARNINGS = -std=c++98 -Wall -pedantic -Werror

MC_CFLAGS = -g $(MC_WARNINGS) $(MC_OPTIMIZE) -mmcu=$(MCU_TARGET)
PC_CFLAGS = $(PC_WARNINGS) $(PC_OPTIMIZE)

all : mc pc

byte_order__mc : byte_order.c platform_specifics_macros.h
	$(MCC) $(MC_CFLAGS) -c byte_order.c -o byte_order__mc.o

byte_order__pc : byte_order.c platform_specifics_macros.h
	$(PCC) $(PC_CFLAGS) -c byte_order.c -o byte_order__pc.o

debug__mc : debug.c platform_specifics_macros.h
	$(MCC) $(MC_CFLAGS) -c debug.c -o debug__mc.o
	
debug__pc : debug.c platform_specifics_macros.h
	$(PCC) $(PC_CFLAGS) -c debug.c -o debug__pc.o

print_dtype__mc : print_dtype.c platform_specifics_macros.h
	$(MCC) $(MC_CFLAGS) -c print_dtype.c -o print_dtype__mc.o

print_dtype__pc : print_dtype.c platform_specifics_macros.h
	$(PCC) $(PC_CFLAGS) -c print_dtype.c -o print_dtype__pc.o

uart_protocol_handler__mc : uart_protocol_handler.c platform_specifics_macros.h
	$(MCC) $(MC_CFLAGS) -c uart_protocol_handler.c -o uart_protocol_handler__mc.o

uart_protocol_handler__pc : uart_protocol_handler.c platform_specifics_macros.h
	$(PCC) $(PC_CFLAGS) -c uart_protocol_handler.c -o uart_protocol_handler__pc.o

mc : byte_order__mc debug__mc uart_protocol_handler__mc print_dtype__mc

pc : byte_order__pc debug__pc uart_protocol_handler__pc print_dtype__pc

clean__mc :
	rm -fv *_mc.o

clean__pc :
	rm -fv *_pc.o

clean : clean__mc clean__pc
