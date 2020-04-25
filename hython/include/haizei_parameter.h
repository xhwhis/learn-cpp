#ifndef _HAIZEI_PARAMETER_H
#define _HAIZEI_PARAMETER_H

#include <map>
#include <string>

namespace haizei {

class IValue;

class Parameter {
public:
    Parameter(Parameter *next = nullptr);
    void define_param(std::string);
    IValue *get(std::string) const;
    void set(std::string, IValue *);
private:
    mutable std::map<std::string, IValue *> memory;
    Parameter *next;
};

}

#endif