#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "allheaders.h"

int changings_list[] = {-60, 60, 0};

double find_start_length(segment segment_list[]){
    int x1 = segment_list[0].seg_end.coordinates_x - segment_list[0].seg_start.coordinates_x;
    int y1 = segment_list[0].seg_end.coordinates_y - segment_list[0].seg_start.coordinates_y;
    return sqrt(x1*x1 + y1*y1);
}


int find_start_angle(segment segment_list[]){
    int x1 = segment_list[0].seg_end.coordinates_x - segment_list[0].seg_start.coordinates_x;
    int y1 = segment_list[0].seg_end.coordinates_y - segment_list[0].seg_start.coordinates_y;
    return (int)( 60 * (acos( ( x1 * ( x1 + 1 ) ) / ( sqrt( x1 * x1 + y1 * y1) * sqrt( (x1+1) * (x1+1) ) ) ) ) );
}


int building_curve(segment segment_list[], int angles_list[]) {
    static int n = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n; j++) {
            angles_list[j + n * (i+1)] = (angles_list[j] + changings_list[i])%360;
        }
    }
    n = n * 4;
    return n;
}

