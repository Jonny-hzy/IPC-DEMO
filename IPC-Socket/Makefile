LOCAL_PATH := $(shell pwd)
BIN_DIR := output

SRC += 	socket/socket.c

SRC_CLIENT +=	$(SRC) \
				client.c

SRC_SERVER +=	$(SRC) \
				server.c

CFLAGS += -I$(LOCAL_PATH)/
CFLAGS += -I$(LOCAL_PATH)/socket

OBJ_CLIENT := $(patsubst %.c,%.o, $(SRC_CLIENT))
OBJ_SERVER := $(patsubst %.c,%.o, $(SRC_SERVER))


cc = gcc

.PHONY : clean
all:client server

outpur_dir:
ifeq ($(wildcard $(BIN_DIR)),)
	mkdir ./$(BIN_DIR)
endif

client:$(OBJ_CLIENT) outpur_dir
	$(cc)  $(OBJ_CLIENT) $(CFLAGS) $(LIBS) -lm -o $(LOCAL_PATH)/$(BIN_DIR)/$@

server:$(OBJ_SERVER) outpur_dir
	$(cc)  $(OBJ_SERVER) $(CFLAGS) $(LIBS) -lm -o $(LOCAL_PATH)/$(BIN_DIR)/$@

%.o:%.c %.h
	#$(warning $(LOCAL_PATH)/$@)
	$(cc) -c $< $(CFLAGS) $(LIBS) -lm -o $@

.PHONY : clean
clean:
	@find . -name "*.o" | xargs rm -f
	@rm -rf ./$(BIN_DIR)
