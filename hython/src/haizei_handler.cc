#include <string>
#include <stdexcept>
#include <haizei_handler.h>
#include <haizei_tree.h>
#include <haizei_factory.h>

namespace haizei {
    FactoryHandler* FactoryHandler::get() {
        if (head == nullptr) {
            head = new PrintFactoryHandler();
            head->next = new ExprFactoryHandler();
            head->next->next = new BlockFactoryHandler();
        }
        return head;
    }

    void FactoryHandler::init_factory(ASTree &tree) {
        auto p = FactoryHandler::get();
        for (; p != nullptr; p = p->next) {
            if (!p->is_valid(tree)) continue;
            p->do_factory(tree);
            break;
        }
        if (p == nullptr) {
            char str[100];
            sprintf(str, "%d", tree.type());
            throw std::runtime_error(std::string("there is no handler with ") + str);
        }
        for (int i = 0; i < tree.size(); i++) {
            FactoryHandler::init_factory(tree.at(i));
        }
        return ;
    }
    
    bool PrintFactoryHandler::is_valid(ASTree &tree) {
        switch (tree.type()) {
            case PRINT: return true;
            default : return false;
        }
        return false;
    }
    
    bool ExprFactoryHandler::is_valid(ASTree &tree) {
        switch (tree.type()) {
            case INT:
            case ID:
            case PLUS:
            case MINUS:
            case TIMES:
            case ASSIGN:
            case DEF:
                return true;
            default:
                return false;
        }
        return false;
    }
    
    bool BlockFactoryHandler::is_valid(ASTree &tree) {
        switch (tree.type()) {
            case BLOCK: return true;
            default : return false;
        }
        return false;
    }

    void PrintFactoryHandler::do_factory(ASTree &tree) {  
        tree.factory = factory;
        return ;
    }
    
    void ExprFactoryHandler::do_factory(ASTree &tree) {
        tree.factory = factory;
        return ;
    }
    
    void BlockFactoryHandler::do_factory(ASTree &tree) {
        tree.factory = factory;
        return ;
    }

    BlockFactory *BlockFactoryHandler::factory = new BlockFactory();
    ExprFactory *ExprFactoryHandler::factory = new ExprFactory();
    PrintFactory *PrintFactoryHandler::factory = new PrintFactory();
    FactoryHandler *FactoryHandler::head = nullptr;
}
