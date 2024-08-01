#ifndef PSW_GRAPHICS_H
# define PSW_GRAPHICS_H

# define G_WINDOW_WIDTH ((int) 1500)
# define G_WINDOW_HEIGHT ((int) 1500)
# define G_MARGIN ((int) 10)
# define G_AREAS_WIDTH ((int) (G_WINDOW_WIDTH - G_MARGIN * 3) / 2) 
# define G_AREAS_HEIGHT ((int) (G_WINDOW_HEIGHT - G_MARGIN * 2))

# define G_X_BEGIN_A ((int) G_AREAS_WIDTH + G_MARGIN)
# define G_Y_BEGIN_A ((int) G_WINDOW_HEIGHT - G_MARGIN)
# define G_X_BEGIN_B ((int) G_WINDOW_WIDTH - G_MARGIN - G_AREAS_WIDTH)
# define G_Y_BEGIN_B ((int) G_WINDOW_HEIGHT - G_MARGIN)

# include <mlx.h>

typedef struct s_mlx_img
{
	void*	img;
	char*	data;
	int		bitsxpxl;
	int		bytesxpxl;
	int		bytesxline;
	int		endian;
} t_mlx_img;


typedef	struct	s_point 
{
	int x;
	int y;
}t_point;

void g_draw_area_A(t_mlx_img img);
void g_draw_pixel(t_mlx_img img, int x, int y, int color);
t_point g_pixel_coords(t_mlx_img, char *pixel);
void mlx_main(int argc, char **argv);
#endif
