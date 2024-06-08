/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * (c) 2024 Ichiro Kawazome
 */
#ifndef  PROC_SAMPLE_H
#define  PROC_SAMPLE_H

#include "bmp.h"

#define  BMP_FILE_NAME "sample.bmp"
struct  proc_info {
	uint8_t* buffer;
	int      width;
	int      height;
};
static struct proc_info* proc_info_list = NULL;
static int               proc_info_size = 0;
static void proc_init(int num, int width, int height)
{
	size_t buffer_size = width*height*3;
	if ((buffer_size % sizeof(uint64_t)) != 0) {
		perror("Illegal buffer size for bmp writing");
		exit(EXIT_FAILURE);
	}
	proc_info_list = (struct proc_info*)malloc(num*sizeof(struct  proc_info));
	if (proc_info_list == NULL) {
		perror("Failed to malloc for bmp writing");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < num ; i++) {
		proc_info_list[i].width  = width;
		proc_info_list[i].height = height;
		if ((proc_info_list[i].buffer = malloc(buffer_size)) == NULL) {
			perror("Failed to malloc for bmp writing");
			exit(EXIT_FAILURE);
		}
	}
	proc_info_size = num;
}
static void proc_run(int proc_index, int buf_index, int plane, void* start, size_t size)
{
	uint64_t* src   = (uint64_t*)start;
	uint64_t* dst   = (uint64_t*)proc_info_list[proc_index].buffer;
        size_t    words = size/sizeof(uint64_t);
	for (int i = 0; i < words; i++)
		dst[i] = src[i];
}
static void proc_done()
{
	struct proc_info proc_info = proc_info_list[proc_info_size-1];
	BMP_WRITE(BMP_FILE_NAME, proc_info.width, proc_info.height, proc_info.buffer);
}
#endif
