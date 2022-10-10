/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:08:13 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/08 17:29:02 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../../libft/libft.h"
# include <float.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>

# define TILE_SIZE	64
# define WIN_WIDTH	1280
# define WIN_HEIGHT 720
# define NUM_RAYS	WIN_WIDTH
# define NUM_IMG	4
# define FACTOR		0.1

# define W_KEY		13
# define S_KEY		1
# define D_KEY		2
# define A_KEY		0
# define UP_KEY		126
# define DOWN_KEY	125
# define RIGHI_KEY	124
# define LEFT_KEY	123
# define ESC_KEY	53
# define ENTRE_KEY	36
# define SPACE_KEY	49

# define NORTH		0
# define SOUTH		1
# define EAST		2
# define WEST		3

typedef struct s_var
{
	char	**tab;
	int		*rgb;
	int		i;
	int		j;
}				t_var;

typedef struct s_column
{
	int	height;
	int	top_y;
	int	bottom_y;
	int	dist_from_top;
	int	facing_side;
}				t_column;

typedef struct s_intercept
{
	double	xintercept;
	double	yintercept;
	double	xstep;
	double	ystep;
}				t_intercept;

typedef struct s_hit
{
	double	hit_distance;
	double	wall_hit_x;
	double	wall_hit_y;
	int		wall_hit;
}				t_hit;

typedef struct s_ray
{
	double	angle;
	double	distance;
	double	wall_hit_x;
	double	wall_hit_y;
	int		vertical_hit;
}				t_ray;

typedef struct s_img
{
	void	*addr;
	int		*buffer;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct player
{
	double	x;
	double	y;
	double	rot_angle;
	double	fov_angle;
	double	side_angle;
	double	rot_speed;
	double	mov_speed;
	int		rot_direction;
	int		mov_direction;
}				t_player;

typedef struct s_elm
{
	char	**path;
	char	**map;
	int		**rgb;
	int		floor_color;
	int		ceiling_color;
	int		map_width;
	int		map_height;
}				t_elm;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_elm		elm;
	t_player	player;
	t_img		main_img;
	t_img		imgs[NUM_IMG];
	t_ray		rays[NUM_RAYS];
	t_column	column[NUM_RAYS];
	double		dist_proj_plane;
}				t_data;

// checker.c
void	checker(t_elm *elm, char *arg);
void	check_elements(t_elm *elm, t_var *var, char **tmp_elm);
int		*check_color(t_var *var, char *str);
char	*check_path(char *str);
void	check_map(char **map);

// create_game.c
void	create_game(t_data *data);
void	create_images(t_data *data);
void	init_images(t_data *data);

// player_data.c
void	player_data(t_player *player, char **map);
double	player_position(t_player *player, char **map);
double	player_starting_angle(char c);
int		is_player(char c);

// mlx_hook.c
int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);
int		close_win(t_data *data);

// render_frame.c 
int		render_frame(t_data *data);
void	render_3d_projection(t_data *data);
void	render_ceiling(t_data *data, int x);
void	render_wall(t_data *data, int x);
void	render_floor(t_data *data, int x);

// player_update.c
void	player_update(t_data *data);
void	move_player(t_data *data);
void	rotate_player(t_data *data);

// raycasting.c
void	raycasting(t_data *data);
void	calculate_distances(t_hit *horizontal, t_hit *vertical, int px, int py);
void	get_shortest_distance(t_ray *ray, t_hit *horizontal, t_hit *vertical);

// ray_horizontal_intercept.c
void	horizontal_intercept(t_hit *horizontal, t_data *data, double ray_angle);
void	first_horz_intercept(t_intercept *horz, t_data *data, double ray_angle);
void	xy_horizontal_steps(t_intercept *horz, double ray_angle);

// ray_vertical_intercept.c
void	vertical_intercept(t_hit *vertical, t_data *data, double ray_angle);
void	first_vert_intercept(t_intercept *vert, t_data *data, double ray_angle);
void	xy_vertical_steps(t_intercept *vert, double ray_angle);

// ray_direction.c
int		ray_facing_down(double angle);
int		ray_facing_up(double angle);
int		ray_facing_right(double angle);
int		ray_facing_left(double angle);

// projection.c
void	projection(t_data *data);
void	projection_facing_side(t_data *data, int i);

// utils_main.c
int		puterror(char *str);
void	free_double_pointer(char **str);

// utils_checker.c
char	**read_file(char *arg);
void	separate_file_elements(t_elm *elm, char ***tmp_elm, char **file);
void	skip_spaces(char *str, int *i);
int		is_color(char *str, int **count);
int		is_direction(char *str, int **count);

// utils_map.c
int		map_width(char **map);
int		map_height(char **map);
int		map_has_wall_at(t_data *data, double x, double y);
int		is_inside_map(t_data *data, double x, double y);

// utils_math.c
double	distance_between_points(double x1, double y1, double x2, double y2);
double	degree_to_radian(double angle);
void	normalize_angle(double *angle);
int		create_trgb(int transparency, int red, int green, int blue);

// get_next_line.c
char	*get_next_line(int fd);
void	get_file(int fd, char **stock, char **line, char **buf);
char	*get_line(char **stock, char **line);
void	get_free(char **str);

#endif
