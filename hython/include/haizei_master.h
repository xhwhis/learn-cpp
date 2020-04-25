#ifndef _HAIZEI_MASTER_H
#define _HAIZEI_MASTER_H

namespace haizei {

class ASTree;
class Parameter;
class IValue;

class IMaster {
public:
    IMaster(ASTree &, Parameter *);
    class IFactory {
    public:
        virtual IMaster *create(ASTree &, Parameter *) = 0;
        virtual void destory(IMaster *);
    };
    virtual IValue *run() = 0;
    virtual ~IMaster();
protected:
    ASTree& tree;
    Parameter *p;
};

class PrintMaster : public IMaster {
public:
    PrintMaster(ASTree &, Parameter *);
    virtual IValue *run();
};

class ExprMaster : public IMaster {
public:
    ExprMaster(ASTree &, Parameter *);
    virtual IValue *run();
};

class BlockMaster : public IMaster {
public:
    BlockMaster(ASTree &, Parameter *);
    virtual IValue *run();
};

}

#endif