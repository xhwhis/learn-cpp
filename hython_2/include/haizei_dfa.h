#ifndef _HAIZEI_DFA_H
#define _HAIZEI_DFA_H

#include <haizei_shared_type.h>
#include <vector>

namespace haizei {

class IDFANode {
public:
    IDFANode(ASTree *, int);
    virtual IDFANode *next(SParameter &) = 0;
    IDFANode *&at(int);
protected:
    ASTree *tree;
    std::vector<IDFANode *> child;
};

class DFA {
public:
    DFA(ASTree *);
    void run(SParameter &);
private:
    DFA();
    DFA *build(ASTree *);
    IDFANode *head, *tail;
};

class DFANode_1 : public IDFANode {
public:
    DFANode_1(ASTree *);
    virtual IDFANode *next(SParameter &) = 0;
};

class DFANode_2 : public IDFANode {
public:
    DFANode_2(ASTree *);
    virtual IDFANode *next(SParameter &) = 0;
};

class ExprDFANode : public DFANode_1 {
public:
    ExprDFANode(ASTree *);
    virtual IDFANode *next(SParameter &);
};

class BlockBeginDFANode : public DFANode_1 {
public:
    BlockBeginDFANode();
    virtual IDFANode *next(SParameter &);
};

class BlockEndDFANode : public DFANode_1 {
public:
    BlockEndDFANode();
    virtual IDFANode *next(SParameter &);
};

class ConditionDFANode : public DFANode_2 {
public:
    ConditionDFANode(ASTree *);
    virtual IDFANode *next(SParameter &);
};

class NopeDFANode : public DFANode_1 {
public:
    NopeDFANode();
    virtual IDFANode *next(SParameter &);
};

}

#endif
