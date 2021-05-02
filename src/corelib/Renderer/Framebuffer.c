/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Framebuffer.h"

////////////////////////////////////////////////////////////////////////////////
// Framebuffer
////////////////////////////////////////////////////////////////////////////////

DE_IMPL void DE_FramebufferCreate(DeccanFramebuffer *fb) {
    sg_image_desc img_desc = (sg_image_desc){
        .render_target = true,
        .width = fb->info.dim.x,
        .height = fb->info.dim.y,
        .pixel_format = SG_PIXELFORMAT_RGBA8,
        .min_filter = SG_FILTER_LINEAR,
        .mag_filter = SG_FILTER_LINEAR,
        .wrap_u = SG_WRAP_REPEAT,
        .wrap_v = SG_WRAP_REPEAT,
        .sample_count = 4,
    };
    
    fb->color_img = sg_make_image(&img_desc);
    img_desc.pixel_format = SG_PIXELFORMAT_DEPTH;
    fb->depth_img = sg_make_image(&img_desc);
    
    fb->pass = sg_make_pass(&(sg_pass_desc){
        .color_attachments[0].image = fb->color_img,
        .depth_stencil_attachment.image = fb->depth_img,
    });
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void DE_FramebufferDestroy(DeccanFramebuffer *fb) {
    sg_destroy_image(fb->color_img);
    sg_destroy_image(fb->depth_img);
    sg_destroy_pass(fb->pass);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void DE_FramebufferUpdate(DeccanFramebuffer *fb) {
    DE_FramebufferDestroy(fb);
    DE_FramebufferCreate(fb);
}
