enum bool {true, false};
typedef enum bool bool;

typedef struct point {
    int coordinates_x;
    int coordinates_y;
} point;

typedef struct segment {
    point seg_start;
    point seg_end;
} segment;

void painting_curve(SDL_Renderer*, int, double, struct point, int[], int);
double find_start_length(struct segment*);
int find_start_angle(struct segment*);
int building_curve(struct segment*, int*);