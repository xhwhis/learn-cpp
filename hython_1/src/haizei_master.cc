#include <iostream>
#include <haizei_master.h>
#include <haizei_tree.h>
#include <haizei_runtime.h>
#include <haizei_visitor.h>
#include <haizei_parameter.h>
#include <haizei_util.h>

namespace haizei {
    IMaster::IMaster(ASTree &tree, Parameter *p) : tree(tree), p(p) {}
    IMaster::~IMaster() {}
    
    PrintMaster::PrintMaster(ASTree &tree, Parameter *p) : IMaster(tree, p) {}
    ExprMaster::ExprMaster(ASTree &tree, Parameter *p) : IMaster(tree, p) {}
    BlockMaster::BlockMaster(ASTree &tree, Parameter *p) : IMaster(tree, p) {}
    ControlMaster::ControlMaster(ASTree &tree, Parameter *p) : IMaster(tree, p) {}

    void IMaster::IFactory::destory(IMaster *m) { delete m; }
    
    IValue *PrintMaster::run() {
        if (tree.type() != PRINT) {
            throw std::runtime_error("tree type is not print!");
        }
        for (int i = 0, I = tree.size(); i < I; i++) {
            auto child_tree = tree.at(i);
            IValue *ret = RunTimeEnv::GetValue(child_tree, p);
            ConvertStringVisitor vis;
            ret->accept(&vis);
            if (i) std::cout << " ";
            std::cout << vis.result;
        }
        std::cout << std::endl;
        return haizei::null_val;
    }
    
    IValue *ExprMaster::run() {
        switch (tree.type()) {
            case INT: {
                const char* s = this->tree.text().c_str();
                int val_int;
                sscanf(s, "%d", &val_int);
                return new IntValue(val_int);
            }
            case FLOAT: {
                const char* s = this->tree.text().c_str();
                double val_float;
                sscanf(s, "%lf", &val_float);
                return new FloatValue(val_float);
            }
            case STRING: {
                std::string tmp = this->tree.text();
                return new StringValue(tmp.substr(1, tmp.size() - 2));
            }
            case ID: {
                return this->p->get(this->tree.text());
            }
            case PLUS: {
                IValue *a = RunTimeEnv::GetValue(tree.at(0), p);
                IValue *b = RunTimeEnv::GetValue(tree.at(1), p);
                return (*a) + (*b);
            }
            case MINUS: {
                IValue *a = RunTimeEnv::GetValue(tree.at(0), p);
                IValue *b = RunTimeEnv::GetValue(tree.at(1), p);
                return (*a) - (*b);
            }
            case TIMES: {
                IValue *a = RunTimeEnv::GetValue(tree.at(0), p);
                IValue *b = RunTimeEnv::GetValue(tree.at(1), p);
                return (*a) * (*b);
            }
            case ASSIGN: {
                std::string var = tree.at(0).text();
                IValue *val = RunTimeEnv::GetValue(tree.at(1), p);
                p->set(var, val);
                return val;
            }
            case DEF : {
                for (int i = 0; i < tree.size(); i++) {
                    std::string var = tree.at(i).text();
                    p->define_param(var);
                    IValue *val = haizei::null_val;
                    if (tree.at(i).size()) {
                        val = RunTimeEnv::GetValue(tree.at(i).at(0), p);
                    }
                    p->set(var, val);
                }
                return haizei::null_val;
            }
            default : {
                throw std::runtime_error("tree type is not expr!");
            }
        }
        return haizei::null_val;
    }
    
    IValue *BlockMaster::run() {
        if (tree.type() != BLOCK) {
            throw std::runtime_error("tree type is not block!");
        }
        Parameter *new_p = new Parameter(p);
        for (int i = 0, I = tree.size(); i < I; i++) {
            auto child_tree = tree.at(i);
            RunTimeEnv::GetValue(child_tree, new_p);
        }
        delete new_p;
        return haizei::null_val;
    }

    IValue *ControlMaster::run() {
        switch (tree.type()) {
            case IF: {
                IValue *cond_val = RunTimeEnv::GetValue(tree.at(0), p);
                if (cond_val->isTrue()) {
                    RunTimeEnv::GetValue(tree.at(1), p);
                } else if (tree.size() == 3) {
                    RunTimeEnv::GetValue(tree.at(2), p);
                }
                return haizei::null_val;
            }
            case WHILE: {
                while (RunTimeEnv::GetValue(tree.at(0), p)->isTrue()) {
                    RunTimeEnv::GetValue(tree.at(1), p);
                }
                return haizei::null_val;
            }
            case FOR: {
                p = new Parameter(p);
                RunTimeEnv::GetValue(tree.at(0), p);
                while (RunTimeEnv::GetValue(tree.at(1), p)->isTrue()) {
                    RunTimeEnv::GetValue(tree.at(3), p);
                    RunTimeEnv::GetValue(tree.at(2), p);
                }
                p = p->next();
                return haizei::null_val;
            }
            case DOWHILE: {
                do {
                    RunTimeEnv::GetValue(tree.at(1), p);
                } while (RunTimeEnv::GetValue(tree.at(0), p)->isTrue());
                return haizei::null_val;
            }
            default: {
                throw std::runtime_error("tree type is not expr!");
            }
        }
        return haizei::null_val;
    }

    IValue *ConditionMaster::run() {
        switch (tree.type()) {
            case OR: {
                IValue *a = RunTimeEnv::GetValue(tree.at(0), p);
                if (a->isTrue()) return haizei::True_val;
                IValue *b = RunTimeEnv::GetValue(tree.at(1), p);
                if (b - >isTrue) return haizei::True_val;
                return haizei:False_val;
            }
            case AND: {
                IValue *a = RunTimeEnv::GetValue(tree.at(0), p);
                if (a->isFalse()) return haizei::False_val;
                IValue *b = RunTimeEnv::GetValue(tree.at(1), p);
                if (b->isTrue()) return haizei::True_val;
                return haizei:False_val;
            }
            case GT: {
                IValue *a = RunTimeEnv::GetValue(tree.at(0), p);
                IValue *b = RunTimeEnv::GetValue(tree.at(1), p);
                if (*a > *b) return haizei::True_val;
                return haizei:False_val;
            }
            case GE: {
                IValue *a = RunTimeEnv::GetValue(tree.at(0), p);
                IValue *b = RunTimeEnv::GetValue(tree.at(1), p);
                if (*a >= *b) return haizei::True_val;
                return haizei:False_val;
            }
            case LITTLE: {
                IValue *a = RunTimeEnv::GetValue(tree.at(0), p);
                IValue *b = RunTimeEnv::GetValue(tree.at(1), p);
                if (*a < *b) return haizei::True_val;
                return haizei:False_val;
            }
            case LE: {
                IValue *a = RunTimeEnv::GetValue(tree.at(0), p);
                IValue *b = RunTimeEnv::GetValue(tree.at(1), p);
                if (*a <= *b) return haizei::True_val;
                return haizei:False_val;
            }
            case EQ: {
                IValue *a = RunTimeEnv::GetValue(tree.at(0), p);
                IValue *b = RunTimeEnv::GetValue(tree.at(1), p);
                if (*a == *b) return haizei::True_val;
                return haizei:False_val;
            }
            case NE: {
                IValue *a = RunTimeEnv::GetValue(tree.at(0), p);
                IValue *b = RunTimeEnv::GetValue(tree.at(1), p);
                if (*a != *b) return haizei::True_val;
                return haizei:False_val;
            }
        }
    }
}
