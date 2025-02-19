LOCAL_PATH := $(shell pwd)
BIN_DIR := output

SRC_SENDER += main.c

CFLAGS += -I$(LOCAL_PATH)/

OBJ_SENDER := $(patsubst %.c,%.o, $(SRC_SENDER))

cc = gcc

.PHONY : clean
all:test

output_dir:
ifeq ($(wildcard $(BIN_DIR)),)
	mkdir ./$(BIN_DIR)
endif

test:$(OBJ_SENDER) output_dir
	$(cc)  $(OBJ_SENDER) $(CFLAGS) $(LIBS) -lm -o $(LOCAL_PATH)/$(BIN_DIR)/$@

%.o:%.c %.h
	#$(warning $(LOCAL_PATH)/$@)
	$(cc) -c $< $(CFLAGS) $(LIBS) -lm -o $@

.PHONY : clean
clean:
	@find . -name "*.o" | xargs rm -f
	@rm -rf ./$(BIN_DIR)
