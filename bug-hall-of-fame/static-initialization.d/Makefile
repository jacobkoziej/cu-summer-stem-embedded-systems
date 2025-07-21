CC = avr-gcc
CFLAGS = \
	-O0 \
	-fdata-sections \
	-ffunction-sections \
	-fno-exceptions \
	-fno-threadsafe-statics \
	-fpermissive \
	-mmcu=atmega328p \
	-std=gnu++17 \

.PHONY: all
all: int.s static.s

.PHONY: clean
clean:
	@rm -rvf *.s

%.s: %.cc
	$(CC) $(CFLAGS) -fverbose-asm -S $<
