PCC=g++

MCU_TARGET = atmega168

PC_OPTIMIZE = -O3
#-pedantic
PC_WARNINGS = -std=c++98 -Wall -Werror
PC_CFLAGS = $(PC_WARNINGS) $(PC_OPTIMIZE)

CFLAGS = -c $(PC_WARNINGS) $(PC_OPTIMIZE)


all: Exceptions.o \
		Vector.o \
		Cube.o \
		CubePosition.o \
		Array3D.o \
		CacheList.o \
		CircleMath.o \
		Coordinate.o \
		CoordinateSystemTranslation.o

#Array3D.o : Array3D.cpp
#	$(PCC) $(CFLAGS) -c $< -o $@

%.o : %.cpp
	$(PCC) $(CFLAGS) -c $< -o $@

clean:
	rm -fv *.o *.gch
