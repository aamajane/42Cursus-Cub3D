/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:08:13 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/16 21:17:48 by aamajane         ###   ########.fr       */
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
# include <signal.h>
# include <stdbool.h>

# define WIN_WIDTH		1280
# define WIN_HEIGHT 	720
# define MINIMAP_WIDTH	320
# define MINIMAP_HEIGHT	180

# define TILE_SIZE		64
# define MINI_SIZE		32
# define RECT_SIZE		5

# define NUM_WALLS		32
# define NUM_LIGHTS		4
# define NUM_LIGHTNING	2
# define NUM_LETTERS	4
# define NUM_OP_DOORS	7
# define NUM_SHOOTING	9
# define NUM_RELOADING	16
# define NUM_BULLETS	10
# define NUM_ENMY_DYING	9
# define NUM_TARGETS	2
# define NUM_RAYS		WIN_WIDTH

# define MIN_WALL_NUM	1
# define MAX_WALL_NUM	36

# define W_KEY			13
# define S_KEY			1
# define D_KEY			2
# define A_KEY			0
# define X_KEY			7
# define UP_KEY			126
# define DOWN_KEY		125
# define RIGHI_KEY		124
# define LEFT_KEY		123
# define ESC_KEY		53
# define KEY_SHIFT		257

# define SHIFT_MODE		8
# define NORMAL_MODE 	4

# define EPSILON		0.3

# define MUSIC			"./bonus/assets/sound/doom.mp3"
# define GUNSHOT		"./bonus/assets/sound/gun.mp3"

typedef enum e_name
{
	letter_n = 0,
	letter_s = 1,
	letter_e = 2,
	letter_w = 3,
	light_1 = 100,
	light_2 = 101,
	light_3 = 102,
	light_4 = 103,
	door = 200,
}			t_name;

typedef struct s_r
{
	int	txt_index;
	int	txt_x;
	int	txt_y;
	int	win_index;
	int	win_x;
	int	win_y;
}				t_r;

typedef struct s_mini
{
	int		map_x;
	int		map_y;
	int		img_x;
	int		img_y;
	int		index;
	int		player_x;
	int		player_y;
	char	c;
}				t_mini;

typedef struct s_column
{
	int	height;
	int	top_y;
	int	bottom_y;
	int	dist_from_top;
}				t_column;

typedef struct s_intercept
{
	double	xintercept;
	double	yintercept;
	double	xstep;
	double	ystep;
	char	c;
}				t_intercept;

typedef struct s_hit
{
	double	hit_distance;
	double	wall_hit_x;
	double	wall_hit_y;
	int		hit_content;
	int		wall_hit;
}				t_hit;

typedef struct s_ray
{
	double	angle;
	double	distance;
	double	wall_hit_x;
	double	wall_hit_y;
	int		hit_content;
	int		vertical_hit;
}				t_ray;

typedef struct s_img
{
	char	*path;
	void	*addr;
	int		*buffer;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_sprite
{
	double	x;
	double	y;
	double	angle;
	double	distance;
	int		size;
	int		top_y;
	int		bottom_y;
	int		dist_from_top;
	int		screen_x;
	int		left_x;
	int		right_x;
	int		health;
	int		on_target;
	int		is_dying;
	int		is_dead;
}				t_sprite;

typedef struct s_gsprite
{
	t_sprite	*all;
	t_sprite	**visible;
	int			all_num;
	int			visible_num;
}				t_gsprite;

typedef struct s_enemy
{
	t_gsprite	gsprite;
	t_img		standing;
	t_img		dying[NUM_ENMY_DYING];
	int			dying_index;
	int			dying_timer;
	int			dead_num;
}				t_enemy;

typedef struct s_light
{
	t_img	imgs[NUM_LIGHTNING];
	int		index;
	int		timer;
}				t_light;

typedef struct s_door
{
	t_img		img;
	t_img		op_imgs[NUM_OP_DOORS];
	t_sprite	sprite;
	int			xintercept;
	int			yintercept;
	int			vertical_hit;
	int			is_open;
	int			render;
	int			index;
	int			timer;
}				t_door;

typedef struct s_weapon
{
	t_img	holding;
	t_img	shooting[NUM_SHOOTING];
	t_img	reloading[NUM_RELOADING];
	int		x;
	int		y;
	int		width;
	int		height;
	int		bullets;
	int		render_shooting;
	int		render_reloading;
	int		shooting_index;
	int		reloading_index;
	int		shooting_timer;
	int		reloading_timer;
	int		target;
}				t_weapon;

typedef struct player
{
	double	x;
	double	y;
	double	rot_angle;
	double	fov_angle;
	double	side_angle;
	double	rot_speed;
	double	mov_speed;
	double	rot_direction;
	int		mov_direction;
}				t_player;

typedef struct s_elm
{
	char	**map;
	int		map_width;
	int		map_height;
}				t_elm;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_name		name;
	t_elm		elm;
	t_img		main_img;
	t_img		minimap;
	t_player	player;
	t_door		door;
	t_enemy		enemy;
	t_weapon	weapon;
	t_img		target[NUM_TARGETS];
	t_img		walls[NUM_WALLS];
	t_light		lights[NUM_LIGHTS];
	t_img		letters[NUM_LETTERS];
	t_ray		rays[NUM_RAYS];
	t_column	column[NUM_RAYS];
	double		dist_proj_plane;
	int			pid_music;
	int			pid_gunshot;
}				t_data;

// checker.c
void	checker(t_elm *elm, char *arg);
char	**read_file(char *arg);
void	check_map(char **map);
int		map_is_valid(char **map, int i, int j);

// create_game.c
void	create_game(t_data *data);
void	create_images(t_data *data);
void	init_variables(t_data *data);
void	random_wall(char ***map);

// images_path.c
void	images_path(t_data *data);
void	images_path_extra_1(t_data *data);
void	images_path_extra_2(t_data *data);
void	images_path_extra_3(t_data *data);

// init_images.c
void	init_all_images(t_data *data, int size);
void	init_all_images_extra(t_data *data, int size);
void	init_image(t_data *data, t_img *img, int size);

// player_data.c
void	player_data(t_player *player, char **map);
double	player_position(t_player *player, char **map);
double	player_starting_angle(char c);
int		is_player(char c);

// mlx_hook.c
int		key_press(int keycode, t_data *data);
void	key_press_2(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);
int		mouse_move(int x, int y, t_data *data);
int		close_win(t_data *data);

// render_frame.c 
int		render_frame(t_data *data);
void	render_3d_projection(t_data *data);
void	render_projected_column(t_data *data, int x, t_img img);
void	render_celing(t_data *data, int x);
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
void	projection_content(t_data *data, int i);
void	light_timer(t_data *data);

// door_checker.c
void	check_door_near_player(t_data *data);
void	door_horz_intercept(t_hit *horizontal, t_data *data, double ray_angle);
void	door_vert_intercept(t_hit *vertical, t_data *data, double ray_angle);
int		door_facing_player(t_data *data, double ray_angle);

// door_rendering.c
void	render_door(t_data *data);
void	door_opening_timer(t_data *data);
void	door_closing_timer(t_data *data);

// enemy_rendering.c
void	enemy_data(t_gsprite *gsprite, char **map);
void	render_enemy_projection(t_data *data);
void	render_enemy(t_data *data, int i);
void	enemy_dying_timer(t_data *data);

// sprite.c
void	find_visible_sprites(t_data *data, t_gsprite *gsprite);
void	sort_visible_sprites(t_gsprite *gsprite);
void	sprite_projection(t_data *data, t_sprite *sprite);
void	sprite_rendering(t_data *data, t_sprite *sprite, t_img sprite_img);
void	sprite_drawing(t_data *data, t_sprite *sprite, t_img sprite_img, int x);

// weapon_rendering.c
void	render_weapon(t_data *data);
void	render_weapon_frames(t_data *data, t_img img);
void	weapon_shooting_timer(t_data *data);
void	weapon_reloading_timer(t_data *data);
void	render_target(t_data *data);

// minimap.c
void	render_minimap(t_data *data);
void	draw_minimap(t_data *data, t_mini *mini);
void	get_minimap_y(t_data *data, t_mini *mini);
void	get_minimap_x(t_data *data, t_mini *mini);
void	draw_minimap_border(t_data *data);

// utils_main.c
int		puterror(char *str);
void	free_double_pointer(char **str);

// utils_map.c
int		map_width(char **map);
int		map_height(char **map);
char	map_content(t_data *data, double x, double y, int size);
int		is_inside_map(t_data *data, double x, double y);
int		is_wall(char c);

// utils_math.c
double	distance_between_points(double x1, double y1, double x2, double y2);
double	degree_to_radian(double angle);
void	normalize_angle(double *angle);
int		create_trgb(int transparency, int red, int green, int blue);
int		increase_color_intensity(double distance, int color);

// utils_sprites.c
int		sprites_number(char **map, char c);
void	sprites_coordinates(t_sprite *sprites, char **map, char c);
void	init_sprites_data(t_sprite *sprites, int sprites_num);
void	draw_rect(t_data *data, int x, int y, int color);

// get_next_line.c
char	*get_next_line(int fd);
void	get_file(int fd, char **stock, char **line, char **buf);
char	*get_line(char **stock, char **line);
void	get_free(char **str);

// music.c
void	ft_afplay(char *sound, int *pid);
void	render_menu(t_data *data);

#endif
