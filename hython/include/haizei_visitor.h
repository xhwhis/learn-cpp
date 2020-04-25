#ifndef _HAIZEI_VISITOR_H
#define _HAIZEI_VISITOR_H

#include <haizei_type.h>

namespace haizei {

class ConvertStringVisitor : public IValue::IVisitor {
public:
    void visit(IntValue *);
    void visit(FloatValue *);
    void visit(StringValue *);
    int int_res;
    double float_res;
    std::string string_res;
};

}

#endif