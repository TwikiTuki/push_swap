#ifndef PSW_GRAPHICS_H
# define PSW_GRAPHICS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <mlx.h>
# include <checker.h>
# include <push_swap.h>

# define G_WINDOW_WIDTH ((coord_val) 800)
# define G_WINDOW_HEIGHT ((coord_val) 800)
# define G_MARGIN ((coord_val) 10)
# define G_AREAS_WIDTH ((coord_val) (G_WINDOW_WIDTH - G_MARGIN * 3) / 2) 
# define G_AREAS_HEIGHT ((coord_val) (G_WINDOW_HEIGHT - G_MARGIN * 2))

# define G_X_BEGIN_A ((coord_val) G_AREAS_WIDTH + G_MARGIN)
# define G_Y_BEGIN_A ((coord_val) G_WINDOW_HEIGHT - G_MARGIN)
# define G_X_BEGIN_B ((coord_val) G_WINDOW_WIDTH - G_MARGIN - G_AREAS_WIDTH)
# define G_Y_BEGIN_B ((coord_val) G_WINDOW_HEIGHT - G_MARGIN)

# define G_SLEEP			((useconds_t) 20)
# define _G_SLEEP			((useconds_t) 1 << G_SLEEP)
//# define G_MAX_SLEEP		((useconds_t) 1 << (sizeof(useconds_t) * 8 - 1))
# define G_MAX_SLEEP		((useconds_t) 2000000) 

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

typedef int coord_val;

typedef struct s_color_scaling
{
	int			color0;
	int			color1;
	coord_val	max_pxl;
} t_color_scaling;

typedef struct s_mlx_img
{
	void*			img;
	char*			data;
	coord_val		bitsxpxl;
	coord_val		bytesxpxl;
	coord_val		bytesxline;
	int				endian;
} t_mlx_img;

typedef struct s_grp_loop_data {
	t_stk_node*		stacks[2];
	void*			mlx;
	void*			mlx_window;
	t_mlx_img		img;
	int 			len;
	useconds_t		sleep;
	int				paused;
	int				next_action;
} t_grp_loop_data;

typedef enum
{
	STACK_A = 0, 
	STACK_B = 1
} t_stack_id;

typedef	struct	s_point 
{
	coord_val x;
	coord_val y;
}t_point;

/* grp_utils.c */
t_point Point(coord_val x, coord_val y);
t_color_scaling ColorScaling(int color0, int color1, coord_val max_pxl);
int min(int val0, int val1);
char grp_average_char(unsigned char color0, unsigned char color1, t_point division);
int grp_average_color(unsigned int color0, unsigned int color1, t_point division);

/* grp_draw.c */
void grp_draw_square(t_mlx_img img, t_point begin, t_point size, t_point direction, t_color_scaling scaling);
void grp_draw_background(t_mlx_img *img);
void grp_draw_area_B(t_mlx_img img);
void grp_draw_area_A(t_mlx_img img);

/* grp_print_stacks.c */
t_color_scaling ColorScaling(int color0, int color1, coord_val max_index);
void grp_print_index_to_A(int y_pos, int order_index, t_mlx_img img, coord_val height, int len, int extra_y, int extra_height);
void grp_print_index_to_B(int y_pos, int order_index, t_mlx_img img, coord_val height, int len, int extra_y, int extra_height);
int grp_print_stack(t_stk_node* stacks[2], t_stack_id stackid, t_mlx_img img, size_t _len);

/* grp_hooks.c */
int grp_key_press(int key, t_grp_loop_data *data);
int grp_key_relese(int key, t_grp_loop_data *data);
int grp_mlx_loop(void *_data);
int grp_init_graphics(t_grp_loop_data *loop_data);

/* unused */
//t_point grp_pixel_coords(t_mlx_img img, char *pixel);
//void grp_draw_pixel(t_mlx_img img, coord_val x, coord_val y, int color);

#endif
