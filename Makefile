TARGET = Console
CFLAGS = -std=c++17

all: $(TARGET)

$(TARGET):
	g++ $(CFLAGS) -o $(TARGET) $(TARGET).cpp
	
clean:
	$(RM) $(TARGET)
