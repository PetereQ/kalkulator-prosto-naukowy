#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_E
#define M_E 2.71828182845904523536
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <errno.h>

typedef enum {
    ERR_NONE,
    ERR_SYNTAX,
    ERR_DIV_ZERO,
    ERR_NEG_ROOT,
    ERR_PAREN,
    ERR_RANGE,
    ERR_OVERFLOW,
    ERR_TOO_LONG
} ErrorCode;

typedef enum {
    TOK_NUM,
    TOK_PLUS, TOK_MINUS, TOK_MUL, TOK_DIV, TOK_MOD, TOK_POW,
    TOK_LPAREN, TOK_RPAREN, TOK_COMMA,
    TOK_SQRT, TOK_ROOT,
    TOK_SIN, TOK_COS, TOK_TAN, TOK_CTG,
    TOK_LN, TOK_LOG,
    TOK_PI, TOK_E,
    TOK_END
} TokenType;

typedef struct {
    TokenType type;
    double value;
    int pos;
} Token;

const char* input;
int pos;
Token current;
ErrorCode error;

double parse_expr();
double parse_factor();
double parse_power();
double parse_term();
int is_half_pi_plus_kpi(double x);
int is_kpi(double x);
double deg_to_rad(double deg) { return deg*M_PI/180.0; }

int is_half_pi_plus_kpi(double x) {
    double k = (x - M_PI/2)/M_PI;
    return fabs(k - round(k)) < 1e-9;
}

int is_kpi(double x) {
    double k = x/M_PI;
    return fabs(k - round(k)) < 1e-9;
}

int check_overflow(double v) {
    if(isinf(v) || isnan(v)){
        error = ERR_OVERFLOW;
        return 1;
    }
    return 0;
}

void next_token() {
    while(isspace(input[pos])) pos++;
    if(strlen(&input[pos]) > 45){ 
        error=ERR_TOO_LONG; 
        return; 
    }
    current.pos = pos;
    char c = input[pos];
    if(c=='\0'){ current.type=TOK_END; return; }

    if(!strncmp(&input[pos],"sin",3)){ pos+=3; current.type=TOK_SIN; return; }
    if(!strncmp(&input[pos],"cos",3)){ pos+=3; current.type=TOK_COS; return; }
    if(!strncmp(&input[pos],"tan",3)){ pos+=3; current.type=TOK_TAN; return; }
    if(!strncmp(&input[pos],"ctg",3)){ pos+=3; current.type=TOK_CTG; return; }
    if(!strncmp(&input[pos],"sqrt",4)){ pos+=4; current.type=TOK_SQRT; return; }
    if(!strncmp(&input[pos],"root",4)){ pos+=4; current.type=TOK_ROOT; return; }
    if(!strncmp(&input[pos],"ln",2)){ pos+=2; current.type=TOK_LN; return; }
    if(!strncmp(&input[pos],"log",3)){ pos+=3; current.type=TOK_LOG; return; }
    if(!strncmp(&input[pos],"pi",2)){ pos+=2; current.type=TOK_NUM; current.value=M_PI; return; }
    if(!strncmp(&input[pos],"e",1)){ pos+=1; current.type=TOK_NUM; current.value=M_E; return; }

    if(isdigit(c) || c=='.'){
        char* end;
        errno=0;
        current.value=strtod(&input[pos],&end);
        if(errno==ERANGE) error=ERR_OVERFLOW;
        pos=end-input;
        current.type=TOK_NUM;
        return;
    }

    pos++;
    switch(c){
        case '+': current.type=TOK_PLUS; break;
        case '-': current.type=TOK_MINUS; break;
        case '*': current.type=TOK_MUL; break;
        case '/': current.type=TOK_DIV; break;
        case '%': current.type=TOK_MOD; break;
        case '^': current.type=TOK_POW; break;
        case '(': current.type=TOK_LPAREN; break;
        case ')': current.type=TOK_RPAREN; break;
        case ',': current.type=TOK_COMMA; break;
        default: error=ERR_SYNTAX;
    }
}

double parse_factor() {
    if(error) return 0.0;
     if(current.type == TOK_MINUS) {
        next_token();
        return -parse_factor();
    }
    if(current.type==TOK_SIN || current.type==TOK_COS || current.type==TOK_TAN || current.type==TOK_CTG){
        TokenType func=current.type;
        next_token();
        if(current.type!=TOK_LPAREN){ error=ERR_SYNTAX; return 0.0; }
        next_token();
        double arg=parse_expr();
        if(current.type!=TOK_RPAREN){ error=ERR_PAREN; return 0.0; }
        next_token();
        double rad = deg_to_rad(arg);
        if(func==TOK_SIN) return sin(rad);
        if(func==TOK_COS) return cos(rad);
        if(func==TOK_TAN){ if(is_half_pi_plus_kpi(rad)){ error=ERR_RANGE; return 0.0; } return tan(rad); }
        if(func==TOK_CTG){ if(is_kpi(rad)){ error=ERR_RANGE; return 0.0; } return cos(rad)/sin(rad); }
    }
    if(current.type==TOK_LN){
        next_token();
        if(current.type!=TOK_LPAREN){ error=ERR_SYNTAX; return 0.0; }
        next_token();
        double arg=parse_expr();
        if(arg<=0){ error=ERR_RANGE; return 0.0; }
        if(current.type!=TOK_RPAREN){ error=ERR_PAREN; return 0.0; }
        next_token();
        return log(arg);
    }

    if(current.type==TOK_LOG){
        next_token();
        double base = 10.0;
        if(current.type == TOK_LPAREN){
            next_token();
            double parsed_base = parse_expr();
            if(error) return 0.0;
            if(current.type == TOK_COMMA){
                base = parsed_base;
                if(base<=0 || base==1){ error=ERR_RANGE; return 0.0; }
                next_token();
                double value = parse_expr();
                if(value<=0){ error=ERR_RANGE; return 0.0; }
                if(current.type!=TOK_RPAREN){ error=ERR_PAREN; return 0.0; }
                next_token();
                return log(value)/log(base);
            } else {
                if(parsed_base<=0){ error=ERR_RANGE; return 0.0; }
                if(current.type!=TOK_RPAREN){ error=ERR_PAREN; return 0.0; }
                next_token();
                return log10(parsed_base);
            }
        } else {
            error = ERR_SYNTAX;
            return 0.0;
        }
    }

    if(current.type==TOK_NUM){
        double v=current.value;
        next_token();
        return v;
    }
    if(current.type==TOK_LPAREN){
        next_token();
        double v=parse_expr();
        if(current.type!=TOK_RPAREN){ error=ERR_PAREN; return 0.0; }
        next_token();
        return v;
    }

    if(current.type==TOK_SQRT){
        next_token();
        if(current.type!=TOK_LPAREN){ error=ERR_SYNTAX; return 0.0; }
        next_token();
        double v=parse_expr();
        if(v<0){ error=ERR_NEG_ROOT; return 0.0; }
        if(current.type!=TOK_RPAREN){ error=ERR_PAREN; return 0.0; }
        next_token();
        return sqrt(v);
    }

    if(current.type==TOK_ROOT){
        next_token();
        if(current.type!=TOK_LPAREN){ error=ERR_SYNTAX; return 0.0; }
        next_token();
        double degree=parse_expr();
        if(current.type!=TOK_COMMA){ error=ERR_SYNTAX; return 0.0; }
        next_token();
        double value=parse_expr();
        if(current.type!=TOK_RPAREN){ error=ERR_PAREN; return 0.0; }
        next_token();
        if((int)degree%2==0 && value<0){ error=ERR_NEG_ROOT; return 0.0; }
        return pow(value,1.0/degree);
    }

    error=ERR_SYNTAX;
    return 0.0;
}

double parse_power(){
    double v = parse_factor();
    if(check_overflow(v)) return 0.0;
    while(current.type == TOK_POW){
        next_token();
        double rhs = parse_power();
        if(v==0 && rhs==0){ error=ERR_RANGE; return 0.0; }
        if(v<0 && fabs(rhs-round(rhs))>1e-9){ error=ERR_RANGE; return 0.0; }
        v = pow(v, rhs);
        if(check_overflow(v)) return 0.0;
    }
    return v;
}

double parse_term(){
    double v = parse_power();
    if(check_overflow(v)) return 0.0;
    while(current.type==TOK_MUL || current.type==TOK_DIV || current.type==TOK_MOD){
        TokenType op=current.type;
        next_token();
        double rhs = parse_power();
        if((op==TOK_DIV || op==TOK_MOD) && fabs(rhs) < 1e-12){ 
            error=ERR_DIV_ZERO; 
            return 0.0; 
        }
        if(op==TOK_MUL) {
            v *= rhs;
        }
        else if(op==TOK_DIV) {
            v /= rhs;
        }
        else {
            if(fabs(rhs - round(rhs)) > 1e-9 || fabs(v - round(v)) > 1e-9){
                error = ERR_SYNTAX;
                return 0.0;
            }
            v = fmod(v, rhs);
            if(v < 0) {
                v += fabs(rhs);
            }
        }

        if(check_overflow(v)) return 0.0;
    }
    return v;
}

double parse_expr(){
    double v = parse_term();
    if(check_overflow(v)) return 0.0;
    while(current.type==TOK_PLUS || current.type==TOK_MINUS){
        TokenType op=current.type;
        next_token();
        double rhs = parse_term();
        if(op==TOK_PLUS) v += rhs;
        else v -= rhs;
        if(check_overflow(v)) return 0.0;
    }
    return v;
}

int validate_and_eval(const char* expr,double* result){
    input=expr;
    pos=0;
    error=ERR_NONE;
    next_token();
    *result=parse_expr();
    if(current.type!=TOK_END) error=ERR_SYNTAX;
    return error==ERR_NONE;
} 

