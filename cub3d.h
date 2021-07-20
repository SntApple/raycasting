/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flurk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 14:53:00 by flurk             #+#    #+#             */
/*   Updated: 2021/03/11 14:53:02 by flurk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include "mlx/mlx.h"

typedef struct	s_draw
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		texx;
	double	step;
	double	tex_pos;
}				t_draw;

typedef struct	s_set
{
	int		screen_width;
	int		screen_height;
	int		tex_width;
	int		tex_height;
	int		sp_height;
	int		sp_width;
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	double	*z;
}				t_set;

typedef struct	s_frame
{
	double	camerax;
	double	ray_dirx;
	double	ray_diry;
	int		mapx;
	int		mapy;
	double	side_distx;
	double	side_disty;
	double	perp_wall_dist;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	double	delta_distx;
	double	delta_disty;
}				t_frame;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_tex
{
	unsigned int	ceiling;
	unsigned int	floor;
	t_data			no;
	t_data			so;
	t_data			ea;
	t_data			we;
	t_data			sp;
	char			*path_no;
	char			*path_so;
	char			*path_ea;
	char			*path_we;
	char			*path_sp;
	char			p;
}				t_tex;

typedef struct	s_spr
{
	double	spritex;
	double	spritey;
	double	inv_det;
	double	transformx;
	double	transformy;
	int		sprite_screenx;
	double	vmove;
	int		vmove_screen;
	int		sprite_height;
	int		draw_starty;
	int		draw_endy;
	int		sprite_width;
	int		draw_startx;
	int		draw_endx;
}				t_spr;

typedef struct	s_key
{
	int	fw_w;
	int	fw;
	int	bc;
	int	bc_w;
	int	sl;
	int	sr;
	int	l;
	int	r;
}				t_key;

typedef struct	s_vars
{
	int			count_spr;
	int			count_map;
	short		save;
	short		pos;
	t_set		set;
	t_data		data;
	t_tex		tex;
	t_spr		spr;
	t_key		key;
	double		square_cf;
	void		*mlx;
	void		*win;
	char		**map;
	double		**sprites;
}				t_vars;

void			step(t_vars *vars, t_frame *frame);
void			dda(t_vars *vars, t_frame *frame);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			pre_color(t_vars *vars, t_frame *frame, int x);
int				key_press(int keycode, t_vars *vars);
int				key_release(int keycode, t_vars *vars);
int				key_hook(t_vars *vars);
void			set_param(t_vars *vars);
void			init_frame(t_vars *vars, t_frame *frame, int x);
void			init_key(t_vars *vars);
double			ft_abs(double num);
void			parse_name(char *argv);
int				parse_file(char *argv, t_vars *vars);
unsigned int	get_color(t_data *data, int x, int y);
void			get_error(char *str);
void			floor_and_ceiling(t_vars *vars, int x);
void			update_sprite(t_vars *vars);
void			draw_sprite(t_vars *vars);
void			init_sprites(t_vars *vars);
int				get_resol(char **ar, t_vars *vars, int *ans);
int				get_tex(char **ar, t_vars *vars, int *ans);
int				get_spr(char **ar, t_vars *vars, int *ans);
int				get_col(char **ar, t_vars *vars, int *ans);
int				parse_map(int fd, t_vars *vars);
int				is_num(char *s);
int				is_valid(t_vars *vars, char **map);
void			get_pos(t_vars *vars);
int				has_char(char c, char *str);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			spr_distance(t_vars *vars);
void			sort_spr(double **sprites, int count);
void			free_ar(char **ar);
void			move(t_vars *vars, double move_speed);
void			rot(t_vars *vars, double r);
void			strafe(t_vars *vars, double move_speed);
void			save(t_vars *vars);
int				ft_close(void);
void			get_screen_size(t_set *set);
void			free_spr(int k, double **sprites);
int				create_trgb(int t, int r, int h, int b);
void			get_addr(t_vars *vars);

#endif
