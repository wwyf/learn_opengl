#ifndef _CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
typedef enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
}camera_movement_t;


class Camera{
public:
    Camera();
    glm::mat4 get_view_matrix();
    void process_keyboard_input(camera_movement_t);
    void process_mouse_movement(float x_offset, float y_offset);
    void update_delta_time(float new_delta_time);
    void reflesh();
private:
    glm::mat4 view_matrix;
    glm::vec3 camera_pos;
    glm::vec3 camera_front;
    glm::vec3 camera_up;
    glm::vec3 world_up;
    float delta_time;
    float yaw;
    float pitch;
};


// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;



#endif // !_CAMERA_H_

