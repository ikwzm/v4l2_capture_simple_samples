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
static struct proc_info proc_info;
static void proc_init(int width, int height)
{
	proc_info.width  = width;
	proc_info.height = height;
	size_t size = width*height*3;
	if ((size % sizeof(uint32_t)) != 0) {
		perror("Illegal size for bmp writing");
		exit(EXIT_FAILURE);
	}
	if ((proc_info.buffer = malloc(size)) == NULL) {
		perror("Failed to malloc for bmp writing");
		exit(EXIT_FAILURE);
	}
}
static void proc_run(int buf_index, int plane, void* start, size_t size)
{
	uint32_t* src   = (uint32_t*)start;
	uint32_t* dst   = (uint32_t*)proc_info.buffer;
        size_t    words = size/sizeof(uint32_t);
	for (int i = 0; i < words; i++)
		dst[i] = src[i];
}
static void proc_done()
{
	BMP_WRITE(BMP_FILE_NAME, proc_info.width, proc_info.height, proc_info.buffer);
}
#endif
