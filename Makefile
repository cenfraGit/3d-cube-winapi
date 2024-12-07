CC = gcc
TARGET = window
SRCS = window.c files/cameramatrix.c files/crossproduct.c files/dividebyw.c files/dotproduct.c files/matrixmultiplication.c files/projectionmatrix.c files/viewportmatrix.c files/rotationmatrices.c files/camera.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -luser32 -lgdi32 -lm

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
