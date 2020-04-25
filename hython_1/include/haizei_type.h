#ifndef _HAIZEI_TYPE_H
#define _HAIZEI_TYPE_H

#include <string>
#include <memory>

namespace haizei {

class IValue;
class IntValue;
class FloatValue;
class StringValue;

using SIValue = std::shared_ptr<IValue>;
using SIntValue = std::shared_ptr<IValue>;
using SFloatValue = std::shared_ptr<IValue>;
using SStringValue = std::shared_ptr<IValue>;

class IValue {
public:
    IValue(std::string);
    class IVisitor {
    public :
        virtual void visit(IntValue *) = 0;
        virtual void visit(FloatValue *) = 0;
        virtual void visit(StringValue *) = 0;
    };
    std::string type();
    virtual void accept(IVisitor *) = 0;
    virtual bool isTrue() = 0;
    virtual bool isFalse();
    virtual SIValue *operator>(IValue &);
    virtual SIValue *operator<(IValue &);
    virtual SIValue *operator>=(IValue &);
    virtual SIValue *operator<=(IValue &);
    virtual SIValue *operator==(IValue &);
    virtual SIValue *operator!=(IValue &);
    virtual SIValue *operator+(IValue &);
    virtual SIValue *operator-(IValue &);
    virtual SIValue *operator*(IValue &);
    void operator_plus_error(IValue &);
    void operator_minus_error(IValue &);
    void operator_times_error(IValue &);
    virtual ~IValue();
protected:
    std::string Tname;
};

class IntValue : public IValue {
public:
    IntValue(int = 0);
    virtual void accept(IVisitor *);
    virtual bool isTrue();
    virtual IValue *operator+(IValue &);
    virtual IValue *operator-(IValue &);
    virtual IValue *operator*(IValue &);
    int val();
private:
    int __val;
};

class FloatValue : public IValue {
public:
    FloatValue(double = 0.0);
    virtual void accept(IVisitor *);
    virtual bool isTrue();
    virtual IValue *operator+(IValue &);
    virtual IValue *operator-(IValue &);
    virtual IValue *operator*(IValue &);
    double val();
private:
    double __val;
};

class StringValue : public IValue {
public:
    StringValue(std::string = "");
    virtual void accept(IVisitor *);
    virtual bool isTrue();
    virtual IValue *operator+(IValue &);
    virtual IValue *operator*(IValue &);
    std::string val();
private: 
    std::string __val;
};

static IntValue *null_val = new IntValue(0);
static IntValue *True_val = new IntValue(1);
static IntValue *False_val = new IntValue(2);

}

#endif
