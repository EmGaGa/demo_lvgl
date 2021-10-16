CC := arm-none-linux-gnueabi-gcc
RM := rm
MV := mv
MKDIR := mkdir

CUR_PATH=$(shell pwd)
LVGL_DIR = $(CUR_PATH)
LVGL_DIR_NAME ?= lvgl

include $(LVGL_DIR)/lvgl/lvgl.mk
include $(LVGL_DIR)/lv_drivers/lv_drivers.mk
include $(LVGL_DIR)/lv_examples/lv_examples.mk

OBJDIR:=./__tmp__
OBJEXT ?= .o
AOBJS = $(ASRCS:.S=$(OBJEXT))
COBJS = $(CSRCS:.c=$(OBJEXT))

SRC = $(ASRCS) $(CSRCS)
OBJ = $(AOBJS) $(COBJS)

CFLAGS:=-g -Wall -std=c99 -I$(LVGL_DIR)/lvgl -I$(LVGL_DIR)/lv_drivers -I$(LVGL_DIR)/lv_examples \
	-DLV_CONF_INCLUDE_SIMPLE -DLV_LVGL_H_INCLUDE_SIMPLE -DLV_EX_CONF_INCLUDE_SIMPLE

.PHONY: all
.DEFAULT: all

all: $(OBJ)
	$(MKDIR) $(OBJDIR) -p
	$(MV) $(OBJ) $(OBJDIR)

clean:
	$(RM) $(OBJDIR) -rf
