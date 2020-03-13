OBJS = 	build/diseaseMonitor.o \
		build/date.o \
		build/hash.o \
		build/input.o
		#build/unit_testing.o


#TEST_OBJS = $(filter-out build/diseaseMonitor.o, $(OBJS))

CC = gcc
FLAGS = -Wall -Wextra -g -c
#CUNIT_FLAG = -lcunit


TARGET = diseaseMonitor
#TARGET_TEST = unit_test

all: $(TARGET) $(TARGET_TEST)

clean:
	$(RM) -r $(TARGET) $(TARGET_TEST) build/*

build/diseaseMonitor.o: src/diseaseMonitor.c
	$(CC) $(FLAGS) $< -o $@

build/date.o: src/date.c
	$(CC) $(FLAGS) $< -o $@

build/hash.o: src/hash.c
	$(CC) $(FLAGS) $< -o $@

build/input.o: src/input.c
	$(CC) $(FLAGS) $< -o $@
#build/unit_testing.o: unit_testing.c
#	$(CC) $(FLAGS) $< -o $@ $(CUNIT_FLAG)




$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lm

#$(TARGET_TEST) : unit_testing.c $(TEST_OBJS)
#	$(CC) $(CFLAGS) $^ -o $@ $(CUNIT_FLAG) -lm

rebuild: clean all
