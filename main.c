#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>

#include "allheaders.h"

const int WIDTH = 1920, HEIGHT = 1080;

struct point start_point, end_point;
bool first_point_got = false;
struct segment segment_list[64];

double start_length;
int angles_list[99999999];
int iteration = 0;
int max_iteration = -100;
int current_segments_count = 1;

int main(int argc, char *argv[]){
    SDL_Init( SDL_INIT_EVERYTHING );
    SDL_Window *window = SDL_CreateWindow("Koch's) triangle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    if (NULL == window){
        printf("Couldn't create window!");
        return 1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL){
        printf("Couldn't create renderer!");
        return 1;
    }
   
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_Event windowEvent;
    while( 1 ){
        if ( SDL_PollEvent ( &windowEvent ) ){
            if ( SDL_QUIT == windowEvent.type ){
                break;
            }
            
            if (SDL_MOUSEBUTTONDOWN == windowEvent.type){
                if(SDL_BUTTON_LEFT == windowEvent.button.button){
                    SDL_GetMouseState(&start_point.coordinates_x, &start_point.coordinates_y);
                    first_point_got = true;
                }
                if(SDL_BUTTON_RIGHT == windowEvent.button.button){
                    SDL_GetMouseState(&end_point.coordinates_x, &end_point.coordinates_y);
                    first_point_got = false;
                    segment_list[0].seg_start = start_point;
                    segment_list[0].seg_end = end_point;
                    start_length = find_start_length(segment_list);
                    angles_list[0] = find_start_angle(segment_list);
                }   
            }
            if (SDL_MOUSEMOTION == windowEvent.type && first_point_got == true){
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(renderer);
                SDL_RenderPresent(renderer);
                point current_draw_point;
                SDL_GetMouseState(&current_draw_point.coordinates_x, &current_draw_point.coordinates_y);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderDrawLine(renderer, start_point.coordinates_x, start_point.coordinates_y, current_draw_point.coordinates_x, current_draw_point.coordinates_y);
                SDL_RenderPresent(renderer);
            }
            if (SDL_KEYDOWN == windowEvent.type){
                if(SDLK_LEFT == windowEvent.key.keysym.sym){
                    iteration--;
                    current_segments_count = current_segments_count / 4;
                    painting_curve(renderer, current_segments_count, start_length, start_point, angles_list, iteration);
                }
                
                if(SDLK_RIGHT == windowEvent.key.keysym.sym){
                    iteration++;
                    if(iteration > max_iteration){
                        current_segments_count = building_curve(segment_list, angles_list);
                        max_iteration = iteration;
                    }
                    else{current_segments_count = current_segments_count * 4;}
                    painting_curve(renderer, current_segments_count, start_length, start_point, angles_list, iteration);
                }
            }
        }
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}