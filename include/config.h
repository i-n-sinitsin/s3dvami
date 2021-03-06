// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include "glm/glm.hpp"

namespace s3dvami
{
    constexpr size_t defaultWindowWidth = 1024;
    constexpr size_t defaultWindowHeight = 768;

    constexpr glm::vec4 defautBackgroundColor = {0.5f, 0.5f, 0.5f, 1.0f};

    constexpr float defaultModelDescroptionWidth = 350.0f;

    constexpr float defaultNearPlate = 0.1f;
    constexpr float defaultFarPlate = 100.0f;

    constexpr float defaultfloorPlateSize = 40.0f;
    constexpr unsigned int defaultfloorPartsByAxes = 40;
    constexpr float defaultModelSize = defaultfloorPlateSize / 2.0f;

    constexpr float defaultGlobalAxesLength = 40.0f;
    constexpr float defaultGlobalAxesWidth = 0.1f;

    constexpr float cameraOrbitMouseMoveSpeed = 0.1f;
    constexpr float cameraFreeMouseMoveSpeed = 0.05f;

    constexpr float cameraOrbitMouseScrollSpeed = 2.0f;
    constexpr float cameraFreeMouseScrollSpeed = 2.0f;
}
