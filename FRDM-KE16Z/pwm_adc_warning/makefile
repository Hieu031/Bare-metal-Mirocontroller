# variables config
TARGET  = main				# output name
CC 	    = arm-none-eabi-gcc	# compiler
OBJCOPY = arm-none-eabi-objcopy # tool to convert elf -> bin/hex
SIZE    = arm-none-eabi-size

CPUFLAGS = -mcpu=cortex-m0plus -mthumb

# cflags: compiler options
CFLAGS = $(CPUFLAGS) -wall -O0 -g -ffunction-sections -fdata-sections -MMD -MP
# -Wall: enbale warn, -O0: no optimize, -g: debug info

# linker flags: use linker script, no link standard lib, remove section unuse
LDFLAGS = -T linker.ld -nostdlib -wl,--gc-sections

# source file
SRC = main.c startup_ke16.s

BUILD = build

DEPS = $(OBJS:.o=.d)

# object files
OBJS = main.o startup_ke16.O

# Tools config
OPENOCD = openocd 
OPENOCD_CFG = -f interface.cmsis-dap.cfg -f targer/ke16.cfg # option follow chip

# Target
.PHONY: all clean size flash debug

# default target: build all file need
all: $(BUILD)/$(TARGET).elf $(BUILD)/$(TARGET).bin $(BUILD)/$(TARGET).hex

# Compile -c to .o
$(BUILD)/%.o: %.c | %(BUILD)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# Complie .s to .o (startup file is usually assembly )
$(BUILD)/%.o: %.s | %(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

# links objs to ELF: .elf from .o
$(BUILD)/$(TARGET).elf: $(OBJS) | $(BUILD)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# Create .bin from .elf
$(BUILD)/$(TARGET).bin: $(BUILD)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@

# Create file .hex from .elf
$(BUILD)/$(TARGET).hex: $(BUILD)/$(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

# Helper: show size 
size: $(BUILD)/$(TARGET).elf
	$(SIZE) $<

# Flash to chip
flash: $(BUILD)/$(TARGET).elf
	$(OPENOCD) $(OPENOCD_CFG) -c "program $< verify reset exit"

# Debug
debug: $(BUILD)/$(TARGET).elf
	$(OPENOCD) $(OPENOCD_CFG) -c "init" -c "reset halt" -c "gdb_port 3333"

# make build directory
$(BUILD):
	mkdir -p $(BUILD)

# Clean file output
clean:
	rm -rf $(BUILD)  

# Include auto-generated dependencies
-include $(DEPS)