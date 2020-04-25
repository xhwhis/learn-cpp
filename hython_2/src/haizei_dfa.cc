#include <haizei_dfa.h>
#include <haizei_runtime.h>
#include <haizei_parameter.h>
#include <haizei_type.h>
#include <haizei_tree.h>

namespace haizei {
    DFA::DFA() : head(nullptr), tail(nullptr) {}
    DFA::DFA(ASTree *tree) {
        DFA *ret = DFA::build(tree);
        head = ret->head, tail = ret->tail;
    }
    
    void DFA::run(SParameter &p) {
        IDFANode *now = this->head;
        while (now) {
            now = now->next(p);
        }
        return ;
    }

    DFA *DFA::build(ASTree *tree) {
        DFA *ret = new DFA();
        switch (tree->type()) {
            case IF: {
                ret->head = new ConditionDFANode(tree->at(0));
                ret->tail = new NopeDFANode();
                DFA *temp = DFA::build(tree->at(1));
                ret->head->at(0) = temp->head;
                temp->tail->at(0) = ret->tail;
                if (tree->size() == 3) {
                    temp = DFA::build(tree->at(2));
                    ret->head->at(1) = temp->head;
                    temp->tail->at(0) = ret->tail;
                } else {
                    ret->head->at(1) = ret->tail;
                }
            } break;
            case FOR: {
                
            } break;
            case BREAK: {

            } break;
            case WHILE: {
                ret->head = new ConditionDFANode(tree->at(0));
                ret->tail = new NopeDFANode();
                DFA *temp = DFA::build(tree->at(1));
                ret->head->at(0) = temp->head;
                temp->tail->at(0) = ret->head;
                ret->head->at(1) = ret->tail;
            } break;
            case DOWHILE: {
                DFA *temp = DFA::build(tree->at(1));
                ret->head = temp->head;
                ret->tail = new NopeDFANode();
                temp->tail->at(0) = new ConditionDFANode(tree->at(0));
                temp->tail->at(0)->at(0) = ret->head;
                temp->tail->at(0)->at(1) = ret->tail;
            } break;
            case BLOCK: {
                ret->head = new BlockBeginDFANode();
                ret->tail = new BlockEndDFANode();
                IDFANode *p = ret->head;
                DFA *temp;
                for (int i = 0; i < tree->size(); i++) {
                    temp = DFA::build(tree->at(i));
                    p->at(0) = temp->head;
                    p = temp->tail;
                }
                p->at(0) = ret->tail;
            } break;
            default: {
                ret->head = ret->tail = new ExprDFANode(tree);
            } break;
        }
        return ret;
    }

    IDFANode::IDFANode(ASTree *tree, int n) : tree(tree), child(n) {}
    DFANode_1::DFANode_1(ASTree *tree) : IDFANode(tree, 1) {}
    DFANode_2::DFANode_2(ASTree *tree) : IDFANode(tree, 2) {}
    ExprDFANode::ExprDFANode(ASTree *tree) : DFANode_1(tree) {}
    BlockBeginDFANode::BlockBeginDFANode() : DFANode_1(nullptr) {}
    BlockEndDFANode::BlockEndDFANode() : DFANode_1(nullptr) {}
    ConditionDFANode::ConditionDFANode(ASTree *tree) : DFANode_2(tree) {}
    NopeDFANode::NopeDFANode() : DFANode_1(nullptr) {}

    IDFANode *&IDFANode::at(int ind) {
        return this->child[ind];
    }

    IDFANode *ExprDFANode::next(SParameter &p) {
        RunTimeEnv::GetValue(this->tree, p);
        return this->at(0);
    }

    IDFANode *BlockBeginDFANode::next(SParameter &p) {
        p = std::make_shared<Parameter>(p);
        return this->at(0);
    }
    
    IDFANode *BlockEndDFANode::next(SParameter &p) {
        p = p->next();
        return this->at(0);
    }
    
    IDFANode *ConditionDFANode::next(SParameter &p) {
        SIValue val = RunTimeEnv::GetValue(this->tree, p);
        if (val->isTrue()) return this->at(0);
        return this->at(1);
    }
    
    IDFANode *NopeDFANode::next(SParameter &p) {
        return this->at(0);
    }
}
