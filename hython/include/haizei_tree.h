#ifndef _HAIZEI_TREE_H
#define _HAIZEI_TREE_H

#include <vector>
#include <string>
#include <hlLexer.h>
#include <hlParser.h>
#include <haizei_master.h>

namespace haizei {

class ASTree {
public:
    ASTree(pANTLR3_BASE_TREE tree);
    int size() const;
    ASTree &at(int ind);
    std::string text() const;
    int type() const;
    IMaster::IFactory *factory;
private:
    pANTLR3_BASE_TREE tree;
    int __type, __size;
    std::vector<ASTree> child;
};

}

#endif