CXX = g++
CPP_STD = -std=c++17

# Common flags for all platforms
COMMON_FLAGS = $(CPP_STD) -Wall -Wextra -Wshadow -Wconversion -Wno-sign-conversion -Wfloat-equal

# Dynamic source file configuration
STATE_FILE = .current_solution
SRCS = solution1.cpp
-include $(STATE_FILE)
SRCS := $(strip $(SRCS))

# Makefile and contest setup
CURRENT_MAKEFILE = $(firstword $(MAKEFILE_LIST))
CID ?= default_contest
CP_TEMPLATE_FILE = template.cpp
IN_FILE ?= input.txt

# Default to Unix-like environment settings
TARGET_EXT :=
RUN_PREFIX := ./
RM := rm -f
COPY := cp
MKDIR := mkdir -p
TOUCH := touch

# Override settings for Windows NT (cmd and PowerShell)
ifeq ($(OS),Windows_NT)
    TARGET_EXT := .exe
    RUN_PREFIX :=
    RM := del /F /Q
    COPY := copy
    MKDIR := mkdir
    # 'touch' equivalent for cmd (creates an empty file)
    TOUCH := type NUL >
endif

# --- Dynamic Build Targets (based on SRCS and platform) ---
SRC_BASE_NAME = $(basename $(SRCS))
TARGET_DEBUG = $(SRC_BASE_NAME)_debug$(TARGET_EXT)
TARGET_RELEASE = $(SRC_BASE_NAME)$(TARGET_EXT)
DEBUG_FLAGS = $(COMMON_FLAGS) -g -DLOCAL
RELEASE_FLAGS = $(COMMON_FLAGS) -O2

# --- Default target ---
all: release

# --- Switch active solution file ---
switch:
ifeq ($(to),)
	@echo "--- Resetting active solution to 'solution1.cpp' ---"
	@$(RM) "$(STATE_FILE)" 2>NUL || @true
	@echo "Active solution is now: solution1.cpp"
else
	$(eval NEW_SRC := solution$(to).cpp)
	@echo "--- Switching active solution to '$(NEW_SRC)' ---"
	@echo SRCS = $(NEW_SRC) > "$(STATE_FILE)"
	@echo "Active solution is now: $(NEW_SRC)"
endif

# --- Check current active solution ---
current:
	@echo "Current active solution file is: $(SRCS)"

# --- Diagnostic check ---
check:
	@echo "--- Checking Makefile Variables ---"
	@echo "OS (Operating System) = $(OS)"
	@echo "SRCS (Source File)    = $(SRCS)"
	@echo "TARGET_EXT (Extension)  = $(TARGET_EXT)"
	@echo "TARGET_DEBUG (Debug Exe) = $(TARGET_DEBUG)"
	@echo "---------------------------------"

# --- Create contest directory structure (Cross-Platform) ---
contest:
ifeq ($(OS),Windows_NT)
	@echo "--- Setting up directory for contest: $(CID) (Windows) ---"
	@if not exist "$(CID)" $(MKDIR) "$(CID)"
	@cd $(CID) && ( \
		echo Creating files... && \
		$(TOUCH) input.txt && $(TOUCH) output.txt && \
		(if exist "..\$(CP_TEMPLATE_FILE)" ( \
			echo Copying template ..\$(CP_TEMPLATE_FILE) to solution1.cpp && \
			$(COPY) "..\$(CP_TEMPLATE_FILE)" solution1.cpp > NUL \
		) else ( \
			echo Template not found. Creating empty solution1.cpp && \
			$(TOUCH) solution1.cpp \
		)) && \
		$(TOUCH) solution2.cpp && $(TOUCH) solution3.cpp && $(TOUCH) solution4.cpp && $(TOUCH) solution5.cpp && $(TOUCH) solution6.cpp && \
		echo Copying Makefile... && \
		$(COPY) "..\$(CURRENT_MAKEFILE)" Makefile > NUL && \
		echo Files created. Makefile copied. && \
		echo Attempting to open VS Code... && \
		(code . || echo Warning: 'code .' command failed. VS Code might not be in your PATH.) \
	)
else
	@echo "--- Setting up directory for contest: $(CID) (Unix) ---"
	@$(MKDIR) "$(CID)" && cd "$(CID)" && ( \
		echo "Creating files in $$(pwd)/..." && \
		$(TOUCH) input.txt output.txt && \
		(if [ -f ../$(CP_TEMPLATE_FILE) ]; then \
			echo "Copying template ../$(CP_TEMPLATE_FILE) to solution1.cpp"; \
			$(COPY) ../$(CP_TEMPLATE_FILE) solution1.cpp; \
		else \
			echo "Template not found. Creating empty solution1.cpp"; \
			$(TOUCH) solution1.cpp; \
		fi) && \
		$(TOUCH) solution2.cpp solution3.cpp solution4.cpp solution5.cpp solution6.cpp && \
		echo "Copying Makefile to $$(pwd)/..." && \
		$(COPY) ../$(CURRENT_MAKEFILE) Makefile && \
		echo "Files created. Makefile copied." && \
		echo "Attempting to open VS Code in $$(pwd)..." && \
		(code . || echo "Warning: 'code .' command failed. VS Code might not be in PATH.") \
	)
endif
	@echo "--- Contest setup for $(CID) complete. ---"
	@echo "You can now 'cd $(CID)' to start working."

# --- Build Targets ---
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

# --- Clean build artifacts ---
clean:
	@echo "Cleaning up..."
	@$(RM) solution?_debug$(TARGET_EXT) solution??_debug$(TARGET_EXT) 2>NUL || @true
	@$(RM) solution?$(TARGET_EXT) solution??$(TARGET_EXT) 2>NUL || @true
	@$(RM) *.o *~ core core.* .current_solution 2>NUL || @true
	@echo "Cleanup complete."

# --- Run and Test Aliases ---
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