#pragma once
#include <string>
#include <vector>
#include <fstream>

struct Float3
{
    float x;
    float y;
    float z;
};

struct Float2
{
    float x;
    float y;
};


struct Vertex
{
    Float3 point;
    Float2 uv;
    Float3 normal;
};

struct Triangle
{
    Vertex v1;
    Vertex v2;
    Vertex v3; 
};

struct MeshObj
{
    std::vector<Triangle> triangles;
};

class ObjParser
{ 
    private:
    ObjParser(){}

    public:
    static bool TryParse(const std::string &path, MeshObj &outObj)
    {
        std::ifstream file(path);
        if(!file.is_open()) return false;


        outObj = MeshObj{};

        return true;
    }
    
};










