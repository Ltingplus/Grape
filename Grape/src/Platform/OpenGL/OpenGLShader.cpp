#include "gppch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace Grape
{
    static GLenum ShaderTypeFromString(const std::string& type)
    {
        if (type == "vertex")
            return GL_VERTEX_SHADER;
        if (type == "fragment" || type == "pixel")
            return GL_FRAGMENT_SHADER;
        GP_CORE_ASSERT(false, "Unknown shader type!");
        return 0;
    }

    OpenGLShader::OpenGLShader(const std::string& filePath)
    {
        std::string source = ReadFile(filePath);
        auto shaderSource = PreProcess(source);
        Compile(shaderSource);

        // Extract name from filepath
        auto lastSlash = filePath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = filePath.rfind('.');
        auto count = lastDot == std::string::npos ? filePath.size() - lastSlash : lastDot - lastSlash;
        m_name = filePath.substr(lastSlash, count);
    }

    OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragSrc)
        : m_name(name)
    {
        std::unordered_map<GLenum, std::string> sources;
        sources[GL_VERTEX_SHADER] = vertexSrc;
        sources[GL_FRAGMENT_SHADER] = fragSrc;
        Compile(sources);        
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_rendererID);
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_rendererID);
    }

    void OpenGLShader::unBind() const
    {
        glUseProgram(0);
    }

    void OpenGLShader::SetInt(const std::string& name, int value)
    {
        UploadUniformInt(name, value);
    }

    void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
    {
        UploadUniformFloat3(name, value);
    }

    void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
    {
        UploadUniformFloat4(name, value);
    }

    void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
    {
        UploadUniformMatrix4(name, value);
    }

    void OpenGLShader::UploadUniformInt(const std::string& name, const int& value)
    {
        GLint location = glGetUniformLocation(m_rendererID, name.c_str());
        glUniform1i(location, value);

    }

    void OpenGLShader::UploadUniformFloat(const std::string& name, const float& value)
    {
        GLint location = glGetUniformLocation(m_rendererID, name.c_str());
        glUniform1f(location, value);
    }

    void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
    {
        GLint location = glGetUniformLocation(m_rendererID, name.c_str());  
        glUniform2f(location, value.x, value.y);
    }
    

    void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
    {
        GLint location = glGetUniformLocation(m_rendererID, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
    {
        GLint location = glGetUniformLocation(m_rendererID, name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::UploadUniformMatrix3(const std::string& name, const glm::mat3& mat)
    {
        GLint location = glGetUniformLocation(m_rendererID, name.c_str());
        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(mat));
    }

    void OpenGLShader::UploadUniformMatrix4(const std::string& name, const glm::mat4& mat)
    {
        GLint location = glGetUniformLocation(m_rendererID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
    }

    std::string OpenGLShader::ReadFile(const std::string& filePath)
    {
        std::string res;
        std::ifstream in(filePath, std::ios::in | std::ios::binary);
        if (in)
        {
            in.seekg(0, std::ios::end);
            res.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&res[0], res.size());
            in.close();
            ;
        }
        else
        {
            GP_CORE_ERROR("Could not open file '{0}'", filePath);
        }
        return res;
    }

    std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& src)
    {
        std::unordered_map<GLenum, std::string> shaderSrcs;
        const char* typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = src.find(typeToken, 0);
        while (pos != std::string::npos)
        {
            size_t eol = src.find_first_of("\r\n", pos);
            GP_CORE_ASSERT(eol != std::string::npos, "Syntax error");
            size_t begin = pos + typeTokenLength + 1;
            std::string type = src.substr(begin, eol - begin);
            GP_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

            size_t nextLinePos = src.find_first_not_of("\r\n", eol);
            pos = src.find(typeToken, nextLinePos);
            shaderSrcs[ShaderTypeFromString(type)] = src.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? src.size() - 1 : nextLinePos));
        }
        return shaderSrcs;
    }

    void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
    {

        GLuint program = glCreateProgram();
        std::vector<GLenum> glShaderIDs(shaderSources.size());
       
        for (auto& kv : shaderSources)
        {
            GLenum type = kv.first;
            const std::string& source = kv.second;
            // Create an empty vertex shader handle
            GLuint shader = glCreateShader(type);
            const GLchar* sourceCStr = source.c_str();
            glShaderSource(shader, 1, &sourceCStr, 0);

            // compile
            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                // The maxLength includes the NULL character
                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

                // We don't need the shader anymore.
                glDeleteShader(shader);

                GP_CORE_ERROR("{0}", infoLog.data());
                GP_CORE_ASSERT(false, "Vertex shader compilation failure!");
                break;
            }
            // Attach our shaders to our program
            glAttachShader(program, shader);
            glShaderIDs.emplace_back(shader);
        }
        m_rendererID = program;
        // Vertex and fragment shaders are successfully compiled.
        // Now time to link them together into a program.
        // Get a program object.
        // Link our program
        glLinkProgram(program);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            // We don't need the program anymore.
            glDeleteProgram(program);
            // Don't leak shaders either.
            for (auto id : glShaderIDs)
                glDeleteShader(id);

            GP_CORE_ERROR("{0}", infoLog.data());
            GP_CORE_ASSERT(false, "Shader link failure!");
            return;
        }
        // Always detach shaders after a successful link.
        for (auto id : glShaderIDs)
            glDetachShader(program, id);
    }

}