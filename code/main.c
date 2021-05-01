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


/* =========================demo========================== */
static lv_obj_t *label;
static void refresh_ui_task(lv_task_t * task)
{
    char temp[50];
    static int count = 0;
    sprintf(temp, "hello why can %d", count++);
    lv_label_set_text(label, temp);
}
static void button_event(lv_obj_t * obj, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED) 
	{
		MAIN_LOG(DEBUG_KEY_E, "button event\n");
    }
}
static void video_disp_window()
{
    lv_obj_t *  this_win = lv_cont_create(lv_scr_act(), NULL);
    lv_obj_set_size(this_win, LV_HOR_RES, LV_VER_RES);
    lv_obj_t *btn = lv_btn_create(this_win, NULL);
    label = lv_label_create(btn, NULL);
    lv_label_set_text(label, "hello why can");
    lv_obj_set_event_cb(btn, button_event);
    lv_task_create(refresh_ui_task, 1000, LV_TASK_PRIO_MID, NULL);
}
/* =========================demo========================== */

uint32_t my_tick(void)
{
    static uint64_t start_ms = 0;
    struct timeval tv_time;
	struct timeval tv_now;

    if(start_ms == 0) 
	{
        gettimeofday(&tv_time, NULL);
        start_ms = (tv_time.tv_sec * 1000000 + tv_time.tv_usec) / 1000;
    }

    gettimeofday(&tv_time, NULL);
    uint64_t now_ms;
    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

    uint32_t time_ms = now_ms - start_ms;
    return time_ms;
}

int main(int argc, char *argv[])
{
#if 0
	int fb = 0;
	struct fb_var_screeninfo vinfo;
	struct fb_fix_screeninfo finfo;
	
	printf("\n\n\n====%s: date:%s. time:%s. =====\n\n", __FILE__, __DATE__,__TIME__);
	fb = open("/dev/fb0", O_RDWR);
	if(fb < 0)
	{
		MAIN_LOG(DEBUG_KEY_E, "[Error]: Cannot open framebuff device !!!\r\n");
		exit(1);
	}
	if (ioctl(fb,FBIOGET_FSCREENINFO,&finfo))
	{
		MAIN_LOG(DEBUG_KEY_E, "Error reading fixed information/n");
		exit(2);
	}

	if (ioctl(fb,FBIOGET_VSCREENINFO,&vinfo))
	{
		MAIN_LOG(DEBUG_KEY_E, "Error reading variable information/n");
		exit(3);
	}
	MAIN_LOG(DEBUG_TRACE_E, "The mem is :%d\r\n",finfo.smem_len);
	MAIN_LOG(DEBUG_TRACE_E, "The line_length is :%d\r\n",finfo.line_length);
	MAIN_LOG(DEBUG_TRACE_E, "The xres is :%d\r\n",vinfo.xres);
	MAIN_LOG(DEBUG_TRACE_E, "The yres is :%d\r\n",vinfo.yres);
	MAIN_LOG(DEBUG_TRACE_E, "bits_per_pixel is :%d\r\n",vinfo.bits_per_pixel);
	close (fb);
	return 0;
#else
    lv_init();  //lvgl gui初始化

    fbdev_init(); //fb初始化 此函数在 lv_drivers/display/fbdev.c 中,就是打开fb设备映射显存出来使用

    static lv_color_t buf[DISP_BUF_SIZE];
    static lv_disp_buf_t disp_buf;

	/* fb init */
    lv_disp_buf_init(&disp_buf, buf, NULL, DISP_BUF_SIZE);
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.buffer = &disp_buf;
    disp_drv.flush_cb = fbdev_flush; //fbdev_flush这就是输入显示驱动提供的操作函数 刷新数据到显存的函数。其他非Linux fb移植照葫芦即可。
    lv_disp_drv_register(&disp_drv);

#if 0
	/* tp init */
	evdev_init();
	lv_indev_drv_t indev_drv;
	lv_indev_drv_init(&indev_drv);	   
	indev_drv.type =LV_INDEV_TYPE_POINTER;				 
	indev_drv.read_cb =evdev_read;			   
	lv_indev_drv_register(&indev_drv);
#endif
    video_disp_window();
    while (1)
	{
        lv_task_handler();
        usleep(5000);
	}
#endif
}
