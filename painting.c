#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "allheaders.h"

void painting_curve(SDL_Renderer* renderer, int current_segments_to_draw, double start_length, point start_point, int angles_list[], int iteration){
    double length = start_length/pow(4, iteration);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    point last_point = start_point;
    point new_point;
    for(int i = 0; i < current_segments_to_draw; i++){
        double current_angle = angles_list[i]*0.0174533;
        new_point.coordinates_x = last_point.coordinates_x + cos(current_angle) * length;
        new_point.coordinates_y = last_point.coordinates_y + sin(current_angle) * length;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer, (int)last_point.coordinates_x, (int)last_point.coordinates_y, (int)new_point.coordinates_x, (int)new_point.coordinates_y);
        SDL_RenderPresent(renderer);
        last_point= new_point;
    }

}