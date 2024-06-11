LOCAL_PATH := $(shell pwd)
BIN_DIR := output

SRC += 	shared_memory/shm.c

SRC_SENDER +=	$(SRC) \
				sender.c

SRC_RECVER +=	$(SRC) \
				receiver.c

CFLAGS += -I$(LOCAL_PATH)/
CFLAGS += -I$(LOCAL_PATH)/shared_memory

OBJ_SENDER := $(patsubst %.c,%.o, $(SRC_SENDER))
OBJ_RECVER := $(patsubst %.c,%.o, $(SRC_RECVER))


cc = gcc

.PHONY : clean
all:sender receiver

outpur_dir:
ifeq ($(wildcard $(BIN_DIR)),)
	mkdir ./$(BIN_DIR)
endif

sender:$(OBJ_SENDER) outpur_dir
	$(cc)  $(OBJ_SENDER) $(CFLAGS) $(LIBS) -lm -o $(LOCAL_PATH)/$(BIN_DIR)/$@

receiver:$(OBJ_RECVER) outpur_dir
	$(cc)  $(OBJ_RECVER) $(CFLAGS) $(LIBS) -lm -o $(LOCAL_PATH)/$(BIN_DIR)/$@

%.o:%.c %.h
	#$(warning $(LOCAL_PATH)/$@)
	$(cc) -c $< $(CFLAGS) $(LIBS) -lm -o $@

.PHONY : clean
clean:
	@find . -name "*.o" | xargs rm -f
	@rm -rf ./$(BIN_DIR)
