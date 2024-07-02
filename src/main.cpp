#include <tools/Pause.hpp>
#include <tools/ThreadSafeLogger.hpp>
#include "GLApi.hpp"
#include "GLInit.hpp"
#include "GLShaders.hpp"

using namespace std;

int main(int argc, char* argv[]) try
{
    enableDebugLogs(EnableDebugLogs::YES);
    initGL(argc, argv);
    buildGeometry();
    buildShaders();
    glutMainLoop();
}
catch (exception& ex)
{
    ERROR_LOG << ex.what();
    pauseIO();
    throw;
}
