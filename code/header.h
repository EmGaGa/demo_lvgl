#ifndef __HEADER_H_
#define __HEADER_H_

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <linux/fb.h>
#include "lvgl.h"
#include "lv_examples.h"
#include "display/fbdev.h"
#include "indev/evdev.h"

#define	DISP_BUF_SIZE	(100 * LV_HOR_RES_MAX)

/* debug */
#if defined(PLAYER_DEBUG_VER)          /* DEBUG_VER */
#define __PLAYER_DEBUG__                          1
#endif

/* log define */
typedef enum
{
    DEBUG_TRACE_E = 0,
    DEBUG_WARING_E, 
    DEBUG_KEY_E,
    DEBUG_ERROR_E,
    /* MAX */
    DEBUG_MAX_E = DEBUG_ERROR_E
} debug_level_enum;



#endif