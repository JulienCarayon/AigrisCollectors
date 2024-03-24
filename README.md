# AigrisCollectors

space_collector client

## Unit testing

This project has unit testing. Only native tests are suported at the moment.

To run unit tests please run :

```
pio test -e test
```

Tests suits are stored in folders, at this path :

`test/<NAME_OF_YOUR_TEST>/test.c`

Other character like '-' are not supported

# Useful informations

## Base location

(abscissa , ordinate)

- UP = (10 000 , 20 000)
- RIGHT = (20 000, 10 000)
- DOWN = (10 000 , 0)
- LEFT = (0 , 10 000)

## Ship location

offset = +1500

#### Attackers

| ID         | 1          | 2          | 3         | 4          | 5         |
| ---------- | ---------- | ---------- | --------- | ---------- | --------- |
| BASE UP    |            |            |           |            |           |
| BASE RIGHT |            |            |           |            |           |
| BASE DOWN  | 10000<br>0 | 11500<br>0 | 8500<br>0 | 13000<br>0 | 7000<br>0 |
| BASE LEFT  |            |            |           |            |           |

#### Explorers

| ID         | 6          | 7         |
| ---------- | ---------- | --------- |
| BASE UP    |            |           |
| BASE RIGHT |            |           |
| BASE DOWN  | 14500<br>0 | 5500<br>0 |
| BASE LEFT  |            |           |

#### Collectors

| ID         | 8          | 9         |
| ---------- | ---------- | --------- |
| BASE UP    |            |           |
| BASE RIGHT |            |           |
| BASE DOWN  | 16000<br>0 | 4000<br>0 |
| BASE LEFT  |            |           |

#### Memory Pool

|         |      **PLANETS**       |        **SHIP_P0**        |        **SHIP_P1**        |        **SHIP_P2**        |        **SHIP_P3**        |
| :-----: | :--------------------: | :-----------------------: | :-----------------------: | :-----------------------: | :-----------------------: |
| **IDs** | 1\|2\|3\|4\|5\|6\|7\|8 | 1\|2\|3\|4\|5\|6\|7\|8\|9 | 1\|2\|3\|4\|5\|6\|7\|8\|9 | 1\|2\|3\|4\|5\|6\|7\|8\|9 | 1\|2\|3\|4\|5\|6\|7\|8\|9 |
