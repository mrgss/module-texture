#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_opengl.h>
#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include <mruby/string.h>
#include <mrgss/mrgss.h>
#include <mrgss/mrgss_texture.h>

static void
texture_free(mrb_state *mrb, void *data) {
    mrgss_texture *tex = data;
    if (tex) {
        mrb_free(mrb, tex);
    };
}

struct mrb_data_type const mrbal_texture_data_type = {"Texture", texture_free};

/**
 * Create a glTexture2d from a surface
 */
static GLuint surface_texture(SDL_Surface *surface) {
    GLuint tid;
    GLenum texture_format;
    GLint ncolors;
    SDL_Surface* s = surface;
    /* Convert SDL_Surface to OpenGL Texture */
    ncolors = s->format->BytesPerPixel;
    if (ncolors == 4) {
        //alpha channel
        if (s->format->Rmask == 0x000000ff) {
            texture_format = GL_RGBA;
        } else {
            texture_format = GL_BGRA;
        }
    } else {
        if (ncolors == 3) {
            //no alpha channel
            if (s->format->Rmask == 0x000000ff)
                texture_format = GL_RGB;
            else
                texture_format = GL_BGR;
        } else {
            return 0;
        }
    }
    glGenTextures(1, &tid);
    glBindTexture(GL_TEXTURE_2D, tid);
    glTexImage2D(GL_TEXTURE_2D, 0, texture_format, s->w, s->h, 0, texture_format, GL_UNSIGNED_BYTE, s->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return tid;
}

static mrb_value initialize(mrb_state *mrb, mrb_value self) {
    mrgss_texture *texture;
    mrb_value param;
    SDL_Surface *pixmap;
    mrb_get_args(mrb, "o", &param);
    texture = mrb_malloc(mrb, sizeof texture);
    if (mrb_string_p(param)) {
        const char *str = mrb_string_value_ptr(mrb, param);
        SDL_Surface *surface = IMG_Load(str);
        texture->tid = surface_texture(surface);
        texture->w = surface->w;
        texture->h = surface->h;
        SDL_FreeSurface(surface);
    } else {
        pixmap = DATA_PTR(param);
        texture->h = pixmap->h;
        texture->w = pixmap->w;
        texture->tid = surface_texture(pixmap);
    }
    DATA_TYPE(self) = &mrbal_texture_data_type;
    DATA_PTR(self) = texture;
    return self;
}

void mrgss_texture_init(mrb_state *mrb) {
    struct RClass *class = mrb_define_class_under(mrb, mrgss_module(), "Texture", mrb->object_class);
    mrb_define_method(mrb, class, "initialize", initialize, MRB_ARGS_REQ(1));
    MRB_SET_INSTANCE_TT(class, MRB_TT_DATA);
}
