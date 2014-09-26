
#CC	= /usr/local/arm/4.2.2-eabi/usr/bin/arm-linux-gcc
#LD	= /usr/local/arm/4.2.2-eabi/usr/bin/arm-linux-gcc
CC	= arm-linux-gcc 
LD	= arm-linux-gcc 

BFLLIBPATH=../Library
INCLUDE = -I . -I ../Library

CFLAGS = -W -g  -DPBOC_DEBUG $(INCLUDE)
SRC    = main.c
OBJ    = main.o
EXE    = pboc_test

all:$(OBJ)
	$(CC) $(OBJ) -L . -lCBFL -o $(EXE)
	cp $(EXE) scl_test
	cp $(EXE) /mnt/hgfs/wintolinux/lw_ftp/
#	cp $(EXE) /mnt/hgfs/E/lw_ftp/pboc_test
%o:%c 
	$(CC)  -c $(CFLAGS) $< -o $@
		
clean:
	rm -f *.o $(EXE)





	
