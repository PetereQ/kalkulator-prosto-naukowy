#include "strcalc.h"
#include <QString>
#include <QStringList>

QString calculate(const QString &input) {

    //                      tutaj bierzemy "11+(80/80)*2" i z tego robimy:
    //                      tokensSingle = { "1","1","+","(","8","0","/","8","0",")","*","2" } a potem
    //                                         1 1 + ( 8 0 / 8 0 ) * 2
    //                      tokensMerged = { "11","+","(","80","/","80",")","*","2" }
    //                                         11 + ( 80 / 80 ) * 2

    QStringList tokensSingle;
    QStringList tokensMerged;

    for (int i = 0; i < input.length(); ++i) {
        QChar ch = input[i];

        if (ch.isSpace())
            continue;

        tokensSingle.append(QString(ch));
    }

    QString numberBuffer;

    for (const QString &tok : tokensSingle) {
        if (tok[0].isDigit()) {
            numberBuffer += tok;
        } else {
            if (!numberBuffer.isEmpty()) {
                tokensMerged.append(numberBuffer);
                numberBuffer.clear();
            }
            tokensMerged.append(tok);
        }
    }

    if (!numberBuffer.isEmpty()) {
        tokensMerged.append(numberBuffer);
    }


    //               jak narazie radzimy sobie z + i -, uwzględniamy też sytuacje kiedy pierwsza jest liczba ujemna
    //               nie ma jeszcze kolejnosci wykonywania dzialan ani nawiasow

    int result = 0;
    int sign = +1;

    for (int i = 0; i < tokensMerged.size(); ++i) {
        const QString &tok = tokensMerged[i];

        if (tok == "+") {
            sign = +1;
        }
        else if (tok == "-") {
            sign = -1;
        }
        else {
            result += sign * tok.toInt();
            sign = +1;
        }
    }


    QString wynik = QString::number(result);
    return wynik;
}
