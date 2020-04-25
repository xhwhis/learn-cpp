#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>
#include <haizei_visitor.h>

namespace haizei {
    void ConvertStringVisitor::visit(IntValue *obj) {
        this->type = "int";
        char str[100];
        sprintf(str, "%d", obj->val());
        this->result = str;
        return ;
    }
    void ConvertStringVisitor::visit(FloatValue *obj) {
        this->type = "float";
        char str[100];
        sprintf(str, "%lf", obj->val());
        this->result = str;
        return ;
    }
    void ConvertStringVisitor::visit(StringValue *obj) {
        this->type = "string";
        this->result = obj->val();
        return ;
    }
    void ConvertStringVisitor::visit(FunctionValue *obj) {
        this->type = "function";
        this->result = obj->val();
        return ;
    }
    void ConvertStringVisitor::visit(ListValue *obj) {
        std::string ret = "[";
        for (int i = 0; i < obj->val().size(); i++) {
            if (i) ret += ", ";
            ConvertStringVisitor vis;
            obj->val()[i]->accept(&vis);
            ret += vis.result;
        }
        ret += "]";
        this->type = "list";
        this->result = ret;
        return ;
    }
    
    // value operator
    ValueOperator::ValueOperator(IValue *lvalue, op_type op) : lvalue(lvalue), op(op) {}
    void ValueOperator::visit(IntValue *obj) { (lvalue->*op)(*obj); }
    void ValueOperator::visit(FloatValue *obj) { (lvalue->*op)(*obj); }
    void ValueOperator::visit(StringValue *obj) { (lvalue->*op)(*obj); }
    void ValueOperator::visit(FunctionValue *obj) { (lvalue->*op)(*obj); }
    void ValueOperator::visit(ListValue *obj) { (lvalue->*op)(*obj); }

    // type value operator
    IntValueOperator::IntValueOperator(IntValue *left, ValueOperator::op_type op) : ValueOperator(left, op), left(left) {}
    FloatValueOperator::FloatValueOperator(FloatValue *left, ValueOperator::op_type op) : ValueOperator(left, op), left(left) {}
    StringValueOperator::StringValueOperator(StringValue *left, ValueOperator::op_type op) : ValueOperator(left, op), left(left) {}
    ListValueOperator::ListValueOperator(ListValue *left, ValueOperator::op_type op) : ValueOperator(left, op), left(left) {}
    
    // IntValue operator
    IntValuePlusOpVisitor::IntValuePlusOpVisitor(IntValue *left) : IntValueOperator(left, &IValue::operator_plus_error) {}
    void IntValuePlusOpVisitor::visit(IntValue *obj) {
        this->result = std::make_shared<IntValue>(left->val() + obj->val());
        return ;
    }
    void IntValuePlusOpVisitor::visit(FloatValue *obj) {
        this->result = std::make_shared<FloatValue>(left->val() + obj->val());
        return ;
    }
    
    IntValueMinusOpVisitor::IntValueMinusOpVisitor(IntValue *left) : IntValueOperator(left, &IValue::operator_minus_error) {}
    void IntValueMinusOpVisitor::visit(IntValue *obj) {
        this->result = std::make_shared<IntValue>(left->val() - obj->val());
        return ;
    }
    void IntValueMinusOpVisitor::visit(FloatValue *obj) {
        this->result = std::make_shared<FloatValue>(left->val() - obj->val());
        return ;
    }

    IntValueTimesOpVisitor::IntValueTimesOpVisitor(IntValue *left) : IntValueOperator(left, &IValue::operator_times_error) {}
    void IntValueTimesOpVisitor::visit(IntValue *obj) {
        this->result = std::make_shared<IntValue>(left->val() * obj->val());
        return ;
    }
    void IntValueTimesOpVisitor::visit(FloatValue *obj) {
        this->result = std::make_shared<FloatValue>(left->val() * obj->val());
        return ;
    }
    void IntValueTimesOpVisitor::visit(StringValue *obj) {
        std::string ret = ""; 
        for (int i = 0, I = left->val(); i < I; i++) {
            ret += obj->val();
        }
        this->result = std::make_shared<StringValue>(ret);
        return ;
    }
    
    IntValueDivOpVisitor::IntValueDivOpVisitor(IntValue *left) : IntValueOperator(left, &IValue::operator_div_error) {}
    void IntValueDivOpVisitor::visit(IntValue *obj) {
        this->result = std::make_shared<FloatValue>(left->val() / obj->val());
        return ;
    }
    void IntValueDivOpVisitor::visit(FloatValue *obj) {
        this->result = std::make_shared<FloatValue>(left->val() / obj->val());
        return ;
    }
    
    IntValueModOpVisitor::IntValueModOpVisitor(IntValue *left) : IntValueOperator(left, &IValue::operator_mod_error) {}
    void IntValueModOpVisitor::visit(IntValue *obj) {
        this->result = std::make_shared<IntValue>(left->val() % obj->val());
        return ;
    }
    
    IntValuePowerOpVisitor::IntValuePowerOpVisitor(IntValue *left) : IntValueOperator(left, &IValue::operator_power_error) {}
    void IntValuePowerOpVisitor::visit(IntValue *obj) {
        this->result = std::make_shared<IntValue>(pow(left->val(), obj->val()));
        return ;
    }
    void IntValuePowerOpVisitor::visit(FloatValue *obj) {
        this->result = std::make_shared<FloatValue>(pow(left->val(), obj->val()));
        return ;
    }

    IntValueLittleOpVisitor::IntValueLittleOpVisitor(IntValue *left) : IntValueOperator(left, &IValue::operator_compare_error){}
    void IntValueLittleOpVisitor::visit(IntValue *obj) {
        this->result = haizei::False_val;
        if ((left->val() < obj->val())) {
            this->result = haizei::True_val;
        }
        return ;
    }
    void IntValueLittleOpVisitor::visit(FloatValue *obj) {
        this->result = haizei::False_val;
        if ((left->val() < obj->val())) {
            this->result = haizei::True_val;
        }
        return ;
    }

    // FloatValue operator
    FloatValuePlusOpVisitor::FloatValuePlusOpVisitor(FloatValue *left) : FloatValueOperator(left, &IValue::operator_plus_error) {}
    void FloatValuePlusOpVisitor::visit(IntValue *obj) {
        this->result = std::make_shared<FloatValue>(left->val() + obj->val());
        return ;
    }
    void FloatValuePlusOpVisitor::visit(FloatValue *obj) {
        this->result = std::make_shared<FloatValue>(left->val() + obj->val());
        return ;
    }

    FloatValueMinusOpVisitor::FloatValueMinusOpVisitor(FloatValue *left) : FloatValueOperator(left, &IValue::operator_minus_error) {}
    void FloatValueMinusOpVisitor::visit(IntValue *obj) {
        this->result = std::make_shared<FloatValue>(left->val() - obj->val());
        return ;
    }
    void FloatValueMinusOpVisitor::visit(FloatValue *obj) {
        this->result = std::make_shared<FloatValue>(left->val() - obj->val());
        return ;
    }
    
    FloatValueTimesOpVisitor::FloatValueTimesOpVisitor(FloatValue *left) : FloatValueOperator(left, &IValue::operator_times_error) {}
    void FloatValueTimesOpVisitor::visit(IntValue *obj) {
        this->result = std::make_shared<FloatValue>(left->val() * obj->val());
        return ;
    }
    void FloatValueTimesOpVisitor::visit(FloatValue *obj) {
        this->result = std::make_shared<FloatValue>(left->val() * obj->val());
        return ;
    }

    FloatValueDivOpVisitor::FloatValueDivOpVisitor(FloatValue *left) : FloatValueOperator(left, &IValue::operator_div_error) {}
    void FloatValueDivOpVisitor::visit(IntValue *obj) {
        this->result = std::make_shared<FloatValue>(left->val() / obj->val());
        return ;
    }
    void FloatValueDivOpVisitor::visit(FloatValue *obj) {
        this->result = std::make_shared<FloatValue>(left->val() / obj->val());
        return ;
    }
    
    FloatValuePowerOpVisitor::FloatValuePowerOpVisitor(FloatValue *left) : FloatValueOperator(left, &IValue::operator_power_error) {}
    void FloatValuePowerOpVisitor::visit(IntValue *obj) {
        this->result = std::make_shared<FloatValue>(pow(left->val(), obj->val()));
        return ;
    }
    void FloatValuePowerOpVisitor::visit(FloatValue *obj) {
        this->result = std::make_shared<FloatValue>(pow(left->val(), obj->val()));
        return ;
    }
    
    FloatValueLittleOpVisitor::FloatValueLittleOpVisitor(FloatValue *left) : FloatValueOperator(left, &IValue::operator_compare_error){}
    void FloatValueLittleOpVisitor::visit(IntValue *obj) {
        this->result = haizei::False_val;
        if ((left->val() < obj->val())) {
            this->result = haizei::True_val;
        }
        return ;
    }
    void FloatValueLittleOpVisitor::visit(FloatValue *obj) {
        this->result = haizei::False_val;
        if ((left->val() < obj->val())) {
            this->result = haizei::True_val;
        }
        return ;
    }

    // StringValue operator
    StringValuePlusOpVisitor::StringValuePlusOpVisitor(StringValue *left) : StringValueOperator(left, &IValue::operator_plus_error) {}
    void StringValuePlusOpVisitor::visit(StringValue *obj) {
        this->result = std::make_shared<StringValue>(left->val() + obj->val());
        return ;
    }

    StringValueTimesOpVisitor::StringValueTimesOpVisitor(StringValue *left) : StringValueOperator(left, &IValue::operator_times_error) {}
    void StringValueTimesOpVisitor::visit(IntValue *obj) {
        std::string ret = ""; 
        for (int i = 0, I = obj->val(); i < I; i++) {
            ret += left->val();
        }
        this->result = std::make_shared<StringValue>(ret);
        return ;
    }
    
    StringValueLittleOpVisitor::StringValueLittleOpVisitor(StringValue *left) : StringValueOperator(left, &IValue::operator_compare_error) {}
    void StringValueLittleOpVisitor::visit(StringValue *obj) {
        this->result = haizei::False_val;
        if ((left->val() < obj->val())) {
            this->result = haizei::True_val;
        }
        return ;
    }

    // ListValue operator
    ListValuePlusOpVisitor::ListValuePlusOpVisitor(ListValue *left) : ListValueOperator(left, &IValue::operator_plus_error) {}
    void ListValuePlusOpVisitor::visit(ListValue *obj) {
        std::vector<SIValue> ret = left->__val;
        ret.insert(ret.end(), obj->__val.begin(), obj->__val.end());
        this->result = std::make_shared<ListValue>(ret);
        return ;
    }

    ListValueTimesOpVisitor::ListValueTimesOpVisitor(ListValue *left) : ListValueOperator(left, &IValue::operator_times_error) {}
    void ListValueTimesOpVisitor::visit(IntValue *obj) {
        std::vector<SIValue> ret;
        for (int i = 0, I = obj->val(); i < I; i++) {
            ret.insert(ret.end(), left->__val.begin(), left->__val.end());
        }
        this->result = std::make_shared<ListValue>(ret);
        return ;
    }
}
