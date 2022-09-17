#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/fb.h>
#include <string.h>
#include <sys/mman.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <signal.h>
#include <ncurses.h>
#include <pthread.h>

int work_flag = 1;
int upFlag = 0, rightFlag = 0, downFlag = 0, leftFlag = 0, ch = 0;

void heandler(int none)
{
	work_flag = 0;
	endwin();
}

static void *keyboard(void *none)
{
	initscr();
	noecho();
	keypad(stdscr, TRUE);
	while(1)
	{
		signal(SIGINT, heandler);
		ch = getch();
		switch(ch)
		{
			case KEY_UP:
				upFlag = 1;
				rightFlag = 0;
				downFlag = 0;
				leftFlag = 0;
				break;
			case KEY_RIGHT:
				upFlag = 0;
				rightFlag = 1;
				downFlag = 0;
				leftFlag = 0;
				break;
			case KEY_DOWN:
				upFlag = 0;
				rightFlag = 0;
				downFlag = 1;
				leftFlag = 0;
				break;
			case KEY_LEFT:
				upFlag = 0;
				rightFlag = 0;
				downFlag = 0;
				leftFlag = 1;
				break;
		}
	}
	endwin();
}

int main(int argc, char *argv[])
{
	int fb, xstep, ystep;
	struct fb_var_screeninfo info;
	size_t fb_size, map_size, page_size;
	uint32_t *ptr, color;


	signal(SIGINT, heandler);

	color = 0xFFFFFFFF;
	unsigned int x = 150, y = 350;
	xstep = ystep = 1;
	page_size = sysconf(_SC_PAGESIZE);
	if (0 > (fb = open("/dev/fb0", O_RDWR)))
	{
		perror("open");
		return __LINE__;
	}

	if ((-1) == ioctl(fb, FBIOGET_VSCREENINFO, &info))
	{
		perror("ioctl");
		close(fb);
		return __LINE__;
	}

	fb_size = sizeof(uint32_t) * info.xres_virtual * info.yres_virtual;
	map_size = (fb_size + (page_size - 1)) & (~(page_size - 1));

	ptr = mmap(NULL, map_size, PROT_READ | PROT_WRITE, MAP_SHARED, fb, 0);
	if (MAP_FAILED == ptr)
	{
		perror("mmap");
		close(fb);
		return __LINE__;
	}
	
	pthread_t pid;
	int buffx = 0, buffy = 0;
	pthread_create(&pid, NULL, keyboard, NULL);
	pthread_detach(pid);
	while(work_flag)
	{
		ptr[y * info.xres_virtual + x] = color;
	
		buffx = x;
		buffy = y;	

		if (upFlag)
		{
			x = buffx;
			y -= ystep;
		}

		if (rightFlag)
		{
			x += xstep;
			y = buffy;
		}

		if (downFlag)
		{
			x = buffx;
			y += ystep;
		}

		if (leftFlag)
		{
			x -= xstep;
			y = buffy;
		}
		
		if (info.xres <= x)
		{
			x %= info.xres_virtual;
		}

		if (info.yres <= y)
		{
			y %= info.yres_virtual;
		}

		usleep(200);
	}

	munmap(ptr, map_size);
	close(fb);
	return 0;
}
