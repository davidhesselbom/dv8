# --------------------------------------------------------------------------
# Variables.
# --------------------------------------------------------------------------

# Path to cross compilation tools.
MIPS_PREFIX = /it/sw/cross/mips-idt/bin/mips-idt-elf

# Compiler.
CC = $(MIPS_PREFIX)-gcc

# Linker.
LD = $(MIPS_PREFIX)-ld

# GCC flags for MIPS architecture (used by both compiler and linker).
# -EL             : little endian
# -G0             : always use small data (using register gp)
# -mips32         : compile for a 32-bit MIPS architecture
ARCH = -EL -G0 -mips32

# Add GCC flags.
# -ggdb           : include debugger info
# -W              : show warnings
# -Wall           : show more warnings
# -Werror         : treat warnings as errors (stops compilation)
# -fno-builtin    : disable built-in functions
# -I              : augment the #include search path
CFLAGS += -ggdb -W -Wall -Werror -fno-builtin -Iinclude

# Add linker flags.
# -Ttext          : tell it where to start the text segment
LDFLAGS += -Ttext 80020000

# Path to Simics installation.
SIMICS = /home/$(shell whoami)/simics-workspace

# Project directories.
DIR_BIN     = bin
DIR_BUILD   = build
DIR_INCLUDE = include
DIR_SCRIPTS = scripts
DIR_SRC     = src

# src/file1.c src/file2.S ...
SOURCES = $(wildcard $(DIR_SRC)/*.c) $(wildcard $(DIR_SRC)/*.S)
# src/file1 src/file2 ...
BASENAMES = $(basename $(SOURCES))
# build/file1.o build/file2.o ...
OBJECTS = $(BASENAMES:$(DIR_SRC)/%=$(DIR_BUILD)/%.o)

# Final binary.
EXE = $(DIR_BIN)/dv8

# --------------------------------------------------------------------------
# Rules.
# --------------------------------------------------------------------------

# Targets that do not correspond to files.
.PHONY: all clean boot build

# Default rule, used when simply typing 'make'.
all: boot

# Compile everything and run Simics.
boot: build
	@- echo '--- Starting simulation ...'
	./$(DIR_SCRIPTS)/run.sh $(SIMICS) $(EXE)
	@- echo "--- Simulation complete!"
	@- echo

# Compile everything.
build: $(EXE)
	@- echo

# Build binary from object files.
$(EXE): $(OBJECTS)
	@- echo
	@- echo '--- Linking $@ ...'
	$(LD) $(ARCH) $(LDFLAGS) $^ -o $@

# Build object from C file.
$(DIR_BUILD)/%.o: $(DIR_SRC)/%.c
	@- echo
	@- echo '--- Compiling $< ...'
	$(CC) $(ARCH) $(CFLAGS) -c $< -o $@

# Build object from assembly file.
$(DIR_BUILD)/%.o: $(DIR_SRC)/%.S
	@- echo
	@- echo '--- Compiling $< ...'
	$(CC) $(ARCH) $(CFLAGS) -c $< -o $@

# Remove unnecessary files and everything generated by make.
clean:
	rm -f ${EXE}
	rm -f $(DIR_BUILD)/*.o
	rm -f $(DIR_INCLUDE)/*~ $(DIR_INCLUDE)/#* $(DIR_INCLUDE)/*#
	rm -f $(DIR_SRC)/*~ $(DIR_SRC)/#* $(DIR_SRC)/*#
	rm -f $(DIR_SCRIPTS)/*~ $(DIR_SCRIPTS)/#* $(DIR_SCRIPTS)/*#
