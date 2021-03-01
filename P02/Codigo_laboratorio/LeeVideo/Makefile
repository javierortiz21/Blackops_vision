EXECUTABLE = lee
SOURCES = main.cpp
CC = g++
ODIR=./
SRCDIR=./
INCLUDE = -I./include -I/usr/include/flycapture `pkg-config --cflags opencv`
CFLAGS=-c -Wall $(INCLUDE)
LIBS = -L/usr/local/lib -lm `pkg-config --libs opencv`

OBJ = $(SOURCES:.c=.o)
OBJS = $(patsubst %,$(ODIR)%,$(OBJ))

${EXECUTABLE}: ${OBJS}
	${CC} -o ${EXECUTABLE} ${OBJS} ${LIBS} ${COMMON_LIBS} 

$(ODIR)%.o : $(SRCDIR)%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f ${OBJS} $(EXECUTABLE)