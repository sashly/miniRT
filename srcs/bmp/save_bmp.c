/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <sashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:23:57 by sashly            #+#    #+#             */
/*   Updated: 2021/03/01 11:34:29 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

unsigned char g_bmpfileheader[14] = {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0,
	0, 0};
unsigned char g_bmpinfoheader[40] = {40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
	24, 0};
unsigned char g_bmppad[3] = {0, 0, 0};

void	fill_bmp_header(int height, int width)
{
	int filesize;

	filesize = 54 + 3 * height * width;
	g_bmpfileheader[2] = (filesize);
	g_bmpfileheader[3] = (filesize >> 8);
	g_bmpfileheader[4] = (filesize >> 16);
	g_bmpfileheader[5] = (filesize >> 24);
	g_bmpinfoheader[4] = (width);
	g_bmpinfoheader[5] = (width >> 8);
	g_bmpinfoheader[6] = (width >> 16);
	g_bmpinfoheader[7] = (width >> 24);
	g_bmpinfoheader[8] = (height);
	g_bmpinfoheader[9] = (height >> 8);
	g_bmpinfoheader[10] = (height >> 16);
	g_bmpinfoheader[11] = (height >> 24);
}

int		save_bmp_close(int fd, unsigned char *bgr_p)
{
	free(bgr_p);
	bgr_p = NULL;
	return (!close(fd));
}

int		save_bmp(const char *filename, const unsigned char *pixels,
	int h, int w)
{
	int				fd;
	unsigned char	*bgr_p;
	int				index;

	index = 0;
	if (!(bgr_p = (unsigned char *)malloc(sizeof(unsigned char) * (3 * w * h))))
		return (0);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	fill_bmp_header(h, w);
	write(fd, g_bmpfileheader, 14);
	write(fd, g_bmpinfoheader, 40);
	while (index < w * h)
	{
		bgr_p[3 * index] = pixels[3 * index + 2];
		bgr_p[3 * index + 1] = pixels[3 * index + 1];
		bgr_p[3 * index + 2] = pixels[3 * index];
		index++;
	}
	index = 0;
	while (index < h)
	{
		write(fd, bgr_p + (w * (index++) * 3), 3 * w);
		write(fd, g_bmppad, (4 - (w * 3) % 4) % 4);
	}
	return (save_bmp_close(fd, bgr_p));
}
