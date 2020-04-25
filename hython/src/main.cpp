#include <iostream>
#include <hlLexer.h>
#include <hlParser.h>
#include <haizei_tree.h>
#include <haizei_runtime.h>

haizei::ASTree init(int argc, char *argv[]) {
    pANTLR3_INPUT_STREAM input;
    phlLexer lex;
    pANTLR3_COMMON_TOKEN_STREAM tokens;
    phlParser parser;
    assert(argc > 1);
    input = antlr3FileStreamNew((pANTLR3_UINT8)argv[1], ANTLR3_ENC_8BIT);
    lex = hlLexerNew(input);
    tokens = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lex));
    parser = hlParserNew(tokens);
    hlParser_prog_return r = parser->prog(parser);
    return r.tree;
}

void check(haizei::ASTree &tree) {
    std::cout << tree.text() << " " << tree.type() << std::endl;
    for (int i = 0; i < tree.size(); i++) {
        check(tree.at(i));
    }
    return ;
}

int main(int argc, char *argv[]) {
    haizei::ASTree tree = init(argc, argv);
    haizei::RunTimeEnv env(tree);
    env.run();
    return 0;
}