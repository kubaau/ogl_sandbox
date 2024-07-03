#include "GLScene.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <tools/SimpleTimer.hpp>
#include <tools/ThreadSafeLogger.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>
#include "GLInit.hpp"

VbHandle vb;
IbHandle ib;
ShaderLocation wvp_loc;

vec3 eye_pos = {0.0f, 0.0f, -3.0f};
vec3 target = {0.0f, 0.0f, 1.0f};
const vec3 up = {0.0f, 1.0f, 0.0f};

using namespace std;

namespace glm
{
    auto& operator<<(ostream& os, const vec3& v) { return os << "{" << v.x << ", " << v.y << ", " << v.z << "}"; }
} // namespace glm

void render()
{
    SimpleTimer render_timer;

    glClear(GL_COLOR_BUFFER_BIT);

    static float i{};
    i += 0.1f;
    DEBUG_LOG << i;
    DEBUG_LOG << "eye_pos: " << eye_pos;
    DEBUG_LOG << "target: " << target;

    const auto rotation_mat = yawPitchRoll(i, 0.0f, 0.0f);
    const auto scale_mat = scale(vec3{1});
    const auto translation_mat = translate(vec3{0, 0, 3});
    const auto world = translation_mat * scale_mat * rotation_mat;

    const auto view = lookAt(eye_pos, target, up);

    const auto projection =
        perspectiveFov(radians(60.0f), static_cast<float>(width), static_cast<float>(height), 1.0f, 100.0f);

    const auto wvp = projection * view * world;

    glUniformMatrix4fv(wvp_loc, 1, GL_FALSE, &wvp[0][0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);

    SimpleTimer draw_timer;
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
    DEBUG_LOG << "draw\t" << fixed << draw_timer.elapsed();

    glDisableVertexAttribArray(0);

    glutSwapBuffers();

    DEBUG_LOG << "render\t" << fixed << render_timer.elapsed();
}
