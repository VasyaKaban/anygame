#pragma once

#include <vector>
#include "Object.h"
#include "Timer.h"
#include "Math/Matrix4x4.h"
#include "Math/Matrix_Transformations.h"
#include <memory>
#include "FrameBuffer.h"

//extern std::vector<Object*> GroupOfObjects;

extern std::vector<std::unique_ptr<Object>> GroupOfObjects;

extern Timer MainTimer;

extern Matrix4x4 Projection;

extern float fov;
