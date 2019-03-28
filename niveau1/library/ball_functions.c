void set_x(double x,int ball_number,world_t* world){
  world->balls[ball_number]->x = x;
}
void set_y(double y,int ball_number,world_t* world){
  world->balls[ball_number]->y = y;
}
double get_x(int ball_number,world_t* world){
  return world->balls[ball_number]->x;
}
double get_y(int ball_number,world_t* world){
  return world->balls[ball_number]->y;
}