.PHONY: all test clean

CC = g++
OBJS = main.o WebNavigation.o
TARGET = web_navigation
TESTBIN = runner
.SUFFIXES : .cpp .o

all : $(TARGET)

test : $(TESTHEADER)
	cxxtestgen --error-printer -o runner.cpp test_web_navigation.h
	$(CC) -o $(TESTBIN) -I$CXXTEST runner.cpp WebNavigation.cpp
	./$(TESTBIN)

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)

clean :
	rm -f $(OBJS) $(TARGET) $(TESTBIN) runner.cpp
