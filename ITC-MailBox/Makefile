#AllDirs := $(shell ls -R | grep '^\./.*:$$' | awk '{gsub(":","");print}') .
#Sources := $(foreach n,$(AllDirs) , $(wildcard $(n)/*.c))
LOCAL_PATH := $(shell pwd)
BIN_DIR := output/

Sources += 	mailbox/mailbox_user.c \
			mailbox/mailbox.c \
			main.c

CFLAGS += -I$(LOCAL_PATH)/
CFLAGS += -I$(LOCAL_PATH)/mailbox
CFLAGS += -D__UBUNTU__

LIBS += -lpthread \
		-lrt


Objs := $(patsubst %.c,%.o, $(Sources))

target = test_mailbox
cc = gcc
$(target):$(Objs) output_dir
	#$(warning $(Objs))
	$(cc)  $(Objs) $(CFLAGS) $(LIBS) -lm -o $(LOCAL_PATH)/$(BIN_DIR)/$@
%.o:%.c
	#$(warning $(LOCAL_PATH)/$@)
	$(cc) -c $< $(CFLAGS) $(LIBS) -lm -o $@

output_dir:
ifeq ($(wildcard $(BIN_DIR)),)
	mkdir $(BIN_DIR)
endif

.PHONY : clean
clean:
	@find . -name "*.o" | xargs rm -f
	@rm -rf ./$(BIN_DIR)
