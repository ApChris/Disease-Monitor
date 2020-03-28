OBJS = 	../build/diseaseMonitor.o \
		../build/date.o \
		../build/hash.o \
		../build/input.o \
		../build/bst.o \
		../build/hashDC.o \
		../build/requests.o \
		../build/binaryMaxHeap.o \
		../build/linkedlist.o
	
CC = gcc
FLAGS = -Wall -Wextra -g -c

TARGET = diseaseMonitor

all: $(TARGET)

clean:
	$(RM) -r $(TARGET) ../build/*

../build/diseaseMonitor.o: ../src/diseaseMonitor.c
	$(CC) $(FLAGS) $< -o $@

../build/date.o: ../src/date.c
	$(CC) $(FLAGS) $< -o $@

../build/hash.o: ../src/hash.c
	$(CC) $(FLAGS) $< -o $@

../build/input.o: ../src/input.c
	$(CC) $(FLAGS) $< -o $@

../build/bst.o: ../src/bst.c
	$(CC) $(FLAGS) $< -o $@

../build/hashDC.o: ../src/hashDC.c
	$(CC) $(FLAGS) $< -o $@

../build/requests.o: ../src/requests.c
	$(CC) $(FLAGS) $< -o $@

../build/binaryMaxHeap.o: ../src/binaryMaxHeap.c
	$(CC) $(FLAGS) $< -o $@

../build/linkedlist.o: ../src/linkedlist.c
	$(CC) $(FLAGS) $< -o $@


$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lm

rebuild: clean all
