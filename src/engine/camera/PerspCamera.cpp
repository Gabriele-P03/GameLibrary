#include "PerspCamera.hpp"

jpl::PerspCamera::PerspCamera(jgl::Vector3f* position, jgl::Vector3f* direction, float near, float far) :
    jpl::BaseCamera(position, direction, near, far){
}

void jpl::PerspCamera::translate(jgl::Vector3f* translatingVector){
    this->position->add(translatingVector);
}
void jpl::PerspCamera::setToTranslation(jgl::Vector3f* translatingVector){
    this->position = translatingVector;
}

void jpl::PerspCamera::setToRotation(jgl::Quaternion* quaternion){
    this->direction = quaternion->getDirectionVector();
}
void jpl::PerspCamera::rotate(jgl::Quaternion* quaternion){
    this->rotate(new jgl::Matrix4(quaternion));
}
void jpl::PerspCamera::rotate(jgl::Matrix4* rotationMatrix){
    this->direction->set(  ((new jgl::Matrix4(this->direction))->mul(rotationMatrix))->getRotation());
}
void jpl::PerspCamera::rotateAround(jgl::Vector3f* point, jgl::Matrix4* rotationMatrix){

    jgl::Vector3f* difPos = this->position->cpy()->addAll(-point->getX(), -point->getY(), -point->getZ());

    jgl::Matrix4* transform = new jgl::Matrix4();
    transform->setToTranslation(difPos, true);
    transform->mul(rotationMatrix);
    transform->translate(point);

    this->position = transform->getTranslation();
}

void jpl::PerspCamera::transform(jgl::Matrix4* transformMatrix){

    jgl::Matrix4* currentMatrix = new jgl::Matrix4(this->direction);
    currentMatrix->translate(this->position);
    currentMatrix->mul(transformMatrix);

    this->direction = currentMatrix->getRotation()->crs(&jgl::Vector3f::yAxis);
    this->position = currentMatrix->getTranslation();
    this->normalizeUpAndRight();
}


void jpl::PerspCamera::tick(float speedMove, float speedRot, bool yawLock){
    float x = 0.0f, y = 0.0f, z = 0.0f;

    if(isKeyPressed(GLFW_KEY_W)){
        y += speedMove;
    }
    if(isKeyPressed(GLFW_KEY_S)){
        y -= speedMove;
    }
    if(isKeyPressed(GLFW_KEY_A)){
        x -= speedMove;
    }
    if(isKeyPressed(GLFW_KEY_D)){
        x += speedMove;
    }
    if(isKeyPressed(GLFW_KEY_Y)){
        z += speedMove;
    }
    if(isKeyPressed(GLFW_KEY_H)){
        z -= speedMove;
    }

    if(x != 0.0f || y != 0.0f || z != 0.0f){
        this->position->addAll(x, y, z);
    }

    if(isKeyPressed(GLFW_KEY_K)){
        jgl::Matrix4* rot = new jgl::Matrix4(0.0f, M_PI_2/10, 0.0f);
        this->rotate(rot);
    }
    if(isKeyPressed(GLFW_KEY_L)){
        jgl::Matrix4* rot = new jgl::Matrix4(0.0f, -M_PI_2/10, 0.0f);
        this->rotate(rot);
    }

    //Rotating
    /*
    double xMouse, yMouse;
    getMousePosition(&xMouse, &yMouse);

    if(lastXMousePos != xMouse || lastYMousePos != yMouse){

        float diffXMousePos = this->lastXMousePos - xMouse;
        float diffYMousePos = this->lastYMousePos - yMouse;

        this->lastXMousePos = xMouse;
        this->lastYMousePos = yMouse;

        jgl::Matrix4* rot = new jgl::Matrix4(diffXMousePos*speedRot, diffYMousePos*speedRot, 0.0f);
        this->rotate(rot);
    }*/
}

void jpl::PerspCamera::updateFrustum(){

    float  w = jpl::WindowSize::INSTANCE.w, h = jpl::WindowSize::INSTANCE.h;

    float aspect = w/h;
    float depth = this->far-this->near;
    float e = tan(this->FOV/2);

    float top = e*this->near;
    float bottom = -top;
    float right = top * aspect;
    float left = -right; 

    if(this->projection != nullptr){
        delete this->projection;
    }
    this->projection = new jgl::Matrix4(
                            near/right, 0.0f, 0.0f, 0.0f,
                            0.0f, near/top, 0.0f, 0.0f,
                            0.0f, 0.0f, -(far+near)/depth, (-2.0f*far*near)/depth,
                            0.0f, 0.0f, 1.0f, 1.0f);
}