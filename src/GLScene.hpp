#pragma once

#include <glm/glm/glm.hpp>
#include "GLTypedefs.hpp"

using namespace glm;

extern VbHandle vb;
extern IbHandle ib;
extern ShaderLocation wvp_loc;

extern vec3 eye_pos;
extern vec3 target;
extern const vec3 up;

void render();
