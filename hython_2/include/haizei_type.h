#ifndef _HAIZEI_TYPE_H
#define _HAIZEI_TYPE_H

#include <string>
#include <haizei_shared_type.h>

namespace haizei {

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
    virtual SIValue operator+(IValue &);
    virtual SIValue operator-(IValue &);
    virtual SIValue operator*(IValue &);
    virtual SIValue operator/(IValue &);
    virtual SIValue operator%(IValue &);
    virtual SIValue operator^(IValue &);
    virtual bool operator<(IValue &) = 0;
    virtual bool operator>(IValue &);
    virtual bool operator<=(IValue &);
    virtual bool operator>=(IValue &);
    virtual bool operator==(IValue &);
    virtual bool operator!=(IValue &);
    void operator_plus_error(IValue &);
    void operator_minus_error(IValue &);
    void operator_times_error(IValue &);
    void operator_div_error(IValue &);
    void operator_mod_error(IValue &);
    void operator_power_error(IValue &);
    void operator_compare_error(IValue &);
protected:
    std::string Tname;
};

class IntValue : public IValue {
public:
    IntValue(int = 0);
    virtual void accept(IVisitor *);
    virtual bool isTrue();
    virtual SIValue operator+(IValue &);
    virtual SIValue operator-(IValue &);
    virtual SIValue operator*(IValue &);
    virtual SIValue operator/(IValue &);
    virtual SIValue operator%(IValue &);
    virtual SIValue operator^(IValue &);
    virtual bool operator<(IValue &);
    int val();
private:
    int __val;
};

class FloatValue : public IValue {
public:
    FloatValue(double = 0.0);
    virtual void accept(IVisitor *);
    virtual bool isTrue();
    virtual SIValue operator+(IValue &);
    virtual SIValue operator-(IValue &);
    virtual SIValue operator*(IValue &);
    virtual SIValue operator/(IValue &);
    virtual SIValue operator^(IValue &);
    virtual bool operator<(IValue &);
    double val();
private:
    double __val;
};

class StringValue : public IValue {
public:
    StringValue(std::string = "");
    virtual void accept(IVisitor *);
    virtual bool isTrue();
    virtual SIValue operator+(IValue &);
    virtual SIValue operator*(IValue &);
    virtual bool operator<(IValue &);
    std::string val();
private: 
    std::string __val;
};

static SIntValue null_val = std::make_shared<IntValue>(0);
static SIntValue True_val = std::make_shared<IntValue>(1);
static SIntValue False_val = std::make_shared<IntValue>(0);

}

#endif
