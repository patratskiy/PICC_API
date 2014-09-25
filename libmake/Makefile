#
#CC	= /usr/local/arm/4.2.2-eabi/usr/bin/arm-linux-gcc
#LD	= /usr/local/arm/4.2.2-eabi/usr/bin/arm-linux-gcc
#CC	= /opt/arm/usr/bin/arm-linux-gcc
#LD	= /opt/arm/usr/bin/arm-linux-gcc


BFLLIBPATH=../Library

SOURCES := $(wildcard $(BFLLIBPATH)/api/*.c)
SOURCES += $(wildcard $(BFLLIBPATH)/bfl_1_1/*.c)
SOURCES += $(wildcard $(BFLLIBPATH)/bfl_1_1/AS3911/*.c)
SOURCES += $(wildcard $(BFLLIBPATH)/bfl_1_1/EMV/*.c)
SOURCES += $(wildcard $(BFLLIBPATH)/bfl_1_1/microchip/src/*.c)
SOURCES += $(wildcard $(BFLLIBPATH)/bfl_1_1/mifare_src/*.c)

LIBCOBJECTS = $(patsubst %.c,%.o,$(SOURCES))


INCLUDE = -I . -I $(BFLLIBPATH)/api -I $(BFLLIBPATH)/bfl_1_1/AS3911 -I $(BFLLIBPATH)/bfl_1_1/EMV -I $(BFLLIBPATH)/bfl_1_1/microchip/include \
	-I $(BFLLIBPATH)/bfl_1_1/mifare_src -I $(BFLLIBPATH)/bfl_1_1

clib: $(LIBCOBJECTS)
	/opt/arm/usr/bin/arm-linux-ar -r libCBFL.a $(LIBCOBJECTS)
	cp libCBFL.a ../app_test/
	
CXXFLAGS = -W -g  $(INCLUDE)
CXX =  /opt/arm/usr/bin/arm-linux-gcc $(CXXFLAGS) -fPIC  -D "AS3911_PBOC"
CXXOPTIONS = -g -D "__DEBUG__"

$(LIBCOBJECTS): %.o: %.c
	$(CXX) $(CXXOPTIONS) -c $< -o $@



PHONY: clean
clean:
	find . -name "*.o" | xargs rm -f
	find ../Library -name "*.o" | xargs rm -f
	rm -f *.so.*
	rm -f *.a
	rm -f *.so
	rm -f core*
	rm -f rf_id_test

	

