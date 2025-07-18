/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:43:06 by cayamash          #+#    #+#             */
/*   Updated: 2025/07/07 18:35:00 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <unistd.h>
# include "libft.h"

/* ********************************* MACROS ********************************* */

# define EMPTY_FILE "Error: Empty file\n"
# define INVALID_FORMAT "Error: Invalid file format\n"
# define INVALID_FILE "Error: Invalid file\n"
# define INVALID_LINE "Error: Invalid line\n"
# define INVALID_MAP "Error: Invalid map\n"
# define INVALID_PLAYER "Error: Invalid player position\n"
# define INVALID_TEXTURE "Error: Invalid texture\n"
# define INVALID_COLOR "Error: Invalid background color\n"
# define MEMORY_ERROR "Error: When using malloc"
# define DUPLICATE_TEXTURE "Error: Duplicate texture\n"
# define DUPLICATE_PLAYER "Error: Duplicate player on the map\n"
# define MISSING_TEXTURE "Error: Missing one or more textures\n"
# define MISSING_COLOR "Error: Missing one or more colors\n"
# define MISSING_MAP "Error: Missing map in file\n"
# define MISSING_PLAYER "Error: Missing player in map\n"
# define MLX_INIT "Error: Failed to initialize MLX.\n"
# define MLX_WIN "Error: Failed to create MLX window.\n"
# define MLX_IMG "Error: Failed to create MLX image.\n"
# define MLX_ADDR "Error: Failed to get MLX image address.\n"
# define MLX_TEX_INIT "Error: Failed to load texture file.\n"
# define MLX_TEX_ADDR "Error: Failed to get texture data.\n"

# define WIN_WIDTH 1200
# define WIN_HEIGHT 800
# define TILE_SIZE 64
# define MINIMAP_MARGIN 10
# define MINIMAP_WIDTH 150
# define MINIMAP_HEIGHT 80
# define MINIMAP_TILE 8	
# define PLAYER_DOT_SIZE 2

# define FOV 70.0
# define M_PI 3.14159265358979323846
# define MOVE_SPEED 0.05
# define ROT_SPEED  0.01
# define COLLISION_OFFSET 0.3
# define MOUSE_SENSITIVITY 0.002

# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define ESC_KEY 65307
# define SPACE_KEY 32

# define TEX_DOOR "assets/textures/door.xpm"
# define TEX_ENEMY0 "assets/sprites/flaviano_0.xpm"
# define TEX_ENEMY1 "assets/sprites/flaviano_1.xpm"
# define TEX_ENEMY2 "assets/sprites/flaviano_2.xpm"
# define TEX_ENEMY3 "assets/sprites/flaviano_3.xpm"
# define TEX_GOAL0 "assets/sprites/cordao_0.xpm"
# define TEX_GOAL1 "assets/sprites/cordao_1.xpm"
# define TEX_GOAL2 "assets/sprites/cordao_2.xpm"
# define TEX_GOAL3 "assets/sprites/cordao_3.xpm"

/* ******************************* STRUCTS ******************************* */

enum	e_axis
{
	X,
	Y
};

enum	e_direction
{
	RIGHT = 1,
	LEFT = -1
};

enum	e_texture
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	DOOR
};

enum	e_map_elements
{
	DOOR_OPEN = -1,
	EMPTY = 0,
	WALL = 1,
	DOOR_CLOSE = 2,
	VOID = 4
};

typedef struct s_keyboard
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	left;
	bool	right;
}	t_keyboard;

typedef struct s_ray
{
	double	camera_x;
	double	wall_dist;
	double	ray_dir[2];
	double	delta_dist[2];
	double	side_dist[2];
	int		map_pos[2];
	int		step[2];
	int		hit;
	int		side;
	int		line_height;
	int		line_start;
	int		line_end;
}	t_ray;

typedef struct s_map
{
	char		*tex_path[4];
	char		*door_tex_path;
	int			sprite_n;
	int			**grid;
	int			width;
	int			height;
	uint32_t	ceiling;
	uint32_t	floor;
}	t_map;

typedef struct s_player
{
	double	pos[2];
	double	dir[2];
	double	plane[2];
	int		player_num;
	char	start_dir;
}	t_player;

//sprite - BONUS
typedef struct s_sprite
{
	double		pos[2];
	double		transform[2];
	double		draw_start[2];
	double		draw_end[2];
	double		radius;
	int			screen_x;
	int			width;
	int			height;
	int			dir[2];
	bool		enemy;
}	t_sprite;

typedef struct s_sprite_order
{
	int		index;
	double	distance;
}	t_sprite_order;

typedef struct s_texture
{
	void	*tex_ptr;
	char	*tex_addr;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_texture;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_mlx;

typedef struct s_game
{
	t_mlx		*mlx;
	t_map		*map;
	t_player	*player;
	t_sprite	*sprites;
	int			num_sprites;
	t_texture	*texture[5];
	t_texture	*enemy_texture[4];
	t_texture	*goal_texture[4];
	char		*enemy_tex_path[4];
	char		*goal_tex_path[4];
	int			frame_count;
	int			current_frame;
	t_keyboard	keys;
	int			mouse_x;
	int			mouse_pressed;
	int			z_buffer[WIN_WIDTH];
}	t_game;

/* ******************************* FUNCTIONS ******************************** */

/* ********************************** Init ********************************** */
t_game		*init(const char *map_file);
void		get_map_dimensions(t_game *game, const char *map_file);
void		init_grid(t_map *map);
void		init_mlx(t_game *game);
void		init_textures(t_game *game);
void		init_sprite_textures(t_game *game);
int			close_window(t_game *game);

/* ******************************** Parsing ********************************* */
bool		is_valid_line(char *line);
bool		is_texture_line(char *line);
bool		is_color_line(char *line);
bool		is_map_line(char *line);
bool		is_empty_line(char *line);
void		parse_textures(t_map *map, char *line);
void		parse_color(t_map *map, char *line);
void		parse_map(t_game *game, int fd, char *line);
void		parse_file(t_game *game, const char *map_file);

/* ******************************* Validation ******************************* */
void		validate(t_game *game);
void		validate_map(t_game *game);
void		validate_player(t_game *game);
void		validate_colors(t_map *map);
void		validate_textures(char *texture[4]);
bool		is_void_or_wall(int curr);
bool		is_empty_or_wall(int curr);
bool		check_around_space(t_map *map, int y, int x);

/* ********************************** Draw ********************************** */
int			render_img(t_game *game);
void		put_pixel(t_game *game, int x, int y, int color);
void		init_ray(t_player *player, t_ray *ray, int x);
void		dda(t_game *game, t_ray *ray);
void		compute_line(t_ray *ray);
void		draw_texture(t_game *game, t_ray *ray, int x);
void		draw_ceiling_and_floor(t_game *game, t_ray *ray, int x);
void		draw_sprites(t_game *game);
void		order_sprites(t_game *game, t_sprite_order *order);	
void		draw_minimap_bg(t_game *g);
void		draw_minimap_tiles(t_game *g, int start_pos[2]);
void		draw_player_dot(t_game *g, int dot_pos[2], int radius, int color);
void		draw_player_line(t_game *g, int start[2], int end[2], int color);
void		draw_mini_sprites(t_game *g, int start_pos[2]);		
uint32_t	interpolate_color(uint32_t color1, uint32_t color2, double factor);

/* ******************************** Actions ********************************* */
void		set_hooks(t_game *game);
void		move_forward(t_player *p, t_map *map);
void		move_backward(t_player *p, t_map *map);
void		strafe_left(t_player *p, t_map *map);
void		strafe_right(t_player *p, t_map *map);
void		rotate_direction(t_player *p, double rot_speed);
void		try_toggle_door(t_game *game);
void		update_sprites(t_game *game);
int			key_press(int key, t_game *game);
int			key_release(int key, t_game *game);
int			handle_keys(t_game *game);
int			mouse_press(int button, int x, int y, t_game *game);
int			mouse_release(int button, int x, int y, t_game *game);
int			mouse_move(int x, int y, t_game *game);		
int			player_touch_sprite(t_game *game);			

/* ********************************* Utils ********************************** */
void		handle_error(char *error, char *str);

#endif