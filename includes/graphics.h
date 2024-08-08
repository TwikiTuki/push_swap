#ifndef PSW_GRAPHICS_H
# define PSW_GRAPHICS_H

# define G_WINDOW_WIDTH ((coord_val) 800)
# define G_WINDOW_HEIGHT ((coord_val) 800)
# define G_MARGIN ((coord_val) 10)
# define G_AREAS_WIDTH ((coord_val) (G_WINDOW_WIDTH - G_MARGIN * 3) / 2) 
# define G_AREAS_HEIGHT ((coord_val) (G_WINDOW_HEIGHT - G_MARGIN * 2))

# define G_X_BEGIN_A ((coord_val) G_AREAS_WIDTH + G_MARGIN)
# define G_Y_BEGIN_A ((coord_val) G_WINDOW_HEIGHT - G_MARGIN)
# define G_X_BEGIN_B ((coord_val) G_WINDOW_WIDTH - G_MARGIN - G_AREAS_WIDTH)
# define G_Y_BEGIN_B ((coord_val) G_WINDOW_HEIGHT - G_MARGIN)

//# define G_SLEEP 1000000
# define G_SLEEP			1000000
# define G_SLEEP			1000000

# define G_SPACE			32
# define G_RIGHT			65363
# define G_LEFT				65361
# define G_UP				65362
# define G_DOWN 			65364
# define G_PLUS				65451
# define G_MINUS			65453
# define G_INTRO			65421
# define G_CARRIAGE_RET		62593
# define G_ESC				65307


# include <mlx.h>

typedef int coord_val;

typedef enum
{
	STACK_A = 0, 
	STACK_B = 1
} t_stack_id;

typedef struct s_mlx_img
{
	void*			img;
	char*			data;
	coord_val		bitsxpxl;
	coord_val		bytesxpxl;
	coord_val		bytesxline;
	int				endian;
} t_mlx_img;


typedef	struct	s_point 
{
	coord_val x;
	coord_val y;
}t_point;

t_point Point(coord_val x, coord_val y);
void g_draw_square(t_mlx_img img, t_point begin, t_point size, t_point direction, int colorBegin, int colorEnd, coord_val max_width_color_scaling);
void g_draw_area_B(t_mlx_img img);
void g_draw_area_A(t_mlx_img img);
void g_draw_pixel(t_mlx_img img, coord_val x, coord_val y, int color);
int grp_average_color(unsigned int color0, unsigned int color1, t_point division);
t_point g_pixel_coords(t_mlx_img img, char *pixel);
#endif
