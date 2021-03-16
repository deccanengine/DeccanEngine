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

    DeccanCamera *camera;
} GenericPipelineInfo = {0};

typedef struct VSParams {
    mat4s transform;
    mat4s view_matrix;
    mat4s projection_matrix;
} VSParams;

typedef struct FSParams {
    float color[4];
} FSParams;

DE_IMPL void DE_GenericPipelineCreate(void) {
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

    GenericPipelineInfo.shader = sg_make_shader(&(sg_shader_desc){
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
                [0] = { .name = "tex", .type = SG_IMAGETYPE_2D, },
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

    GenericPipelineInfo.pip = sg_make_pipeline(&(sg_pipeline_desc){
        .shader = GenericPipelineInfo.shader,
        .index_type = SG_INDEXTYPE_UINT16,
        .layout = {
            .attrs = {
                [0].format = SG_VERTEXFORMAT_FLOAT3,
                [1].format = SG_VERTEXFORMAT_FLOAT2,
            }
        },
        .blend = {
            .enabled = true,
            .src_factor_rgb = SG_BLENDFACTOR_SRC_ALPHA,
            .dst_factor_rgb = SG_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
            .color_write_mask = SG_COLORMASK_RGB,
        },
        .depth_stencil = {
            .depth_compare_func = SG_COMPAREFUNC_LESS_EQUAL,
            .depth_write_enabled = true,
        },
        .rasterizer = {
            .cull_mode = SG_CULLMODE_BACK,
        },
    });

    GenericPipelineInfo.pass_action = (sg_pass_action){
        .colors[0] = {
            .action = SG_ACTION_CLEAR,
            .val = {0.0f, 0.0f, 0.0f, 1.0f},
        },
    };

    /* clang-format on */
}

DE_IMPL void DE_GenericPipelineDestroy(void) {
    sg_destroy_shader(GenericPipelineInfo.shader);
    sg_destroy_pipeline(GenericPipelineInfo.pip);
}

DE_IMPL void DE_GenericPipelineBegin(DeccanCamera *camera) {
    vec4s clear_color = DE_RendererGetClearColor();
    glm_vec4_copy(clear_color.raw, GenericPipelineInfo.pass_action.colors[0].val);

    vec2s viewport = DE_RendererGetViewport();
    sg_begin_default_pass(&GenericPipelineInfo.pass_action, (uint32_t)viewport.x, (uint32_t)viewport.y);
    sg_apply_pipeline(GenericPipelineInfo.pip);

    GenericPipelineInfo.camera = camera;
}

DE_IMPL void DE_GenericPipelineDrawGeometry(DeccanGeometry geometry) {
    sg_bindings binds = {
        .vertex_buffers[0] = geometry.vbuf,
        .index_buffer = geometry.ibuf,
        .fs_images[0] = geometry.image,
    };

    VSParams vs_params = {
        .transform = geometry.transform,
        .view_matrix = GenericPipelineInfo.camera->cam.view,
        .projection_matrix = GenericPipelineInfo.camera->proj,
    };

    FSParams fs_params = {
        .color = {geometry.color[0], geometry.color[1], geometry.color[2], geometry.color[3]},
    };

    sg_apply_uniforms(SG_SHADERSTAGE_VS, 0, &vs_params, sizeof(VSParams));
    sg_apply_uniforms(SG_SHADERSTAGE_FS, 0, &fs_params, sizeof(FSParams));
    sg_apply_bindings(&binds);
    sg_draw(0, geometry.index_count, 1);
}

DE_IMPL void DE_GenericPipelineEnd(void) {
    sg_end_pass();
}
