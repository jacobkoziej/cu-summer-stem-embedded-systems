CC      = avr-gcc
CFLAGS += \
	-DF_CPU=16000000ULL \
	-O0 \
	-Wall \
	-Wextra \
	-Wpedantic \
	-g \
	-mmcu=atmega328p \
	-std=c23 \

.PHONY: all
all: main.elf

.PHONY: clean
clean:
	@rm -rvf *.d *.elf *.o

main.elf: main.o ws2812b.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.S
	$(CC) $(CFLAGS) -MM -MF $*.d $<
	$(CC) $(CFLAGS) -c $<

%.o: %.c
	$(CC) $(CFLAGS) -MM -MF $*.d $<
	$(CC) $(CFLAGS) -c $<

-include $(wildcard *.d)
