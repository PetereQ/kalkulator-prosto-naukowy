#include "strcalc.h"
#include "evaluate_result.h"
#include <map>
#include <QString>
#include "mainwindow.h"
std::map<ErrorCode, QString> error_code_to_message = {
    {ERR_SYNTAX, "To nie jest poprawne wyrażenie"},
    {ERR_DIV_ZERO, "Dzielenie przez 0"},
    {ERR_NEG_ROOT, "Pierwiastek z liczby ujemnej"},
    {ERR_PAREN, "Niepoprawne nawiasowanie"},
    {ERR_RANGE, "Zbyt duza liczba"},
    {ERR_OVERFLOW, "Zbyt duza liczba"},
    {ERR_TOO_LONG, "Zbyt dlugie wyrażenie"},
    {ERR_EXIST, "Nie istnieje"} //Dodalem nowy blad dla tangensa i cotangensa, dla przejrzystosci
};

QString calculate(const QString &input, OutputState &error) {
    if(input.size() == 0) {
        error = EMPTY;
        return "";
    }
    double result;
    QString out_str;
    ErrorCode code = validate_and_eval(input.toStdString().c_str(), &result);
    if(code==ERR_NONE) {
        error = RESULT;
        out_str = QString::number(result, 'g', 9);
    }
    else {
        error = ERROR;
        out_str = error_code_to_message[code];
    }
    return out_str;
}
