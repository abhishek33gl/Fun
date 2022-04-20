#pragma once
class GLShaderCompiler
{
public:
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    GLShaderCompiler();
    void CreateFromFile(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
    void CreateFromFile(const char* commonPath);
    void CreateFromString(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
    GLShaderCompiler(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
    // activate the shader
    // ------------------------------------------------------------------------
   
    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const char* name, bool value) const;
    // ------------------------------------------------------------------------
    void setInt(const char* name, int value) const;
    // ------------------------------------------------------------------------
    void setFloat(const char* name, float value) const;
    // ------------------------------------------------------------------------
    void setVec2(const char* name, float x, float y) const;
    // ------------------------------------------------------------------------
    void setVec3(const char* name, float x, float y, float z) const;
    // ------------------------------------------------------------------------
    void setVec4(const char* name, float x, float y, float z, float w);
    void setVec4(const char* name, float v[4]);
    // ------------------------------------------------------------------------
    void setMat2(const char* name, const float* arr22) const;
    // ------------------------------------------------------------------------
    void setMat3(const char* name, const float* arr33) const;
    // ------------------------------------------------------------------------
    void setMat4(const char* name, const float* arr44) const;
    /// <summary>
    /// Array
    /// </summary>
    // ----------------------------------------------------------------------------
    void SetIntArray(const char* name, int array[],int size) const;
    /*------------------------*/
    void Begin();
    void End();
    void Use();

private:
    void use();
    bool m_isBegin = false;
    unsigned int ID=0;
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(unsigned int shader, const char* type);
};

