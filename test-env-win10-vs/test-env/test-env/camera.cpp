#include "camera.h"
#include <iostream>

Camera::Camera(){
    this->camera_pos = glm::vec3(0.0f, 1.5f,  5.0f);
    this->camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
    this->world_up = glm::vec3(0.0f, 1.0f, 0.0f);
    this->camera_up = glm::vec3(0.0f, 1.0f,  0.0f);
    this->view_matrix = glm::mat4(1.0f);
    this->pitch = 0;
    this->yaw = -90;
}

glm::mat4 Camera::get_view_matrix(){
    return glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);
}


void Camera::process_keyboard_input(camera_movement_t cm){
    float camera_speed = 2 * this->delta_time;
    switch (cm){
        case FORWARD:
            camera_pos += camera_speed * camera_front;
            break;
        case BACKWARD:
            camera_pos -= camera_speed * camera_front;
            break;
        case LEFT:
            camera_pos -= camera_speed * glm::normalize(glm::cross(camera_front, camera_up));
            break;
        case RIGHT:
            camera_pos += camera_speed * glm::normalize(glm::cross(camera_front, camera_up));
            break;
        case UP:
            camera_pos += camera_speed * camera_up;
            break;
        case DOWN:
            camera_pos -= camera_speed * camera_up;
            break;
        default:
            break;
    }
    return ;
}

void Camera::process_mouse_movement(float x_offset, float y_offset){
    // std::cout << x_offset << "   " << y_offset << std::endl;
    this->pitch -= y_offset * 1;
    this->yaw += x_offset * 1;
    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front = glm::vec3(1.0f);
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camera_front = glm::normalize(front);

    glm::vec3 right = glm::normalize(glm::cross(camera_front, world_up));
    camera_up = glm::normalize(glm::cross(right, camera_front));

}

void Camera::reflesh(){
    this->camera_pos = glm::vec3(0.0f, 0.0f,  3.0f);
    this->camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
    this->world_up = glm::vec3(0.0f, 1.0f, 0.0f);
    this->camera_up = glm::vec3(0.0f, 1.0f,  0.0f);
    this->view_matrix = glm::mat4(1.0f);
    this->pitch = 0;
    this->yaw = -90;
}


void Camera::update_delta_time(float new_delta_time){
    this->delta_time = new_delta_time;
}