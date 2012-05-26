DEMONAME=hardwareTest

all:
	avr-gcc $(CFLAGS) -L$(PROJ_DIR)/build -lcontrol -I$(PROJ_DIR)/include/ $(DEMONAME).c -c -o $(PROJ_DIR)/build/$(DEMONAME).o
	avr-gcc $(CFLAGS) -L$(PROJ_DIR)/build -lcontrol -I$(PROJ_DIR)/include/ usart.c -c -o $(PROJ_DIR)/build/usart.o
	avr-gcc $(LDFLAGS) -L$(PROJ_DIR)/build -lcontrol -I$(PROJ_DIR)/include/ \
 $(PROJ_DIR)/build/$(DEMONAME).o $(PROJ_DIR)/build/usart.o -lcontrol -o $(PROJ_DIR)/build/$(DEMONAME).out 
	avr-objcopy -j .text -j .data -O ihex  $(PROJ_DIR)/build/$(DEMONAME).out ../../build/$(DEMONAME).hex

.PHONY: upload fuses
upload:
	sudo avrdude -p m168 -c usbasp -e -U flash:w:../../build/$(DEMONAME).hex 

fuses:
	sudo avrdude -p m168 -c usbasp -t #-U lfuse:w:fuses
