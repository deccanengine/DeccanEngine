#include "Camera.h"

////////////////////////////////////////////////////////////////////////////////
// View
////////////////////////////////////////////////////////////////////////////////

void DE_ViewInit(DeccanView *camera, vec3s position) {
    camera->position = position;
	camera->yaw = 0.0f;
	camera->pitch = 0.0f;
	camera->roll = 0.0f;
}

////////////////////////////////////////////////////////////////////////////////

void DE_ViewUpdate(DeccanView *camera) {
	mat4s transform = glms_mat4_identity();

	transform = glms_rotate_x(transform, glm_rad(camera->roll));
	transform = glms_rotate_y(transform, glm_rad(camera->pitch));
	transform = glms_rotate_z(transform, glm_rad(camera->yaw));

	transform = glms_translate(transform, camera->position);

	camera->view = glms_mat4_inv(transform);
}

////////////////////////////////////////////////////////////////////////////////
// Camera
////////////////////////////////////////////////////////////////////////////////

void DE_CameraInit(DeccanCamera *camera, float near, float far) {
	DE_ViewInit(&camera->cam, (vec3s){ .x = 0.0f, .y = 0.0f, .z = 1.0f});
	
    camera->proj = glms_mat4_identity();
	camera->near = near;
	camera->far  = far;
	camera->aspect_ratio = (float)(4.0f / 3.0f);
}

////////////////////////////////////////////////////////////////////////////////

void DE_CameraSetViewport(DeccanCamera *camera, vec2s viewport) { 
	if(viewport.y <= 0) 
        return;
	camera->aspect_ratio = (float)(viewport.x / viewport.y);
}

////////////////////////////////////////////////////////////////////////////////

void DE_CameraSetOrtho(DeccanCamera *camera, float size) {
	camera->proj = glms_ortho(-camera->aspect_ratio * size, 
            camera->aspect_ratio * size, -size, size, camera->near, camera->far);

	DE_ViewUpdate(&camera->cam);
}

////////////////////////////////////////////////////////////////////////////////

void DE_CameraSetPersp(DeccanCamera *camera, float vfov) {
	camera->proj = glms_perspective(glm_rad(vfov), 
            camera->aspect_ratio, camera->near, camera->far);

	DE_ViewUpdate(&camera->cam);
}
