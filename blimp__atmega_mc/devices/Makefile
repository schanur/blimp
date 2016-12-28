# directory: blimp__atmega_mc/devices/

MCC=avr-gcc

MCU_TARGET = atmega168
MC_OPTIMIZE = -Os

MC_CFLAGS = -g -Wall -Werror $(MC_OPTIMIZE) -mmcu=$(MCU_TARGET)

all : stepper_motor stepper_matrix

stepper_motor :
		$(MCC) $(MC_CFLAGS) -c stepper_motor.c

stepper_matrix :
		$(MCC) $(MC_CFLAGS) -c stepper_matrix.c

clean :
		rm -fv *.o
