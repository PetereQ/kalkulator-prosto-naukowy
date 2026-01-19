#ifndef MATHPARSER_H
#define MATHPARSER_H

#include <QString>

class MathParser {
public:
    enum ErrorCode {
        ERR_NONE,
        ERR_SYNTAX,
        ERR_DIV_ZERO,
        ERR_NEG_ROOT,
        ERR_PAREN,
        ERR_RANGE,
        ERR_OVERFLOW,
        ERR_TOO_LONG
    };

    MathParser();
    QString calculate(const QString &input);
    ErrorCode lastError() const { return m_error; }
    QString errorString() const;
    int errorPosition() const { return m_errorPos; }
    void setAngleModeDegrees(bool degrees) { m_angleModeDegrees = degrees; }
    
private:
    enum TokenType {
        TOK_NUM,
        TOK_PLUS, TOK_MINUS, TOK_MUL, TOK_DIV, TOK_MOD, TOK_POW,
        TOK_LPAREN, TOK_RPAREN, TOK_COMMA,
        TOK_SQRT, TOK_ROOT,
        TOK_SIN, TOK_COS, TOK_TAN, TOK_CTG,
        TOK_LN, TOK_LOG,
        TOK_PI, TOK_E,
        TOK_END
    };
    
    struct Token {
        TokenType type;
        double value;
        int pos;
    };
    
    struct ParserContext {
        const QString* input;
        int pos;
        Token current;
        ErrorCode error;
        int errorPos;
        bool angleModeDegrees;
    };
    double degToRad(double deg) const;
    bool isHalfPiPlusKPi(double x) const;
    bool isKPi(double x) const;
    bool checkOverflow(ParserContext* ctx, double v);
    void nextToken(ParserContext* ctx);
    double parseExpr(ParserContext* ctx);
    double parseTerm(ParserContext* ctx);
    double parsePower(ParserContext* ctx);
    double parseFactor(ParserContext* ctx);
    bool validateAndEval(const QString& expr, double* result, ParserContext* ctx);
    ErrorCode m_error;
    int m_errorPos;
    bool m_angleModeDegrees;
};

#endif