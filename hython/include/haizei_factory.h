#ifndef _HAIZEI_FACTORY_H
#define _HAIZEI_FACTORY_H

#include <haizei_master.h>

namespace haizei {

class PrintFactory : public IMaster::IFactory {
    virtual IMaster *create(ASTree &, Parameter *);
};

class ExprFactory : public IMaster::IFactory {
    virtual IMaster *create(ASTree &, Parameter *);
};

class BlockFactory : public IMaster::IFactory {
    virtual IMaster *create(ASTree &, Parameter *);
};

}

#endif