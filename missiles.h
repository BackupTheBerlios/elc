#ifdef MISSILES

#ifndef __MISSILES_H__
#define __MISSILES_H__

#include "actors.h"
#include "cal3d_wrapper.h"

typedef enum {MISSILE_ARROW} MissileType;

typedef struct
{
	MissileType type;
	float position[3];
	float direction[3];
	float speed;
	float covered_distance;
	float remaining_distance;
} Missile;

void clear_missiles();

unsigned int add_missile(MissileType type,
						 float origin[3],
						 float target[3],
						 float speed,
						 float delta);

void update_missiles();
void draw_missiles();

unsigned int fire_arrow(actor *a, float target[3]);

float compute_actor_rotation(struct CalQuaternion *q, actor *a, float target[3]);
void rotate_actor_bones(actor *a);


void actor_aim_at_b(int actor1_id, int actor2_id);
void actor_aim_at_xyz(int actor_id, float *target);
void missile_fire_a_to_b(int actor1_id, int actor2_id);
void missile_fire_a_to_xyz(int actor_id, float *target);
void missile_fire_xyz_to_b(float *origin, int actor_id);

#endif // __MISSILES_H__

#endif // MISSILES