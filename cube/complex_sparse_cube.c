#include <stdlib.h>
#include "complex_sparse_cube.h"

COMPLEX_SPARSE_PLANE *complex_sparse_plane_create(int x_dim,int y_dim) {
	COMPLEX_SPARSE_PLANE *plane = (COMPLEX_SPARSE_PLANE *)
		malloc(sizeof(COMPLEX_SPARSE_PLANE));
	plane->x_dim = x_dim;
	plane->y_dim = y_dim;
	plane->x_index = (COMPLEX_SPARSE_PLANE_ELEM **)
		calloc(x_dim, sizeof(COMPLEX_SPARSE_PLANE_ELEM*));
	plane->y_index = (COMPLEX_SPARSE_PLANE_ELEM **)
		calloc(y_dim, sizeof(COMPLEX_SPARSE_PLANE_ELEM*));
	return plane;
}

COMPLEX_SPARSE_CUBE *complex_sparse_cube_create(
		int d1_dim, int d2_dim, int d3_dim,
		double constant) {
	COMPLEX_SPARSE_CUBE *cube = (COMPLEX_SPARSE_CUBE *) 
		malloc(sizeof(COMPLEX_SPARSE_CUBE));
	cube->constant = constant;
	cube->d1_d2 = complex_sparse_plane_create(d1_dim, d2_dim);
	cube->d2_d3 = complex_sparse_plane_create(d2_dim, d3_dim);
	cube->d3_d1 = complex_sparse_plane_create(d3_dim, d1_dim);

	return cube;
}

COMPLEX_SPARSE_PLANE_ELEM *
	complex_sparse_plane_put(COMPLEX_SPARSE_PLANE *plane,
				int x,int y, int *error) {
	if (!plane) { *error = INVALID_PLANE; return NULL; }
	if (x < 0 || x >= plane->x_dim ||
		y < 0 || y >= plane->y_dim) {
		*error = INVALID_POS;
		return NULL;
	}
	
	COMPLEX_SPARSE_PLANE_ELEM **xp = &plane->x_index[x];
	COMPLEX_SPARSE_PLANE_ELEM **yp = &plane->y_index[y];

	while (*xp && (*xp)->y < y && xp = &(*xp)->y_next);
	while (*yp && (*yp)->x < x && yp = &(*yp)->x_next);

	if (*xp && *yp && (*xp)->y == y && (*yp)->x == x)
		return *xp;
	else {
		COMPLEX_SPARSE_PLANE_ELEM *new =
		   (COMPLEX_SPARSE_PLANE_ELEM *)
		      calloc(1, sizeof(COMPLEX_SPARSE_PLANE_ELEM));
		new->x = x;
		new->y = y;
		new->x_next = *yp;
		new->y_next = *xp;
		*xp = new;
		*yp = new;

		return new;
	}
}

int complex_sparse_cube_put(COMPLEX_SPARSE_CUBE *cube,
				int d1, int d2, int d3,
				double elem) {
	if (!cube) return INVALID_CUBE;
	if (d1 < 0 || d1 >= cube->d1_dim ||
		d2 < 0 || d2 >= cube->d2_dim ||
		d3 < 0 || d3 >= cube->d3_dim)
			return INVALID_POS;
	if (cube->constant == elem) {
		return complex_sparse_cube_remove(cube, d1, d2, d3);
	}

	// Creating the planes
	COMPLEX_SPARSE_PLANE_ELEM *elem_d1_d2 =
		complex_sparse_plane_put(cube->d1_d2, d1, d2);
	COMPLEX_SPARSE_PLANE_ELEM *elem_d2_d3 =
		complex_sparse_plane_put(cube->d2_d3, d2, d3);
	COMPLEX_SPARSE_PLANE_ELEM *elem_d3_d1 =
		complex_sparse_plane_put(cube->d3_d1, d3, d1);

	// Inserting element
	COMPLEX_SPARSE_CUBE_ELEM **p_d1_d2 = 
		&elem_d1_d2->three_d_element;
	COMPLEX_SPARSE_CUBE_ELEM **p_d2_d3 = 
		&elem_d2_d3->three_d_element;
	COMPLEX_SPARSE_CUBE_ELEM **p_d3_d1 = 
		&elem_d3_d1->three_d_element;

	while (*p_d1_d2 && (*p_d1_d2)->d3 < d3) 
		p_d1_d2 = &(*p_d1_d2)->d3_next;
	while (*p_d2_d3 && (*p_d2_d3)->d1 < d1)
		p_d2_d3 = &(*p_d2_d3)->d1_next;
	while (*p_d3_d1 && (*p_d3_d1)->d2 < d2)
		p_d3_d1 = &(*p_d3_d1)->d2_next;

	if (*p_d1_d2 && *p_d2_d3 && *p_d3_d1 &&
		*p_d1_d2 == *p_d2_d3 && *p_d2_d3 == *p_d3_d1) {
		(*p_d1_d2)->elem = elem;
	} else {
		COMPLEX_SPARSE_CUBE_ELEM *new =
		   (COMPLEX_SPARSE_CUBE_ELEM *)
			calloc(1, sizeof(COMPLEX_SPARSE_CUBE_ELEM));
		new->d1 = d1;
		new->d2 = d2;
		new->d3 = d3;
		new->elem = elem;
		new->d1_next = *p_d2_d3;
		new->d2_next = *p_d3_d1;
		new->d3_next = *p_d1_d2;
		*p_d2_d3 = *p_d3_d1 = *p_d1_d2 = new;
	}
		
}

void complex_sparse_cube_get_plane(COMPLEX_SPARSE_PLANE *plane,int x,int y ,int d3){
COMPLEX_SPARSE_PLANE_ELEM **xp=&plane->x_index;
COMPLEX_SPARSE_PLANE_ELEM **yp=&plane->y_index;

while((*xp)->y <= x)
	xp = (&(*xp)->x_next;
while((*yp)->x <= x)
	yp = (&(*yp)->y_next);
	if (*xp && *yp && (*xp)->y == y && (*yp)->x == x)
		return *xp;
}
// complex_sparse_cube_remove
// complex_sparse_cube_free

