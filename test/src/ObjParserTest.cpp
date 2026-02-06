#define CLOVE_SUITE_NAME ObjParserTest
#include "clove-unit.h"
#include "ObjParser.h"

CLOVE_TEST(FileIsNotExist) {
    MeshObj mesh;
    bool result = ObjParser::TryParse("non exist File", mesh);
    CLOVE_IS_FALSE(result);
}