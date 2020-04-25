#ifndef _HAIZEI_TYPE_H
#define _HAIZEI_TYPE_H

#include <string>

namespace haizei {

class IntValue;
class FloatValue;
class StringValue;

class IValue {
public:
    class IVisitor {
    public:
        virtual void visit(IntValue *) = 0;
        virtual void visit(FloatValue *) = 0;
        virtual void visit(StringValue *) = 0;
    };
    virtual void accept(IVisitor *) = 0;
    virtual IValue* operator+(IValue &) = 0;
    virtual IValue* operator-(IValue &) = 0;
    virtual IValue* operator*(IValue &) = 0;
    virtual ~IValue();
};

class IntValue : public IValue {
public:
    IntValue();
    IntValue(int);
    virtual void accept(IVisitor *);
    IValue* operator+(IValue &);
    IValue* operator-(IValue &);
    IValue* operator*(IValue &);
    int getVal();
    void setVal(int val);
private:
    int __val;
};

class FloatValue : public IValue {
public:
    FloatValue();
    FloatValue(double);
    virtual void accept(IVisitor *);
    IValue* operator+(IValue &);
    IValue* operator-(IValue &);
    IValue* operator*(IValue &);
    double getVal();
    void setVal(double);
private:
    double __val;
};

class StringValue : public IValue {
public:
    StringValue();
    StringValue(std::string);
    virtual void accept(IVisitor *);
    IValue* operator+(IValue &);
    IValue* operator-(IValue &);
    IValue* operator*(IValue &);
    std::string getVal();
    void setVal(std::string);
private: 
    std::string __val;
};

static IntValue *null_val = new IntValue(0);

}

#endif