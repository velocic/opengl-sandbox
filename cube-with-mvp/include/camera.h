#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <controls.h>

class Camera
{
    private:
        Controls controls;
        glm::vec3 position;
        float horizontalAngle;
        float verticalAngle;
        float fieldOfView;
        float speed;
        float mouseSpeed;
    public:
        Camera(
            Controls controls,
            glm::vec3 position,
            float horizontalAngle,
            float verticalAngle,
            float fieldOfView,
            float speed,
            float mouseSpeed
        ):
            controls(controls),
            position(position),
            horizontalAngle(horizontalAngle),
            verticalAngle(verticalAngle),
            fieldOfView(fieldOfView),
            speed(speed),
            mouseSpeed(mouseSpeed)
        {};

        glm::mat4 getProjectionMatrix();
        glm::mat4 getViewMatrix();
};

#endif
