#include "ModelAttrib.h"
#include <iostream>
#include <vector>

namespace backlash {
    void ModelAttrib::UpdateTransform() {
        mTransform = glm::mat4();
        // glm::mat4 orientation = glm::mat4_cast(mOrientation);

        mTransform *= mOrientation;
        mTransform *= glm::translate(glm::mat4(), mPosition);
        mTransform *= glm::scale(glm::mat4(), mScale);
    }

    void ModelAttrib::DisplayModelAttrib() {
        std::cout << "Now Displaying the Model Attributes:" << std::endl;

        std::cout << "\t  Model Transform: " << std::endl;

        std::cout << "\t  { " << mTransform[0][0] << " ,\t" << mTransform[0][1] << " ,\t" << mTransform[0][2] << " ,\t" <<mTransform[0][3] << "}" << std::endl;
        std::cout << "\t  { " << mTransform[1][0] << " ,\t" << mTransform[1][1] << " ,\t" << mTransform[1][2] << " ,\t" <<mTransform[1][3] << "}" << std::endl;
        std::cout << "\t  { " << mTransform[2][0] << " ,\t" << mTransform[2][1] << " ,\t" << mTransform[2][2] << " ,\t" <<mTransform[2][3] << "}" << std::endl;
        std::cout << "\t  { " << mTransform[3][0] << " ,\t" << mTransform[3][1] << " ,\t" << mTransform[3][2] << " ,\t" <<mTransform[3][3] << "}" << std::endl;

        std::cout << "\t  Orientation: " << std::endl;
        std::cout << "\t  { " << mOrientation[0][0] << " ,\t" << mOrientation[0][1] << " ,\t" << mOrientation[0][2] << " ,\t" <<mOrientation[0][3] << "}" << std::endl;
        std::cout << "\t  { " << mOrientation[1][0] << " ,\t" << mOrientation[1][1] << " ,\t" << mOrientation[1][2] << " ,\t" <<mOrientation[1][3] << "}" << std::endl;
        std::cout << "\t  { " << mOrientation[2][0] << " ,\t" << mOrientation[2][1] << " ,\t" << mOrientation[2][2] << " ,\t" <<mOrientation[2][3] << "}" << std::endl;
        std::cout << "\t  { " << mOrientation[3][0] << " ,\t" << mOrientation[3][1] << " ,\t" << mOrientation[3][2] << " ,\t" <<mOrientation[3][3] << "}" << std::endl;

        std::cout << "\t  Position: " << std::endl;
        std::cout << "\t  { " << mPosition.x << " ,\t" << mPosition.y << " ,\t" << mPosition.z << "}" << std::endl;
    }

    AABB ModelAttrib::ComputeBoundingBox() {
        std::vector<glm::vec4> points;
        glm::vec3 min = mBoundingBox.mMin;
        glm::vec3 max = mBoundingBox.mMax;

        points.push_back(glm::vec4(min, 1.0));
        points.push_back(glm::vec4(max, 1.0));
        points.push_back(glm::vec4(min.x, min.y, max.z, 1.0));
        points.push_back(glm::vec4(min.x, max.y, min.z, 1.0));
        points.push_back(glm::vec4(min.x, max.y, max.z, 1.0));
        points.push_back(glm::vec4(max.x, min.y, min.z, 1.0));
        points.push_back(glm::vec4(max.x, min.y, max.z, 1.0));
        points.push_back(glm::vec4(max.x, max.y, min.z, 1.0));

        for (auto& x : points) {
            // std::cout << "(" << x.x << ", " << x.y << ", " << x.z << ")" << std::endl;
            x = x * mTransform;
        }

        AABB box; 
        for (auto& x : points) {
            glm::vec3 newPoint(x);
            if (!box.IsPointInside(newPoint)) 
                box.Update(newPoint);
        }

        return box;
    }
}