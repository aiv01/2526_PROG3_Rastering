#pragma once
#include <string>
#include <vector>
#include <fstream>
#include<iostream>

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

class Tokenizer
{
    private:
    Tokenizer(){}

    public:
    static std::vector<std::string> Split(const std::string &line, char separator)
    {
        std::vector<std::string> tokens;

        size_t end;
        size_t start = 0;

        std::string sep {separator};
      
        while((end = line.find(sep, start)) != std::string::npos)
        {
            tokens.push_back(line.substr(start, end-start));
            start = end + 1;
        }
        tokens.push_back(line.substr(start));

        return tokens;
    }

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
        std::string line;

        std::vector<Float3> points;
        std::vector<Float3> normals;
        std::vector<Float2> uvs;

        while(std::getline(file,line)) // return true if file is readable
        {
            if(line.empty())
            {
                continue;
            }

            auto tokens = Tokenizer::Split(line,' ');

            if(tokens[0] == "v") // starts parsing data from "v" tokens
            {
                if (tokens.size() != 4) return false;

                Float3 v;
                try
                {
                    v.x = std::stof(tokens[1]); // using stof (string to float) is better, because throws an exception error and aborts the program
                    v.y = std::stof(tokens[2]);
                    v.z = std::stof(tokens[3]); 
                    //atof -> converts string to float ( c type, no exceptions )
                    //atoi -> converts string to int   ( c type, no exceptions )

                }
                catch(const std::exception& e)
                {
                    return false;
                }

                points.push_back(v);
                
            }
            else if(tokens[0] == "vt") // starts parsing data from "vt" tokens
            {
                if (tokens.size() != 3) return false;

                Float2 vt;
                try
                {
                    vt.x = std::stof(tokens[1]); 
                    vt.y = std::stof(tokens[2]);

                }
                catch(const std::exception& e)
                {
                    return false;
                }

                uvs.push_back(vt);
                
            }
            else if(tokens[0] == "vn") // starts parsing data from "vn" tokens
            {
                if (tokens.size() != 4) return false;

                Float3 vn;
                try
                {
                    vn.x = std::stof(tokens[1]); 
                    vn.y = std::stof(tokens[2]);
                    vn.y = std::stof(tokens[3]);

                }
                catch(const std::exception& e)
                {
                    return false;
                }

                normals.push_back(vn);
                
            }
            else if (tokens[0] == "f")
            {
                if (tokens.size() != 4) return false;

                auto vertex0 = Tokenizer::Split(tokens[1], '/');
                auto vertex1 = Tokenizer::Split(tokens[2], '/');
                auto vertex2 = Tokenizer::Split(tokens[3], '/');

                if (vertex0.size() != 3 || vertex1.size() != 3 || vertex2.size() != 3) return false;
                
                Triangle t;
                try // Vertex 0
                {
                    const int VIndex0 = std::stoi(vertex0[0]) - 1;
                    const int VIndex1 = std::stoi(vertex0[1]) - 1;
                    const int VIndex2 = std::stoi(vertex0[2]) - 1;

                    t.v1 = {points[VIndex0], uvs[VIndex1], normals[VIndex2]};
                }
                catch(const std::exception& e)
                {
                    return false;
                }

                try // Vertex 1
                {
                    const int VIndex0 = std::stoi(vertex1[0]) - 1;
                    const int VIndex1 = std::stoi(vertex1[1]) - 1;
                    const int VIndex2 = std::stoi(vertex1[2]) - 1;

                    t.v2 = {points[VIndex0], uvs[VIndex1], normals[VIndex2]};
                }
                catch(const std::exception& e)
                {
                    return false;
                }

                try // Vertex 2
                {
                    const int VIndex0 = std::stoi(vertex2[0]) - 1;
                    const int VIndex1 = std::stoi(vertex2[1]) - 1;
                    const int VIndex2 = std::stoi(vertex2[2]) - 1;

                    t.v3 = {points[VIndex0], uvs[VIndex1], normals[VIndex2]};
                }
                catch(const std::exception& e)
                {
                    return false;
                }
                
                outObj.triangles.push_back(t);
            }
        }                              

        return true;
    }
    
};










