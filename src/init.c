#include <mruby.h>
#include <mrgss/mrgss-texture.h>

void
mrb_mrgss_texture_gem_init(mrb_state *mrb) {
    mrgss_init_texture(mrb);
}

void
mrb_mrgss_texture_gem_final(mrb_state* mrb) {
    /* finalizer */
}
