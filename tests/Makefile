CC = gcc
CFLAGS = -I../src
LDFLAGS = -L../src -lraylib -lgdi32 -lwinmm
CFLAGS += -DPLATFORM_DESKTOP
TARGET = Base64Test
SRC = Base64Test.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)