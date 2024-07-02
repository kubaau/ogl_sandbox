#include "GLInit.hpp"
#include <tools/CheckResult.hpp>
#include <tools/ThreadSafeLogger.hpp>
#include "GLApi.hpp"
#include "GLIo.hpp"
#include "GLScene.hpp"

namespace
{
    using namespace std;

    void redisplay() { glutPostRedisplay(); }

    void initGlutCallbacks()
    {
        glutIdleFunc(redisplay);
        glutDisplayFunc(render);
        glutKeyboardFunc(keyboard);
        glutSpecialFunc(special);
    }

    void initGlut(int argc, char* argv[])
    {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
        glutInitWindowSize(width, height);
        glutInitWindowPosition(100, 100);
        glutCreateWindow("ogl");
        initGlutCallbacks();
    }

    void initGlew()
    {
        const auto res = glewInit();
        check(res == GLEW_OK, reinterpret_cast<const char*>(glewGetErrorString(res)));
    }

    void buildVb()
    {
        vector<vec3> vs(4);
        vs[0] = {-1.0f, -1.0f, 0.5773f};
        vs[1] = {0.0f, -1.0f, -1.15475f};
        vs[2] = {1.0f, -1.0f, 0.5773f};
        vs[3] = {0.0f, 1.0f, 0.0f};

        glGenBuffers(1, &vb);
        glBindBuffer(GL_ARRAY_BUFFER, vb);
        glBufferData(GL_ARRAY_BUFFER, vs.size() * sizeof(vec3), vs.data(), GL_STATIC_DRAW);
    }

    void buildIb()
    {
        vector<unsigned> is{0, 3, 1, 1, 3, 2, 2, 3, 0, 0, 1, 2};

        glGenBuffers(1, &ib);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, is.size() * sizeof(unsigned), is.data(), GL_STATIC_DRAW);
    }
} // namespace

void initGL(int argc, char* argv[])
{
    initGlut(argc, argv);
    initGlew();
    DEBUG_LOG << "GL version: " << glGetString(GL_VERSION);
}

void buildGeometry()
{
    buildVb();
    buildIb();
}
