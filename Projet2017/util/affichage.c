#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
  int fd = open("../maps/saved.map", O_RDONLY);

  int width;
  read(fd, &width, sizeof(int));
  int height;
  read(fd, &height, sizeof(int));
  int nb_objects;
  read(fd, &nb_objects, sizeof(int));

  int map[width][height];
  for(int x=0; x<width; x++){
    for(int y=0; y<height; y++){
      read(fd, &map[x][y], sizeof(int));
    }
  }

  char *objectsname[nb_objects];
  for(int i=0; i<nb_objects; i++){
    objectsname[i] = calloc(256, sizeof(char));
  }
  int frames[nb_objects];
  int soliditys[nb_objects];
  int destructibles[nb_objects];
  int collectibles[nb_objects];
  int generators[nb_objects];

  char *object = calloc(256, sizeof(char));
  for(int i=0; i<nb_objects; i++){
    read(fd, object, 256*sizeof(char));
    strcpy(objectsname[i], object);

    read(fd, frames+i, sizeof(int));

    int solidity;
    read(fd, soliditys+i, sizeof(int));
    int destructible;
    read(fd, destructibles+i, sizeof(int));
    int collectible;
    read(fd, collectibles+i, sizeof(int));
    int generator;
    read(fd, generators+i, sizeof(int));
  }
  char buf;
  if(read(fd, &buf, sizeof(char)) > 0){
    printf("Error: Not end of file\n");
  }

  printf("Width : %d\n", width);
  printf("Height : %d\n", height);
  printf("Nb_Objects : %d\n", nb_objects);
  for(int y=0; y<height; y++){
    for(int x=0; x<width; x++){
      if(x == width-1){
        if(map[x][y] == -1){
          printf("\n");
        }
        else{
          printf("%d\n", map[x][y]);
        }
      }
      else{
        if(map[x][y] == -1){
          printf(" ");
        }
        else{
          printf("%d", map[x][y]);
        }
      }

    }
  }

  for(int i=0; i<nb_objects; i++){
    printf("Object : %s\n", objectsname[i]);
    printf("Frames : %d\n", frames[i]);
    printf("Solidity : %d\n", soliditys[i]);
    printf("Destructible : %d\n", destructibles[i]);
    printf("Collectible : %d\n", collectibles[i]);
    printf("Generator : %d\n", generators[i]);
  }
}
