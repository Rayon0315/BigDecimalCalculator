#include "CalculatorEngine.h"
#include "BigDecimal.h"

std::string CalculatorEngine::calc(
    const std::string &s,
    const std::string &t,
    char op) {
    BigDecimal A = BigDecimal::convertFromString(s);
    BigDecimal B = BigDecimal::convertFromString(t);

    switch (op) {
        case '+': return (A + B).convertToString();
        case '-': return (A - B).convertToString();
        case '*': return (A * B).convertToString();
        case '/': return (A / B).convertToString();
        default: return "ERR";
    }
}
