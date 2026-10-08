time ./add_serial 1000000
real    0m2.032s
user    0m0.136s
sys     0m0.180s

time ./add_parallel 1000000 1
real    0m1.979s
user    0m0.149s
sys     0m0.174s

time ./add_parallel 1000000 12
real    0m2.025s
user    0m0.129s
sys     0m0.205s



./add_serial  1000000
0.001363 s

./add_parallel  1000000 1
0.001761 s

./add_parallel  1000000 12
0.000910 s



OBS:
- time masoara timpul de executie al intregului proces => overhead de la afisarile I/O
- folosind biblioteca time.h, masuram doar timpul de executie al lucrului paralelizat/serial (arr[i] += 100)
- Exista overhead de creare a thread-urilor
- Operatia paralelizata nu foloseste intensiv CPU-ul => scalarea este mica