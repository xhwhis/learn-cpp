#include <haizei_runtime.h>
#include <haizei_parameter.h>
#include <haizei_handler.h>
#include <haizei_master.h>
#include <haizei_tree.h>

namespace haizei {
    RunTimeEnv::RunTimeEnv(ASTree &tree) : tree(tree) {}
    void RunTimeEnv::run() {
        Parameter *p = new Parameter(nullptr);
        FactoryHandler::init_factory(tree);
        RunTimeEnv::GetValue(tree, p);
        delete p;
        return ;
    }
    IValue *RunTimeEnv::GetValue(ASTree &tree, Parameter *p) {
        IMaster *m = tree.factory->create(tree, p);
        IValue *val = m->run();
        tree.factory->destory(m);
        return val;
    }
}