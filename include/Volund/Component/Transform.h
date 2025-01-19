#pragma once

#include "Component.h"

namespace Volund
{
    class Transform : public Component
    {
    public:
        void SetRotation(const Vec3& rotation);
        Vec3 GetRotation() const;
        void AddRotation(const Vec3& rotation);
        Vec3 GetFront() const;
        Vec3 GetRight() const;
        Vec3 GetUp() const;
        Mat4x4 GetModelMatrix() const;
        Vec3 pos;
        Vec3 scale;
        Quat quat;
        Transform(Vec3 pos = Vec3(0.0f), Vec3 rotation = Vec3(0.0f), Vec3 scale = Vec3(1.0f));
    private:
    };
}