#include <vector>
#include "AABB.h"

namespace backlash {
    AABB::AABB() {
        mMin = glm::vec3(0,0,0);
        mMax = glm::vec3(0,0,0);
    };

    AABB::AABB(const glm::vec3& min, const glm::vec3& max) {
        mMin = min;
        mMax = max;
    }

    void AABB::Update(const glm::vec3& pos) {
        if (pos.x < mMin.x) 
            mMin.x = pos.x;

        if (pos.y < mMin.y) 
            mMin.y = pos.y;

        if (pos.z < mMin.z) 
            mMin.z = pos.z;

        if (pos.x > mMax.x) 
            mMax.x = pos.x;

        if (pos.y > mMax.y) 
            mMax.y = pos.y;

        if (pos.z > mMax.z) 
            mMax.z = pos.z;
    }

    bool AABB::IsPointInside(const glm::vec3& point) const {
        if (point.x < mMin.x ||
            point.y < mMin.y ||
            point.z < mMin.z || 
            point.x > mMax.x || 
            point.y > mMax.y ||
            point.z > mMax.z ) 
            return false;
        return true;
    }



}