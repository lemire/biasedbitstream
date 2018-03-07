# biasedbitstream
Current status: garbage, experiments, random crap... don't expect anything good in this repo


Usage:
```
$ gcc -o test test.c simdxorshift128plus.c -march=native
$ ./test
p = 5 (0.000488) ratio = 0.000492
p = 6 (0.000977) ratio = 0.000959
p = 7 (0.001953) ratio = 0.001966
p = 8 (0.003906) ratio = 0.003871
p = 9 (0.007812) ratio = 0.007811
p = 10 (0.015625) ratio = 0.015577
p = 11 (0.031250) ratio = 0.031284
p = 12 (0.062500) ratio = 0.062396
p = 13 (0.125000) ratio = 0.124957
p = 14 (0.250000) ratio = 0.250040
p = 15 (0.500000) ratio = 0.500158
```
