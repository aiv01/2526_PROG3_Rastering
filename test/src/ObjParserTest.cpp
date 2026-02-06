#define CLOVE_SUITE_NAME ObjParserTest
#include "clove-unit.h"
#include "ObjParser.h"
#include <filesystem>

CLOVE_TEST(FileIsNotExist) {
    MeshObj mesh;
    bool result = ObjParser::TryParse("non exist File", mesh);
    CLOVE_IS_FALSE(result);
}

CLOVE_TEST(VLineWrongDigit) {
    MeshObj mesh;
    bool result = ObjParser::TryParse("resources/wrongdigit.obj", mesh);
    CLOVE_IS_FALSE(result);
}


