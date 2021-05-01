SRCDIR:=.
OBJDIR:=.

TOP_PATH=$(shell pwd)

CC:=arm-none-linux-gnueabi-gcc
#STRIP:=strip
RM := rm
MV := mv
CD := cd

LVGL_DIR = $(TOP_PATH)/external/lvgl
LVGL_DIR_NAME ?= lvgl

include $(LVGL_DIR)/lvgl/lvgl.mk
include $(LVGL_DIR)/lv_drivers/lv_drivers.mk

CFLAGS:=-w -O2 -O3 -g0 -std=c99 -I$(LVGL_DIR)/lvgl -I$(LVGL_DIR)/lv_drivers \
        -DPLAYER_DEBUG_VER -DLV_CONF_INCLUDE_SIMPLE -DLV_LVGL_H_INCLUDE_SIMPLE

.PHONY: all
.DEFAULT: all

LVGL_OBJDIR:=./external/lvgl/__tmp__
#LVGL_OBJS:=$(wildcard $(LVGL_OBJDIR)/*.o)

OBJDIR:=./__tmp__
SRCS:=$(wildcard $(SRCDIR)/*.c)
OBJS:=$(addprefix $(OBJDIR)/,$(patsubst %.c,%.o,$(SRCS)))

PROGRAM:=player

all: $(LVGL_OBJDIR) $(PROGRAM)

$(LVGL_OBJDIR) : 
	$(CD) $(LVGL_DIR) && make

$(OBJS) : $(OBJDIR)/%.o : %.c
	@if [ ! -d $(dir $@) ] ; then mkdir -v -p $(dir $@) ; fi
	@echo compile: $<
	$(CC) $(CFLAGS) -c $< -o $@

$(PROGRAM): $(OBJS) $(LVGL_OBJDIR)
	$(CC) $(OBJS) $(wildcard $(LVGL_OBJDIR)/*.o) -o $(PROGRAM) -lpthread -static -lm
	$(MV) $(PROGRAM) $(OBJDIR)
	
clean:
	$(RM) -rf $(LVGL_OBJDIR)
	$(RM) -rf $(OBJDIR)
