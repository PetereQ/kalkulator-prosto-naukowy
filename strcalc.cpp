#include "strcalc.h"
#include "evaluate_result.h"
#include <map>
#include <QString>
std::map<ErrorCode, QString> error_code_to_message = {
    {ERR_SYNTAX, "To nie jest poprawne wyrażenie"},
    {ERR_DIV_ZERO, "Dzielenie przez 0"},
    {ERR_NEG_ROOT, "Pierwiastek z liczby ujemnej"},
    {ERR_PAREN, "Niepoprawne nawiasowanie"},
    {ERR_RANGE, "Zbyt duza liczba"},
    {ERR_OVERFLOW, "Zbyt duza liczba"},
    {ERR_TOO_LONG, "Zbyt dlugie wyrażenie"}
};

QString calculate(const QString &input) {
    double result;
    QString out_str = "Test";
    ErrorCode code = validate_and_eval(input.toStdString().c_str(), &result);
    if(code==ERR_NONE)
        out_str = QString::number(result);
    else
        out_str = error_code_to_message[code];
    return out_str;
}
