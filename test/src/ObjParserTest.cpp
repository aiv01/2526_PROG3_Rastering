#define CLOVE_SUITE_NAME ObjParserTest
#include "clove-unit.h"
#include "ObjParser.h"

CLOVE_TEST(FileDoesNotExist)
{
   Obj obj;
   bool result = ObjParser::TryParse("non_existent_file.obj", obj);

   CLOVE_IS_FALSE(result);
}

CLOVE_TEST(VertexLineWithWrongDigit) {
    Obj mesh;
    bool result = ObjParser::TryParse("resources/wrongdigit.obj", mesh);
    CLOVE_IS_FALSE(result);
}

CLOVE_TEST(ParseQuadObj){
   Obj obj;
   std::string objPath = "resources/quad.obj";
    
   bool result = ObjParser::TryParse(objPath, obj);

   CLOVE_IS_TRUE(result);
   
   CLOVE_SIZET_EQ(2, obj.triangles.size());
   
   //Tiangle 1

   //Vertex 1
   CLOVE_FLOAT_EQ(1.000000, obj.triangles[0].v1.point.x);
   CLOVE_FLOAT_EQ(-1.000000, obj.triangles[0].v1.point.y);
   CLOVE_FLOAT_EQ(0.000000, obj.triangles[0].v1.point.z);

   CLOVE_FLOAT_EQ(1.000000, obj.triangles[0].v1.uv.x);
   CLOVE_FLOAT_EQ(0.000000, obj.triangles[0].v1.uv.y);

   CLOVE_FLOAT_EQ(0.000000, obj.triangles[0].v1.normal.x);
   CLOVE_FLOAT_EQ(0.000000, obj.triangles[0].v1.normal.y);
   CLOVE_FLOAT_EQ(1.000000, obj.triangles[0].v1.normal.z);

   //Vertex 2
   CLOVE_FLOAT_EQ(-1.000000, obj.triangles[0].v2.point.x);
   CLOVE_FLOAT_EQ(-1.000000, obj.triangles[0].v2.point.y);
   CLOVE_FLOAT_EQ(0.000000, obj.triangles[0].v2.point.z);

   CLOVE_FLOAT_EQ(0.000000, obj.triangles[0].v2.uv.x);
   CLOVE_FLOAT_EQ(0.000000, obj.triangles[0].v2.uv.y);

   CLOVE_FLOAT_EQ(0.000000, obj.triangles[0].v2.normal.x);
   CLOVE_FLOAT_EQ(0.000000, obj.triangles[0].v2.normal.y);
   CLOVE_FLOAT_EQ(1.000000, obj.triangles[0].v2.normal.z);

   //Vertex 3
   CLOVE_FLOAT_EQ(-1.000000, obj.triangles[0].v3.point.x);
   CLOVE_FLOAT_EQ(1.000000, obj.triangles[0].v3.point.y);
   CLOVE_FLOAT_EQ(0.000000, obj.triangles[0].v3.point.z);

   CLOVE_FLOAT_EQ(0.000000, obj.triangles[0].v3.uv.x);
   CLOVE_FLOAT_EQ(1.000000, obj.triangles[0].v3.uv.y);

   CLOVE_FLOAT_EQ(0.000000, obj.triangles[0].v3.normal.x);
   CLOVE_FLOAT_EQ(0.000000, obj.triangles[0].v3.normal.y);
   CLOVE_FLOAT_EQ(1.000000, obj.triangles[0].v3.normal.z);



   //Tiangle 2

   //Vertex 1
   CLOVE_FLOAT_EQ(1.000000, obj.triangles[1].v1.point.x);
   CLOVE_FLOAT_EQ(1.000000, obj.triangles[1].v1.point.y);
   CLOVE_FLOAT_EQ(0.000000, obj.triangles[1].v1.point.z);

   CLOVE_FLOAT_EQ(1.000000, obj.triangles[1].v1.uv.x);
   CLOVE_FLOAT_EQ(1.000000, obj.triangles[1].v1.uv.y);

   CLOVE_FLOAT_EQ(0.000000, obj.triangles[1].v1.normal.x);
   CLOVE_FLOAT_EQ(0.000000, obj.triangles[1].v1.normal.y);
   CLOVE_FLOAT_EQ(1.000000, obj.triangles[1].v1.normal.z);
   
   //Vertex 2
   CLOVE_FLOAT_EQ(1.000000, obj.triangles[1].v2.point.x);
   CLOVE_FLOAT_EQ(-1.000000, obj.triangles[1].v2.point.y);
   CLOVE_FLOAT_EQ(0.000000, obj.triangles[1].v2.point.z);

   CLOVE_FLOAT_EQ(1.000000, obj.triangles[1].v2.uv.x);
   CLOVE_FLOAT_EQ(0.000000, obj.triangles[1].v2.uv.y);

   CLOVE_FLOAT_EQ(0.000000, obj.triangles[1].v2.normal.x);
   CLOVE_FLOAT_EQ(0.000000, obj.triangles[1].v2.normal.y);
   CLOVE_FLOAT_EQ(1.000000, obj.triangles[1].v2.normal.z);

   //Vertex 3
   CLOVE_FLOAT_EQ(-1.000000, obj.triangles[1].v3.point.x);
   CLOVE_FLOAT_EQ(1.000000, obj.triangles[1].v3.point.y);
   CLOVE_FLOAT_EQ(0.000000, obj.triangles[1].v3.point.z);

   CLOVE_FLOAT_EQ(0.000000, obj.triangles[1].v3.uv.x);
   CLOVE_FLOAT_EQ(1.000000, obj.triangles[1].v3.uv.y);

   CLOVE_FLOAT_EQ(0.000000, obj.triangles[1].v3.normal.x);
   CLOVE_FLOAT_EQ(0.000000, obj.triangles[1].v3.normal.y);
   CLOVE_FLOAT_EQ(1.000000, obj.triangles[1].v3.normal.z);
   
}

CLOVE_TEST(EmptyFile)
{
   Obj obj;
   std::string objPath = "resources/empty.obj";
   bool result = ObjParser::TryParse(objPath, obj); 

   CLOVE_IS_FALSE(result);
}

CLOVE_TEST(WrongFile)
{
   Obj obj;
   std::string objPath = "resources/wrong.obj";

   bool result = ObjParser::TryParse(objPath, obj);
   CLOVE_IS_FALSE(result);
}

CLOVE_TEST(MissingNormals)
{
   Obj obj;
   std::string objPath = "resources/missingNormals.obj";

   bool result = ObjParser::TryParse(objPath, obj);
   CLOVE_IS_FALSE(result);
}

CLOVE_TEST(WrongFace)
{
   Obj obj;
   std::string objPath = "resources/wrongFace.obj";

   bool result = ObjParser::TryParse(objPath, obj);
   CLOVE_IS_FALSE(result);
}