#include "header.h"

#if defined(__PLAYER_DEBUG__)
static char main_debug_level = DEBUG_TRACE_E;
#else
static char main_debug_level = DEBUG_KEY_E;
#endif
#define MAIN_LOG(level, fmt, arg...){  \
                                         if(level >=main_debug_level)  \
                                         {   \
                                             printf(fmt, ##arg);  \
                                         }\
                                     }

uint32_t my_tick(void)
{
    static uint64_t start_ms = 0;
    if(start_ms == 0) {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);
        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
    }
    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t now_ms;
    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;
    uint32_t time_ms = now_ms - start_ms;
    return time_ms;
}

int main(int argc, char *argv[])
{
    lv_init();

    fbdev_init();

    static lv_color_t buf[DISP_BUF_SIZE];
    static lv_disp_buf_t disp_buf;

	/* fb init */
    lv_disp_buf_init(&disp_buf, buf, NULL, DISP_BUF_SIZE);
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.buffer = &disp_buf;
    disp_drv.flush_cb = fbdev_flush;
    lv_disp_drv_register(&disp_drv);

#if 1
	/* tp init */
	evdev_init();
	static lv_indev_drv_t indev_drv;
	lv_indev_drv_init(&indev_drv);	   
	indev_drv.type = LV_INDEV_TYPE_POINTER;				 
	indev_drv.read_cb = evdev_read;			   
	lv_indev_drv_register(&indev_drv);
#endif
    lv_demo_music();
    while (1)
	{
		lv_tick_inc(5);
        lv_task_handler();
        usleep(5000);
	}
}
