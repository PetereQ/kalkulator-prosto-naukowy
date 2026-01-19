#ifndef STRCALC_H
#define STRCALC_H
#include <QString>
#include "mathparser.h"

class StrCalc {
public:
    StrCalc();
    ~StrCalc();
    QString calculate(const QString &input);
    void setAngleModeDegrees(bool degrees);
    QString lastError() const;
private:
    MathParser m_parser;
};

#endif