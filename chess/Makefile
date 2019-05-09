# Take all the source files available in src
SRC = src/*.cpp

# Irrlicht includes, change this according to your machine 
CPPFLAGS = -I/usr/include/irrlicht/
# Generic includes
CPPFLAGS += -I./include
# General compiler flags
#CXXFLAGS = -O3 -ffast-math
CXXFLAGS = -g -Wall

# Linker flags, change this according to your machine
LDFLAGS = -L/usr/lib/x86_64-linux-gnu/libIrrlicht.a -lIrrlicht -lGL -lGLU -lXext -lXrandr -lX11

# Name of binary, feel free to change it
# If you change the path of the binary, 
# remember to add the font/ and img/ folders in the same path
BIN = chess

# Generic rules
all:
	$(warning Building $(BIN))
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SRC) -o $(BIN) $(LDFLAGS)

clean:
	$(warning Cleaning $(BIN))
	rm $(BIN)

.PHONY: all clean 
