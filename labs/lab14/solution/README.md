Initial Tree

```
                13
        +--------+---+
        10          15
    +---+---+        +--+
    5       11          16
+---+---+
4       8
```

Insert 14

```
                13
        +--------+---+
        10          15
    +---+---+     +--+--+
    5       11   14     16
+---+---+
4       8
```

Insert 3

```

                        13
            +-----------+---------+
            5                     15
    +-------+---+           +-----+-----+
    4           10          14          16
+---+       +---+---+
3           8       11
```

Remove 3

```

                        13
            +-----------+---------+
            5                     15
    +-------+---+           +-----+-----+
    4           10          14          16
            +---+---+
            8       11
```

Remove 4

```
               13
      +--------+--------+
      10                15
+-----+-----+       +---+---+
5           11      14      16
+---+
    8
```