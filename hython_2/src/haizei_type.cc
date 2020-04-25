#include <iostream>
#include <haizei_type.h>
#include <haizei_visitor.h>

namespace haizei {
    IValue::IValue(std::string Tname) : Tname(Tname) {}
    std::string IValue::type() { return this->Tname; }

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
    bool IValue::isFalse() { return !(this->isTrue()); }

    SIValue IValue::operator+(IValue &obj) {
        this->operator_plus_error(obj);
        return haizei::null_val;
    }
    SIValue IValue::operator-(IValue &obj) {
        this->operator_minus_error(obj);
        return haizei::null_val;
    }
    SIValue IValue::operator*(IValue &obj) {
        this->operator_times_error(obj);
        return haizei::null_val;
    }
    SIValue IValue::operator/(IValue &obj) {
        this->operator_div_error(obj);
        return haizei::null_val;
    }
    SIValue IValue::operator%(IValue &obj) {
        this->operator_mod_error(obj);
        return haizei::null_val;
    }
    SIValue IValue::operator^(IValue &obj) {
        this->operator_power_error(obj);
        return haizei::null_val;
    }
    bool IValue::operator>(IValue &obj) {
        return obj < (*this);
    }
    bool IValue::operator<=(IValue &obj) {
        return !(obj < (*this));
    }
    bool IValue::operator>=(IValue &obj) {
        return !((*this) < obj);
    }
    bool IValue::operator==(IValue &obj) {
        return !((*this) != obj);
    }
    bool IValue::operator!=(IValue &obj) {
        return ((*this) < obj || obj < (*this));
    }
    
    void IValue::operator_plus_error(IValue &obj) {
        std::string msg = "\nnot support operator (";
        msg += this->type() + " + " + obj.type() + ")";
        throw std::runtime_error(msg);
        return ; 
    }
    
    void IValue::operator_minus_error(IValue &obj) {
        std::string msg = "\nnot support operator (";
        msg += this->type() + " - " + obj.type() + ")";
        throw std::runtime_error(msg);
        return ; 
    }

    void IValue::operator_times_error(IValue &obj) {
        std::string msg = "\nnot support operator (";
        msg += this->type() + " * " + obj.type() + ")";
        throw std::runtime_error(msg);
        return ;
    }
    
    void IValue::operator_div_error(IValue &obj) {
        std::string msg = "\nnot support operator (";
        msg += this->type() + " / " + obj.type() + ")";
        throw std::runtime_error(msg);
        return ;
    }
    
    void IValue::operator_mod_error(IValue &obj) {
        std::string msg = "\nnot support operator (";
        msg += this->type() + " % " + obj.type() + ")";
        throw std::runtime_error(msg);
        return ;
    }
    
    void IValue::operator_power_error(IValue &obj) {
        std::string msg = "\nnot support operator (";
        msg += this->type() + " ** " + obj.type() + ")";
        throw std::runtime_error(msg);
        return ;
    }
    
    void IValue::operator_compare_error(IValue &obj) {
        std::string msg = "\n(" + this->type() + " vs " + obj.type();
        msg += ") can not be compared!";
        throw std::runtime_error(msg);
        return ;
    }
    
    // IntValue operator
    bool IntValue::isTrue() {
        return this->val() != 0;
    }
    SIValue IntValue::operator+(IValue &obj) {
        IntValuePlusOpVisitor vis(this);
        obj.accept(&vis);
        return vis.result;
    }
    SIValue IntValue::operator-(IValue &obj) {
        IntValueMinusOpVisitor vis(this);
        obj.accept(&vis);
        return vis.result;
    }
    SIValue IntValue::operator*(IValue &obj) {
        IntValueTimesOpVisitor vis(this);
        obj.accept(&vis);
        return vis.result;
    }
    SIValue IntValue::operator/(IValue &obj) {
        IntValueDivOpVisitor vis(this);
        obj.accept(&vis);
        return vis.result;
    }
    SIValue IntValue::operator%(IValue &obj) {
        IntValueModOpVisitor vis(this);
        obj.accept(&vis);
        return vis.result;
    }
    SIValue IntValue::operator^(IValue &obj) {
        IntValuePowerOpVisitor vis(this);
        obj.accept(&vis);
        return vis.result;
    }
    bool IntValue::operator<(IValue &obj) {
        IntValueLittleOpVisitor vis(this);
        obj.accept(&vis);
        return vis.result->isTrue();
    }
    
    // FloatValue operator
    bool FloatValue::isTrue() {
        return this->val() != 0.0;
    }
    SIValue FloatValue::operator+(IValue &obj) {
        FloatValuePlusOpVisitor vis(this);
        obj.accept(&vis);
        return vis.result;
    }
    SIValue FloatValue::operator-(IValue &obj) {
        FloatValueMinusOpVisitor vis(this);
        obj.accept(&vis);
        return vis.result;
    }
    SIValue FloatValue::operator*(IValue &obj) {
        FloatValueTimesOpVisitor vis(this);
        obj.accept(&vis);
        return vis.result;
    }
    SIValue FloatValue::operator/(IValue &obj) {
        FloatValueDivOpVisitor vis(this);
        obj.accept(&vis);
        return vis.result;
    }
    SIValue FloatValue::operator^(IValue &obj) {
        FloatValuePowerOpVisitor vis(this);
        obj.accept(&vis);
        return vis.result;
    }
    bool FloatValue::operator<(IValue &obj) {
        FloatValueLittleOpVisitor vis(this);
        obj.accept(&vis);
        return vis.result->isTrue();
    }

    //StringValue operator
    bool StringValue::isTrue() {
        return this->val() != "";
    }
    SIValue StringValue::operator+(IValue &obj) {
        StringValuePlusOpVisitor vis(this);
        obj.accept(&vis);
        return vis.result;
    }
    SIValue StringValue::operator*(IValue &obj) {
        StringValueTimesOpVisitor vis(this);
        obj.accept(&vis);
        return vis.result;
    }
    bool StringValue::operator<(IValue &obj) {
        StringValueLittleOpVisitor vis(this);
        obj.accept(&vis);
        return vis.result->isTrue();
    }
}
