# Explain makefile:
#--- $< is dependency first after ":"
#--- $@ is target (file is left of ":")
#--- $^ is all dependency (unique) after ":"
#--- $+ is all dependency
#--- $* is file name not include "extension"
#--- Pattern rules: %.o: %.c is way to create file .o from file .c which the same name.
#--- -o <file> is file output
#--- -c is compile only (not link)
#--- | $(BUILD ) is order-only prerequisite (tiền đề theo thứ tự) - tức là chỉ chắc rằng có folder build trước khi tạo ra các output
# project target name
TARGET = main

# Build output folder
BUILD = build

# Toolchain
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

# CPU type
CPU = cortex-m4

# Compiler flags
CFLAGS = -mcpu=$(CPU) -mthumb -O2 -ffunction-sections -fdata-sections -Wall -O0
# Linker flasgs (use custom linker script)
LDFLAGS = -T linker.ld -nostdlib -Wl,--gc-sections

# OpenOCD settings
OPENOCD = openocd
OPENOCD_CFG = -f interface/cmsis-dap.cfg -f target/stm32f4x.cfg

# Source files 
SRCS = main.c  startup.c
ASMS = startup_stm32f4.s

# Object files (build/*.o)
OBJS = $(addprefix $(BUILD)/, $(SRCS:.c=.o) $(ASMS:.s=.o))

.PHONY: all clean size flash debug

# Default build
all: $(BUILD)/$(TARGET).elf $(BUILD)/$(TARGET).bin $(BUILD)/$(TARGET).hex

# create folder build if not exists 
$(BUILD):
	mkdir -p $(BUILD)

# compile C source ->  Object
$(BUILD)/%.o: %.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

# compile ASM source -> Object (startup file)
$(BUILD)/%.o: %.s | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

# Link object -> elf 
$(BUILD)/$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# Generate file .bin from .elf
$(BUILD)/$(TARGET).bin: $(BUILD)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@

# Generate file .hex from .elf
$(BUILD)/$(TARGET).hex: $(BUILD)/$(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

# show elf size
size: $(BUILD)/$(TARGET).elf
	$(SIZE) $<

# flash elf to target MCU
flash: $(BUILD)/$(TARGET).elf
	$(OPENOCD) $(OPENOCD_CFG) -c "program $< verify reset exit" 

# debug session
debug: $(BUILD)/$(TARGET).elf
	$(OPENOCD) $(OPENOCD_CFG) -c "init" -c "reset halt" -c "gdb_port 3333"

# clean output
clean:
	rm -rf $(BUILD)
