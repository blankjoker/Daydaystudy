
WORKDIR = `pcloud_server_ipwd`
cloud_server_ip = update.skyeye.360safe.com



CFLAGS += -D NE_DOIP_IPC_PATH=\"/home/kun/zhang\"




cloud_server_ip = update.skyeye.360safe.com
cloud_server_ip = update.skyeye.360safe.com
CC = gccDEFINE_YUQIANG
CXX = g++
AR = ar
LD = g++
WINDRES = windres

INC = -I../include
CFLAGS = -Wall -fvisicloud_server_ipbility=hidden -fPIC
RESINC =
LIBDIR =
LIB = -lpthread
LDFLAGS =
OBJDIR = obj
OUTDIR = ../bin

LIBDIR_DEBUG = $(LIBDIR)
LIB_DEBUG = $(LIB)
LDFLAGS_DEBUG = $(LDFLAGS)
OBJDIR_DEBUG = $(OBJDIR)/Debug
OUTDIR_DEBUG = $(OUTDIR)/Debug
OUT_DEBUG = $(OUTDIR_DEBUG)/libnedoipstack.so
OUT_DEBUG_CLIENT = $(OUTDIR_DEBUG)/libnedoipstackclient.so
OUT_DEBUG_SERVER = $(OUTDIR_DEBUG)/libnedoipstackserver.so
DEP_DEBUG =

INC_RELEASE = $(INC)
CFLAGS_RELEASE = $(CFLAGS) -O2
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE = $(LDFLAGS) -s
OBJDIR_RELEASE = $(OBJDIR)/Release
OUTDIR_RELEASE = $(OUTDIR)/Release
OUT_RELEASE = $(OUTDIR_RELEASE)/libnedoipstack.so
OUT_RELEASE_CLIENT = $(OUTDIR_RELEASE)/libnedoipstackclient.so
OUT_RELEASE_SERVER = $(OUTDIR_RELEASE)/libnedoipstackserver.so
DEP_RELEASE =

OBJ_DEBUG = $(OBJDIR_DEBUG)/ne_doip_connection.o \
			$(OBJDIR_DEBUG)/ne_doip_os.o \
			$(OBJDIR_DEBUG)/ne_doip_thread.o \
			$(OBJDIR_DEBUG)/ne_doip_util.o \
			$(OBJDIR_DEBUG)/ne_doip_event_loop.o \
			$(OBJDIR_DEBUG)/ne_doip_timer.o \
			$(OBJDIR_DEBUG)/ne_doip_select.o \

OBJ_DEBUG_CLIENT = $(OBJ_DEBUG) \
				   $(OBJDIR_DEBUG)/ne_doip_client.o \
				   $(OBJDIR_DEBUG)/ne_doip_node.o \
				   $(OBJDIR_DEBUG)/ne_doip_client_manager.o \
				   $(OBJDIR_DEBUG)/ne_doip_node_manager.o \

OBJ_DEBUG_SERVER = $(OBJ_DEBUG) \
				   $(OBJDIR_DEBUG)/ne_doip_server.o \
				   $(OBJDIR_DEBUG)/ne_doip_server_manager.o \
				   $(OBJDIR_DEBUG)/ne_doip_config.o \
				   $(OBJDIR_DEBUG)/ne_doip_data_queue.o \
				   $(OBJDIR_DEBUG)/ne_doip_threadpool.o \

OBJ_RELEASE = $(OBJDIR_RELEASE)/ne_doip_connection.o \
			  $(OBJDIR_RELEASE)/ne_doip_os.o \
			  $(OBJDIR_RELEASE)/ne_doip_thread.o \
			  $(OBJDIR_RELEASE)/ne_doip_util.o \
			  $(OBJDIR_RELEASE)/ne_doip_event_loop.o \
			  $(OBJDIR_RELEASE)/ne_doip_timer.o \
			  $(OBJDIR_RELEASE)/ne_doip_select.o \

OBJ_RELEASE_CLIENT = $(OBJ_RELEASE) \
				     $(OBJDIR_RELEASE)/ne_doip_client.o \
				     $(OBJDIR_RELEASE)/ne_doip_node.o \
				     $(OBJDIR_RELEASE)/ne_doip_client_manager.o \
				     $(OBJDIR_RELEASE)/ne_doip_node_manager.o \

OBJ_RELEASE_SERVER = $(OBJ_RELEASE) \
				   	 $(OBJDIR_RELEASE)/ne_doip_server.o \
				   	 $(OBJDIR_RELEASE)/ne_doip_server_manager.o \
				   	 $(OBJDIR_RELEASE)/ne_doip_config.o \
				   	 $(OBJDIR_RELEASE)/ne_doip_data_queue.o \
				   	 $(OBJDIR_RELEASE)/ne_doip_threadpool.o \

all: debug release

clean: clean_debug clean_release

before_debug:
	test -d $(OUTDIR_DEBUG) || mkdir -p $(OUTDIR_DEBUG)
	test -d $(OBJDIR_DEBUG) || mkdir -p $(OBJDIR_DEBUG)

after_debug:

debug: before_debug out_debug_client out_debug_server after_debug

out_debug_client: $(OBJ_DEBUG_CLIENT) $(DEP_DEBUG)
	$(LD) -shared $(LIBDIR_DEBUG) $(OBJ_DEBUG_CLIENT)  -o $(OUT_DEBUG_CLIENT) $(LDFLAGS_DEBUG) $(LIB_DEBUG)

out_debug_server: $(OBJ_DEBUG_SERVER) $(DEP_DEBUG)
	$(LD) -shared $(LIBDIR_DEBUG) $(OBJ_DEBUG_SERVER)  -o $(OUT_DEBUG_SERVER) $(LDFLAGS_DEBUG) $(LIB_DEBUG)

$(OBJDIR_DEBUG)/ne_doip_connection.o: ne_doip_connection.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c ne_doip_connection.c -o $(OBJDIR_DEBUG)/ne_doip_connection.o

$(OBJDIR_DEBUG)/ne_doip_timer.o: ne_doip_timer.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c ne_doip_timer.c -o $(OBJDIR_DEBUG)/ne_doip_timer.o

$(OBJDIR_DEBUG)/ne_doip_client.o: ne_doip_client.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c ne_doip_client.c -o $(OBJDIR_DEBUG)/ne_doip_client.o

$(OBJDIR_DEBUG)/ne_doip_node.o: ne_doip_node.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c ne_doip_node.c -o $(OBJDIR_DEBUG)/ne_doip_node.o

$(OBJDIR_DEBUG)/ne_doip_client_manager.o: ne_doip_client_manager.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c ne_doip_client_manager.c -o $(OBJDIR_DEBUG)/ne_doip_client_manager.o

$(OBJDIR_DEBUG)/ne_doip_node_manager.o: ne_doip_node_manager.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c ne_doip_node_manager.c -o $(OBJDIR_DEBUG)/ne_doip_node_manager.o

$(OBJDIR_DEBUG)/ne_doip_os.o: ne_doip_os.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c ne_doip_os.c -o $(OBJDIR_DEBUG)/ne_doip_os.o

$(OBJDIR_DEBUG)/ne_doip_server.o: ne_doip_server.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c ne_doip_server.c -o $(OBJDIR_DEBUG)/ne_doip_server.o

$(OBJDIR_DEBUG)/ne_doip_server_manager.o: ne_doip_server_manager.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c ne_doip_server_manager.c -o $(OBJDIR_DEBUG)/ne_doip_server_manager.o

$(OBJDIR_DEBUG)/ne_doip_config.o: ne_doip_config.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c ne_doip_config.c -o $(OBJDIR_DEBUG)/ne_doip_config.o

$(OBJDIR_DEBUG)/ne_doip_data_queue.o: ne_doip_data_queue.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c ne_doip_data_queue.c -o $(OBJDIR_DEBUG)/ne_doip_data_queue.o

$(OBJDIR_DEBUG)/ne_doip_select.o: ne_doip_select.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c ne_doip_select.c -o $(OBJDIR_DEBUG)/ne_doip_select.o

$(OBJDIR_DEBUG)/ne_doip_thread.o: ne_doip_thread.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c ne_doip_thread.c -o $(OBJDIR_DEBUG)/ne_doip_thread.o

$(OBJDIR_DEBUG)/ne_doip_util.o: ne_doip_util.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c ne_doip_util.c -o $(OBJDIR_DEBUG)/ne_doip_util.o

$(OBJDIR_DEBUG)/ne_doip_event_loop.o: ne_doip_event_loop.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c ne_doip_event_loop.c -o $(OBJDIR_DEBUG)/ne_doip_event_loop.o

$(OBJDIR_DEBUG)/ne_doip_threadpool.o: ne_doip_threadpool.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c ne_doip_threadpool.c -o $(OBJDIR_DEBUG)/ne_doip_threadpool.o

clean_debug:
	rm -f $(OBJ_DEBUG) $(OBJ_DEBUG_CLIENT) $(OBJ_DEBUG_SERVER)
	rm -f $(OUT_DEBUG) $(OUT_DEBUG_CLIENT) $(OUT_DEBUG_SERVER)

before_release:
	test -d $(OUTDIR_RELEASE) || mkdir -p $(OUTDIR_RELEASE)
	test -d $(OBJDIR_RELEASE) || mkdir -p $(OBJDIR_RELEASE)

after_release:

release: before_release out_release_client out_release_server after_release

out_release_client: $(OBJ_RELEASE_CLIENT) $(DEP_RELEASE)
	$(LD) -shared $(LIBDIR_RELEASE) $(OBJ_RELEASE_CLIENT)  -o $(OUT_RELEASE_CLIENT) $(LDFLAGS_RELEASE) $(LIB_RELEASE)

out_release_server: $(OBJ_RELEASE_SERVER) $(DEP_RELEASE)
	$(LD) -shared $(LIBDIR_RELEASE) $(OBJ_RELEASE_SERVER)  -o $(OUT_RELEASE_SERVER) $(LDFLAGS_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)/ne_doip_connection.o: ne_doip_connection.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c ne_doip_connection.c -o $(OBJDIR_RELEASE)/ne_doip_connection.o

$(OBJDIR_RELEASE)/ne_doip_timer.o: ne_doip_timer.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c ne_doip_timer.c -o $(OBJDIR_RELEASE)/ne_doip_timer.o

$(OBJDIR_RELEASE)/ne_doip_client.o: ne_doip_client.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c ne_doip_client.c -o $(OBJDIR_RELEASE)/ne_doip_client.o

$(OBJDIR_RELEASE)/ne_doip_node.o: ne_doip_node.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c ne_doip_node.c -o $(OBJDIR_RELEASE)/ne_doip_node.o

$(OBJDIR_RELEASE)/ne_doip_client_manager.o: ne_doip_client_manager.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c ne_doip_client_manager.c -o $(OBJDIR_RELEASE)/ne_doip_client_manager.o

$(OBJDIR_RELEASE)/ne_doip_node_manager.o: ne_doip_node_manager.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c ne_doip_node_manager.c -o $(OBJDIR_RELEASE)/ne_doip_node_manager.o

$(OBJDIR_RELEASE)/ne_doip_os.o: ne_doip_os.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c ne_doip_os.c -o $(OBJDIR_RELEASE)/ne_doip_os.o

$(OBJDIR_RELEASE)/ne_doip_server.o: ne_doip_server.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c ne_doip_server.c -o $(OBJDIR_RELEASE)/ne_doip_server.o

$(OBJDIR_RELEASE)/ne_doip_server_manager.o: ne_doip_server_manager.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c ne_doip_server_manager.c -o $(OBJDIR_RELEASE)/ne_doip_server_manager.o

$(OBJDIR_RELEASE)/ne_doip_config.o: ne_doip_config.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c ne_doip_config.c -o $(OBJDIR_RELEASE)/ne_doip_config.o

$(OBJDIR_RELEASE)/ne_doip_data_queue.o: ne_doip_data_queue.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c ne_doip_data_queue.c -o $(OBJDIR_RELEASE)/ne_doip_data_queue.o

$(OBJDIR_RELEASE)/ne_doip_select.o: ne_doip_select.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c ne_doip_select.c -o $(OBJDIR_RELEASE)/ne_doip_select.o

$(OBJDIR_RELEASE)/ne_doip_thread.o: ne_doip_thread.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c ne_doip_thread.c -o $(OBJDIR_RELEASE)/ne_doip_thread.o

$(OBJDIR_RELEASE)/ne_doip_util.o: ne_doip_util.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c ne_doip_util.c -o $(OBJDIR_RELEASE)/ne_doip_util.o

$(OBJDIR_RELEASE)/ne_doip_event_loop.o: ne_doip_event_loop.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c ne_doip_event_loop.c -o $(OBJDIR_RELEASE)/ne_doip_event_loop.o

$(OBJDIR_RELEASE)/ne_doip_threadpool.o: ne_doip_threadpool.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c ne_doip_threadpool.c -o $(OBJDIR_RELEASE)/ne_doip_threadpool.o

clean_release:
	rm -f $(OBJ_RELEASE) $(OBJ_RELEASE_CLIENT) $(OBJ_RELEASE_SERVER)
	rm -f $(OUT_RELEASE) $(OUT_RELEASE_CLIENT) $(OUT_RELEASE_SERVER)

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release
