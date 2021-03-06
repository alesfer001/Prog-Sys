#include "SDL.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <pthread.h>

#include "timer.h"

#define EMPTY_TIMER 100000000
#define MAX_TIMERS 100

void* sigalrm_catcher(void* arg);
void sigalrm_handler(int signum);
void swap(int *xp, int *yp);
void swaptimerids(timer_id_t *xp, timer_id_t *yp);
void sort(int arr[], int paramids[], timer_id_t timerids[], int n);
void timeval(struct itimerval *time, int val);

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

int timers[MAX_TIMERS];
void* params[MAX_TIMERS];
int paramids[MAX_TIMERS];
timer_id_t timerids[MAX_TIMERS];
timer_id_t timerid = 0;

// Return number of elapsed µsec since... a long time ago
static unsigned long get_time (void){
  struct timeval tv;

  gettimeofday (&tv ,NULL);

  // Only count seconds since beginning of 2016 (not jan 1st, 1970)
  tv.tv_sec -= 3600UL * 24 * 365 * 46;

  return tv.tv_sec * 1000000UL + tv.tv_usec;
}

#ifdef PADAWAN

// timer_init returns 1 if timers are fully implemented, 0 otherwise
int timer_init (void){
  for(int i=0; i<MAX_TIMERS; i++){
    timers[i] = EMPTY_TIMER;
    params[i] = NULL;
    paramids[i] = -1;
    timerids[i] = -1;
  }

  sigset_t sigset;

  sigemptyset(&sigset);
  sigaddset(&sigset, SIGALRM);
  pthread_sigmask(SIG_BLOCK, &sigset, NULL);

  pthread_t tid;
  pthread_create(&tid, NULL, sigalrm_catcher, NULL);

  return 1;
}

void* sigalrm_catcher(void* arg){
  struct sigaction act;
  act.sa_handler = sigalrm_handler;
  act.sa_flags = 0;
  sigemptyset(&act.sa_mask);

  sigaction(SIGALRM , &act, NULL);

  while(1){
    sigsuspend(&act.sa_mask);
  }
}

void sigalrm_handler(int signum){
  pthread_mutex_lock(&mut);
  sdl_push_event(params[paramids[0]]);
  int i=1;
  while(timers[i] != EMPTY_TIMER){
    timers[i] -= timers[0];
    i++;
  }
  timers[0] = EMPTY_TIMER;
  params[paramids[0]] = NULL;
  timerids[0] = -1;
  sort(timers, paramids, timerids, MAX_TIMERS);
  if(timers[0] != EMPTY_TIMER){
    struct itimerval time;
    timeval(&time, timers[0]);
    setitimer(ITIMER_REAL, &time, NULL);
  }
  pthread_mutex_unlock(&mut);
}

timer_id_t timer_set (Uint32 delay, void *param){
  pthread_mutex_lock(&mut);
  struct itimerval time;
  getitimer(ITIMER_REAL, &time);
  if(time.it_value.tv_usec == 0){
    timeval(&time, delay*1000);
    timers[0] = delay*1000;
    params[0] = param;
    paramids[0] = 0;
    timerids[0] = timerid;
    timerid++;
    setitimer(ITIMER_REAL, &time, NULL);
  }
  else if(time.it_value.tv_usec > delay*1000){
    int decrease = timers[0] - time.it_value.tv_usec;
    timers[0] = time.it_value.tv_usec;
    int i=1;
    while(timers[i] != EMPTY_TIMER){
      timers[i] -= decrease;
      i++;
    }
    timers[i] = delay*1000;
    int j=0;
    while(params[j] != NULL){
      j++;
    }
    params[j] = param;
    paramids[i] = j;
    timerids[i] = timerid;
    timerid++;
    sort(timers, paramids, timerids, MAX_TIMERS);
    timeval(&time, timers[0]);
    setitimer(ITIMER_REAL, &time, NULL);
  }
  else{
    int i=0;
    while(timers[i] != EMPTY_TIMER){
      i++;
    }
    timers[i] = delay*1000 + timers[0] - time.it_value.tv_usec;
    int j=0;
    while(params[j] != NULL){
      j++;
    }
    params[j] = param;
    paramids[i] = j;
    timerids[i] = timerid;
    timerid++;
    sort(timers, paramids, timerids, MAX_TIMERS);
  }
  pthread_mutex_unlock(&mut);
  return timerid-1;
}

void swap(int *xp, int *yp){
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void swaptimerids(timer_id_t *xp, timer_id_t *yp){
    timer_id_t temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort(int arr[], int paramids[], timer_id_t timerids[], int n){
    int i, j, min_idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
          if (arr[j] < arr[min_idx])
            min_idx = j;

        // Swap the found minimum element with the first element
        swap(&arr[min_idx], &arr[i]);
        swap(&paramids[min_idx], &paramids[i]);
        swaptimerids(&timerids[min_idx], &timerids[i]);
    }
}

void timeval(struct itimerval *time, int val){
  time->it_interval.tv_sec=0;
  time->it_interval.tv_usec=0;
  if(val >= 1000*1000){
    int sec = 0;
    while(val >= 1000*1000){
      sec++;
      val-=1000*1000;
    }
    time->it_value.tv_sec=sec;
    time->it_value.tv_usec=val;
  }
  else{
    time->it_value.tv_sec=0;
    time->it_value.tv_usec=val;
  }
}

int timer_cancel (timer_id_t timer_id){
  int t=0;
  while(timerids[t] != timer_id && t < MAX_TIMERS){
    t++;
  }

  if(t < MAX_TIMERS){
    if(t == 0){
      struct itimerval time;
      getitimer(ITIMER_REAL, &time);
      int decrease = timers[0] - time.it_value.tv_usec;
      int i=1;
      while(timers[i] != EMPTY_TIMER){
        timers[i] -= decrease;
        i++;
      }
      timers[0] = EMPTY_TIMER;
      params[paramids[0]] = NULL;
      timerids[0] = -1;
      sort(timers, paramids, timerids, MAX_TIMERS);
      if(timers[0] != EMPTY_TIMER){
        struct itimerval time;
        timeval(&time, timers[0]);
        setitimer(ITIMER_REAL, &time, NULL);
      }
      else{
        struct itimerval time;
        timeval(&time, 0);
        setitimer(ITIMER_REAL, &time, NULL);
      }
    }
    else{
      timers[t] = EMPTY_TIMER;
      params[paramids[t]] = NULL;
      timerids[t] = -1;
      sort(timers, paramids, timerids, MAX_TIMERS);
    }
    return 1;
  }

  return 0; // failure
}

#endif
