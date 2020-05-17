#ifndef _COMPLEX_SPARSE_CUBE_H_
#define _COMPLEX_SPARSE_CUBE_H_

struct complex_sparse_cube_elem {
	int d1, d2, d3;
	double elem;
	struct complex_sparse_cube_elem *d1_next, *d2_next, *d3_next;
};

struct complex_sparse_plane_elem {
	int x, y;
	struct complex_sparse_plane_elem *x_next, *y_next;
	struct complex_sparse_cube_elem *three_d_element;
};

struct complex_sparse_plane {
	int x_dim, y_dim;
	struct complex_sparse_plane_elem **x_index, **y_index;
};

struct complex_sparse_cube {
	double constant;
	struct complex_sparse_plane *d1_d2, *d2_d3, *d3_d1;
};

typedef struct complex_sparse_cube COMPLEX_SPARSE_CUBE;
typedef struct complex_sparse_plane COMPLEX_SPARSE_PLANE;
typedef struct complex_sparse_plane_elem COMPLEX_SPARSE_PLANE_ELEM;
typedef struct complex_sparse_cube_elem COMPLEX_SPARSE_CUBE_ELEM;

#endif
