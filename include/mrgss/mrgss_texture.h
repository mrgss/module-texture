/* 
 * File:   mrgss_texture.h
 * Author: manuel
 *
 * Created on 8 de octubre de 2015, 17:22
 */

#ifndef MRGSS_TEXTURE_H
#define	MRGSS_TEXTURE_H
#include <mruby.h>
#include <SDL/SDL_opengl.h>

#ifdef	__cplusplus
extern "C" {
#endif

    void mrgss_texture_init(mrb_state *mrb);

    typedef struct texture {
        mrb_int w, h;
        GLuint tid;
    } mrgss_texture;



#ifdef	__cplusplus
}
#endif

#endif	/* MRGSS_TEXTURE_H */

