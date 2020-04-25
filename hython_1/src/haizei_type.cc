#include <iostream>
#include <haizei_type.h>
#include <haizei_visitor.h>

namespace haizei {
    IValue::IValue(std::string Tname) : Tname(Tname) {}
    std::string IValue::type() { return this->Tname; }
    IValue::~IValue() {}
    
    // visitor function
    void IntValue::accept(IVisitor *vis) { vis->visit(this); }
    void FloatValue::accept(IVisitor *vis) { vis->visit(this); }
    void StringValue::accept(IVisitor *vis) { vis->visit(this); }

    // convert constructor
    IntValue::IntValue(int x) : IValue("int"), __val(x) {}
    FloatValue::FloatValue(double x) : IValue("float"), __val(x) {}
    StringValue::StringValue(std::string x) : IValue("string"), __val(x) {}

    // get value function
    int IntValue::val() { return __val; }
    double FloatValue::val() { return __val; }
    std::string StringValue::val() { return __val; }
    
    // IValue operator
    IValue *IValue::operator+(IValue &obj) {
        this->operator_plus_error(obj);
        return haizei::null_val;
    }

    IValue *IValue::operator-(IValue &obj) {
        this->operator_minus_error(obj);
        return haizei::null_val;
    }
    
    IValue *IValue::operator*(IValue &obj) {
        this->operator_times_error(obj);
        return haizei::null_val;
    }

    void IValue::operator_plus_error(IValue &obj) {
        std::string msg = "not support operator (";
        msg += this->Tname + " + " + obj.Tname + ")";
        throw std::runtime_error(msg);
        return ; 
    }
    
    void IValue::operator_minus_error(IValue &obj) {
        std::string msg = "not support operator (";
        msg += this->type() + " - " + obj.type() + ")";
        throw std::runtime_error(msg);
        return ; 
    }

    void IValue::operator_times_error(IValue &obj) {
        std::string msg = "not support operator (";
        msg += this->Tname + " * " + obj.Tname + ")";
        throw std::runtime_error(msg);
        return ;
    }
    
    // IntValue operator
    IValue *IntValue::operator+(IValue &obj) {
        IntValuePlusOpVisitor vis(this);
        obj.accept(&vis);
        return vis.result;
    }
    IValue *IntValue::operator-(IValue &obj) {
        IntValueMinusOpVisitor vis(this);
        obj.accept(&vis);
        return vis.result;
    }
    IValue *IntValue::operator*(IValue &obj) {
        IntValueTimesOpVisitor vis(this);
        obj.accept(&vis);
        return vis.result;
    }
    
    // FloatValue operator
    IValue *FloatValue::operator+(IValue &obj) {
        FloatValuePlusOpVisitor vis(this);
        obj.accept(&vis);
        return vis.result;
    }
    IValue *FloatValue::operator-(IValue &obj) {
        FloatValueMinusOpVisitor vis(this);
        obj.accept(&vis);
        return vis.result;
    }
    IValue *FloatValue::operator*(IValue &obj) {
        FloatValueTimesOpVisitor vis(this);
        obj.accept(&vis);
        return vis.result;
    }

    //StringValue operator
    IValue *StringValue::operator+(IValue &obj) {
        StringValuePlusOpVisitor vis(this);
        obj.accept(&vis);
        return vis.result;
    }
    IValue *StringValue::operator*(IValue &obj) {
        StringValueTimesOpVisitor vis(this);
        obj.accept(&vis);
        return vis.result;
    }

    virtual IValue *operator>(IValue &obj) {
        return *this > obj;
    }
    virtual IValue *operator<(IValue &obj) {
        return *this < obj;
    }
    virtual IValue *operator>=(IValue &obj) {
        return !(*this < obj);
    }
    virtual IValue *operator<=(IValue &obj) {
        return !(*this > obj);
    }
    virtual IValue *operator==(IValue &obj) {
        return !(*this != obj);
    }
    virtual IValue *operator!=(IValue &obj) {
        return (*this < obj || *this > obj);
    } :NERDTreeToggle

}
