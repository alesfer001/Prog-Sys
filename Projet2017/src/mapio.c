#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"
#include "error.h"

#ifdef PADAWAN

void map_new (unsigned width, unsigned height)
{
  map_allocate (width, height);

  for (int x = 0; x < width; x++)
    map_set (x, height - 1, 0); // Ground

  for (int y = 0; y < height - 1; y++) {
    map_set (0, y, 1); // Wall
    map_set (width - 1, y, 1); // Wall
  }

  map_object_begin (8);

  // Texture pour le sol
  map_object_add ("images/ground.png", 1, MAP_OBJECT_SOLID);

  // Mur
  map_object_add ("images/wall.png", 1, MAP_OBJECT_SOLID);
  // Gazon
  map_object_add ("images/grass.png", 1, MAP_OBJECT_SEMI_SOLID);
  // Marbre
  map_object_add ("images/marble.png", 1, MAP_OBJECT_SOLID | MAP_OBJECT_DESTRUCTIBLE);
  // Herbe
  map_object_add ("images/herb.png", 1, MAP_OBJECT_AIR);
  // Petit plancher flottant
  map_object_add ("images/floor.png", 1, MAP_OBJECT_SEMI_SOLID);
  // Fleur
  map_object_add ("images/flower.png", 1, MAP_OBJECT_AIR);
  // Coin
  map_object_add ("images/coin.png", 20, MAP_OBJECT_AIR | MAP_OBJECT_COLLECTIBLE);



  map_object_end ();
}

void map_save (char *filename)
{
  int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
  if(fd == -1){
    fprintf (stderr, "Error 001: Save Failed\n");
  }

  int width = map_width();
  write(fd, &width, sizeof(int));
  int height = map_height();
  write(fd, &height, sizeof(int));
  int nb_objects = map_objects();
  write(fd, &nb_objects, sizeof(int));

  int map[width][height];
  for(int x=0; x<width; x++){
    for(int y=0; y<height; y++){
      map[x][y] = map_get(x,y);
      write(fd, &map[x][y], sizeof(int));
    }
  }

  for(int i=0; i<nb_objects; i++){
    char *object = map_get_name(i);
    char *buf = calloc(256, sizeof(char));
    strcpy(buf, object);
    write(fd, buf, 256*sizeof(char));
    int frames = map_get_frames(i);
    write(fd, &frames, sizeof(int));
    int solidity = map_get_solidity(i);
    write(fd, &solidity, sizeof(int));
    int destructible = map_is_destructible(i);
    write(fd, &destructible, sizeof(int));
    int collectible = map_is_collectible(i);
    write(fd, &collectible, sizeof(int));
    int generator = map_is_generator(i);
    write(fd, &generator, sizeof(int));
  }

  close(fd);
}

void map_load (char *filename)
{
  int fd = open(filename, O_RDONLY);
  if(fd == -1){
    fprintf (stderr, "Error 002: Load Failed\n");
  }

  int width;
  read(fd, &width, sizeof(int));
  int height;
  read(fd, &height, sizeof(int));

  map_allocate (width, height);

  int nb_objects;
  read(fd, &nb_objects, sizeof(int));

  int objects[width][height];
  for(int x=0; x<width; x++){
    for(int y=0; y<height; y++){
      read(fd, &objects[x][y], sizeof(int));
      /*
      if(x==1){
        printf("object %d %d : %d\n", x, y, objects[x][y]);
      }
      */
    }
  }

  map_object_begin (nb_objects);

  for(int i=0; i<nb_objects; i++){
    char *object = calloc(256, sizeof(char));
    char buf = ' ';
    int count=0;
    while(buf != 0){
      read(fd, &buf, sizeof(char));
      count++;
    }
    lseek(fd, (0-count) * sizeof(char), SEEK_CUR);
    read(fd, object, count*sizeof(char));
    lseek(fd, (256-count) * sizeof(char), SEEK_CUR);
    //printf("Object : %s\n", object);
    int frames;
    read(fd, &frames, sizeof(int));
    //printf("frames : %d\n", frames);

    int obj_type;
    int solidity;
    read(fd, &solidity, sizeof(int));
    //printf("solidity : %d\n", solidity);
    obj_type = solidity;
    int destructible;
    read(fd, &destructible, sizeof(int));
    //printf("destructible : %d\n", destructible);
    if(destructible){
      obj_type = obj_type | MAP_OBJECT_DESTRUCTIBLE;
    }
    int collectible;
    read(fd, &collectible, sizeof(int));
    //printf("collectible : %d\n", collectible);
    if(collectible){
      obj_type = obj_type | MAP_OBJECT_COLLECTIBLE;
    }
    int generator;
    read(fd, &generator, sizeof(int));
    //printf("generator : %d\n", generator);
    if(generator){
      obj_type = obj_type | MAP_OBJECT_GENERATOR;
    }
    map_object_add (object, frames, obj_type);
  }

  for(int x=0; x<width; x++){
    for(int y=0; y<height; y++){
      map_set(x, y, objects[x][y]);
    }
  }

  map_object_end ();
  close(fd);
}

#endif
