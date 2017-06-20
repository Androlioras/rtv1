# define CAMERA			1
# define LIGHT_SPOT		2
# define SPHERE			4
# define PLAN			8
# define CONE			16
# define CYLINDER		32

#define STRING_LEN		128
#define AMBIANT			0.21
#define SHADOW			0.06

#define PI				3.1415926535

typedef struct			s_vec
{
	float				x;
	float				y;
	float				z;
}						t_vec;

typedef struct			s_quat
{
	float				w;
	float				x;
	float				y;
	float				z;
}						t_quat;

typedef struct			s_collision
{
	t_vec				point;
	char				collision;
}						t_collision;

typedef struct			s_ray
{
	t_vec				pos;
	t_vec				dir;
}						t_ray;

typedef struct			s_color
{
	uchar				r;
	uchar				g;
	uchar				b;
	uchar				a;
}						t_color;

typedef struct			s_camera
{
	t_vec				pos;
	t_quat				q;
	float				w;
	float				h;
	float				d;
	float				fov_w;
	float				fov_h;
}						t_camera;

typedef struct			s_object
{
	char				name[STRING_LEN];
	uchar				type;
	t_color				color;
	uchar				ref;
	t_quat				angle;
	t_vec				norm;
	t_vec				pos;
	t_vec				i;
	float				r;
	float				d;
	float				fov_w;
	float				fov_h;
}						t_object;

float			scalar_vectors(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

float			get_vector_norm(t_vec a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

inline float	get_angle_from_vectors(t_vec a, t_vec b)
{
	return (scalar_vectors(a, b) / (get_vector_norm(a) *
	get_vector_norm(b)));
}

float 			get_distance(t_vec a, t_vec b)
{
	return (sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z)));
}

t_vec			create_vector(float x, float y, float z)
{
	return ((t_vec){x, y, z});
}

t_vec			substract_vectors(t_vec a, t_vec b)
{
	return ((t_vec){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vec		multiply_vectors(t_vec a, float b)
{
	return ((t_vec){a.x * b, a.y * b, a.z * b});
}

void		normalize_vector(t_vec *a)
{
	float	norm;

	norm = get_vector_norm(*a);
	a->x /= norm;
	a->y /= norm;
	a->z /= norm;
}

t_vec		rotate_vector(t_vec a, __global t_quat *q)
{
	return ((t_vec){
	a.x * (q->w * q->w + q->x * q->x - q->y * q->y - q->z * q->z) + a.y * 2 * (q->x * q->y - q->w * q->z) + a.z * 2 * (q->x * q->z + q->w * q->y),
	a.x * 2 * (q->x * q->y + q->w * q->z) + a.y * (q->w * q->w - q->x * q->x + q->y * q->y - q->z * q->z) + a.z * 2 * (q->y * q->z - q->w * q->x),
	a.x * 2 * (q->x * q->z - q->w * q->y) + a.y * 2 * (q->y * q->z + q->w * q->x) + a.z * (q->w * q->w - q->x * q->x - q->y * q->y + q->z * q->z)});
}

t_collision	find_sphere_collision(__global t_object *obj, t_ray *ray)
{
	t_collision	collision;
	t_vec		x = (t_vec){ray->pos.x - obj->pos.x, ray->pos.y - obj->pos.y, ray->pos.z - obj->pos.z};
	float		a = scalar_vectors(ray->dir, ray->dir);
	float		b = 2 * scalar_vectors(ray->dir, x);
	float		c = scalar_vectors(x, x) - obj->r * obj->r;
	float		delta = b * b - 4 * a * c;
	float		h1;
	float		h2;

	collision.collision = 0;
	if (delta < 0)
		return (collision);
	h1 = (-b - sqrt(delta)) / (2 * a);
	h2 = (-b + sqrt(delta)) / (2 * a);
	if (h1 < 0 && h2 < 0)
		return (collision);
	collision.collision = 1;
	if (h1 >= 0 && h2 >= 0)
		collision.point = (h1 < h2) ? (t_vec){ray->dir.x * h1 + ray->pos.x, ray->dir.y * h1 + ray->pos.y, ray->dir.z * h1 + ray->pos.z} :
		(t_vec){ray->dir.x * h2 + ray->pos.x, ray->dir.y * h2 + ray->pos.y, ray->dir.z * h2 + ray->pos.z};
	else if (h1 >= 0)
		collision.point = (t_vec){ray->dir.x * h1 + ray->pos.x, ray->dir.y * h1 + ray->pos.y, ray->dir.z * h1 + ray->pos.z};
	else if (h2 >= 0)
		collision.point = (t_vec){ray->dir.x * h2 + ray->pos.x, ray->dir.y * h2 + ray->pos.y, ray->dir.z * h2 + ray->pos.z};
	else
		collision.collision = 0;
	return (collision);
}

t_collision	find_plan_collision(__global t_object *obj, t_ray *ray)
{
	t_collision	collision;
	float		h;

	collision.collision = 0;
	h = scalar_vectors(obj->norm, ray->dir);
	if (h == 0)
		return (collision);
	h = -scalar_vectors(obj->norm, substract_vectors(ray->pos, obj->pos)) / h;
	if (h < 0)
		return (collision);
	collision.collision = 1;
	collision.point = (t_vec){ray->dir.x * h + ray->pos.x, ray->dir.y * h + ray->pos.y, ray->dir.z * h + ray->pos.z};
	return (collision);
}

t_collision	find_cone_collision(__global t_object *obj, t_ray *ray)
{
	t_collision	collision;
	t_vec		x = (t_vec){ray->pos.x - obj->pos.x, ray->pos.y - obj->pos.y, ray->pos.z - obj->pos.z};
	float		k = 1 + pow(tan((float)obj->color.a * PI / 360), 2);
	float		a = scalar_vectors(ray->dir, ray->dir) - k * pow(scalar_vectors(ray->dir, obj->norm), 2);
	float		b = 2 * (scalar_vectors(ray->dir, x) - k * scalar_vectors(ray->dir, obj->norm) * scalar_vectors(x, obj->norm));
	float		c = scalar_vectors(x, x) - k * pow(scalar_vectors(x, obj->norm), 2);
	float		delta = b * b - 4 * a * c;
	float		h1;
	float		h2;

	collision.collision = 0;
	if (delta < 0)
		return (collision);
	h1 = (-b - sqrt(delta)) / (2 * a);
	h2 = (-b + sqrt(delta)) / (2 * a);
	if (h1 < 0 && h2 < 0)
		return (collision);
	collision.collision = 1;
	if (h1 >= 0 && h2 >= 0)
		collision.point = (h1 < h2) ? (t_vec){ray->dir.x * h1 + ray->pos.x, ray->dir.y * h1 + ray->pos.y, ray->dir.z * h1 + ray->pos.z} :
		(t_vec){ray->dir.x * h2 + ray->pos.x, ray->dir.y * h2 + ray->pos.y, ray->dir.z * h2 + ray->pos.z};
	else if (h1 >= 0)
		collision.point = (t_vec){ray->dir.x * h1 + ray->pos.x, ray->dir.y * h1 + ray->pos.y, ray->dir.z * h1 + ray->pos.z};
	else if (h2 >= 0)
		collision.point = (t_vec){ray->dir.x * h2 + ray->pos.x, ray->dir.y * h2 + ray->pos.y, ray->dir.z * h2 + ray->pos.z};
	else
		collision.collision = 0;
	return (collision);
}

t_collision	find_cylinder_collision(__global t_object *obj, t_ray *ray)
{
	t_collision	collision;
	t_vec		x = (t_vec){ray->pos.x - obj->pos.x, ray->pos.y - obj->pos.y, ray->pos.z - obj->pos.z};
	float		a = scalar_vectors(ray->dir, ray->dir) - pow(scalar_vectors(ray->dir, obj->norm), 2);
	float		b = 2 * (scalar_vectors(ray->dir, x) - scalar_vectors(ray->dir, obj->norm) * scalar_vectors(x, obj->norm));
	float		c = scalar_vectors(x, x) - pow(scalar_vectors(x, obj->norm), 2) - obj->r * obj->r;
	float		delta = b * b - 4 * a * c;
	float		h1;
	float		h2;

	collision.collision = 0;
	if (delta < 0)
		return (collision);
	h1 = (-b - sqrt(delta)) / (2 * a);
	h2 = (-b + sqrt(delta)) / (2 * a);
	if (h1 < 0 && h2 < 0)
		return (collision);
	collision.collision = 1;
	if (h1 >= 0 && h2 >= 0)
		collision.point = (h1 < h2) ? (t_vec){ray->dir.x * h1 + ray->pos.x, ray->dir.y * h1 + ray->pos.y, ray->dir.z * h1 + ray->pos.z} :
		(t_vec){ray->dir.x * h2 + ray->pos.x, ray->dir.y * h2 + ray->pos.y, ray->dir.z * h2 + ray->pos.z};
	else if (h1 >= 0)
		collision.point = (t_vec){ray->dir.x * h1 + ray->pos.x, ray->dir.y * h1 + ray->pos.y, ray->dir.z * h1 + ray->pos.z};
	else if (h2 >= 0)
		collision.point = (t_vec){ray->dir.x * h2 + ray->pos.x, ray->dir.y * h2 + ray->pos.y, ray->dir.z * h2 + ray->pos.z};
	else
		collision.collision = 0;
	return (collision);
}

char		light_is_visible(t_vec point, __global t_object *objects, __global t_object *light, __global t_object *obj)
{
	t_collision	collision;
	t_ray		ray;
	float		d;

	ray.pos = point;
	ray.dir = (t_vec){light->pos.x - point.x, light->pos.y - point.y, light->pos.z - point.z};
	d = get_distance(light->pos, point);
	normalize_vector(&ray.dir);
	while (objects->type)
	{
		collision.collision = 0;
		if (objects != obj)
		{
			if (objects->type == SPHERE)
				collision = find_sphere_collision(objects, &ray);
			else if (objects->type == PLAN)
				collision = find_plan_collision(objects, &ray);
			else if (objects->type == CONE)
				collision = find_cone_collision(objects, &ray);
			else if (objects->type == CYLINDER)
				collision = find_cylinder_collision(objects, &ray);
			if (collision.collision && collision.point.x != point.x && collision.point.y != point.y && collision.point.z != point.z)
				if (get_distance(point, collision.point) < d)
					return (0);
		}
		objects++;
	}
	return (1);
}

void		shadow(__global t_color *c, t_vec point, __global t_object *objects, __global t_object *obj, t_vec dir)
{
	__global t_object	*light;
	t_vec				r;
	t_vec				n;
	t_vec				l;
	float				f;
	float				k;

	light = objects;
	while (light->type)
	{
		if (light->type == LIGHT_SPOT)
		{
			if (obj->type == SPHERE)
				n = (t_vec){point.x - obj->pos.x, point.y - obj->pos.y, point.z - obj->pos.z};
			else if (obj->type == PLAN)
				n = obj->norm;
			else if (obj->type == CONE)
			{
				k = 1 + pow(tan((float)obj->color.a * PI / 360), 2);
				n = substract_vectors(substract_vectors(point, obj->pos), multiply_vectors(obj->norm, k));
			}
			else if (obj->type == CYLINDER)
				n = substract_vectors(substract_vectors(point, obj->pos), obj->norm);
			l = (t_vec){point.x - light->pos.x, point.y - light->pos.y, point.z - light->pos.z};
			r = substract_vectors(multiply_vectors(n, 2 * get_angle_from_vectors(n , l)), l);
			if (light_is_visible(point, objects, light, obj))
			{
				f = -light->i.y * obj->ref * get_angle_from_vectors(n, l);
				if (f > 0)
				{
					c->r = (c->r + obj->color.r * f < 255) ? c->r + obj->color.r * f : 255;
					c->g = (c->g + obj->color.g * f < 255) ? c->g + obj->color.g * f : 255;
					c->b = (c->b + obj->color.b * f < 255) ? c->b + obj->color.b * f : 255;
				}
				if (obj->type != LIGHT_SPOT && obj->type != PLAN)
				{
					f = light->i.z * obj->ref * pow(-get_angle_from_vectors(r, dir), light->color.a);
					c->r = (c->r + f < 255) ? c->r + f : 255;
					c->g = (c->g + f < 255) ? c->g + f : 255;
					c->b = (c->b + f < 255) ? c->b + f : 255;
				}
			}
			else
			{
				c->r = (c->r - obj->color.r * SHADOW >= 0) ? c->r - obj->color.r * SHADOW : 0;
				c->g = (c->g - obj->color.g * SHADOW >= 0) ? c->g - obj->color.g * SHADOW : 0;
				c->b = (c->b - obj->color.b * SHADOW >= 0) ? c->b - obj->color.b * SHADOW : 0;
			}
		}
		light++;
	}
}

__kernel void	render_pixel(__global t_color *map, __global t_camera *cam, __global int *w, __global int *h, __global t_object *objects, __global float *a, __global float *b)
{
	__global t_object	*obj = objects;
	__global t_object	*mem = 0;
	t_collision			collision;
	t_collision			memc;
	t_ray				ray;
	int					id = get_global_id(0);
	int					x = id % *w;
	int					y = id / *w;
	float				z = 1000;

	ray.dir = rotate_vector((t_vec){cam->d, x * a[0] + b[0], y * a[1] + b[1]}, &cam->q);
	ray.pos = cam->pos;
	map[id] = (t_color){0, 0, 0, 0};
	while (obj->type)
	{
		collision.collision = 0;	
		if (obj->type == SPHERE)
			collision = find_sphere_collision(obj, &ray);
		else if (obj->type == PLAN)
			collision = find_plan_collision(obj, &ray);
		else if (obj->type == CONE)
			collision = find_cone_collision(obj, &ray);
		else if (obj->type == CYLINDER)
			collision = find_cylinder_collision(obj, &ray);
		if (collision.collision == 1 && get_distance(collision.point, cam->pos) < z)
		{
			mem = obj;
			memc = collision;
			z = get_distance(collision.point, cam->pos);
		}
		obj++;
	}
	if (mem)
	{
		map[id].r = mem->color.r * AMBIANT;
		map[id].g = mem->color.g * AMBIANT;
		map[id].b = mem->color.b * AMBIANT;
		map[id].a = 0;
		shadow(map + id, memc.point, objects, mem, ray.dir);
	}
}
