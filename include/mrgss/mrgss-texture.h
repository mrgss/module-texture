/* 
 * File:   mrgss-texture.h
 * Author: manuel
 *
 * Created on 3 de octubre de 2015, 00:16
 */

#ifndef MRGSS_TEXTURE_H
#define	MRGSS_TEXTURE_H

#include <mruby.h>
#include <GL/gl.h>

#ifdef	__cplusplus
extern "C" {
#endif

    void mrgss_init_texture(mrb_state *mrb);
    
    typedef struct texture {
        GLuint tid;
    } mrgss_texture;

#ifdef	__cplusplus
}
#endif

#endif	/* MRGSS_TEXTURE_H */

