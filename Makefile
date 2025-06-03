# Compiler
CXX = g++

# C++ standard
CPP_STD = -std=c++17

# Common compiler flags
COMMON_FLAGS = $(CPP_STD) -Wall -Wextra -Wshadow -Wconversion -Wno-sign-conversion -Wfloat-equal

# Source file(s) - This is for the compilation targets, not for make_dirs
SRCS = solution.cpp

# Name of this Makefile, for self-copying
# Using $(MAKEFILE_LIST) gets the name of the current makefile being processed.
# We take the first word in case there are multiple included makefiles.
CURRENT_MAKEFILE = $(firstword $(MAKEFILE_LIST))


# OS detection for platform-specific commands
ifeq ($(OS),Windows_NT)
    TARGET_EXT := .exe
    RUN_PREFIX :=
    RM := del /Q /F
    MKDIR_CMD = if not exist "$(1)" mkdir "$(1)"
    COPY_CMD = copy /Y
else
    TARGET_EXT :=
    RUN_PREFIX := ./
    RM := rm -f
    MKDIR_CMD = mkdir -p "$(1)"
    COPY_CMD = cp
endif

# --- Contest Directory Setup ---
CONTEST_ID ?= default_contest
CP_TEMPLATE_FILE = template.cpp # Example: uncomment and set your template name


# --- Debug Build ---
TARGET_DEBUG_BASE = solution_debug
TARGET_DEBUG = $(TARGET_DEBUG_BASE)$(TARGET_EXT)
DEBUG_FLAGS = $(COMMON_FLAGS) -g -DLOCAL

# --- Release/Normal Build (for submission) ---
TARGET_RELEASE_BASE = solution
TARGET_RELEASE = $(TARGET_RELEASE_BASE)$(TARGET_EXT)
RELEASE_FLAGS = $(COMMON_FLAGS) -O2

# --- Default target ---
all: release

# --- Target to create contest directory structure ---
make_dirs:
	@echo "--- Setting up directory for contest: $(CONTEST_ID) ---"
	$(call MKDIR_CMD,$(CONTEST_ID))
	@echo "Changing directory to $(CONTEST_ID)..."
ifeq ($(OS),Windows_NT)
	( \
		cd $(CONTEST_ID) && \
		echo Creating files in %CD%... && \
		type NUL > input.txt && \
		type NUL > output.txt && \
		($(if $(CP_TEMPLATE_FILE),\
			(if exist ..\$(CP_TEMPLATE_FILE) (\
				echo Copying template ..\$(CP_TEMPLATE_FILE) to solution.cpp && \
				$(COPY_CMD) ..\$(CP_TEMPLATE_FILE) solution.cpp \
			) else (\
				echo Template ..\$(CP_TEMPLATE_FILE) not found. Creating empty solution.cpp && \
				type NUL > solution.cpp \
			)),\
			type NUL > solution.cpp \
		)) && \
		type NUL > solution1.cpp && \
		type NUL > solution2.cpp && \
		type NUL > solution3.cpp && \
		type NUL > solution4.cpp && \
		type NUL > solution5.cpp && \
		type NUL > solution6.cpp && \
		echo Copying Makefile to %CD%... && \
		$(COPY_CMD) ..\$(CURRENT_MAKEFILE) Makefile && \
		echo Files created. Makefile copied. && \
		echo Attempting to open VS Code in %CD%... && \
		(start code . || echo Warning: 'start code .' failed. VS Code might not be in PATH or not installed. Please open %CD% manually.) \
	)
else
# Unix-like shell version
	( \
		cd $(CONTEST_ID) && \
		echo "Creating files in $$(pwd)/..." && \
		touch input.txt output.txt && \
		($(if $(CP_TEMPLATE_FILE),\
			(if [ -f ../$(CP_TEMPLATE_FILE) ]; then \
				echo "Copying template ../$(CP_TEMPLATE_FILE) to solution.cpp"; \
				$(COPY_CMD) ../$(CP_TEMPLATE_FILE) solution.cpp; \
			else \
				echo "Template ../$(CP_TEMPLATE_FILE) not found. Creating empty solution.cpp"; \
				touch solution.cpp; \
			fi), \
			touch solution.cpp \
		)) && \
		touch solution1.cpp solution2.cpp solution3.cpp solution4.cpp solution5.cpp solution6.cpp && \
		echo "Copying Makefile to $$(pwd)/..." && \
		$(COPY_CMD) ../$(CURRENT_MAKEFILE) Makefile && \
		echo "Files created. Makefile copied." && \
		echo "Attempting to open VS Code in $$(pwd)..." && \
		(code . || echo "Warning: 'code .' command failed. VS Code might not be in PATH or not installed. Please open $$(pwd) manually.") \
	)
endif
	@echo "--- Contest setup for $(CONTEST_ID) complete. ---"
	@echo "You can now 'cd $(CONTEST_ID)' to start working if VS Code didn't open automatically."


# --- Target to build for debugging ---
# Note: This target and 'release' will operate on SRCS in the directory where 'make' is run.
# If you 'cd' into a contest directory and run 'make' using the copied Makefile,
# SRCS should ideally be defined relative to that subdirectory's Makefile or just be 'solution.cpp'.
debug: $(TARGET_DEBUG)

$(TARGET_DEBUG): $(SRCS)
	@echo "Compiling for DEBUG: $(SRCS) -> $@"
	$(CXX) $(DEBUG_FLAGS) $(SRCS) -o $@
	@echo "Debug build complete: $(RUN_PREFIX)$@"

# --- Target to build for release/submission ---
release: $(TARGET_RELEASE)

$(TARGET_RELEASE): $(SRCS)
	@echo "Compiling for RELEASE: $(SRCS) -> $@"
	$(CXX) $(RELEASE_FLAGS) $(SRCS) -o $@
	@echo "Release build complete: $(RUN_PREFIX)$@"

# --- Clean up build files ---
clean:
	@echo "Cleaning up..."
	$(RM) $(TARGET_DEBUG_BASE)$(TARGET_EXT) $(TARGET_DEBUG_BASE) \
	      $(TARGET_RELEASE_BASE)$(TARGET_EXT) $(TARGET_RELEASE_BASE) \
	      *.o *~ core core.*
	@echo "Cleanup complete."

# --- Phony targets (targets that don't produce a file with their name) ---
.PHONY: all debug release clean make_dirs run_debug run_release test_debug test_release

# ========================================================================
# --- Options to RUN your compiled code (these run solution.cpp from root Makefile) ---
# ========================================================================
# ... (run_debug, run_release, test_debug, test_release targets remain the same) ...
# --- Run the DEBUG version (compiles if needed) ---
IN_FILE ?= input.txt
run_d: debug
	@echo "Running DEBUG version ($(RUN_PREFIX)$(TARGET_DEBUG))..."
	$(RUN_PREFIX)$(TARGET_DEBUG)

# --- Run the RELEASE version (compiles if needed) ---
run_r: release
	@echo "Running RELEASE version ($(RUN_PREFIX)$(TARGET_RELEASE))..."
	$(RUN_PREFIX)$(TARGET_RELEASE)

# --- Run the DEBUG version with input from a file ---
# Usage: make test_debug IN_FILE=input.txt
test_d: debug
	@echo "Testing DEBUG version ($(RUN_PREFIX)$(TARGET_DEBUG)) with input from $(IN_FILE)..."
	$(RUN_PREFIX)$(TARGET_DEBUG) < $(IN_FILE)

# --- Run the RELEASE version with input from a file ---
# Usage: make test_release IN_FILE=input.txt
test_r: release
	@echo "Testing RELEASE version ($(RUN_PREFIX)$(TARGET_RELEASE)) with input from $(IN_FILE)..."
	$(RUN_PREFIX)$(TARGET_RELEASE) < $(IN_FILE)