## Assemblea di condominio ( assemblea )
### Descrizione del problema
Un'assemblea di condominio è stata convocata per l'ora X (numero di secondi a partire dalla mezzanotte: X=3600 indica le ore 1:00:00 del mattino).

L'i-esimo degli N condomini arriva al luogo di convocazione all'orario Ci.

Il regolamento di condominio prevede che l'assemblea sia valida se all'orario di inizio sono presenti almeno K condomini (un condomino si considera presente se il suo orario di arrivo è inferiore o uguale all'ora di inizio dell'assemblea).

Data l'ora di convocazione dell'assemblea X, la soglia di validità K e l'orario di arrivo di ciascun condomino, determinare se l'assemblea è valida oppure no.


**Assunzione**: 0 ≤ X, Ci ≤ 86400, 1 ≤ K ≤ N ≤ 10<sup>9</sup>.

**Formato di input**: la prima riga contiene X, N e K separati da spazi, la seconda riga contiene gli N valori Ci separati da spazio.


**Formato di output**: YES, se l'assemblea è valida, NO altrimenti.
