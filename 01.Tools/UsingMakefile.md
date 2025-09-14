# Competitive Programming Workflow with a Makefile

This `Makefile` is designed to streamline the competitive programming workflow for platforms like Codeforces, AtCoder, etc. It automates directory setup, compilation, testing, and switching between multiple problem files within a single contest, allowing for focus on solving problems.

## Features

-   **One-Command Contest Setup:** Create a dedicated, clean directory for a new contest with all necessary files (`make contest`).
-   **Dynamic File Switching:** Seamlessly switch the active problem file, compiling and running without renaming or moving files (`make switch`).
-   **Debug & Release Builds:** Easily compile with full debugging symbols (`-g`, `-DLOCAL`) or with optimizations for submission (`-O2`).
-   **Fast Aliases:** Two-letter commands for common actions (`td` for test-debug, `rd` for run-debug, etc.) to save precious seconds.
-   **Cross-Platform:** Works consistently across Linux(bash), WSL (Ubuntu), and Windows.
-   **State Management:** The Makefile remembers which solution file is being worked on, even if the terminal is closed.
-   **Safe Cleanup:** A `clean` command removes all generated build artifacts without touching the source code.
-   **Self-Contained Workflow:** The `Makefile` copies itself into new contest directories, so the workflow is always available.

## Prerequisites

Before using the Makefile, ensure having installed the following and make sure it is accessible from the terminal's PATH:

1.  **A C++ Compiler:** `g++` (GCC) is recommended.
2.  **`make` Utility:** Standard on Linux/WSL. On Windows, it's included with tools like MinGW/MSYS2 or Git for Windows.
3.  **(Optional) Visual Studio Code:** The `contest` command will try to open the new directory in VS Code if the `code` command is available in the system's PATH.


## One-Time Setup

1.  **Create a Root Directory:** Create a main folder where all the contest directories will be stored. For example: `D:\CP\` or `~/cp/`.
2.  **Place Files:** Place the `Makefile` and the C++ `template.cpp` (optional) file inside this root directory.
3.  **Configure Template Name (Optional):** If the template file is not named `template.cpp`, open the `Makefile` and edit this line to match the filename:
    ```makefile
    CP_TEMPLATE_FILE = new_template_name.cpp
    ```

## Contest Workflow: A Step-by-Step Guide

Here is a realistic example of how to use this Makefile during a contest.

### Step 1: Start the Contest

Open the terminal in the **root** CP directory (e.g., `~/cp/`). Run the `contest` command, providing the contest ID (CID).

```bash
# Example for Codeforces Round 999
make contest CID=CF_Round_999
```

This command will:
-   Create a new folder named `CF_Round_999`.
-   Inside it, create `input.txt`, `output.txt`, and empty solution files (`solution2.cpp`, `solution3.cpp`, etc.).
-   Copy the `template.cpp` into `solution1.cpp`.
-   Copy the `Makefile` itself into the new directory.
-   Attempt to open the `CF_Round_999` folder in VS Code.

Now, navigate into the new contest directory:
```bash
cd CF_Round_999
```

### Step 2: Solve Problem A (in `solution1.cpp`)

The Makefile automatically targets `solution1.cpp` by default.

1.  Open `solution1.cpp` and write the code.
2.  Paste the test case input into `input.txt`.
3.  Compile and run the code against the input file using the **test-debug** alias:
    ```bash
    make td
    ```
    This compiles `solution1.cpp` with debug flags and runs it, feeding it `input.txt`. The output appears in the terminal.
4.  Once the logic is correct, you can submit the `solution1.cpp` file.

### Step 3: Solve Problem B (in `solution2.cpp`)

1.  Tell the Makefile to switch its focus to `solution2.cpp`:
    ```bash
    make switch to=2
    ```
2.  Open the (currently empty) `solution2.cpp`, paste the template code, and start solving Problem B.
3.  Update `input.txt` with the test cases for Problem B.
4.  Test the code using the **exact same command as before**:
    ```bash
    make td
    ```
    The Makefile is now smart enough to compile and run `solution2.cpp`.

### Step 4: Switching and Checking

-   **Go back to Problem A?** Simply switch back:
    ```bash
    make switch to=1
    ```
-   **Forgot which file is active?** Check the current status:
    ```bash
    make current
    # Output: Current active solution file is: solution2.cpp
    ```
-   **Reset to the default file?**
    ```bash
    make switch to=
    # This resets the active file to solution1.cpp
    ```

### Step 5: After the Contest

Once done, the user can clean up all the compiled executables and state files:
```bash
make clean
```
This leaves the directory with only the source code and input/output files.

## Command Reference

| Command | Meaning | Description |
| :--- | :--- | :--- |
| **Setup & Management** | | |
| `make contest CID=<id>` | Contest ID | Creates a new contest directory with all necessary files. |
| `make switch to=<n>` | Problem Number | Switches the active build target to `solution<n>.cpp`. |
| `make switch to=` | To Problem 1 | Resets the active build target to the default (`solution1.cpp`). |
| `make current` | Current File | Displays the currently active solution file. |
| `make check` | | A diagnostic tool to check key Makefile variables. |
| `make clean` | | Removes all compiled files and temporary state files. |
| **Building & Testing** | | |
| `make debug` | | Compiles the active file with debug flags. |
| `make release` | | Compiles the active file with optimization flags. |
| `make rd` | run_debug | Compiles and runs the debug version (for interactive input). |
| `make rr` | run_release | Compiles and runs the release version (for interactive input). |
| `make td` | test_debug | Compiles and runs the debug version with `input.txt` as input. |
| `make tr` | test_release | Compiles and runs the release version with `input.txt` as input. |

## Customization

-   **Default Input File:** The default input file is `input.txt`. You can override this for a single run:
    ```bash
    make td IN_FILE=my_input.txt
    ```
    Or change the default by editing this line in the Makefile:
    ```makefile
    IN_FILE ?= input.txt
    ```