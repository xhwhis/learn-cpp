#include <iostream>
#include <haizei_master.h>
#include <haizei_tree.h>
#include <haizei_runtime.h>
#include <haizei_visitor.h>
#include <haizei_parameter.h>

namespace haizei {
    IMaster::IMaster(ASTree &tree, Parameter *p) : tree(tree), p(p) {}
    IMaster::~IMaster() {}
    
    PrintMaster::PrintMaster(ASTree &tree, Parameter *p) : IMaster(tree, p) {}
    ExprMaster::ExprMaster(ASTree &tree, Parameter *p) : IMaster(tree, p) {}
    BlockMaster::BlockMaster(ASTree &tree, Parameter *p) : IMaster(tree, p) {}

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
            std::cout << vis.string_res;
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
}