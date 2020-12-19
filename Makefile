### User Configuration ###

# Name of ROM to build
TARGET := tecto

DEBUG ?= 0

# Do not change below this line!

# Set powershell as the shell on Windows
ifeq ($(OS),Windows_NT)
  SHELL := powershell.exe
  .SHELLFLAGS := -NoProfile -Command
endif

# Default config generation
ifeq ($(OS),Windows_NT)
  ifeq (,$(wildcard ./Makefile.winconfig))
    DUMMY != New-Item Makefile.winconfig -ItemType File
    DUMMY != Add-Content Makefile.winconfig "\# Location of your mips gcc (must have a slash after it!)"
    DUMMY != Add-Content Makefile.winconfig "N64CHAIN := C:/n64/gcc-toolchain-mips64-win64/bin/"
    DUMMY != Add-Content Makefile.winconfig "\# Location of your N64 SDK"
    DUMMY != Add-Content Makefile.winconfig "SDK := C:/n64/n64sdk"
    DUMMY != Add-Content Makefile.winconfig "\# Python command, e.g. python3 (or location if not on the path)"
    DUMMY != Add-Content Makefile.winconfig "PYTHON := python"
    DUMMY != Add-Content Makefile.winconfig "\# Location of Everdrive usb64 application"
    DUMMY != Add-Content Makefile.winconfig "UNFLOADER := C:/n64/UNFLoader.exe)"
  endif
else
  ifeq (,$(wildcard Makefile.config))
    DUMMY != printf "\# Python command, e.g. python3 (or location if not on the path)\nPYTHON := python3\n" >> Makefile.config
  endif
endif

# System config
ifeq ($(OS),Windows_NT)
  include Makefile.winconfig
  SDK_INCLUDE := -I$(SDK)/ultra/usr/include
  NUSTD_INCLUDE := -I$(SDK)/nintendo/n64kid/nustd/include
  ULTRA_LINKER := -L $(SDK)/ultra/usr/lib
  NUSTD_LINKER := -L $(SDK)/nintendo/n64kit/nustd/lib
  GCC_LINKER := -L $(N64CHAIN)../lib/gcc/mips64-elf/10.1.0
  LIBULTRA := gultra_rom
else
  include Makefile.config
  SDK_INCLUDE := -I /usr/include/n64
  NUSTD_INCLUDE := -I /usr/include/n64/nustd
  ULTRA_LINKER := -L /usr/lib/n64
  GCC_LINKER := -L $(N64_LIBGCCDIR)
  LIBULTRA := ultra_rom
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


ifeq ($(OS),Windows_NT)
  MKDIR := New-Item -Path 
  MKDIR_OPTS := -Force -Type Directory | Out-Null
  
  RMDIR := (Remove-Item
  RMDIR_OPTS := -ErrorAction SilentlyContinue -Recurse -Force) -or $$true | Out-Null # The -or $true is needed to prevent make from saying error
  
  RUN := cmd /c
  
  PRINT := Write-Host -NoNewline 
   ENDCOLOR := $(PRINT) "$$([char]27)[0m"; 
   WHITE     := 
   ENDWHITE  := $(space) -ForegroundColor White; $(ENDCOLOR) $(PRINT) 
   GREEN     := 
   ENDGREEN  := $(space) -ForegroundColor Green; $(ENDCOLOR) $(PRINT) 
   BLUE      := 
   ENDBLUE   := $(space) -ForegroundColor Blue; $(ENDCOLOR) $(PRINT) 
   YELLOW    := 
   ENDYELLOW := $(space) -ForegroundColor Yellow; $(ENDCOLOR) $(PRINT) 
  ENDLINE := ; Write-Host 

  PREFIX  := mips64-elf-
else
  MKDIR := mkdir
  MKDIR_OPTS := -p

  RMDIR := rm
  RMDIR_OPTS := -rf

  PRINT := printf '
   ENDCOLOR := \033[0m
   WHITE     := \033[0m
   ENDWHITE  := $(ENDCOLOR)
   GREEN     := \033[0;32m
   ENDGREEN  := $(ENDCOLOR)
   BLUE      := \033[0;34m
   ENDBLUE   := $(ENDCOLOR)
   YELLOW    := \033[0;33m
   ENDYELLOW := $(ENDCOLOR)
  ENDLINE := \n'

  RUN := 
  
  PREFIX  := mips64-elf-
endif

# Build tools
CC      := $(N64CHAIN)$(PREFIX)gcc
AS      := $(N64CHAIN)$(PREFIX)as
CPP     := $(N64CHAIN)$(PREFIX)cpp
CXX     := $(N64CHAIN)$(PREFIX)g++
LD      := $(N64CHAIN)$(PREFIX)ld
OBJCOPY := $(N64CHAIN)$(PREFIX)objcopy

CKSUM   := $(PYTHON) tools/n64cksum.py

### Files and Directories ###

# Source files
SRC_ROOT  := src
SRC_DIRS  := $(wildcard $(SRC_ROOT)/*)
C_SRCS    := $(foreach src_dir,$(SRC_DIRS),$(wildcard $(src_dir)/*.c))
CXX_SRCS  := $(foreach src_dir,$(SRC_DIRS),$(wildcard $(src_dir)/*.cpp))
ASM_SRCS  := $(foreach src_dir,$(SRC_DIRS),$(wildcard $(src_dir)/*.s))
BIN_FILES := $(foreach src_dir,$(SRC_DIRS),$(wildcard $(src_dir)/*.bin))
SEG_SRCS  := $(wildcard segments/*.c)
LD_SCRIPT := n64.ld
BOOT      := boot/boot.6102
ENTRY_AS  := boot/entry.s

# Build folders
ifeq ($(DEBUG),0)
BUILD_ROOT     := bin
else
BUILD_ROOT     := debug
endif
SEG_BUILD_DIR  := $(BUILD_ROOT)/segments
BOOT_BUILD_DIR := $(BUILD_ROOT)/boot
BUILD_DIRS     := $(addprefix $(BUILD_ROOT)/,$(SRC_DIRS)) $(SEG_BUILD_DIR) $(BOOT_BUILD_DIR)

# Build files
C_OBJS   := $(addprefix $(BUILD_ROOT)/,$(C_SRCS:.c=.o))
CXX_OBJS := $(addprefix $(BUILD_ROOT)/,$(CXX_SRCS:.cpp=.o))
ASM_OBJS := $(addprefix $(BUILD_ROOT)/,$(ASM_SRCS:.s=.o))
BIN_OBJS := $(addprefix $(BUILD_ROOT)/,$(BIN_FILES:.bin=.o))
OBJS     := $(C_OBJS) $(CXX_OBJS) $(ASM_OBJS) $(BIN_OBJS)
SEG_OBJS := $(addprefix $(BUILD_ROOT)/,$(SEG_SRCS:.c=.o))
LD_CPP   := $(BUILD_ROOT)/$(LD_SCRIPT)
BOOT_OBJ := $(BUILD_ROOT)/$(BOOT).o
ENTRY_OBJ:= $(BUILD_ROOT)/$(ENTRY_AS:.s=.o)
D_FILES  := $(C_OBJS:.o=.d) $(CXX_OBJS:.o=.d) $(LD_CPP).d $(SEG_OBJS:.o=.d)

CODESEG  := $(BUILD_ROOT)/codesegment.o
Z64      := $(addprefix $(BUILD_ROOT)/,$(TARGET).z64)
V64      := $(addprefix $(BUILD_ROOT)/,$(TARGET).v64)
ELF      := $(Z64:.z64=.elf)

### Flags ###

# Build tool flags

ifeq ($(OS),Windows_NT)
CFLAGS     := -march=vr4300 -mtune=vr4300 -mfix4300 -mabi=32 -mno-shared -G 0 -mhard-float -fno-stack-protector -fno-common -fno-zero-initialized-in-bss \
			  -I include -I . -I src/ $(SDK_INCLUDE) $(NUSTD_INCLUDE) -fno-PIC -mno-abicalls -fno-strict-aliasing -fno-inline-functions -ffreestanding -fwrapv -Wall -Wextra \
			  -mno-check-zero-division -mno-split-addresses -mno-relax-pic-calls -mfp32 -mgp32 -mbranch-cost=1 \
			  -fno-dse -fno-check-pointer-bounds -Wno-chkp -mno-odd-spreg -D_FINALROM \
			  -D_MIPS_SZLONG=32 -D_MIPS_SZINT=32 -D_LANGUAGE_C -D_ULTRA64 -D__EXTENSIONS__ -DF3DEX_GBI_2
else
CFLAGS     := -mabi=32 -ffreestanding -G 0 \
		      -Wall -Wextra \
              -I include -I . -I src/ $(SDK_INCLUDE) $(NUSTD_INCLUDE) \
			  -D_FINALROM -D_MIPS_SZLONG=32 -D_MIPS_SZINT=32 -D_LANGUAGE_C -D_ULTRA64 -D__EXTENSIONS__ -DF3DEX_GBI_2
endif
CXXFLAGS   := 
ASFLAGS    := -mtune=vr4300 -march=vr4300 -mabi=32 -mips3
LDFLAGS    := -T $(LD_CPP) --accept-unknown-input-arch --no-check-sections -Map $(BUILD_ROOT)/$(TARGET).map \
			  $(ULTRA_LINKER) $(NUSTD_LINKER) -L lib $(GCC_LINKER)
SEG_LDFLAGS:= $(ULTRA_LINKER) $(NUSTD_LINKER) -L lib $(GCC_LINKER) \
			  -l$(LIBULTRA) -lnustd -lgcc
LDCPPFLAGS := -P -Wno-trigraphs -DBUILD_ROOT=$(BUILD_ROOT) -DLIBULTRA=lib$(LIBULTRA) -Umips
OCOPYFLAGS := --pad-to=0x400000 --gap-fill=0xFF
OPT_FLAGS  := -Os # Somehow Os is the fastest option according to testing

ifneq ($(DEBUG),0)
CFLAGS     += -DDEBUG_MODE
endif


$(BUILD_ROOT)/src/usb/usb.o: OPT_FLAGS := -O0
$(BUILD_ROOT)/src/usb/usb.o: CFLAGS += -Wno-unused-variable -Wno-sign-compare -Wno-unused-function
$(BUILD_ROOT)/src/usb/debug.o: CFLAGS += -Wno-unused-parameter -Wno-maybe-uninitialized

### Rules ###

# Default target, all
all: $(Z64)

# Make directories
$(BUILD_ROOT) $(BUILD_DIRS) :
	@$(PRINT)$(GREEN)Creating directory: $(ENDGREEN)$(BLUE)$@$(ENDBLUE)$(ENDLINE)
	@$(MKDIR) $@ $(MKDIR_OPTS)

# .c -> .o
$(BUILD_ROOT)/%.o : %.c | $(BUILD_DIRS)
	@$(PRINT)$(GREEN)Compiling C source file: $(ENDGREEN)$(BLUE)$<$(ENDBLUE)$(ENDLINE)
	@$(CC) $< -o $@ -c -MMD -MF $(@:.o=.d) $(CFLAGS) $(OPT_FLAGS)

# .bin -> .o
$(BUILD_ROOT)/%.o : %.bin | $(BUILD_DIRS)
	@$(PRINT)$(GREEN)Objcopying binary file: $(ENDGREEN)$(BLUE)$<$(ENDBLUE)$(ENDLINE)
	@$(OBJCOPY) -I binary -O elf32-big $< $@

# .s -> .o
$(BUILD_ROOT)/%.o : %.s | $(BUILD_DIRS)
	@$(PRINT)$(GREEN)Compiling ASM source file: $(ENDGREEN)$(BLUE)$<$(ENDBLUE)$(ENDLINE)
	@$(AS) $< -o $@ $(ASFLAGS)

# boot -> .o
$(BOOT_OBJ) : $(BOOT) | $(BOOT_BUILD_DIR)
	@$(PRINT)$(GREEN)Copying boot to object file$(ENDGREEN)$(ENDLINE)
	@$(OBJCOPY) -I binary -O elf32-big $< $@

# All .o -> codesegment.o
$(CODESEG) : $(OBJS)
	@$(PRINT)$(GREEN)Combining code objects into code segment$(ENDGREEN)$(ENDLINE)
	@$(LD) -o $@ -r $^ $(SEG_LDFLAGS)

# .o -> .elf
$(ELF) : $(CODESEG) $(SEG_OBJS) $(LD_CPP) $(BOOT_OBJ) $(ENTRY_OBJ)
	@$(PRINT)$(GREEN)Linking elf file:$(ENDGREEN)$(BLUE)$@$(ENDBLUE)$(ENDLINE)
	@$(LD) $(LDFLAGS) -o $@

# .elf -> .z64
$(Z64) : $(ELF)
	@$(PRINT)$(GREEN)Creating z64: $(ENDGREEN)$(BLUE)$@$(ENDBLUE)$(ENDLINE)
	@$(OBJCOPY) $< $@ -O binary $(OCOPYFLAGS)
	@$(PRINT)$(GREEN)Calculating checksums$(ENDGREEN)$(ENDLINE)
	@$(CKSUM) $@
	@$(PRINT)$(WHITE)ROM Built!$(ENDWHITE)$(ENDLINE)

# byteswap z64
$(V64) : $(Z64)
	@$(PRINT)$(GREEN)Byteswapping z64 to v64$(ENDGREEN)$(ENDLINE)
	@$(OBJCOPY) $< $@ -I binary -O binary --reverse-bytes=2

# Preprocess LD script
$(LD_CPP) : $(LD_SCRIPT) | $(BUILD_ROOT)
	@$(PRINT)$(GREEN)Preprocessing linker script$(ENDGREEN)$(ENDLINE)
	@$(CPP) $(LDCPPFLAGS) -MMD -MP -MT $@ -MF $@.d -o $@ $<

clean:
	@$(PRINT)$(YELLOW)Cleaning build$(ENDYELLOW)$(ENDLINE)
	@$(RMDIR) $(BUILD_ROOT) $(RMDIR_OPTS)

load: $(Z64)
	@$(PRINT)$(GREEN)Loading $(Z64) onto flashcart$(ENDGREEN)$(ENDLINE)
	@$(RUN) $(UNFLOADER) -r $(Z64) -d

.PHONY: all clean load

-include $(D_FILES)

print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
