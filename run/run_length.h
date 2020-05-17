/*Lucas Henrique Braga Martins
11275126*/
#ifndef run_length
#define run_length



void decompress(int height, int width);
void read_image(int ***matrix, int height, int width);
void compress(int ***matrix, int height, int width);
void free_matrix(int ***matrix, int height, int width);
#endif
