#include <haizei_type.h>
#include <haizei_visitor.h>

namespace haizei {
    IValue::~IValue() {}
    
    // visitor function
    void IntValue::accept(IVisitor *vis) { 
        vis->visit(this); 
    }
    void FloatValue::accept(IVisitor *vis) { 
        vis->visit(this); 
    }
    void StringValue::accept(IVisitor *vis) { 
        vis->visit(this); 
    }

    // default constructor
    IntValue::IntValue() { __val = 0; }
    FloatValue::FloatValue() { __val = 0.0; }
    StringValue::StringValue() { __val = ""; }

    // convert constructor
    IntValue::IntValue(int x) : __val(x) {}
    FloatValue::FloatValue(double x) : __val(x) {}
    StringValue::StringValue(std::string x) : __val(x) {}

    // get value function
    int IntValue::getVal() { return __val; }
    double FloatValue::getVal() { return __val; }
    std::string StringValue::getVal() { return __val; }
    
    // set value function
    void IntValue::setVal(int val) { __val = val; }
    void FloatValue::setVal(double val) { __val = val; }
    void StringValue::setVal(std::string val) { __val = val; }

    IValue* IntValue::operator+(IValue &obj) {
        ConvertStringVisitor vis_this, vis_obj;
        this->accept(&vis_this);
        obj.accept(&vis_obj);
        IntValue *int_val = new IntValue();
        int_val->setVal(vis_this.int_res + vis_obj.int_res);
        return int_val;
    }
    IValue* IntValue::operator-(IValue &obj) {
        ConvertStringVisitor vis_this, vis_obj;
        this->accept(&vis_this);
        obj.accept(&vis_obj);
        IntValue *int_val = new IntValue();
        int_val->setVal(vis_this.int_res - vis_obj.int_res);
        return int_val;
    }
    IValue* IntValue::operator*(IValue &obj) {
        ConvertStringVisitor vis_this, vis_obj;
        this->accept(&vis_this);
        obj.accept(&vis_obj);
        IntValue *int_val = new IntValue();
        int_val->setVal(vis_this.int_res * vis_obj.int_res);
        return int_val;
    }
    
    IValue* FloatValue::operator+(IValue &obj) {
        ConvertStringVisitor vis_this, vis_obj;
        this->accept(&vis_this);
        obj.accept(&vis_obj);
        FloatValue *float_val = new FloatValue();
        float_val->setVal(vis_this.float_res + vis_obj.float_res);
        return float_val;
    }
    IValue* FloatValue::operator-(IValue &obj) {
        ConvertStringVisitor vis_this, vis_obj;
        this->accept(&vis_this);
        obj.accept(&vis_obj);
        FloatValue *float_val = new FloatValue();
        float_val->setVal(vis_this.float_res - vis_obj.float_res);
        return float_val;
    }
    IValue* FloatValue::operator*(IValue &obj) {
        ConvertStringVisitor vis_this, vis_obj;
        this->accept(&vis_this);
        obj.accept(&vis_obj);
        FloatValue *float_val = new FloatValue();
        float_val->setVal(vis_this.float_res * vis_obj.float_res);
        return float_val;
    }
    
    IValue* StringValue::operator+(IValue &obj) {
        ConvertStringVisitor vis_this, vis_obj;
        this->accept(&vis_this);
        obj.accept(&vis_obj);
        StringValue *string_val = new StringValue();
        string_val->setVal(vis_this.string_res + vis_obj.string_res);
        return string_val;
    }
    IValue* StringValue::operator-(IValue &obj) {
        ConvertStringVisitor vis_this, vis_obj;
        this->accept(&vis_this);
        obj.accept(&vis_obj);
        StringValue *string_val = new StringValue();
        string_val->setVal(vis_this.string_res + vis_obj.string_res);
        return string_val;
    }
    IValue* StringValue::operator*(IValue &obj) {
        ConvertStringVisitor vis_this, vis_obj;
        this->accept(&vis_this);
        obj.accept(&vis_obj);
        StringValue *string_val = new StringValue();
        string_val->setVal(vis_this.string_res + vis_obj.string_res);
        return string_val;
    }
}