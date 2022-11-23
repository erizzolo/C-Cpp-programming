/*
 * Programma di esempio: funzioni relative alle date
 * Author:  ER
 * Date:    2022/11/11
 * Note:    La rappresentazione scelta per una data
 *          è numerica, con un dato che rappresentato in
 *          formato decimale corrisponde ad AAAAMMGG, dove:
 *           AAAA sono quattro cifre rappresentanti l'anno
 *           MM sono due cifre rappresentanti il mese (1..12)
 *           GG sono due cifre rappresentanti il giorno (1..31)
 *          Ad esempio:
 *           20221225: 25 dicembre 2022
 *           20000229: 29 febbraio 2000 (bisestile)
 */

#include <iostream>
#include <limits>

const bool DEBUG = true; // false to disable

using namespace std;

// date functions
// date representation (AAAAMMGG and GG, MM, AAAA)
int makeDate(int day, int month, int year);
int getDay(int date);
int getMonth(int date);
int getYear(int date);
// info
int daysOfMonth(int month, int year);
bool isValidDate(int date);
// computation
int tomorrow(int today);
int yesterday(int today);
int plusDays(int today, int days);
int minusDays(int today, int days);
int daysBetween(int begin, int end);
// I/O
int getDate();
void outDate(int date);

int main(int argc, char *args[])
{
    printf("Esempio di funzioni relative alle date \n");

    // restituisce true se le data date è valida, false altrimenti
    printf("isValidDate(20001535) = false %d \n", isValidDate(20001535));
    printf("isValidDate(20001231) = true %d \n", isValidDate(20001231));

    // restituisce il numero di giorni del mese month nell'anno year
    // restituisce 0 se il mese month non è valido
    printf("daysOfMonth(2, 2000) = 29 (bisestile) %d \n", daysOfMonth(2, 2000));
    printf("daysOfMonth(20,2310) = 0 %d \n", daysOfMonth(20, 2310));
    printf("daysOfMonth(1,310) = 31 %d \n", daysOfMonth(1, 310));

    // restituisce la data corrispondente a day, month e year
    // supponendo che i dati siano validi
    printf("makeDate(31, 12, 2000) = 20001231 %d \n", makeDate(31, 12, 2000));
    printf("makeDate(35, 120, 2000) = 20012035 (NON VALIDA!) %d \n", makeDate(35, 120, 2000));
    printf("makeDate(-35, 120, 2000) = 20011965 (NON VALIDA!) %d \n", makeDate(-35, 120, 2000));

    // restituisce il giorno del mese della data date,
    // supponendo che date sia valida
    printf("getDay(20001231) = 31 %d \n", getDay(20001231));
    printf("getDay(20001235) = 35 %d \n", getDay(20001235));

    // restituisce il mese della data date,
    // supponendo che date sia valida
    printf("getMonth(20001231) = 12 %d \n", getMonth(20001231));
    printf("getMonth(20003535) = 35 %d \n", getMonth(20003535));

    // restituisce l'anno della data date,
    // supponendo che date sia valida
    printf("getYear(20001231) = 2000 %d \n", getYear(20001231));
    printf("getYear(3535) = 0 %d \n", getYear(3535));

    // restituisce la data del giorno successivo alla data today
    // restituisce today se today non è valida
    printf("tomorrow(20001231) = 20010101 %d \n", tomorrow(20001231));
    printf("tomorrow(3535) = 3535 %d \n", tomorrow(3535));

    // restituisce la data del giorno precedente la data today
    // restituisce today se today non è valida
    printf("yesterday(20001231) = 20001230 %d \n", yesterday(20001231));
    printf("yesterday(3535) = 3535 %d \n", yesterday(3535));

    // restituisce la data del giorno successivo di days alla data today
    // restituisce today se today non è valida
    printf("plusDays(20001231, 3) = 20010103 %d \n", plusDays(20001231, 3));
    printf("plusDays(3535, 5) = 3535 %d \n", plusDays(3535, 5));

    // restituisce la data del giorno precedente di days alla data today
    // restituisce today se today non è valida
    printf("minusDays(20001231, 3) = 20001228 %d \n", minusDays(20001231, 3));
    printf("minusDays(3535,5 ) = 3535 %d \n", minusDays(3535, 5));

    // restituisce il numero di giorni tra le date begin e end
    // undefined behaviour se begin o end non valide
    printf("daysBetween(20001231, 20001231) = 0 %d \n", daysBetween(20001231, 20001231));
    printf("daysBetween(20001231, 20010101) = 1 %d \n", daysBetween(20001231, 20010101));
    printf("daysBetween(20001235, 20001231) = 42 (o altro) %d \n", daysBetween(20001235, 20001231));

    cout << "Enter your birthdate (GG/MM/AAAA): ";
    int birthdate = getDate();
    int today;
    do
    {
        cout << "Enter today's date (GG/MM/AAAA): ";
        today = getDate();
    } while (today < birthdate);
    cout << "Hey! You're " << daysBetween(birthdate, today) << " days old!!!" << endl;

    cout << "Enter a valid date (GG/MM/AAAA): ";
    outDate(getDate());
    cout << " in GG/MM/AAAA format..." << endl;

    // termine con codice 0 = successo
    return 0;
}

/// @brief restituisce la data corrispondente a day, month e year
/// con un dato che rappresentato in formato decimale corrisponde ad AAAAMMGG
/// ad es. makeDate(31, 12, 2000) = 20001231
/// ad es. makeDate(35, 120, 2000) = 20012035 (NON VALIDA!)
/// @param day il giorno del mese
/// @param month il mese
/// @param year l'anno
/// @return la data corrispondente a day, month e year
int makeDate(int day, int month, int year)
{
    return (year * 100 + month) * 100 + day;
}

/// @brief restituisce il giorno del mese della data date,
/// supponendo che date sia valida
/// ad es. getDay(20001231) = 31
/// ad es. getDay(20001235) = 35
/// @param date la data nel formato AAAAMMGG
/// @return il giorno del mese della data date
int getDay(int date)
{
    return date % 100;
}

/// @brief restituisce il mese della data date,
/// supponendo che date sia valida
/// ad es. getMonth(20001231) = 12
/// ad es. getMonth(20003535) = 35
/// @param date la data nel formato AAAAMMGG
/// @return il mese della data date
int getMonth(int date)
{
    return (date / 100) % 100;
}

/// @brief restituisce l'anno della data date,
/// supponendo che date sia valida
/// ad es. getYear(20001231) = 2000
/// ad es. getYear(3535) = 0
/// @param date la data nel formato AAAAMMGG
/// @return l'anno della data date
int getYear(int date)
{
    return date / 100 / 100;
}

/// @brief restituisce true se l'anno year è bisestile, false altrimenti
/// @param year l'anno
/// @return true se l'anno year è bisestile, false altrimenti
bool isLeapYear(int year)
{
    return (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));
}

/// @brief restituisce il numero di giorni del mese month nell'anno year
/// restituisce 0 se il mese month non è valido
/// ad es. daysOfMonth(2, 2000) = 29 (bisestile)
/// ad es. daysOfMonth(20,2310) = 0
/// @param month il mese
/// @param year l'anno (utilizzato solo per month = 2)
/// @return il numero di giorni del mese month nell'anno year
int daysOfMonth(int month, int year)
{
    // NR.2: Don’t insist to have only a single return-statement in a function
    // See https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rnr-single-return
    // single return implementation
    // int days;
    // if (month < 1 || 12 < month)
    // {
    //     days = 0;
    // }
    // else
    // {
    //     if (month == 2) // febbraio
    //     {
    //         days = isLeapYear(year) ? 29 : 28;
    //     }
    //     else if (month < 8) // gennaio, marzo-luglio
    //     {
    //         days = 30 + (month % 2); // 31 per 1 gennaio, 3 marzo, 5 maggio, 7 luglio
    //     }
    //     else // agosto-dicembre
    //     {
    //         days = 31 - (month % 2); // 30 per 9 settembre, 11 novembre
    //     }
    // }
    // return days;
    // multiple return implementation with {}
    // if (month < 1 || 12 < month)
    // {
    //     return 0;
    // }
    // if (month == 2) // febbraio
    // {
    //     return isLeapYear(year) ? 29 : 28;
    // }
    // if (month < 8) // gennaio, marzo-luglio
    // {
    //     return 30 + (month % 2); // 31 per 1 gennaio, 3 marzo, 5 maggio, 7 luglio
    // }
    // // agosto-dicembre
    // return 31 - (month % 2); // 30 per 9 settembre, 11 novembre
    // multiple return implementation and no {}
    if (month < 1 || 12 < month)
        return 0;
    if (month == 2) // febbraio
        return isLeapYear(year) ? 29 : 28;
    if (month < 8)               // gennaio, marzo-luglio
        return 30 + (month % 2); // 31 per 1 gennaio, 3 marzo, 5 maggio, 7 luglio
    // agosto-dicembre
    return 31 - (month % 2); // 30 per 9 settembre, 11 novembre
}

/// @brief restituisce true se le data date è valida, false altrimenti
/// ad es. isValidDate(20001535) = false
/// ad es. isValidDate(20001231) = true
/// @param date la data nel formato AAAAMMGG
/// @return true se le data date è valida, false altrimenti
bool isValidDate(int date)
{
    int day = getDay(date);
    return (1 <= day) && (day <= daysOfMonth(getMonth(date), getYear(date)));
}

/// @brief restituisce la data del giorno successivo alla data today
/// restituisce today se today non è valida
/// ad es.tomorrow(20001231) = 20010101
/// ad es. tomorrow(3535) = 3535
/// @param today il giorno di cui si vuole conoscere il successivo
/// @return la data del giorno successivo alla data today
int tomorrow(int today)
{
    // NR.2: Don’t insist to have only a single return-statement in a function
    // See https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rnr-single-return
    // single return implementation
    // int result = today;
    // if (isValidDate(result))
    // {
    //     // correct but inefficient
    //     // do
    //     // {
    //     //     ++result;
    //     // } while (!isValidDate(result));
    //     // more efficient
    //     int day = getDay(result), month = getMonth(result), year = getYear(result);
    //     if (day < daysOfMonth(month, year))
    //     {
    //         ++day;
    //     }
    //     else
    //     {
    //         day = 1;
    //         if (month < 12)
    //         {
    //             ++month;
    //         }
    //         else
    //         {
    //             month = 1;
    //             ++year;
    //         }
    //     }
    //     result = makeDate(day, month, year);
    // }
    // return result;
    // multiple return implementation with {}
    // if (!isValidDate(today))
    // {
    //     return today;
    // }
    // // correct but inefficient
    // // do
    // // {
    // //     ++today;
    // // } while (!isValidDate(today));
    // // return today;
    // // more efficient
    // int day = getDay(today), month = getMonth(today), year = getYear(today);
    // if (day < daysOfMonth(month, year))
    // {
    //     return today + 1;
    // }
    // if (month < 12)
    // {
    //     return makeDate(1, month + 1, year);
    // }
    // return makeDate(1, 1, year + 1);
    // multiple return implementation and no {}
    if (!isValidDate(today))
        return today;
    int day = getDay(today), month = getMonth(today), year = getYear(today);
    if (day < daysOfMonth(month, year))
        return today + 1;
    if (month < 12)
        return makeDate(1, month + 1, year);
    return makeDate(1, 1, year + 1);
}

/// @brief restituisce la data del giorno precedente la data today
/// restituisce today se today non è valida
/// ad es. yesterday(20001231) = 20001230
/// ad es. yesterday(3535) = 3535
/// @param today il giorno di cui si vuole conoscere il precedente
/// @return la data del giorno precedente la data today
int yesterday(int today)
{
    int result = today;
    if (isValidDate(result))
    {
        // correct but inefficient
        // do
        // {
        //     --result;
        // } while (!isValidDate(result));
        // more efficient
        int day = getDay(result), month = getMonth(result), year = getYear(result);
        if (day > 1)
        {
            --day;
        }
        else
        {
            if (month > 1)
            {
                --month;
            }
            else
            {
                month = 12;
                --year;
            }
            day = daysOfMonth(month, year);
        }
        result = makeDate(day, month, year);
    }
    return result;
}

/// @brief restituisce il numero di giorni dell'anno year
/// @param year l'anno
/// @return il numero di giorni dell'anno year
int daysOfYear(int year)
{
    return isLeapYear(year) ? 366 : 365;
}

/// @brief restituisce il giorno dell'anno corrispondente a date
/// 1° gennaio = giorno 1, 31 dicembre = 365|366
/// @param date la data
/// @return il giorno dell'anno corrispondente a date
int dayOfYear(int date)
{
    int result = getDay(date);
    // somma i giorni dei mesi precedenti
    int month = getMonth(date) - 1, year = getYear(date);
    while (month > 0)
    {
        result += daysOfMonth(month, year);
        --month;
    }
    return result;
}

/// @brief restituisce la data del giorno successivo di days alla data today
/// restituisce today se today non è valida
/// ad es. plusDays(20001231, 3) = 20010103
/// ad es. plusDays(3535) = 3535
/// @param today il giorno di cui si vuole conoscere il successivo di days
/// @param days il numero di giorni di cui incrementare today
/// @return la data del giorno successivo di days alla data today
int plusDays(int today, int days)
{
    // multiple return, no {}
    if (!isValidDate(today))
        return today;
    if (days < 0)
        return minusDays(today, -days);
    // let's start from the 1° of january
    int month = 1, year = getYear(today);
    days += dayOfYear(today) - 1;
    // skip a whole year while possible
    while (days >= daysOfYear(year))
    {
        days -= daysOfYear(year);
        ++year;
    }
    // now skip a whole month while possible
    while (days >= daysOfMonth(month, year))
    {
        days -= daysOfMonth(month, year);
        ++month;
    }
    // now skip days from 1°
    return makeDate(days + 1, month, year);
}

/// @brief restituisce la data del giorno precedente di days alla data today
/// restituisce today se today non è valida
/// ad es. minusDays(20001231, 3) = 20001228
/// ad es. minusDays(3535) = 3535
/// @param today il giorno di cui si vuole conoscere il precedente di days
/// @param days il numero di giorni di cui decrementare today
/// @return la data del giorno precedente di days alla data today
int minusDays(int today, int days)
{
    int result = today;
    if (isValidDate(result))
    {
        if (days < 0)
        {
            result = plusDays(result, -days);
        }
        else
        {
            // correct but inefficient
            while (days > 0)
            {
                result = yesterday(result);
                --days;
            }
        }
    }
    return result;
}

// count multiples of positive n in [min, max]
int multiples(int min, int max, int n)
{
    int qmin = min / n, qmax = max / n;
    int result = qmax - qmin + 1;
    if (qmin * n < min)
        --result;
    if (qmax * n > max)
        --result;
    return result;
}

/// @brief restituisce il numero di giorni tra le date begin e end
/// undefined behaviour se begin o end non valide
/// ad es. daysBetween(20001231, 20001231) = 0
/// ad es. daysBetween(20001231, 20010101) = 1
/// ad es. daysBetween(20010101, 20001231) = -1
/// ad es. daysBetween(20001235, 20001231) = 42 (o altro)
/// @param begin la data iniziale
/// @param end la data finale
/// @return il numero di giorni tra le date begin e end
int daysBetween(int begin, int end)
{
    if (!(isValidDate(begin) && isValidDate(end)))
        return 42;
    if (begin > end)
        return -daysBetween(end, begin);
    // inefficient
    // int result = 0;
    // while (begin < end)
    // {
    //     begin = tomorrow(begin);
    //     ++result;
    // }
    // return result;
    // something better
    int beginYear = getYear(begin), endYear = getYear(end);
    // count from 01/01/beginYear to 31/12/endYear
    int result = (endYear - beginYear + 1) * 365;
    result += multiples(beginYear, endYear, 4);   // leap year if multiple of 4
    result -= multiples(beginYear, endYear, 100); // non leap year if multiple of 100
    result += multiples(beginYear, endYear, 400); // leap year if multiple of 400
    // subtract days from 01/01/beginYear to begin included
    result -= dayOfYear(begin);
    // subtract days from end to 31/12/endYear
    result -= (daysOfYear(endYear) - dayOfYear(end));
    return result;
}

/// @brief legge una data (valida) da tastiera nel formato GG/MM/AAAA
/// @return una data valida (formato AAAAMMGG) letta da tastiera
int getDate()
{
    int result;
    bool valid = false; // not yet valid
    do
    {
        int day, month, year;
        char separator; // almost any separator is valid...
        cin >> day >> separator >> month >> separator >> year;
        if (cin.fail())
        {
            cerr << "Enter a valid date GG/MM/AAAA" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            result = makeDate(day, month, year);
            valid = isValidDate(result);
        }
    } while (!valid);
    return result;
}
/// @brief visualizza una data in formato GG/MM/AAAA
/// @param date la data da visualizzare
void outDate(int date)
{
    int day = getDay(date), month = getMonth(date), year = getYear(date);
    cout << (day < 10 ? "0" : "") << day << "/" << (month < 10 ? "0" : "") << month << "/" << year;
}
