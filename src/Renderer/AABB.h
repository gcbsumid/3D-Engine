#ifndef AABB_H
#define AABB_H

#include <glm/glm.hpp>

namespace backlash {
    struct AABB {
        glm::vec3 mMin;
        glm::vec3 mMax;

        AABB();
        AABB(const glm::vec3& min, const glm::vec3& max);

        ~AABB() {}

        void Update(const glm::vec3&);
        bool IsPointInside(const glm::vec3&) const;
    };

}

#endif