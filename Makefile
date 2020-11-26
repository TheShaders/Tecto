### User Configuration ###

# Toolchain locations
include Makefile.config

# Name of ROM to build
TARGET := boilerplate

# Do not change below this line!

# System config
ifeq ($(OS),Windows_NT)
  SHELL := powershell.exe
  .SHELLFLAGS := -NoProfile -Command
endif

### Text variables ###

# These use the fact that += always adds a space to create a variable that is just a space
# Space has a single space, indent has 2
space :=
space +=

indent =
indent += 
indent += 

### Tools ###

# System tools
CD := cd
CP := cp
RM := rm
MKDIR := New-Item -Path 
MKDIR_OPTS := -Force -Type Directory | Out-Null

RMDIR := (Remove-Item
RMDIR_OPTS := -ErrorAction SilentlyContinue -Recurse -Force) -or $$true | Out-Null # The -or $true is needed to prevent make from saying error

PRINT := Write-Host -NoNewline
 ENDCOLOR := $(PRINT) "$$([char]27)[0m";
 GREEN     := 
 ENDGREEN  := $(space)-ForegroundColor Green; $(ENDCOLOR) $(PRINT)
 BLUE      := 
 ENDBLUE   := $(space)-ForegroundColor Blue; $(ENDCOLOR) $(PRINT)
 YELLOW    := 
 ENDYELLOW := $(space)-ForegroundColor Yellow; $(ENDCOLOR) $(PRINT)
 WHITE     := 
 ENDWHITE  := $(space)-ForegroundColor White; $(ENDCOLOR) $(PRINT)
ENDLINE := ; Write-Host

# Build tools
PREFIX  := mips64-elf-
CC      := $(N64CHAIN)/bin/$(PREFIX)gcc
AS      := $(N64CHAIN)/bin/$(PREFIX)as
CPP     := $(N64CHAIN)/bin/$(PREFIX)cpp
CXX     := $(N64CHAIN)/bin/$(PREFIX)g++
LD      := $(N64CHAIN)/bin/$(PREFIX)ld
OBJCOPY := $(N64CHAIN)/bin/$(PREFIX)objcopy

CKSUM   := $(PYTHON) tools/n64cksum.py

### Files and Directories ###

# Source files
SRC_ROOT  := src
SRC_DIRS  := $(wildcard $(SRC_ROOT)/*)
C_SRCS    := $(foreach src_dir,$(SRC_DIRS),$(wildcard $(src_dir)/*.c))
CXX_SRCS  := $(foreach src_dir,$(SRC_DIRS),$(wildcard $(src_dir)/*.cpp))
ASM_SRCS  := $(foreach src_dir,$(SRC_DIRS),$(wildcard $(src_dir)/*.s))
BIN_FILES := $(foreach src_dir,$(SRC_DIRS),$(wildcard $(src_dir)/*.bin))
LD_SCRIPT := n64.ld
BOOT      := boot/boot.6102

# Build folders
BUILD_ROOT     := bin
BOOT_BUILD_DIR := $(BUILD_ROOT)/boot
BUILD_DIRS     := $(addprefix $(BUILD_ROOT)/,$(SRC_DIRS)) $(BOOT_BUILD_DIR)

# Build files
C_OBJS   := $(addprefix $(BUILD_ROOT)/,$(C_SRCS:.c=.o))
CXX_OBJS := $(addprefix $(BUILD_ROOT)/,$(CXX_SRCS:.cpp=.o))
ASM_OBJS := $(addprefix $(BUILD_ROOT)/,$(ASM_SRCS:.s=.o))
BIN_OBJS := $(addprefix $(BUILD_ROOT)/,$(BIN_FILES:.bin=.o))
OBJS     := $(C_OBJS) $(CXX_OBJS) $(ASM_OBJS) $(BIN_OBJS)
LD_CPP   := $(BUILD_ROOT)/$(LD_SCRIPT)
BOOT_OBJ := $(BUILD_ROOT)/$(BOOT).o
D_FILES  := $(C_OBJS:.o=.d) $(CXX_OBJS:.o=.d) $(LD_CPP).d

Z64      := $(addprefix $(BUILD_ROOT)/,$(TARGET).z64)
V64      := $(addprefix $(BUILD_ROOT)/,$(TARGET).v64)
ELF      := $(Z64:.z64=.elf)

### Flags ###

# Build tool flags

CFLAGS     := -march=vr4300 -mtune=vr4300 -mfix4300 -mabi=32 -mno-shared -G 0 -mhard-float -fno-stack-protector -fno-common -fno-zero-initialized-in-bss \
			  -I include -I . -I src/ -I $(SDK)/ultra/usr/include -I $(SDK)/nintendo/n64kit/nustd/include -fno-PIC -mno-abicalls -fno-strict-aliasing -fno-inline-functions -ffreestanding -fwrapv -Wall -Wextra \
			  -mno-check-zero-division -mno-split-addresses -mno-relax-pic-calls -mfp32 -mgp32 -mbranch-cost=1 \
			  -fno-dse -fno-check-pointer-bounds -Wno-chkp -mno-odd-spreg -D_FINALROM \
			  -D_MIPS_SZLONG=32 -D_MIPS_SZINT=32 -D_LANGUAGE_C -D_ULTRA64 -D__EXTENSIONS__ -DF3DEX_GBI_2
CXXFLAGS   := 
ASFLAGS    := -mtune=vr4300 -march=vr4300 -mabi=32 -mips3
LDFLAGS    := -T $(LD_CPP) -mips3 --accept-unknown-input-arch --no-check-sections -Map $(BUILD_ROOT)/$(TARGET).map \
			  -L $(SDK)/ultra/usr/lib -lgultra_rom -L $(SDK)/nintendo/n64kit/nustd/lib -lnustd -L lib -L $(N64CHAIN)/lib/gcc/mips64-elf/10.1.0 -lgcc
LDCPPFLAGS := -P -Wno-trigraphs -DBUILD_ROOT=$(BUILD_ROOT) -DSDK=$(SDK) -DCHAIN=$(N64CHAIN) -Umips
OCOPYFLAGS := --pad-to=0x400000 --gap-fill=0xFF
OPT_FLAGS  := -O2

$(BUILD_ROOT)/src/usb/usb.o: OPT_FLAGS := -O0

### Rules ###

# Default target, all
all: $(Z64)

# Make directories
$(BUILD_ROOT) $(BUILD_DIRS) :
	@$(PRINT) $(GREEN) Creating directory: $(ENDGREEN) $(BLUE) $@ $(ENDBLUE) $(ENDLINE)
	@$(MKDIR) $@ $(MKDIR_OPTS)

# .c -> .o
$(BUILD_ROOT)/%.o : %.c | $(BUILD_DIRS)
	@$(PRINT) $(GREEN) Compiling C source file: $(ENDGREEN) $(BLUE) $< $(ENDBLUE) $(ENDLINE)
	@$(CC) $< -o $@ -c -MMD -MF $(@:.o=.d) $(CFLAGS) $(OPT_FLAGS)

# .bin -> .o
$(BUILD_ROOT)/%.o : %.bin | $(BUILD_DIRS)
	@$(PRINT) $(GREEN) Objcopying binary file: $(ENDGREEN) $(BLUE) $< $(ENDBLUE) $(ENDLINE)
	@$(OBJCOPY) -I binary -O elf32-big $< $@

# .s -> .o
$(BUILD_ROOT)/%.o : %.s | $(BUILD_DIRS)
	@$(PRINT) $(GREEN) Compiling ASM source file: $(ENDGREEN) $(BLUE) $< $(ENDBLUE) $(ENDLINE)
	@$(AS) $< -o $@ $(ASFLAGS)

# boot -> .o
$(BOOT_OBJ) : $(BOOT) | $(BOOT_BUILD_DIR)
	@$(PRINT) $(GREEN) Copying boot to object file $(ENDGREEN) $(ENDLINE)
	@$(OBJCOPY) -I binary -O elf32-big $< $@

# .o -> .elf
$(ELF) : $(OBJS) $(LD_CPP) $(BOOT_OBJ) $(SDK)/ultra/usr/lib/PR/gspF3DEX2.fifo.o
	@$(PRINT) $(GREEN) Linking elf file: $(ENDGREEN) $(BLUE) $@ $(ENDBLUE) $(ENDLINE)
	@$(LD) $(LDFLAGS) -L $(BUILD_ROOT) -o $@

# .elf -> .z64
$(Z64) : $(ELF)
	@$(PRINT) $(GREEN) Creating z64: $(ENDGREEN) $(BLUE) $@ $(ENDBLUE) $(ENDLINE)
	@$(OBJCOPY) $< $@ -O binary $(OCOPYFLAGS)
	@$(PRINT) $(GREEN) Calculating checksums $(ENDGREEN) $(ENDLINE)
	@$(CKSUM) $@
	@$(PRINT) $(WHITE) ROM Built! $(ENDWHITE) $(ENDLINE)

# byteswap z64
$(V64) : $(Z64)
	@$(PRINT) $(GREEN) Byteswapping z64 to v64 $(ENDGREEN) $(ENDLINE)
	@$(OBJCOPY) $< $@ -I binary -O binary --reverse-bytes=2

# Preprocess LD script
$(LD_CPP) : $(LD_SCRIPT) | $(BUILD_ROOT)
	@$(PRINT) $(GREEN) Preprocessing linker script $(ENDGREEN) $(ENDLINE)
	@$(CPP) $(LDCPPFLAGS) -MMD -MP -MT $@ -MF $@.d -o $@ $<

clean:
	@$(PRINT) $(YELLOW) Cleaning build $(ENDYELLOW) $(ENDLINE)
	@$(RMDIR) $(BUILD_ROOT) $(RMDIR_OPTS)

load: $(Z64)
	@$(PRINT) $(GREEN) Loading $(Z64) onto Everdrive $(ENDGREEN) $(ENDLINE)
	@$(CP) $(Z64) $(TARGET)
	@$(USB64) -rom=$(TARGET) -start
	@$(RM) $(TARGET)

.PHONY: all clean load

-include $(D_FILES)

print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
