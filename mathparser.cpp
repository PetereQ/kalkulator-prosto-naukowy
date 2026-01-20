#include "mathparser.h"
#include <cmath>
#include <cctype>
#include <cstring>
#include <cerrno>
#include <QString>
#include <QJSEngine>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_E
#define M_E 2.71828182845904523536
#endif

MathParser::MathParser() 
    : m_error(ERR_NONE), m_errorPos(-1), m_angleModeDegrees(true) {
}

QString MathParser::calculate(const QString &input) {
    double result = 0.0;
    m_error = ERR_NONE;
    m_errorPos = -1;
    ParserContext ctx;
    ctx.input = &input;
    ctx.pos = 0;
    ctx.error = ERR_NONE;
    ctx.errorPos = -1;
    ctx.angleModeDegrees = m_angleModeDegrees;
    
    if (validateAndEval(input, &result, &ctx)) {
        QString str = QString::number(result, 'f', 10);
        while (str.contains('.') && (str.endsWith('0') || str.endsWith('.'))) {
            str.chop(1);
            if (str.endsWith('.')) {
                str.chop(1);
                break;
            }
        }
        return str;
    } else {
        m_error = ctx.error;
        m_errorPos = ctx.errorPos;
        if (m_error == ERR_DIV_ZERO){
            return "Blad: Dzielenie przez zero";
        } else if (m_error == ERR_SYNTAX) {
            return QString("Blad skladni na pozycji %1").arg(m_errorPos);
        } else if (m_error == ERR_NEG_ROOT) {
            return "Blad: Pierwiastek z liczby ujemnej";
        } else if (m_error == ERR_PAREN) {
            return "Blad: Nieprawidlowe nawiasy";
        } else {
            return QString("Blad: %1").arg(errorString());
        }
    }
}

QString MathParser::errorString() const {
    switch (m_error) {
        case ERR_NONE: return "Brak bledu";
        case ERR_SYNTAX: return "Blad skladni";
        case ERR_DIV_ZERO: return "Dzielenie przez zero";
        case ERR_NEG_ROOT: return "Pierwiastek z liczby ujemnej";
        case ERR_PAREN: return "Nieprawidlowe nawiasy";
        case ERR_RANGE: return "Blad dziedziny funkcji";
        case ERR_OVERFLOW: return "Przepelnienie";
        case ERR_TOO_LONG: return "Wyrazenie zbyt dlugie";
        default: return "Nieznany blad";
    }
}
double MathParser::degToRad(double deg) const {
    return deg * M_PI / 180.0;
}

bool MathParser::isHalfPiPlusKPi(double x) const {
    double k = (x - M_PI / 2) / M_PI;
    return std::fabs(k - std::round(k)) < 1e-9;
}

bool MathParser::isKPi(double x) const {
    double k = x / M_PI;
    return std::fabs(k - std::round(k)) < 1e-9;
}

bool MathParser::checkOverflow(ParserContext* ctx, double v) {
    if (std::isinf(v) || std::isnan(v)) {
        ctx->error = ERR_OVERFLOW;
        ctx->errorPos = ctx->current.pos;
        return true;
    }
    return false;
}

void MathParser::nextToken(ParserContext* ctx) {
    const QString& input = *(ctx->input);

    while (ctx->pos < input.length() && input[ctx->pos].isSpace()){
        ctx->pos++;
    }
    if (input.length() - ctx->pos > 100) {
        ctx->error = ERR_TOO_LONG;
        ctx->errorPos = ctx->pos;
        return;
    }
    
    ctx->current.pos = ctx->pos;
    if (ctx->pos >= input.length()) {
        ctx->current.type = TOK_END;
        return;
    }
    
    QChar c = input[ctx->pos];
    if (ctx->pos + 2 < input.length()) {
        QStringRef substr = input.midRef(ctx->pos, 3);
        if (substr == "sin") { ctx->pos += 3; ctx->current.type = TOK_SIN; return; }
        if (substr == "cos") { ctx->pos += 3; ctx->current.type = TOK_COS; return; }
        if (substr == "tan") { ctx->pos += 3; ctx->current.type = TOK_TAN; return; }
        if (substr == "log") { ctx->pos += 3; ctx->current.type = TOK_LOG; return; }
        
        if (ctx->pos + 3 < input.length()) {
            QStringRef substr4 = input.midRef(ctx->pos, 4);
            if (substr4 == "sqrt") { ctx->pos += 4; ctx->current.type = TOK_SQRT; return; }
            if (substr4 == "root") { ctx->pos += 4; ctx->current.type = TOK_ROOT; return; }
        }
        if (ctx->pos + 1 < input.length()) {
            QStringRef substr2 = input.midRef(ctx->pos, 2);
            if (substr2 == "ln") { ctx->pos += 2; ctx->current.type = TOK_LN; return; }
            if (substr2 == "pi") { ctx->pos += 2; ctx->current.type = TOK_PI; ctx->current.value = M_PI; return; }
        }
        
        if (c == 'e' && !input[ctx->pos+1].isLetterOrNumber()) {
            ctx->pos++; ctx->current.type = TOK_E; ctx->current.value = M_E; return;
        }
        if(c == 'c' && ctx->pos + 2 < input.length()) {
            QStringRef substr3 = input.midRef(ctx->pos, 3);
            if (substr3 == "ctg") { ctx->pos += 3; ctx->current.type = TOK_CTG; return;}
        }
    }
    if (c.isDigit() || c == '.') {
        bool ok;
        QString numStr;
        int startPos = ctx->pos;
        while (ctx->pos < input.length() && 
               (input[ctx->pos].isDigit() || input[ctx->pos] == '.' || 
                input[ctx->pos] == 'e' || input[ctx->pos] == 'E' ||
                (ctx->pos > startPos && (input[ctx->pos] == '+' || input[ctx->pos] == '-')))) {
            numStr.append(input[ctx->pos]);
            ctx->pos++;
        }
        ctx->current.value = numStr.toDouble(&ok);
        if (!ok) {
            ctx->error = ERR_SYNTAX;
            ctx->errorPos = startPos;
            return;
        }
        ctx->current.type = TOK_NUM;
        return;
    }
    ctx->pos++;
    switch (c.unicode()) {
        case '+': ctx->current.type = TOK_PLUS; break;
        case '-': ctx->current.type = TOK_MINUS; break;
        case '*': ctx->current.type = TOK_MUL; break;
        case '/': ctx->current.type = TOK_DIV; break;
        case '%': ctx->current.type = TOK_MOD; break;
        case '^': ctx->current.type = TOK_POW; break;
        case '(': ctx->current.type = TOK_LPAREN; break;
        case ')': ctx->current.type = TOK_RPAREN; break;
        case ',': ctx->current.type = TOK_COMMA; break;
        default: 
            ctx->error = ERR_SYNTAX;
            ctx->errorPos = ctx->pos - 1;
    }
}

double MathParser::parseFactor(ParserContext* ctx) {
    if (ctx->error != ERR_NONE) return 0.0;
    if (ctx->current.type == TOK_MINUS){
        nextToken(ctx);
        return -parseFactor(ctx);
    }
    if (ctx->current.type == TOK_SIN || ctx->current.type == TOK_COS || 
        ctx->current.type == TOK_TAN || ctx->current.type == TOK_CTG) {
        TokenType func = ctx->current.type;
        nextToken(ctx);
        
        if (ctx->current.type != TOK_LPAREN) {
            ctx->error = ERR_SYNTAX;
            ctx->errorPos = ctx->current.pos;
            return 0.0;
        }
        nextToken(ctx);
        double arg = parseExpr(ctx);
        
        if (ctx->current.type != TOK_RPAREN)
        {
            ctx->error = ERR_PAREN;
            ctx->errorPos = ctx->current.pos;
            return 0.0;
        }
        nextToken(ctx);
        double rad = ctx->angleModeDegrees ? degToRad(arg) : arg;
        switch (func) {
            case TOK_SIN: return std::sin(rad);
            case TOK_COS: return std::cos(rad);
            case TOK_TAN: 
                if (isHalfPiPlusKPi(rad)) {
                    ctx->error = ERR_RANGE;
                    ctx->errorPos = ctx->current.pos;
                    return 0.0;
                }
                return std::tan(rad);
            case TOK_CTG:
                if (isKPi(rad)){
                    ctx->error = ERR_RANGE;
                    ctx->errorPos = ctx->current.pos;
                    return 0.0;
                }
                return std::cos(rad) / std::sin(rad);
            default: return 0.0;
        }
    }
    
    if (ctx->current.type == TOK_LN) {
        nextToken(ctx);
        if (ctx->current.type != TOK_LPAREN){
            ctx->error = ERR_SYNTAX;
            ctx->errorPos = ctx->current.pos;
            return 0.0;
        }
        nextToken(ctx);
        double arg = parseExpr(ctx);
        if (arg <= 0) {
            ctx->error = ERR_RANGE;
            ctx->errorPos = ctx->current.pos;
            return 0.0;
        }
        if (ctx->current.type != TOK_RPAREN) {
            ctx->error = ERR_PAREN;
            ctx->errorPos = ctx->current.pos;
            return 0.0;
        }
        nextToken(ctx);  
        return std::log(arg);
    }
    
    if (ctx->current.type == TOK_LOG) {
        nextToken(ctx);
        double base = 10.0;
        
        if (ctx->current.type == TOK_LPAREN) {
            nextToken(ctx);
            double parsedBase = parseExpr(ctx); 
            if (ctx->error != ERR_NONE) return 0.0; 
            if (ctx->current.type == TOK_COMMA) {
                base = parsedBase;
                if (base <= 0 || base == 1) {
                    ctx->error = ERR_RANGE;
                    ctx->errorPos = ctx->current.pos;
                    return 0.0;
                }
                nextToken(ctx);
                
                double value = parseExpr(ctx);
                if (value <= 0) {
                    ctx->error = ERR_RANGE;
                    ctx->errorPos = ctx->current.pos;
                    return 0.0;
                }
                if (ctx->current.type != TOK_RPAREN) {
                    ctx->error = ERR_PAREN;
                    ctx->errorPos = ctx->current.pos;
                    return 0.0;
                }
                nextToken(ctx);
                return std::log(value) / std::log(base);
            } else {
                if (parsedBase <= 0) {
                    ctx->error = ERR_RANGE;
                    ctx->errorPos = ctx->current.pos;
                    return 0.0;
                }
                if (ctx->current.type != TOK_RPAREN) {
                    ctx->error = ERR_PAREN;
                    ctx->errorPos = ctx->current.pos;
                    return 0.0;
                }
                nextToken(ctx);
                
                return std::log10(parsedBase);
            }
        }else
        {
            ctx->error = ERR_SYNTAX;
            ctx->errorPos = ctx->current.pos;
            return 0.0;
        }
    }
    
    if (ctx->current.type == TOK_NUM){
        double v = ctx->current.value;
        nextToken(ctx);
        return v;
    }
    if (ctx->current.type == TOK_PI || ctx->current.type == TOK_E) {
        double v = ctx->current.value;
        nextToken(ctx);
        return v;
    }
    if (ctx->current.type == TOK_LPAREN) {
        nextToken(ctx);
        double v = parseExpr(ctx);
        
        if (ctx->current.type != TOK_RPAREN) {
            ctx->error = ERR_PAREN;
            ctx->errorPos = ctx->current.pos;
            return 0.0;
        }
        nextToken(ctx);
        
        return v;
    }
    
    if(ctx->current.type == TOK_SQRT) {
        nextToken(ctx);
        if (ctx->current.type != TOK_LPAREN) {
            ctx->error = ERR_SYNTAX;
            ctx->errorPos = ctx->current.pos;
            return 0.0;
        }
        nextToken(ctx); 
        double v = parseExpr(ctx);
        if (v < 0) {
            ctx->error = ERR_NEG_ROOT;
            ctx->errorPos = ctx->current.pos;
            return 0.0;
        }
        
        if(ctx->current.type != TOK_RPAREN) {
            ctx->error = ERR_PAREN;
            ctx->errorPos = ctx->current.pos;
            return 0.0;
        }
        nextToken(ctx);
        return std::sqrt(v);
    }
    
    if (ctx->current.type == TOK_ROOT) {
        nextToken(ctx);
        if (ctx->current.type != TOK_LPAREN) {
            ctx->error = ERR_SYNTAX;
            ctx->errorPos = ctx->current.pos;
            return 0.0;
        }
        nextToken(ctx);  
        double degree = parseExpr(ctx);
        if (ctx->current.type != TOK_COMMA) {
            ctx->error = ERR_SYNTAX;
            ctx->errorPos = ctx->current.pos;
            return 0.0;
        }
        nextToken(ctx);
        
        double value = parseExpr(ctx);
        if (ctx->current.type != TOK_RPAREN) {
            ctx->error = ERR_PAREN;
            ctx->errorPos = ctx->current.pos;
            return 0.0;
        }
        nextToken(ctx);
        
        if(static_cast<int>(degree) % 2 == 0 && value < 0) {
            ctx->error = ERR_NEG_ROOT;
            ctx->errorPos = ctx->current.pos;
            return 0.0;
        } 
        return std::pow(value, 1.0 / degree);
    }
    ctx->error = ERR_SYNTAX;
    ctx->errorPos = ctx->current.pos;
    return 0.0;
}

double MathParser::parsePower(ParserContext* ctx) {
    double v = parseFactor(ctx);
    if (checkOverflow(ctx, v)) return 0.0;
    while (ctx->current.type == TOK_POW) {
        nextToken(ctx);
        double rhs = parsePower(ctx);
        
        if (std::fabs(v) < 1e-12 && std::fabs(rhs) < 1e-12) {
            ctx->error = ERR_RANGE;
            ctx->errorPos = ctx->current.pos;
            return 0.0;
        }
        if(v < 0 && std::fabs(rhs - std::round(rhs)) > 1e-9) {
            ctx->error = ERR_RANGE;
            ctx->errorPos = ctx->current.pos;
            return 0.0;
        }  
        v = std::pow(v, rhs);
        if (checkOverflow(ctx, v)) return 0.0;
    }
    return v;
}

double MathParser::parseTerm(ParserContext* ctx)
{
    double v = parsePower(ctx);
    if (checkOverflow(ctx, v)) return 0.0;
    
    while (ctx->current.type == TOK_MUL || ctx->current.type == TOK_DIV || ctx->current.type == TOK_MOD) {
        TokenType op = ctx->current.type;
        int opPos = ctx->current.pos;
        nextToken(ctx);
        double rhs = parsePower(ctx);
        
        if ((op == TOK_DIV || op == TOK_MOD) && std::fabs(rhs) < 1e-12) {
            ctx->error = ERR_DIV_ZERO;
            ctx->errorPos = opPos;
            return 0.0;
        }
        
        switch (op) {
            case TOK_MUL: v *= rhs; break;
            case TOK_DIV: v /= rhs; break;
            case TOK_MOD: 
                if (std::fabs(rhs - std::round(rhs)) > 1e-9 || std::fabs(v - std::round(v)) > 1e-9){
                    ctx->error = ERR_SYNTAX;
                    ctx->errorPos = opPos;
                    return 0.0;
                }
                v = std::fmod(v, rhs);
                if (v < 0) v += std::fabs(rhs);
                break;
            default: break;
        } 
        if (checkOverflow(ctx, v)) return 0.0;
    }  
    return v;
}

double MathParser::parseExpr(ParserContext* ctx){
    double v = parseTerm(ctx);
    if (checkOverflow(ctx, v)) return 0.0;
    while (ctx->current.type == TOK_PLUS || ctx->current.type == TOK_MINUS) {
        TokenType op = ctx->current.type;
        int opPos = ctx->current.pos;
        nextToken(ctx); 
        double rhs = parseTerm(ctx); 
        if (op == TOK_PLUS) {
            v += rhs;
        } else {
            v -= rhs;
        }
        if (checkOverflow(ctx, v)) return 0.0;
    }
    
    return v;
}

bool MathParser::validateAndEval(const QString& expr, double* result, ParserContext* ctx){
    nextToken(ctx);
    *result = parseExpr(ctx);
    
    if (ctx->current.type != TOK_END && ctx->error == ERR_NONE) {
        ctx->error = ERR_SYNTAX;
        if (ctx->errorPos == -1) ctx->errorPos = ctx->current.pos;
    }
    return ctx->error == ERR_NONE;
}
