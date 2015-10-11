#include <mruby.h>
#include <mrgss/mrgss_texture.h>

void
mrb_mrgss_texture_gem_init(mrb_state *mrb) {
    mrgss_texture_init(mrb);
}

void
mrb_mrgss_texture_gem_final(mrb_state* mrb) {
    /* finalizer */
}
