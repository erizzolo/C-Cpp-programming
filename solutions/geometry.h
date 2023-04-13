/*
 * Libreria di dati e funzioni "geometriche"
 * Author:  ER
 * Date:    2023/02/22
 * Note:
 */

#ifndef GEOMETRY_H
#define GEOMETRY_H

// un punto nel piano cartesiano
struct punto
{
    double x; // ascissa
    double y; // ordinata
};

// segmento definito dai due punti estremi
struct segmento
{
    punto a, b;
};

// retta di equazione a x + b y + c = 0
struct retta
{
    double a, b, c;
};

// triangolo definito dai vertici
struct triangolo
{
    punto a, b, c;
};

#ifndef MAX_VERTICI
#define MAX_VERTICI 20
#endif // MAX_VERTICI

// poligono definito dai suoi vertici
struct poligono
{
    punto vertici[MAX_VERTICI];
    size_t numVertici{0};
};

// circonferenza definita da centro e raggio
struct circonferenza
{
    punto c;
    double r;
};

#include <iostream>
#include <cmath>

using namespace std;

// manda sullo stream out (default cout) una rappresentazione testuale
void print(const punto &, ostream &out = cout);

// manda sullo stream out (default cout) una rappresentazione testuale
void print(const segmento &, ostream &out = cout);

// manda sullo stream out (default cout) una rappresentazione testuale
void print(const retta &, ostream &out = cout);

// manda sullo stream out (default cout) una rappresentazione testuale
void print(const triangolo &, ostream &out = cout);

// manda sullo stream out (default cout) una rappresentazione testuale
void print(const poligono &, ostream &out = cout);

// manda sullo stream out (default cout) una rappresentazione testuale
void print(const circonferenza &, ostream &out = cout);

// restituisce un punto con i parametri specificati
punto getPunto(double x, double y);

// restituisce un segmento con i parametri specificati
segmento getSegmento(const punto &, const punto &);

// restituisce una retta con i parametri specificati
retta getRetta(double a, double b, double c);

// restituisce la retta passante per i due punti dati
retta getRetta(const punto &a, const punto &b);

// restituisce un triangolo con i parametri specificati
triangolo getTriangolo(const punto &, const punto &, const punto &);

// restituisce un poligono con i parametri specificati
poligono getPoligono(const punto[], size_t);

// restituisce un circonferenza con i parametri specificati
circonferenza getCirconferenza(const punto &centro, double raggio);

// restituisce una copia di original
punto copy(const punto &original);

// restituisce una copia di original
segmento copy(const segmento &original);

// restituisce una copia di original
retta copy(const retta &original);

// restituisce una copia di original
triangolo copy(const triangolo &original);

// restituisce una copia di original
poligono copy(const poligono &original);

// restituisce una copia di original
circonferenza copy(const circonferenza &original);

// restituisce true se lhs e rhs coincidono, false altrimenti
bool equals(const punto &lhs, const punto &rhs);

// restituisce true se lhs e rhs coincidono, false altrimenti
bool equals(const segmento &lhs, const segmento &rhs);

// restituisce true se lhs e rhs coincidono, false altrimenti
bool equals(const retta &lhs, const retta &rhs);

// restituisce true se lhs e rhs coincidono, false altrimenti
bool equals(const triangolo &lhs, const triangolo &rhs);

// restituisce true se lhs e rhs coincidono, false altrimenti
bool equals(const poligono &lhs, const poligono &rhs);

// restituisce true se lhs e rhs coincidono, false altrimenti
bool equals(const circonferenza &lhs, const circonferenza &rhs);

// restituisce la lunghezza del segmento
double length(const segmento &);

// restituisce il perimetro del triangolo
double perimeter(const triangolo &);

// restituisce il perimetro del poligono
double perimeter(const poligono &);

// restituisce il perimetro della circonferenza
double perimeter(const circonferenza &);

// restituisce l'area del triangolo
double area(const triangolo &);

// restituisce l'area del poligono
double area(const poligono &);

// restituisce l'area della circonferenza
double area(const circonferenza &);

// restituisce true se p appartiene al segmento s, false altrimenti
bool contains(const segmento &s, const punto &p);

// restituisce true se p appartiene allla retta r, false altrimenti
bool contains(const retta &r, const punto &p);

// helper function
// restituisce la distanza euclidea tra i punti a e b
// ovvero √( xa − xb)^2 +( ya − yb)^2 (usare sqrt della libreria cmath)
double distance(const punto &a, const punto &b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

// manda sullo stream out (default cout) una rappresentazione testuale
void print(const punto &p, ostream &out /* = cout */)
{
    out << "(" << p.x << "," << p.y << ")";
}

// manda sullo stream out (default cout) una rappresentazione testuale
void print(const segmento &s, ostream &out /* = cout */)
{
    out << "Segmento da ";
    print(s.a, out);
    out << " a ";
    print(s.b, out);
}

// manda sullo stream out (default cout) una rappresentazione testuale
void print(const retta &r, ostream &out /* = cout */)
{
    out << "retta " << r.a << " x + " << r.b << " y + " << r.c << " = 0";
}

// manda sullo stream out (default cout) una rappresentazione testuale
void print(const triangolo &t, ostream &out /* = cout */)
{
    out << "Triangolo di vertici ";
    print(t.a, out);
    out << ", ";
    print(t.b, out);
    out << " e ";
    print(t.c, out);
}

// manda sullo stream out (default cout) una rappresentazione testuale
void print(const poligono &p, ostream &out /* = cout */)
{
    out << "Poligono di " << p.numVertici << " vertici: ";
    for (size_t v = 0; v < p.numVertici; ++v)
    {
        if (v != 0)
            out << ",";
        print(p.vertici[v], out);
    }
}

// manda sullo stream out (default cout) una rappresentazione testuale
void print(const circonferenza &c, ostream &out /* = cout */)
{
    out << "Circonferenza di centro ";
    print(c.c);
    out << " e raggio " << c.r;
}

// restituisce un punto con i parametri specificati
punto getPunto(double x, double y)
{
    return punto{x, y};
}

// restituisce un segmento con i parametri specificati
segmento getSegmento(const punto &a, const punto &b)
{
    return segmento{a, b};
}

// restituisce una retta con i parametri specificati
retta getRetta(double a, double b, double c)
{
    return retta{a, b, c};
}

// restituisce la retta passante per i due punti dati
retta getRetta(const punto &a, const punto &b)
{
    if (a.x == b.x)
    {
        return getRetta(1.0, 0.0, -a.x);
    }
    if (a.y == b.y)
    {
        return getRetta(0.0, 1.0, -a.y);
    }
    double dx = b.x - a.x, dy = b.y - a.y;
    return getRetta(dy, -dx, a.y * dx - a.x * dy);
}

// restituisce un triangolo con i parametri specificati
triangolo getTriangolo(const punto &a, const punto &b, const punto &c)
{
    return triangolo{a, b, c};
}

// restituisce un poligono con i parametri specificati
poligono getPoligono(const punto vertici[], size_t numVertici)
{
    poligono result;
    result.numVertici = numVertici;
    for (size_t v = 0; v < numVertici; ++v)
    {
        result.vertici[v] = vertici[v];
    }
    return result;
}

// restituisce un circonferenza con i parametri specificati
circonferenza getCirconferenza(const punto &centro, double raggio)
{
    return circonferenza{centro, raggio};
}

// restituisce una copia di original
punto copy(const punto &original)
{
    punto result = original;
    return result;
}

// restituisce una copia di original
segmento copy(const segmento &original)
{
    segmento result = original;
    return result;
}

// restituisce una copia di original
retta copy(const retta &original)
{
    retta result = original;
    return result;
}

// restituisce una copia di original
triangolo copy(const triangolo &original)
{
    triangolo result = original;
    return result;
}

// restituisce una copia di original
poligono copy(const poligono &original)
{
    poligono result = original;
    return result;
}

// restituisce una copia di original
circonferenza copy(const circonferenza &original)
{
    circonferenza result = original;
    return result;
}

// restituisce true se lhs e rhs coincidono, false altrimenti
bool equals(const punto &lhs, const punto &rhs)
{
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

// restituisce true se lhs e rhs coincidono, false altrimenti
bool equals(const segmento &lhs, const segmento &rhs)
{
    return equals(lhs.a, rhs.a) && equals(lhs.b, rhs.b);
}

// restituisce true se lhs e rhs coincidono, false altrimenti
bool equals(const retta &lhs, const retta &rhs)
{
    // wrong implementation: x + y + 1 = 0 and 2x + 2y + 2 = 0 are the same line
    // return lhs.a == rhs.a && lhs.b == rhs.b && lhs.c == rhs.c;

    // correct, but actual result may be wrong due to approximation ...
    if (rhs.a != 0)
    {
        double factor = lhs.a / rhs.a;
        return (lhs.b == rhs.b * factor) && (lhs.c == rhs.c * factor);
    }
    else
    { // either a or b must differ from 0
        double factor = lhs.b / rhs.b;
        return (lhs.a == rhs.a * factor) && (lhs.c == rhs.c * factor);
    }
}

// restituisce true se lhs e rhs coincidono, false altrimenti
bool equals(const triangolo &lhs, const triangolo &rhs)
{
    return equals(lhs.a, rhs.a) && equals(lhs.b, rhs.b) && equals(lhs.c, rhs.c);
}

// restituisce true se lhs e rhs coincidono, false altrimenti
bool equals(const poligono &lhs, const poligono &rhs)
{
    bool result = lhs.numVertici == rhs.numVertici;
    for (size_t v = 0; v < lhs.numVertici && result; ++v)
    {
        result = equals(lhs.vertici[v], rhs.vertici[v]);
    }
    return result;
}

// restituisce true se lhs e rhs coincidono, false altrimenti
bool equals(const circonferenza &lhs, const circonferenza &rhs)
{
    return equals(lhs.c, rhs.c) && lhs.r == rhs.r;
}

// restituisce la lunghezza del segmento
double length(const segmento &s)
{
    return distance(s.a, s.b);
}

// restituisce il perimetro del triangolo
double perimeter(const triangolo &t)
{
    return distance(t.a, t.b) + distance(t.b, t.c) + distance(t.c, t.a);
}

// restituisce il perimetro del poligono
double perimeter(const poligono &p)
{
    double result = 0;
    for (size_t v = 0; v < p.numVertici; ++v)
    {
        result += distance(p.vertici[v], p.vertici[(v + 1) % p.numVertici]);
    }
    return result;
}

// with c++20: compile with -std=c++20 option
// #include <numbers>

// restituisce il perimetro della circonferenza
double perimeter(const circonferenza &c)
{
    // with c++20: compile with -std=c++20 option
    // return 2 * numbers::pi * c.r;
    return 2 * atan(1) * 4 * c.r; // atan(1) * 4 yields pi
}

// http://www.cs.berkeley.edu/~wkahan/Triangle.pdf
double kahan(double a, double b, double c)
{
    return sqrt((a + (b + c)) * (c - (a - b)) * (c + (a - b)) * (a + (b - c))) / 4;
}
// restituisce l'area del triangolo
double area(const triangolo &t)
{
    // formula di Erone
    // dato a, b, c lunghezze dei lati, semiperimetro s = (a+b+c)/2
    // area = sqrt(s(s-a)(s-b)(s-c))
    // formula poco stabile se un lato è molto più piccolo degli altri
    double a = distance(t.a, t.b);
    double b = distance(t.b, t.c);
    double c = distance(t.c, t.a);
    double s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
    // using kahan's formula
    if (a > b)
    {
        if (b > c)
            return kahan(a, b, c);
        else if (a > c)
            return kahan(a, c, b);
        else
            return kahan(c, a, b);
    }
    else
    {
        if (a > c)
            return kahan(b, a, c);
        else if (b > c)
            return kahan(b, c, a);
        else
            return kahan(c, b, a);
    }
}

// restituisce l'area del poligono
double area(const poligono &p)
{
    double result = 0;
    for (size_t v = 0, next = p.numVertici - 1; v < p.numVertici; next = v++)
    {
        result += (p.vertici[v].x + p.vertici[next].x) * (p.vertici[v].y + p.vertici[next].y);
    }
    return result < 0 ? -result / 2 : result / 2;
}

// with c++20: compile with -std=c++20 option
// #include <numbers>

// restituisce l'area della circonferenza
double area(const circonferenza &c)
{
    // with c++20: compile with -std=c++20 option
    // return numbers::pi * c.r * c.r;
    return atan(1) * 4 * c.r * c.r; // atan(1) * 4 yields pi
}

// restituisce true se p appartiene al segmento s, false altrimenti
bool contains(const segmento &s, const punto &p)
{
    // actual result may be wrong due to approximation ...
    return distance(p, s.a) + distance(p, s.b) == length(s);
}

// restituisce true se p appartiene alla retta r, false altrimenti
bool contains(const retta &r, const punto &p)
{
    // actual result may be wrong due to approximation ...
    return r.a * p.x + r.b * p.y + r.c == 0;
}

// restituisce true se p appartiene alla circonferenza r, false altrimenti
bool contains(const circonferenza &c, const punto &p)
{
    // actual result may be wrong due to approximation ...
    return distance(p, c.c) == c.r;
}

#endif
