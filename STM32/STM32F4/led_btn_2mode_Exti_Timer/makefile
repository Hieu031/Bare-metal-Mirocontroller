# Explain makefile:
#--- 
#---


TARGET = main
BUILD = build
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

CPU = cortex-m4

CFLAGS = -mcpu=$(CPU) -mthumb -O2 -ffunction-sections -fdata-sections -Wall -O0
LDFLAGS = -T linker.ld -nostdlib -Wl,--gc-sections

OPENOCD = openocd
OPENOCD_CFG = -f interface/cmsis-dap.cfg -f target/stm32f4x.cfg

SRCS = main.c 
ASMS = startup_stm32f4.s
OBJS = $(addprefix $(BUILD)/, $(SRCS:.c=.o) $(ASMS:.s=.o))

.PHONY: all clean size flash debug

all: $(BUILD)/$(TARGET).elf $(BUILD)/$(TARGET).bin $(BUILD)/$(TARGET).hex

# create folder build to save output file 
$(BUILD):
	mkdir -p $(BUILD)

# compile .c to .o
$(BUILD)/%.o: %.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

# compile .s to .o (startup file)
$(BUILD)/%.o: %.s | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

# create file .elf 
$(BUILD)/$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# create file .bin from .elf
$(BUILD)/$(TARGET).bin: $(BUILD)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@

# create file .hex from .elf
$(BUILD)/$(TARGET).hex: $(BUILD)/$(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

# show size
size: $(BUILD)/$(TARGET).elf
	$(SIZE) $<

# flash elf to chip
flash: $(BUILD)/$(TARGET).elf
	$(OPENOCD) $(OPENOCD_CFG) -c "program $< verify reset exit" 

# debug
debug: $(BUILD)/$(TARGET).elf
	$(OPENOCD) $(OPENOCD_CFG) -c "init" -c "reset halt" -c "gdb_port 3333"

# clean output
clean:
	rm -rf $(BUILD)
