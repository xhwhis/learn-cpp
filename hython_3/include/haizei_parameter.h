#ifndef _HAIZEI_PARAMETER_H
#define _HAIZEI_PARAMETER_H

#include <map>
#include <string>
#include <haizei_shared_type.h>

namespace haizei {

class Parameter {
public:
    Parameter(SParameter, int = 0);
    void define_param(std::string);
    SIValue get(std::string) const;
    void set(std::string, SIValue);
    SParameter next() const;
    int pos();
private:
    mutable std::map<std::string, SIValue> memory;
    SParameter __next;
    int __pos;
};

}

#endif
