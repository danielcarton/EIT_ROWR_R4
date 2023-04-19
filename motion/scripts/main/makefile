PACK_PATH  = pack
DEVICE     = avr128db28
PROGRAMMER = jtagice3
PROTOCOL   = updi
PYMCUPROG  = /mnt/c/Users/medlem/AppData/Local/Programs/Python/Python311/Scripts/pymcuprog.exe

FLAGS = -Wall \
        -O3 \
				-I. \
        -Wno-unused-function \
        -Wno-unused-variable \
        -DF_CPU=24000000UL \
        -B$(PACK_PATH)/gcc/dev/$(DEVICE)  \
        -I$(PACK_PATH)/include \
        -mmcu=$(DEVICE)

.PHONY: build install

build:
	@avr-gcc $(FLAGS) main.c print.c serial.c -o program.elf
	@avr-objcopy -j .text -j .data -j .bss -O ihex program.elf program.hex
	@sudo $(PYMCUPROG) erase -t $(PROGRAMMER) -d $(DEVICE) -i $(PROTOCOL)
	@sudo $(PYMCUPROG) write -t $(PROGRAMMER) -d $(DEVICE) -i $(PROTOCOL) --verify -f program.hex
	@rm -f program.hex program.elf

test:
	@/mnt/c/Users/medlem/AppData/Local/Programs/Python/Python311/python.exe test.py

install:
	@sudo apt install gcc-avr binutils-avr avr-libc
	@sudo pip3 install pymcuprog
	@wget http://packs.download.atmel.com/Atmel.AVR-Dx_DFP.2.2.253.atpack -O pack.zip
	@unzip pack.zip -d pack
	@rm -rf pack.zip

