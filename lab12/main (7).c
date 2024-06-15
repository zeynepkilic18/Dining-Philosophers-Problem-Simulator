/**Assign a number to each philosopher and chopstick
A philosopher can choose two chopsticks
i, 
i+1 %5
Each philosopher takes the lower numbered chopstick first
P0-C0, 
P2-C2, 
P3-C3, 
P4-cannot take C0 
The highest numbered philosopher does not have any chopy stick.
Then each gets the higher numbered chopstick
P4 is able to get C5 and eat
*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NPHYLS 10
pthread_mutex_t chopsticks[NPHYLS];
void eat(int left, int right) {
    /* Dijkstra'nın algoritmasına göre düşük numaralı çubuk önce alınır*/
    if (left < right) {
        pthread_mutex_lock(&chopsticks[left]);
        pthread_mutex_lock(&chopsticks[right]);
    } else {
        pthread_mutex_lock(&chopsticks[right]);
        pthread_mutex_lock(&chopsticks[left]);
    }
    
    printf("Philosopher is eating with chopsticks %d and %d.\n", left, right);
    
    pthread_mutex_unlock(&chopsticks[left]);
    pthread_mutex_unlock(&chopsticks[right]);
}

void *philosopher1(void *arg) {
 long i = (long)arg;
 pthread_mutex_t *left = &chopsticks[i];
 pthread_mutex_t *right = &chopsticks[(i + 1) % NPHYLS];
 while (1) {
   printf("id %ld: state: %.10s \n", i, "thinking!");
   sleep(1);
   printf("id %ld: state: %.10s \n", i, "hungry!");
   /* Filozof ilk çubuğu alıyor (sol) */
   pthread_mutex_lock(left);
   /* Filozof ikinci çubuğu alıyor (sağ) */
   pthread_mutex_lock(right);
   eat(i, (i + 1) % NPHYLS);
   printf("id %ld: state: %.10s \n", i, "eating");
   pthread_mutex_unlock(right);
   pthread_mutex_unlock(left);
   printf("id %ld: state: %.10s \n", i, "done!");

   sleep(1);
 }
}

int main(){
  /*TODO: create threads, */
    pthread_t phils[NPHYLS];
    long i;
    for (i = 0; i < NPHYLS; i++) {
    /*Her filozof pthread_create ile bir numara alır.*/
        pthread_create(&phils[i], NULL, philosopher1, (void *)i);
    }
    for (i = 0; i < NPHYLS; i++) {
        pthread_join(phils[i], NULL);
    }
    return 0;
}

