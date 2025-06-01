# Compiler
FC = gfortran

# Compiler flags
FLAGS = -fimplicit-none -Wall -Werror -pedantic -O1 -fopenmp -fcheck=bounds #-Wextra 

# Source file
SRC = main.f90

# Output executable
OUT = main

# Default target
all: $(OUT)

# Rule to build the executable
$(OUT): $(SRC)
	$(FC) $(FLAGS) $(SRC) -o $(OUT)

# Clean up
clean:
	rm -f $(OUT)
