# directory: .

all : mc pc

mc :
		cd shared_source; make mc
		cd blimp__atmega_mc; make

pc :
		cd shared_source; make pc

clean__mc :
		cd shared_source; make clean__mc
		cd blimp__atmega_mc; make clean

clean__pc :
		cd shared_source; make clean__pc

clean : clean__mc clean__pc
