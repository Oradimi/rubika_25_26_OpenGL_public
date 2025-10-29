#pragma once

#include "Camera.h"

namespace threshold
{
    void init();
    void update();
    void draw(Camera& camera);
    void destroy();
}