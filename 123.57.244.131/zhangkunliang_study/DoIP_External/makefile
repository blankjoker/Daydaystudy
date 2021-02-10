CC = gcc
CXX = g++
AR = ar
LD = gcc

OBJDIR = obj/
CFLAGS = -Wall -fvisibility=hidden -fPIC
CFLAGS_DEBUG = $(CFLAGS) -g
LIB = -lpthread
OUT_DEBUG_CLIENT = equipment_canoe

OBJ_DEBUG = $(OBJDIR)/ne_doip_connection.o \
			$(OBJDIR)/ne_doip_os.o \
			$(OBJDIR)/ne_doip_thread.o \
			$(OBJDIR)/ne_doip_util.o \
			$(OBJDIR)/ne_doip_event_loop.o \
			$(OBJDIR)/ne_doip_timer.o \
			$(OBJDIR)/ne_doip_select.o \
			$(OBJDIR)/main.o \

all: debug
clean: clean_debug

debug: before_debug out_debug_client after_debug

after_debug:

before_debug:
	test -d $(OBJDIR) || mkdir -p $(OBJDIR)

out_debug_client:$(OBJ_DEBUG)
	$(LD) $(OBJ_DEBUG) -o $(OUT_DEBUG_CLIENT) $(LIB)

$(OBJDIR)/ne_doip_connection.o: ne_doip_connection.c
	$(CC) $(CFLAGS_DEBUG) -c ne_doip_connection.c -o $(OBJDIR)/ne_doip_connection.o

$(OBJDIR)/ne_doip_timer.o: ne_doip_timer.c
	$(CC) $(CFLAGS_DEBUG) -c ne_doip_timer.c -o $(OBJDIR)/ne_doip_timer.o

$(OBJDIR)/ne_doip_os.o: ne_doip_os.c
	$(CC) $(CFLAGS_DEBUG) -c ne_doip_os.c -o $(OBJDIR)/ne_doip_os.o

$(OBJDIR)/ne_doip_select.o: ne_doip_select.c
	$(CC) $(CFLAGS_DEBUG) -c ne_doip_select.c -o $(OBJDIR)/ne_doip_select.o

$(OBJDIR)/ne_doip_thread.o: ne_doip_thread.c
	$(CC) $(CFLAGS_DEBUG) -c ne_doip_thread.c -o $(OBJDIR)/ne_doip_thread.o

$(OBJDIR)/ne_doip_util.o: ne_doip_util.c
	$(CC) $(CFLAGS_DEBUG) -c ne_doip_util.c -o $(OBJDIR)/ne_doip_util.o

$(OBJDIR)/ne_doip_event_loop.o: ne_doip_event_loop.c
	$(CC) $(CFLAGS_DEBUG) -c ne_doip_event_loop.c -o $(OBJDIR)/ne_doip_event_loop.o

$(OBJDIR)/main.o: main.c
	$(CC) $(CFLAGS_DEBUG) -c main.c -o $(OBJDIR)/main.o

clean_debug:
	rm -rf $(OBJ_DEBUG)
	rm -rf $(OUT_DEBUG_CLIENT)

.PHONY: before_debug after_debug clean_debug