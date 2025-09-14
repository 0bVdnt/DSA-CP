# Compiler
CXX = g++

# C++ standard
CPP_STD = -std=c++17

# Common compiler flags
COMMON_FLAGS = $(CPP_STD) -Wall -Wextra -Wshadow -Wconversion -Wno-sign-conversion -Wfloat-equal

# --- Dynamic Source File Configuration ---
STATE_FILE = .current_solution

# Set a default value for the source file. Default is now solution1.cpp
SRCS = solution1.cpp

# Use the 'include' directive to override the default SRCS if the state file exists.
-include $(STATE_FILE)

# Name of this Makefile
CURRENT_MAKEFILE = $(firstword $(MAKEFILE_LIST))

# --- Platform-specific setup ---
RUN_PREFIX := ./
ifeq ($(OS),Windows_NT)
    TARGET_EXT := .exe
else
    TARGET_EXT :=
endif

# --- Contest Directory Setup ---
CID ?= default_contest
CP_TEMPLATE_FILE = template.cpp
IN_FILE ?= input.txt

# --- Build Targets & Flags (Dynamic based on SRCS) ---
SRC_BASE_NAME = $(basename $(SRCS))
TARGET_DEBUG = $(SRC_BASE_NAME)_debug$(TARGET_EXT)
TARGET_RELEASE = $(SRC_BASE_NAME)$(TARGET_EXT)
DEBUG_FLAGS = $(COMMON_FLAGS) -g -DLOCAL
RELEASE_FLAGS = $(COMMON_FLAGS) -O2

# --- Default target ---
all: release

# ========================================================================
# --- Solution and Contest Management Targets ---
# ========================================================================

# --- Target to switch the active solution file ---
switch:
ifeq ($(to),)
	@echo "--- Resetting active solution to 'solution1.cpp' ---"
	@rm -f "$(STATE_FILE)"
	@echo "Active solution is now: solution1.cpp"
else
	$(eval NEW_SRC := solution$(to).cpp)
	@echo "--- Switching active solution to '$(NEW_SRC)' ---"
	@echo "SRCS = $(NEW_SRC)" > "$(STATE_FILE)"
	@echo "Active solution is now: $(NEW_SRC)"
endif

# --- Target to check the current active solution file ---
current:
	@echo "Current active solution file is: $(SRCS)"

# --- Diagnostic check target ---
check:
	@echo "--- Checking Makefile Variables ---"
	@echo "OS (Operating System) = $(OS)"
	@echo "SRCS (Source File)    = $(SRCS)"
	@echo "RUN_PREFIX (Executor) = $(RUN_PREFIX)"
	@echo "TARGET_EXT (Extension)  = $(TARGET_EXT)"
	@echo "TARGET_DEBUG (Debug Exe) = $(TARGET_DEBUG)"
	@echo "---------------------------------"

# --- Target to create contest directory structure ---
contest:
	@echo "--- Setting up directory for contest: $(CID) ---"
	( \
		mkdir -p "$(CID)" && \
		cd "$(CID)" && \
		echo "Creating files in $$(pwd)/..." && \
		touch input.txt output.txt && \
		($(if $(CP_TEMPLATE_FILE),\
			(if [ -f ../$(CP_TEMPLATE_FILE) ]; then \
				echo "Copying template ../$(CP_TEMPLATE_FILE) to solution1.cpp"; \
				cp ../$(CP_TEMPLATE_FILE) solution1.cpp; \
			else \
				echo "Template ../$(CP_TEMPLATE_FILE) not found. Creating empty solution1.cpp"; \
				touch solution1.cpp; \
			fi), \
			touch solution1.cpp \
		)) && \
		touch solution2.cpp solution3.cpp solution4.cpp solution5.cpp solution6.cpp && \
		echo "Copying Makefile to $$(pwd)/..." && \
		cp ../$(CURRENT_MAKEFILE) Makefile && \
		echo "Files created. Makefile copied." && \
		echo "Attempting to open VS Code in $$(pwd)..." && \
		(code . || echo "Warning: 'code .' command failed. VS Code might not be in PATH or not installed. Please open $$(pwd) manually.") \
	)
	@echo "--- Contest setup for $(CID) complete. ---"
	@echo "You can now 'cd $(CID)' to start working on solution1.cpp."

# --- Build, Run, and Test Targets ---

debug: $(TARGET_DEBUG)
$(TARGET_DEBUG): $(SRCS)
	@echo "--- Compiling for DEBUG: $(SRCS) -> $@ ---"
	$(CXX) $(DEBUG_FLAGS) $(SRCS) -o $@
	@echo "Build complete: $(RUN_PREFIX)$@"

release: $(TARGET_RELEASE)
$(TARGET_RELEASE): $(SRCS)
	@echo "--- Compiling for RELEASE: $(SRCS) -> $@ ---"
	$(CXX) $(RELEASE_FLAGS) $(SRCS) -o $@
	@echo "Build complete: $(RUN_PREFIX)$@"

clean:
	@echo "Cleaning up..."
	# This command is now very specific. It cleans up build artifacts for
	# solutions 1-9 (using solution?) and 10-99 (using solution??),
	# but will not touch other files like 'solution_extra.cpp'.
	@rm -f solution?_debug.exe solution??_debug.exe \
	       solution?_debug     solution??_debug \
	       solution?.exe       solution??.exe \
	       solution?           solution?? \
	       *.o *~ core core.* .current_solution
	@echo "Cleanup complete."

# .PHONY list updated with the 'check' target
.PHONY: all debug release clean contest switch current check rd rr td tr

rd: debug
	@echo "--- Running DEBUG version of $(SRCS) ---"
	$(RUN_PREFIX)$(TARGET_DEBUG)

rr: release
	@echo "--- Running RELEASE version of $(SRCS) ---"
	$(RUN_PREFIX)$(TARGET_RELEASE)

td: debug
	@echo "--- Testing DEBUG version of $(SRCS) with input from $(IN_FILE)... ---"
	$(RUN_PREFIX)$(TARGET_DEBUG) < $(IN_FILE)

tr: release
	@echo "--- Testing RELEASE version of $(SRCS) with input from $(IN_FILE)... ---"
	$(RUN_PREFIX)$(TARGET_RELEASE) < $(IN_FILE)