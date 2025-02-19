LOCAL_PATH := $(shell pwd)
BIN_DIR := output

SRC += 	fifo/fifo.c

SRC_SENDER +=	$(SRC) \
				sender.c

SRC_RECVER +=	$(SRC) \
				receiver.c

CFLAGS += -I$(LOCAL_PATH)/
CFLAGS += -I$(LOCAL_PATH)/fifo

OBJ_SENDER := $(patsubst %.c,%.o, $(SRC_SENDER))
OBJ_RECVER := $(patsubst %.c,%.o, $(SRC_RECVER))


cc = gcc

.PHONY : clean
all:sender receiver

output_dir:
ifeq ($(wildcard $(BIN_DIR)),)
	mkdir ./$(BIN_DIR)
endif

sender:$(OBJ_SENDER) output_dir
	$(cc)  $(OBJ_SENDER) $(CFLAGS) $(LIBS) -lm -o $(LOCAL_PATH)/$(BIN_DIR)/$@
	
receiver:$(OBJ_RECVER) output_dir
	$(cc)  $(OBJ_RECVER) $(CFLAGS) $(LIBS) -lm -o $(LOCAL_PATH)/$(BIN_DIR)/$@

%.o:%.c %.h
	#$(warning $(LOCAL_PATH)/$@)
	$(cc) -c $< $(CFLAGS) $(LIBS) -lm -o $@

.PHONY : clean
clean:
	@find . -name "*.o" | xargs rm -f
	@rm -rf ./$(BIN_DIR)
