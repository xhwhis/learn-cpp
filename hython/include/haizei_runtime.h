#ifndef _HAIZEI_RUNTIME_H
#define _HAIZEI_RUNTIME_H

namespace haizei {

class ASTree;
class Parameter;
class IValue;

class RunTimeEnv {
public:
    RunTimeEnv(ASTree &);
    void run();
    static IValue *GetValue(ASTree &, Parameter *);
private:
    ASTree& tree;
};

}

#endif