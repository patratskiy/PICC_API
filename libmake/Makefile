#
#CC	= /usr/local/arm/4.2.2-eabi/usr/bin/arm-linux-gcc
#LD	= /usr/local/arm/4.2.2-eabi/usr/bin/arm-linux-gcc
#CC	= /opt/arm/usr/bin/arm-linux-gcc
#LD	= /opt/arm/usr/bin/arm-linux-gcc


BFLLIBPATH=../Library

SOURCES := $(wildcard $(BFLLIBPATH)/*.c) 

LIBCOBJECTS = $(patsubst %.c,%.o,$(SOURCES))


INCLUDE = -I . 
clib: $(LIBCOBJECTS)
	arm-linux-ar -r libCBFL.a $(LIBCOBJECTS)
	cp libCBFL.a ../app_test/
	
CXXFLAGS = -W -g  $(INCLUDE)
CXX =  arm-linux-gcc $(CXXFLAGS) -fPIC  -D "AS3911_PBOC"
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

	

