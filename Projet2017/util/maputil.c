#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char** argv){
  if(argc < 3){
    fprintf (stderr, "Error 003: Not Enough Args for maputil\n maputil <file> --options [value]\n options : getwidth, getheight, getobjects, getinfo\n options : setwidth [value], setheight [value]\n");
  }

  int fd = open(argv[1], O_RDWR);

  for(int i=2; i<argc; i++){
    if(strcmp(argv[i], "--getwidth") == 0){
      int width;
      lseek(fd, 0, SEEK_SET);
      read(fd, &width, sizeof(int));
      printf("Map width : %d\n", width);
    }
    else if(strcmp(argv[i], "--getheight") == 0){
      int height;
      lseek(fd, sizeof(int), SEEK_SET);
      read(fd, &height, sizeof(int));
      printf("Map height : %d\n", height);
    }
    else if(strcmp(argv[i], "--getobjects") == 0){
      int nb_objects;
      lseek(fd, 2 * sizeof(int), SEEK_SET);
      read(fd, &nb_objects, sizeof(int));
      printf("Map objects number : %d\n", nb_objects);
    }
    else if(strcmp(argv[i], "--getinfo") == 0){
      int width, height, nb_objects;
      lseek(fd, 0, SEEK_SET);
      read(fd, &width, sizeof(int));
      read(fd, &height, sizeof(int));
      read(fd, &nb_objects, sizeof(int));
      printf("Map width : %d\n", width);
      printf("Map height : %d\n", height);
      printf("Map objects number : %d\n", nb_objects);
    }
    else if(strcmp(argv[i], "--setwidth") == 0){
      i++;
      if(argv[i] == NULL){
        fprintf (stderr, "Error 003: Not Enough Args for maputil\n maputil <file> --options [value]\n options : getwidth, getheight, getobjects, getinfo\n options : setwidth [value], setheight [value]\n");
      }
      else{
        int new_width = atoi(argv[i]);
        int old_width = 0;
        int height = 0;
        int nb_objects = 0;
        lseek(fd, 0, SEEK_SET);
        read(fd, &old_width, sizeof(int));
        read(fd, &height, sizeof(int));
        read(fd, &nb_objects, sizeof(int));

        int objects[old_width][height];
        for(int x=0; x<old_width; x++){
          for(int y=0; y<height; y++){
            read(fd, &objects[x][y], sizeof(int));
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
          char buf = ' ';
          int count=0;
          while(buf != 0){
            read(fd, &buf, sizeof(char));
            count++;
          }
          lseek(fd, (0-count) * sizeof(char), SEEK_CUR);
          read(fd, object, count*sizeof(char));
          lseek(fd, (256-count) * sizeof(char), SEEK_CUR);
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

        lseek(fd, 3 * sizeof(int), SEEK_SET);
        if(old_width > new_width){
          for(int x=0; x<new_width; x++){
            for(int y=0; y<height; y++){
              write(fd , &objects[x][y], sizeof(int));
            }
          }
        }
        else if(old_width < new_width){
          for(int x=0; x<old_width; x++){
            for(int y=0; y<height; y++){
              write(fd , &objects[x][y], sizeof(int));
            }
          }
          int buf = -1;
          for(int x=old_width; x<new_width; x++){
            for(int y=0; y<height; y++){
              write(fd, &buf, sizeof(int));
            }
          }
        }

        if(old_width != new_width){
          for(int i=0; i<nb_objects; i++){
            char *buf = calloc(256, sizeof(char));
            strcpy(buf, objectsname[i]);
            write(fd, buf, 256*sizeof(char));
            write(fd, frames+i, sizeof(int));
            write(fd, soliditys+i, sizeof(int));
            write(fd, destructibles+i, sizeof(int));
            write(fd, collectibles+i, sizeof(int));
            write(fd, generators+i, sizeof(int));
          }

        lseek(fd, 0, SEEK_SET);
        write(fd, &new_width, sizeof(int));
      }
        printf("New map width : %d\n", new_width);
      }
    }
    else if(strcmp(argv[i], "--setheight") == 0){
      i++;
      if(argv[i] == NULL){
        fprintf (stderr, "Error 003: Not Enough Args for maputil\n maputil <file> --options [value]\n options : getwidth, getheight, getobjects, getinfo\n options : setwidth [value], setheight [value]\n");
      }
      else{
        int new_height = atoi(argv[i]);
        int old_height = 0;
        int width = 0;
        int nb_objects = 0;
        lseek(fd, 0, SEEK_SET);
        read(fd, &width, sizeof(int));
        read(fd, &old_height, sizeof(int));
        read(fd, &nb_objects, sizeof(int));

        int objects[width][old_height];
        for(int x=0; x<width; x++){
          for(int y=0; y<old_height; y++){
            read(fd, &objects[x][y], sizeof(int));
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
          char buf = ' ';
          int count=0;
          while(buf != 0){
            read(fd, &buf, sizeof(char));
            count++;
          }
          lseek(fd, (0-count) * sizeof(char), SEEK_CUR);
          read(fd, object, count*sizeof(char));
          lseek(fd, (256-count) * sizeof(char), SEEK_CUR);
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

        lseek(fd, 3 * sizeof(int), SEEK_SET);
        if(old_height > new_height){
          for(int x=0; x<width; x++){
            for(int y=(old_height-new_height); y<old_height; y++){
              write(fd , &objects[x][y], sizeof(int));
            }
          }
        }
        else if(old_height < new_height){
          int buf = -1;
          for(int x=0; x<width; x++){
            for(int y=0; y<new_height; y++){
              if(y < new_height - old_height){
                write(fd, &buf, sizeof(int));
              }
              else{
                write(fd, &objects[x][y-(new_height-old_height)], sizeof(int));
              }
            }
          }
        }

        if(old_height != new_height){
          for(int i=0; i<nb_objects; i++){
            char *buf = calloc(256, sizeof(char));
            strcpy(buf, objectsname[i]);
            write(fd, buf, 256*sizeof(char));
            write(fd, frames+i, sizeof(int));
            write(fd, soliditys+i, sizeof(int));
            write(fd, destructibles+i, sizeof(int));
            write(fd, collectibles+i, sizeof(int));
            write(fd, generators+i, sizeof(int));
          }

          lseek(fd, sizeof(int), SEEK_SET);
          write(fd, &new_height, sizeof(int));
        }
        printf("New map height : %d\n", new_height);
      }
    }
    else if(strcmp(argv[i], "--setobjects") == 0){
      if(argc < 9){
        fprintf (stderr, "Error 003: Not Enough Args for maputil\n maputil <file> --options [value]\n options : getwidth, getheight, getobjects, getinfo\n options : setwidth [value], setheight [value]\n");
      }
      else{
        i++; //filename
        char *object = calloc(256, sizeof(char));
        strcpy(object, argv[i]);
        i++; //frames
        int frames = atoi(argv[i]);
        i++; //solidity
        int solidity = atoi(argv[i]);
        i++; //destructible
        int destructible = atoi(argv[i]);
        i++; //collectible
        int collectible = atoi(argv[i]);
        i++; //generator
        int generator = atoi(argv[i]);
      }
    }
    else{
      fprintf (stderr, "Error 003: Not Enough Args for maputil\n maputil <file> --options [value]\n options : getwidth, getheight, getobjects, getinfo\n options : setwidth [value], setheight [value]\n");
    }
  }

  return 0;
}
