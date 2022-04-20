#include"..\glad\glad.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "GLShaderCompiler.h"

GLShaderCompiler::GLShaderCompiler()
{

}

void GLShaderCompiler::CreateFromFile(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{

    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}
void GLShaderCompiler::CreateFromFile(const char* commonPath)
{
    std::string name = commonPath;
    CreateFromFile(std::string(name + ".vert").c_str(), std::string(name + ".frag").c_str());
}
void GLShaderCompiler::CreateFromString(const char* vertexString, const char* fragmentString, const char* geometryString)
{


    const char* vShaderCode = vertexString;
    const char* fShaderCode = fragmentString;
    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}
GLShaderCompiler::GLShaderCompiler(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
    CreateFromString(vertexPath, fragmentPath);
}

void GLShaderCompiler::use()
{
    glUseProgram(ID);
}

void GLShaderCompiler::setBool(const char* name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name), (int)value);
}

void GLShaderCompiler::setInt(const char* name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name), value);
}

void GLShaderCompiler::setFloat(const char* name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name), value);
}

void GLShaderCompiler::setVec2(const char* name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(ID, name), x, y);
}

void GLShaderCompiler::setVec3(const char* name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(ID, name), x, y, z);
}

void GLShaderCompiler::setVec4(const char* name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(ID, name), x, y, z, w);
}

void GLShaderCompiler::setVec4(const char* name, float v[4])
{
    glUniform4f(glGetUniformLocation(ID, name),v[0], v[1], v[2], v[3]);
}

void GLShaderCompiler::setMat2(const char* name, const float* arr22) const
{
    glUniformMatrix2fv(glGetUniformLocation(ID, name), 1, GL_FALSE, arr22);
}

void GLShaderCompiler::setMat3(const char* name, const float* arr33) const
{
    glUniformMatrix3fv(glGetUniformLocation(ID, name), 1, GL_FALSE, arr33);
}

void GLShaderCompiler::setMat4(const char* name, const float* arr44) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, arr44);
}

void GLShaderCompiler::SetIntArray(const char* name, int array[], int size) const
{
    glUniform1iv(glGetUniformLocation(ID, name), size, array);
}

void GLShaderCompiler::Begin()
{
    if (m_isBegin)
    {
        //error
        std::cout << "already Begin() must call End()\n";
    }
    else
    {
        m_isBegin = true;
        glUseProgram(ID);
    }
}

void GLShaderCompiler::End()
{
    if (m_isBegin)
    {
        
        m_isBegin = false;
    }
    else
    {
        //error
       
        std::cout << "already End() must call Begin()\n";
    }
}

void GLShaderCompiler::Use()
{
    glUseProgram(ID);
}

void GLShaderCompiler::checkCompileErrors(unsigned int shader, const char* type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}
