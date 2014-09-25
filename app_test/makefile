
#CC	= /usr/local/arm/4.2.2-eabi/usr/bin/arm-linux-gcc
#LD	= /usr/local/arm/4.2.2-eabi/usr/bin/arm-linux-gcc
CC	= /opt/arm/usr/bin/arm-linux-gcc
LD	= /opt/arm/usr/bin/arm-linux-gcc

BFLLIBPATH=../Library
INCLUDE = -I . 

CFLAGS = -W -g  -DPBOC_DEBUG $(INCLUDE)
SRC    = pboc_test.c
OBJ    = pboc_test.o
EXE    = pboc_test

all:$(OBJ)
	$(CC) $(OBJ) -L . -lCBFL -o $(EXE)
	cp $(EXE) scl_test
	cp $(EXE) /mnt/hgfs/wintolinux/lw_ftp/scl_test
#	cp $(EXE) /mnt/hgfs/E/lw_ftp/pboc_test
%o:%c 
	$(CC)  -c $(CFLAGS) $< -o $@
		
clean:
	rm -f *.o $(EXE)





	
