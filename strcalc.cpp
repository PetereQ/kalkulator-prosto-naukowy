#include "strcalc.h"
StrCalc::StrCalc() {
}
StrCalc::~StrCalc() {
}
QString StrCalc::calculate(const QString &input) {
    return m_parser.calculate(input);
}
void StrCalc::setAngleModeDegrees(bool degrees) {
    m_parser.setAngleModeDegrees(degrees);
}

QString StrCalc::lastError() const {
    return m_parser.errorString();
}