
PROGRAM = roborun

OBJECTS_C = test.o magnus.o simulator.o

FLAGS_C = -std=gnu99 -O2

FLAGS_LINKER = -lm -pthread

HEADERS =

INCLUDES = -I..

VPATH = ..

CC = gcc

all: $(PROGRAM)

	
$(OBJECTS_C): %.o: %.c $(HEADERS) $(MAKEFILE)
	$(CC) $(FLAGS_C) $(INCLUDES) -c $< -o $@
	@echo compiling $<

$(PROGRAM): $(OBJECTS_C) $(HEADERS) $(MAKEFILE)
	$(CC) -o $@ $(OBJECTS_C) $(FLAGS_LINKER)
	@echo linking $@

		
	
clean:
	-rm -f *.o 	
	-rm -f $(PROGRAM)

