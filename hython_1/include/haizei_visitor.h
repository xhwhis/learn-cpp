#ifndef _HAIZEI_VISITOR_H
#define _HAIZEI_VISITOR_H

#include <haizei_type.h>

namespace haizei {

class ConvertStringVisitor : public IValue::IVisitor {
public:
    void visit(IntValue *);
    void visit(FloatValue *);
    void visit(StringValue *);
    std::string result;
};

class ValueOperator : public IValue::IVisitor {
public:
    typedef void (IValue::*op_type)(IValue &);
    ValueOperator(IValue *, op_type);
    void visit(IntValue *);
    void visit(FloatValue *);
    void visit(StringValue *);
    op_type op;
    IValue *lvalue, *result;
};

class IntValueOperator : public ValueOperator {
public:
    IntValueOperator(IntValue *, op_type);
    IntValue *left;
};

class FloatValueOperator : public ValueOperator {
public:
    FloatValueOperator(FloatValue *, op_type);
    FloatValue *left;
};

class StringValueOperator : public ValueOperator {
public:
    StringValueOperator(StringValue *, op_type);
    StringValue *left;
};

class IntValuePlusOpVisitor : public IntValueOperator {
public:
    IntValuePlusOpVisitor(IntValue *);
    void visit(IntValue *);
    void visit(FloatValue *);
};

class IntValueMinusOpVisitor : public IntValueOperator {
public:
    IntValueMinusOpVisitor(IntValue *);
    void visit(IntValue *);
    void visit(FloatValue *);
};

class IntValueTimesOpVisitor : public IntValueOperator {
public:
    IntValueTimesOpVisitor(IntValue *);
    void visit(IntValue *);
    void visit(FloatValue *);
};

class FloatValuePlusOpVisitor : public FloatValueOperator {
public:
    FloatValuePlusOpVisitor(FloatValue *);
    void visit(IntValue *);
    void visit(FloatValue *);
};

class FloatValueMinusOpVisitor : public FloatValueOperator {
public:
    FloatValueMinusOpVisitor(FloatValue *);
    void visit(IntValue *);
    void visit(FloatValue *);
};

class FloatValueTimesOpVisitor : public FloatValueOperator {
public:
    FloatValueTimesOpVisitor(FloatValue *);
    void visit(IntValue *);
    void visit(FloatValue *);
};

class StringValuePlusOpVisitor : public StringValueOperator {
public:
    StringValuePlusOpVisitor(StringValue *);
    void visit(IntValue *);
    void visit(FloatValue *);
    void visit(StringValue *);
};

class StringValueTimesOpVisitor : public StringValueOperator {
public:
    StringValueTimesOpVisitor(StringValue *);
    void visit(IntValue *);
};

}

#endif