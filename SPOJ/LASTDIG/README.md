The idea is that the last digit of power of number has some period. For example, for number 2 (and same applies to number 12, 22, 32 and so on, because last digit is always result of multiplication of last digits), we have:

```
Number | Last digit
-------------------
2      | 2 
4      | 4
8      | 8
16     | 6
32     | 2
64     | 4
128    | 8
256    | 6
512    | 2
...
```

Before sending to SPOJ, remove whitespaces or otherwise you will hit 700B size limit for problem.

Original: http://www.spoj.com/problems/LASTDIG/
