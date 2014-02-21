#ifndef CALCULATE_H
#define CALCULATE_H
#include "expression.h"
#include "mainwindow.h"

enum CALC_ERRORS{BAD_OPEN, COULDNT_SAVE};

namespace Calculate
{
    QString process(string &input,expression list[]);
    void normalize(string &input);
    QString doCommand(string &input,expression *list);
    void assignment(string &input,expression *list, char result);
};

#endif // CALCULATE_H
