#include <iostream>
#include <sstream>
#include <haizei_type.h>
#include <haizei_visitor.h>
#include <haizei_dfa.h>
#include <haizei_tree.h>
#include <haizei_parameter.h>
#include <haizei_runtime.h>

namespace haizei {
    IValue::IValue(std::string Tname) : Tname(Tname) {}
    std::string IValue::type() { return this->Tname; }

    // visitor function
    void IntValue::accept(IVisitor *vis) { vis->visit(this); }
    void FloatValue::accept(IVisitor *vis) { vis->visit(this); }
    void StringValue::accept(IVisitor *vis) { vis->visit(this); }
    void FunctionValue::accept(IVisitor *vis) { vis->visit(this); }
    void ListValue::accept(IVisitor *vis) { vis->visit(this); }

    // convert constructor
    IntValue::IntValue(int val) : IValue("int"), __val(val) {}
    FloatValue::FloatValue(double val) : IValue("float"), __val(val) {}
    StringValue::StringValue(std::string val) : IValue("string"), __val(val) {}
    FunctionValue::FunctionValue(ASTree *tree, DFA *dfa) : IValue("function"), __val(dfa) { convert(tree); }
    ListValue::ListValue(std::vector<SIValue> val) : IValue("list"), __val(val) {}

    // get value function
    int IntValue::val() { return this->__val; }
    double FloatValue::val() { return this->__val; }
    std::string StringValue::val() { return this->__val; }
    std::vector<SIValue> ListValue::val() { return this->__val; }

    std::string FunctionValue::val() {
        std::string ret = "function " + this->func_name;
        ret += "(";
        for (int i = 0; i < this->param.size(); i++) {
            if (i) ret += ", ";
            ret += this->param[i];
        }
        ret += ")";
        return ret;
    }

    // IValue operator
    bool IValue::isFalse() { return !(this->isTrue()); }

    SIValue IValue::run(SParameter &p, ASTree *tree) {
        std::string msg = this->type() + " is not callable.";
        throw std::runtime_error(msg);
        return haizei::False_val;
    }
    SIValue IValue::at(SIValue &obj) {
        std::string msg = this->type() + " is not callable.";
        throw std::runtime_error(msg);
        return haizei::False_val;
    }
    void IValue::assign(SIValue &ind, SIValue &val) {
        std::string msg = this->type() + " is not callable.";
        throw std::runtime_error(msg);
        return ;
    }
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
    bool IValue::operator<(IValue &obj) {
        this->operator_compare_error(obj);
        return false;
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
    


    // FunctionValue operator
    bool FunctionValue::isTrue() { return true; }
    std::string FunctionValue::name() { return this->func_name; }
    void FunctionValue::convert(ASTree *tree) {
        this->func_name = tree->at(0)->text();
        this->param.clear();
        for (int i = 0, I = tree->at(1)->size(); i < I; i++) {
            this->param.push_back(tree->at(1)->at(i)->text());
        }
        return ;
    }
    void FunctionValue::set_param(SParameter init_param) {
        this->init_param = init_param;
    }
    SIValue FunctionValue::run(SParameter &p, ASTree *tree) {
        this->init_param = std::make_shared<Parameter>(this->init_param);
        if (tree->size() != this->param.size()) {
            std::string msg;
            std::stringstream out(msg);
            out << this->name() << " call is wrong" << std::endl;
            out << " expect " << this->param.size() << " param, but ";
            out << tree->size() << " given." << std::endl;
            throw std::runtime_error(msg);
            return haizei::null_val;
        }
        for (int i = 0; i < tree->size(); i++) {
            this->init_param->define_param(this->param[i]);
            this->init_param->set(this->param[i], RunTimeEnv::GetValue(tree->at(i), p->next()));
        }
        this->init_param->define_param(haizei::Return_val);
        this->init_param->set(haizei::Return_val, haizei::null_val);
        this->__val->run(this->init_param);
        SIValue retValue = this->init_param->get(haizei::Return_val);
        this->init_param = this->init_param->next();
        return retValue;
    }

    // ListValue operatorvirtual SIValue operator+(IValue &);
    bool ListValue::isTrue() {
        return this->__val.size() != 0;
    }
    SIValue ListValue::at(SIValue &obj) {
        ConvertStringVisitor vis;
        obj->accept(&vis);
        if (vis.type != "int") {
            throw std::runtime_error("list indices must be integers");
        }
        int ind = stoi(vis.result);
        if (ind >= this->__val.size()) {
            throw std::runtime_error("list index out of range");
        }
        return this->__val[ind];
    }
    void ListValue::assign(SIValue &obj, SIValue &val) {
        ConvertStringVisitor vis;
        obj->accept(&vis);
        int ind = stoi(vis.result);
        if (ind >= this->__val.size()) {
            throw std::runtime_error("list assignment index out of range");
        }
        this->__val[ind] = val;
        return ;
    }

    SIValue ListValue::operator+(IValue &obj) {
        ListValuePlusOpVisitor vis(this);
        obj.accept(&vis);
        return vis.result;
    }
    
    SIValue ListValue::operator*(IValue &obj) {
        ListValueTimesOpVisitor vis(this);
        obj.accept(&vis);
        return vis.result;
    }
}
