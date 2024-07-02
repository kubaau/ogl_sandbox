#include "GLIo.hpp"
#include "GLApi.hpp"
#include "GLScene.hpp"

namespace
{
    constexpr auto step_factor = 1.0f;
}

void keyboard(unsigned char key, int, int)
{
    switch (key)
    {
        case 'a':
        {
            const auto dir = normalize(cross(up, normalize(target))) * step_factor;
            eye_pos += dir;
            target += dir;
            return;
        }
        case 'w': eye_pos += target * step_factor; return;
        case 'd':
        {
            const auto dir = normalize(cross(normalize(target), up)) * step_factor;
            eye_pos += dir;
            target += dir;
            return;
        }
        case 's': eye_pos -= target * step_factor; return;
    }
}

void special(int code, int, int)
{
    switch (code)
    {
        case GLUT_KEY_LEFT:
        {
            const auto dir = normalize(cross(up, normalize(target))) * step_factor;
            eye_pos += dir;
            target += dir;
            return;
        }
        case GLUT_KEY_UP: eye_pos += target * step_factor; return;
        case GLUT_KEY_RIGHT:
        {
            const auto dir = normalize(cross(normalize(target), up)) * step_factor;
            eye_pos += dir;
            target += dir;
            return;
        }
        case GLUT_KEY_DOWN: eye_pos -= target * step_factor; return;
        case GLUT_KEY_PAGE_UP: eye_pos.y += step_factor; return;
        case GLUT_KEY_PAGE_DOWN: eye_pos.y -= step_factor; return;
    }
}
