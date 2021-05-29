# Custom-Vector-OOP

## Tuščių vektorių užpildymas

|                | 10000    | 100000   | 1000000  | 10000000 | 100000000 |
| -------------  |----------| ---------|----------|----------|---------- |
| **std::vector**| 0.0001s  | 0.001999s| 0.016953s| 0.140651s| 1.954s    |
| **Vector**     | 0.0019s  | 0.003285s| 0.016638s| 0.134073s| 1.675s    |

## Konteinerių atminties perskirstymai

|                | 100000000|
| -------------  |----------|
| **std::vector**| 13       |
| **Vector**     | 27       |

## Naudojant duomenų failą su 100000 studentų įrašų, palyginimas kiek laiko užtrunka programos veikimas naudojant std::vector ir Vector realizacijas

|                 | 100000   |
| --------------- |----------|
| **std::vector** |          |
| Nuskaitymas     | 1.19s    |
| Rūšiavimas      | 0.071s   |
| **Vector**      |          |
| Nuskaitymas     | 1.225s   |
| Rūšiavimas      | 0.91s    |
