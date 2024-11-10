# Compiler
FC = gfortran

# Compiler flags
FLAGS = -fimplicit-none -Wall -Wextra -pedantic -O3 -fopenmp -fcheck=bounds #-Werror 

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
