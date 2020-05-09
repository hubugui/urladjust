AR=ar
CC=gcc
DEL=rm -rf
MK=mkdir
OUT=objs
RM=rmdir /s /q
CFLAGS=-Wall -O3
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
TARGET=$(notdir $(CURDIR))
LIBS=lib$(TARGET).a

all: $(TARGET)

$(TARGET): $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^
	-$(DEL) *.a

$(LIBS): $(OBJS)
	$(AR) -r $@ $^
	-$(DEL) *.o

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	-$(DEL) *.a
	-$(DEL) *.o
	-$(DEL) *.out
	-$(DEL) *.lib

rebuild: clean all