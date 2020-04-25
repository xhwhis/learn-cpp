#include <cstdio>
#include <cstdlib>
#include <string>
#include <haizei_visitor.h>

namespace haizei {
    void ConvertStringVisitor::visit(IntValue *obj) {
        this->int_res = obj->getVal();
        char str[100];
        sprintf(str, "%d", obj->getVal());
        this->string_res = str;
        return ;
    }
    
    void ConvertStringVisitor::visit(FloatValue *obj) {
        this->float_res = obj->getVal();
        char str[100];
        sprintf(str, "%lf", obj->getVal());
        this->string_res = str;
        return ;
    }
    
    void ConvertStringVisitor::visit(StringValue *obj) {
        this->string_res = obj->getVal();
        return ;
    }
}