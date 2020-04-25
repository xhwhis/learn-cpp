#include <haizei_runtime.h>
#include <haizei_parameter.h>
#include <haizei_handler.h>
#include <haizei_master.h>
#include <haizei_tree.h>
#include <haizei_shared_type.h>
#include <haizei_dfa.h>

namespace haizei {
    RunTimeEnv::RunTimeEnv(ASTree *tree) : tree(tree) {}
    
    void RunTimeEnv::run() {
        SParameter p = std::make_shared<Parameter>(nullptr);
        FactoryHandler::init_factory(tree);
        DFA program(tree);
        program.run(p);
        return ;
    }
    
    SIValue RunTimeEnv::GetValue(ASTree *tree, SParameter p) {
        IMaster *m = tree->factory->create(tree, p);
        SIValue val = m->run();
        tree->factory->destory(m);
        return val;
    }
}
