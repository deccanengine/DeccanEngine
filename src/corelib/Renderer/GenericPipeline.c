/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "GenericPipeline.h"
#include "Renderer.h"

DE_PRIV struct {
    sg_shader shader;
    sg_pipeline pip;
    sg_pass_action pass_action;

    deccan_camera_t *camera;
} generic_pipeline_info = {0};

typedef struct VSParams {
    mat4s transform;
    mat4s view_matrix;
    mat4s projection_matrix;
} VSParams;

typedef struct FSParams {
    float color[4];
} FSParams;

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_generic_pipeline_create(void) {
    /* clang-format off */
    const char *vs_source =
        "#version 330\n"
        "in vec3 position;\n"
        "in vec2 texcoord;\n"
        "out vec2 uv;\n"
        "uniform mat4 transform;\n"
        "uniform mat4 view_matrix;\n"
        "uniform mat4 projection_matrix;\n"
        "void main() {\n"
        "    gl_Position = projection_matrix * view_matrix * transform * vec4(position, 1.0f);\n"
        "    uv = texcoord;\n"
        "}\n";

    const char *fs_source = 
        "#version 330\n"
        "uniform sampler2D tex;\n"
        "uniform vec4 color;\n"
        "in vec2 uv;\n"
        "out vec4 frag_color;\n"
        "void main() {\n"
        "    vec4 tex_color = texture(tex, uv) * color;\n"
        "    if(tex_color.a < 0.1)\n"
        "        discard;\n"
        "    frag_color = tex_color;\n"
        "}\n";

    generic_pipeline_info.shader = sg_make_shader(&(sg_shader_desc){
        .vs = {
            .uniform_blocks = {
                [0] = {
                    .size = sizeof(VSParams),
                    .uniforms = {
                        [0] = {.name = "transform", .type = SG_UNIFORMTYPE_MAT4},
                        [1] = {.name = "view_matrix", .type = SG_UNIFORMTYPE_MAT4},
                        [2] = {.name = "projection_matrix", .type = SG_UNIFORMTYPE_MAT4},
                    },
                },
            },
        },
        .fs = {
            .images = {
                [0] = { .name = "tex", .image_type = SG_IMAGETYPE_2D, },
            },
            .uniform_blocks = {
                [0] = {
                    .size = sizeof(FSParams),
                    .uniforms = {
                        [0] = { .name = "color", .type = SG_UNIFORMTYPE_FLOAT4, },
                    },
                },
            },
        },
        .vs.source = vs_source,
        .fs.source = fs_source,
    });

    generic_pipeline_info.pip = sg_make_pipeline(&(sg_pipeline_desc){
        .shader = generic_pipeline_info.shader,
        .index_type = SG_INDEXTYPE_UINT16,
        .cull_mode = SG_CULLMODE_BACK,
        .sample_count = 4,
        .layout = {
            .attrs = {
                [0].format = SG_VERTEXFORMAT_FLOAT3,
                [1].format = SG_VERTEXFORMAT_FLOAT2,
            }
        },
        .colors[0] = {
            .write_mask = SG_COLORMASK_RGB,
            .pixel_format = SG_PIXELFORMAT_RGBA8,
            .blend = {
                .enabled = true,
                .src_factor_rgb = SG_BLENDFACTOR_SRC_ALPHA,
                .dst_factor_rgb = SG_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
            },
        },
        .depth = {
            .pixel_format = SG_PIXELFORMAT_DEPTH,
            .compare = SG_COMPAREFUNC_LESS_EQUAL,
            .write_enabled = true,
        },
    });

    generic_pipeline_info.pass_action = (sg_pass_action){
        .colors[0] = {
            .action = SG_ACTION_CLEAR,
            .value = {0.0f, 0.0f, 0.0f, 1.0f},
        },
    };
    /* clang-format on */
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_generic_pipeline_destroy(void) {
    sg_destroy_shader(generic_pipeline_info.shader);
    sg_destroy_pipeline(generic_pipeline_info.pip);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_generic_pipeline_begin(deccan_camera_t *camera) {
    vec4s clear_color = deccan_renderer_get_clear_color(); 
    memcpy(&generic_pipeline_info.pass_action.colors[0].value, clear_color.raw, sizeof(sg_color));

    deccan_framebuffer_t *fb = deccan_renderer_get_framebuffer();
    if (fb != NULL) {
        sg_begin_pass(fb->pass, &generic_pipeline_info.pass_action);
    }
    else {
        vec2s viewport = deccan_renderer_get_viewport();
        sg_begin_default_pass(&generic_pipeline_info.pass_action, (uint32_t)viewport.x, (uint32_t)viewport.y);
    }

    sg_apply_pipeline(generic_pipeline_info.pip);

    generic_pipeline_info.camera = camera;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_generic_pipeline_draw(deccan_draw_action_t action) {
    // TODO: shaders taking material directly
    sg_bindings binds = {
        .vertex_buffers[0] = action.geometry->vbuf,
        .index_buffer = action.geometry->ibuf,
        .fs_images[0] = action.texture->image,
    };

    VSParams vs_params = {
        .transform = action.transform,
        .view_matrix = generic_pipeline_info.camera->cam.view,
        .projection_matrix = generic_pipeline_info.camera->proj,
    };

    deccan_color_t color = deccan_color_r_b_g_to_floats(action.material->color);
    
    FSParams fs_params = { 0 };
    memcpy(fs_params.color, color.norm, sizeof(float[4]));

    sg_apply_uniforms(SG_SHADERSTAGE_VS, 0, &SG_RANGE(vs_params));
    sg_apply_uniforms(SG_SHADERSTAGE_FS, 0, &SG_RANGE(fs_params));
    sg_apply_bindings(&binds);
    sg_draw(0, action.geometry->index_count, 1);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_generic_pipeline_end(void) {
    sg_end_pass();
}
