## Scomposizione in fattori primi (scomponi)
Il teorema fondamentale dell'aritmetica afferma che ogni numero naturale
maggiore di 1 o è un numero primo o si può esprimere come prodotto di numeri
primi in modo unico se si prescinde dall'ordine in cui compaiono i fattori.
Scrivere un programma che, dato un numero naturale n > 1, produca in output
l’elenco delle coppie (fattore, esponente) della sua scomposizione in fattori
primi.
Assunzione: 1 < n < 2·10^9.
Formato di input: leggere da tastiera il numero n.
Formato di output: l’elenco separato da spazi delle coppie (fattore, esponente)
della scomposizione.
Esempi:
| Input      | Output               |
| ---------- | -------------------- |
| 13         | (13, 1)              |
| 81         | (3, 4)               |
| 1987653424 | (2, 4) (124228339 1) |
Parti opzionali:
• usare in output una notazione leggermente più “matematica”, ad
esempio: “1987653424 = 2^4 * 124228339”
• usare in output codice HTML, ad esempio “1987653424 =
2<sup>4</sup> &coppie; 124228339” → 1987653424 = ...
