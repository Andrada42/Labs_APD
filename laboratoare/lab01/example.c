#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 4


void *f(void *arg) {
  long id = *(long *)arg;
  for (int i = 1; i <= 100; i++)
    printf("[Thread %ld] Hello World #%d!\n", id, i);

  pthread_exit(NULL);
}

void *f1(void *arg) {
  long id = *(long *)arg;
  // usleep(1000);  // => sansa ca al doilea thread sa termine primul e mai mare
  printf("[Thread %ld] Buna!\n", id);

  pthread_exit(NULL);
}

void *f2(void *arg) {
  long id = *(long *)arg;
  printf("[Thread %ld] Salut!\n", id);

  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  long cores = sysconf(_SC_NPROCESSORS_CONF);
  if (cores <= 0)
    return 0;
  printf("Ai %ld core-uri\n", cores);

  pthread_t threads[cores];
  int r;
  long id;
  void *status;
  long ids[cores + 1];

  // (2-3)
  // for (id = 1; id <= cores; id++) {
  //   ids[id] = id;
  //   r = pthread_create(&threads[id], NULL, f, &ids[id]);

  //   if (r) {
  //     printf("Eroare la crearea thread-ului %ld\n", id);
  //     exit(-1);
  //   }
  // }
  // OBS: Ordinea in care incep thread-urile nu e mereu la fel
  //      Afisarea celor 100 de mesaje / thread se intercaleaza deoarece ruleaza in paralel

  // for (id = 1; id <= cores; id++) {
  //   r = pthread_join(threads[id], &status);

  //   if (r) {
  //     printf("Eroare la asteptarea thread-ului %ld\n", id);
  //     exit(-1);
  //   }
  // }

  // (4)
  if (cores <= 1)
    printf("Ai nevoie de cel putin 2 core-uri\n");
  
  id = 1;
  ids[id] = id;
  r = pthread_create(&threads[id], NULL, f1, &ids[id]);
  if (r) {
    printf("Eroare la crearea thread-ului %ld\n", id);
    exit(-1);
  }

  id = 2;
  ids[id] = id;
  r = pthread_create(&threads[id], NULL, f2, &ids[id]);
  if (r) {
    printf("Eroare la crearea thread-ului %ld\n", id);
    exit(-1);
  }

  for (id = 1; id <= 2; id++) {
    r = pthread_join(threads[id], &status);
    if (r) {
      printf("Eroare la asteptarea thread-ului %ld\n", id);
      exit(-1);
    }
  }

  return 0;
}
