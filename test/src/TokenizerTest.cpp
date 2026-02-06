#define CLOVE_SUITE_NAME TokenizerTest
#include "clove-unit.h"
#include "ObjParser.h"

CLOVE_TEST(Split4Tokens) {

    auto tokens = Tokenizer::Split("v -1.000000 1.000000 0.000000",' ');

    CLOVE_SIZET_EQ(4,tokens.size()); // bullet-proof test

    CLOVE_STRING_EQ("v",tokens[0].c_str());
    CLOVE_STRING_EQ("-1.000000",tokens[1].c_str());
    CLOVE_STRING_EQ("1.000000",tokens[2].c_str());
    CLOVE_STRING_EQ("0.000000",tokens[3].c_str());
    
    
}