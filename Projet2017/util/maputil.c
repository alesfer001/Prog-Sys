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
        int width = 0;
        int height = 0;
        int nb_objects = 0;
        read(fd, &width, sizeof(int));
        read(fd, &height, sizeof(int));
        read(fd, &nb_objects, sizeof(int));

        if(argc < (6 * nb_objects) + 3){
          fprintf(stderr, "Error 004: Number of objects is incompatible with constraint\n");
          return -1;
        }
        else{
          nb_objects = 0;
          lseek(fd, (3+width*height)*sizeof(int), SEEK_SET);
          while(i < argc - 1){
            i++; //filename
            char *object = calloc(256, sizeof(char));
            strcpy(object, argv[i]);
            i++; //frames
            int frames = atoi(argv[i]);
            i++; //solidity
            int solidity;
            int destructible;
            int collectible;
            int generator;
            if(strcmp(argv[i], "solid") == 0){
              solidity = 2;
            }
            else if(strcmp(argv[i], "semi-solid") == 0){
              solidity = 1;
            }
            else if(strcmp(argv[i] , "air") == 0){
              solidity = 0;
            }
            else if(strcmp(argv[i] , "liquid") == 0){
              solidity = 3;
            }

            i++; //destructible
            if(strcmp(argv[i], "destructible") == 0){
              destructible = 1;
            }
            else if(strcmp(argv[i], "not-destructible") == 0){
              destructible = 0;
            }

            i++; //collectible
            if(strcmp(argv[i], "collectible") == 0){
              collectible = 1;
            }
            else if(strcmp(argv[i], "not-collectible") == 0){
              collectible = 0;
            }

            i++; //generator
            if(strcmp(argv[i], "generator") == 0){
              generator = 1;
            }
            else if(strcmp(argv[i], "not-generator") == 0){
              generator = 0;
            }

            write(fd, object, 256*sizeof(char));
            write(fd, &frames, sizeof(int));
            write(fd, &solidity, sizeof(int));
            write(fd, &destructible, sizeof(int));
            write(fd, &collectible, sizeof(int));
            write(fd, &generator, sizeof(int));
            nb_objects++;
          }
          lseek(fd, 2*sizeof(int), SEEK_SET);
          write(fd, &nb_objects, sizeof(int));
        }
      }
    }
    else if(strcmp(argv[i], "--pruneobjects") == 0){
      int width = 0;
      int height = 0;
      int nb_objects = 0;
      read(fd, &width, sizeof(int));
      read(fd, &height, sizeof(int));
      read(fd, &nb_objects, sizeof(int));

      int object_exists[nb_objects];
      for(int i=0; i<nb_objects; i++){
        object_exists[i] = 0;
      }

      int objectxy = -1;
      for(int x=0; x<width; x++){
        for(int y=0; y<height; y++){
          read(fd, &objectxy, sizeof(int));
          if(objectxy != -1){
            object_exists[objectxy] = 1;
          }
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

      int nb_existing_objects = 0;
      lseek(fd, (3+width*height)*sizeof(int), SEEK_SET);
      char *object = calloc(256, sizeof(char));
      for(int i=0; i<nb_objects; i++){
        if(object_exists[i]){
          read(fd, object, 256*sizeof(char));
          strcpy(objectsname[i], object);
          //printf("object : %s\n", objectsname[i]);

          read(fd, frames+i, sizeof(int));
          //printf("frames : %d\n", frames[i]);

          int solidity;
          read(fd, soliditys+i, sizeof(int));
          //printf("soliditys : %d\n", soliditys[i]);
          int destructible;
          read(fd, destructibles+i, sizeof(int));
          //printf("destructibles : %d\n", destructibles[i]);
          int collectible;
          read(fd, collectibles+i, sizeof(int));
          //printf("collectibles : %d\n", collectibles[i]);
          int generator;
          read(fd, generators+i, sizeof(int));
          //printf("generators : %d\n", generators[i]);
          nb_existing_objects++;
          //printf("nb_existing_objects : %d\n", nb_existing_objects);
        }
        else{
          lseek(fd, 256*sizeof(char) + 5*sizeof(int), SEEK_CUR);
        }
      }

      // Works

      lseek(fd, (3+width*height)*sizeof(int), SEEK_SET);
      for(int i=0; i<nb_objects; i++){
        if(object_exists[i]){
          char *buf = calloc(256, sizeof(char));
          strcpy(buf, objectsname[i]);
          write(fd, buf, 256*sizeof(char));
          //printf("object : %s\n", objectsname[i]);
          //printf("object buf : %s\n", buf);
          write(fd, &frames[i], sizeof(int));
          //printf("frames : %d\n", frames[i]);
          write(fd, &soliditys[i], sizeof(int));
          //printf("soliditys : %d\n", soliditys[i]);
          write(fd, &destructibles[i], sizeof(int));
          //printf("destructibles : %d\n", destructibles[i]);
          write(fd, &collectibles[i], sizeof(int));
          //printf("collectibles : %d\n", collectibles[i]);
          write(fd, &generators[i], sizeof(int));
          //printf("generators : %d\n", generators[i]);
          //printf("nb_existing_objects : %d\n", nb_existing_objects);
        }
      }

      int new_id[nb_existing_objects];
      int id = 0;
      for(int i=0; i<nb_objects; i++){
        if(object_exists[i]){
          new_id[id] = i;
          id++;
        }
      }

      lseek(fd, 3*sizeof(int), SEEK_SET);
      for(int x=0; x<width; x++){
        for(int y=0; y<height; y++){
          read(fd, &objectxy, sizeof(int));
          if(objectxy != -1){
            for(int i=0; i<nb_existing_objects; i++){
              if(objectxy == new_id[i]){
                lseek(fd, (0-1)*sizeof(int), SEEK_CUR);
                write(fd, &i, sizeof(int));
              }
            }
          }
        }
      }



      lseek(fd, 2*sizeof(int), SEEK_SET);
      write(fd, &nb_existing_objects, sizeof(int));
      ftruncate(fd, (3+width*height)*sizeof(int) + nb_existing_objects*(256*sizeof(char) + 5*sizeof(int)));
    }
    else{
      fprintf (stderr, "Error 003: Not Enough Args for maputil\n maputil <file> --options [value]\n options : getwidth, getheight, getobjects, getinfo\n options : setwidth [value], setheight [value]\n");
    }
  }

  return 0;
}
