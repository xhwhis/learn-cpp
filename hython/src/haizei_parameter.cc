#include <stdexcept>
#include <haizei_parameter.h>
#include <haizei_type.h>

namespace haizei {
    Parameter::Parameter(Parameter *next) : next(next) {}
    
    void Parameter::define_param(std::string name) {
        if (memory.find(name) != memory.end()) {
            throw std::runtime_error("redefined param: " + name);
        }
        this->memory[name] = haizei::null_val;
        return ;
    }
    
    IValue *Parameter::get(std::string name) const {
        if (memory.find(name) == memory.end()) {
            if (this->next == nullptr) {
                throw std::runtime_error("undefined param: " + name);
            }
            return this->next->get(name);
        }
        return this->memory[name];
    }
    
    void Parameter::set(std::string name, IValue *val) {
        if (memory.find(name) == memory.end()) {
            if (this->next == nullptr) {
                throw std::runtime_error("undefined param: " + name);
            }
            this->next->set(name, val);
            return ;
        }
        this->memory[name] = val;
        return ;
    }
}