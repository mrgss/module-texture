#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include <mrgss.h>
#include <mrgss/mrgss-texture.h>
#include <mrgss/mrgss-pixmap.h>
#include <GL/gl.h>

static void
texture_free(mrb_state *mrb, void *data) {
    mrgss_texture *tex = data;
    if (tex) {
        mrb_free(mrb, tex);
    };
}

struct mrb_data_type const mrbal_texture_data_type = {"Texture", texture_free};

static mrb_value initialize(mrb_state *mrb, mrb_value self) {
    mrgss_texture *texture;
    mrb_value param;
    mrb_get_args(mrb, "o", &param);
    texture = mrb_malloc(mrb, sizeof texture);
    glGenTextures(1, &texture->tid);
    if (mrgss_object_is_a(mrb, param, "Pixmap")) {
        mrgss_pixmap *pixmap = DATA_PTR(param);
        glBindTexture(GL_TEXTURE_2D, texture->tid);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pixmap->width, pixmap->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixmap->data);
        glBindTexture(GL_TEXTURE_2D, 0);
    } else {
        mrgss_raise(mrb, E_ARGUMENT_ERROR, "Wrong Type of parameter");
        return mrb_nil_value();
    }
    DATA_TYPE(self) = &mrbal_texture_data_type;
    DATA_PTR(self) = texture;
    return self;
}

/**
 * Type initializer
 * @param mrb
 */
void mrgss_init_texture(mrb_state *mrb) {
    struct RClass *type = mrgss_create_class(mrb, "Texture");
    mrb_define_method(mrb, type, "initialize", initialize, MRB_ARGS_REQ(1));
     MRB_SET_INSTANCE_TT(type, MRB_TT_DATA);
}
