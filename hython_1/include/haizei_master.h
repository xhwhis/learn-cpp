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
    virtual SIValue *run() = 0;
    virtual ~IMaster();
protected:
    ASTree& tree;
    Parameter *p;
};

class PrintMaster : public IMaster {
public:
    PrintMaster(ASTree &, Parameter *);
    virtual SIValue *run();
};

class ExprMaster : public IMaster {
public:
    ExprMaster(ASTree &, Parameter *);
    virtual SIValue *run();
};

class BlockMaster : public IMaster {
public:
    BlockMaster(ASTree &, Parameter *);
    virtual SIValue *run();
};

class ControlMaster : public IMaster {
public:
    ControlMaster(ASTree &, Parameter *);
    virtual SIValue *run();
};

}

#endif
