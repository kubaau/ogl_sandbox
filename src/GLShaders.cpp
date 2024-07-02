#include "GLShaders.hpp"
#include <tools/CheckResult.hpp>
#include <tools/ReadFile.hpp>
#include "GLApi.hpp"
#include "GLScene.hpp"

using namespace std;

namespace
{
    auto buildShader(GLuint program, GLenum type, string code)
    {
        const auto shader = glCreateShader(type);
        check(shader, "Error creating shader type " + to_string(type));

        const auto code_data = code.data();
        const auto code_length = static_cast<GLResult>(code.size());
        glShaderSource(shader, 1, &code_data, &code_length);

        glCompileShader(shader);
        GLResult compile_result;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);
        if (not compile_result)
        {
            string log;
            log.resize(1024);
            glGetShaderInfoLog(shader, static_cast<GLsizei>(log.size()), nullptr, log.data());
            throw runtime_error{"Error compiling shader type " + to_string(type) + ": " + log};
        }

        glAttachShader(program, shader);
        return shader;
    }
} // namespace

void buildShaders()
{
    const auto program = glCreateProgram();
    check(program, "Error creating shader program");

    const string shader_folder = "../../src/";
    const auto vs_code = readTextFile(shader_folder + "vs.glsl");
    const auto fs_code = readTextFile(shader_folder + "fs.glsl");

    const auto vs = buildShader(program, GL_VERTEX_SHADER, vs_code);
    const auto fs = buildShader(program, GL_FRAGMENT_SHADER, fs_code);

    glLinkProgram(program);
    GLResult result = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (not result)
    {
        string log;
        log.resize(1024);
        glGetProgramInfoLog(program, static_cast<GLsizei>(log.size()), nullptr, log.data());
        throw runtime_error{"Error linking shader program: " + log};
    }

    glDetachShader(program, vs);
    glDeleteShader(vs);
    glDetachShader(program, fs);
    glDeleteShader(fs);

    glValidateProgram(program);
    glGetProgramiv(program, GL_VALIDATE_STATUS, &result);
    if (not result)
    {
        string log;
        log.resize(1024);
        glGetProgramInfoLog(program, static_cast<GLsizei>(log.size()), nullptr, log.data());
        throw runtime_error{"Invalid shader program: " + log};
    }

    glUseProgram(program);

    string loc = "wvp";
    wvp_loc = static_cast<ShaderLocation>(glGetUniformLocation(program, loc.c_str()));
    check(wvp_loc != static_cast<ShaderLocation>(-1), "Wrong " + loc + " location");
}
