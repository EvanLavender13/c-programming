#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <errno.h>
#include <stdio.h>

#include <GL/glew.h>

#include <mem.h>
#include <spng.h>

typedef struct spng_ihdr spng_ihdr;

int
texinit(char *fp)
{
    unsigned int texid;
    FILE *f;
    size_t size;
    spng_ctx *ctx;
    spng_ihdr hdr;
    void *out;

    f = fopen(fp, "rb");
    if (f == NULL) {
        printf("unable to open file: %s, errno: %d\n", fp, errno);
        return 0;
    }
    
    // TODO: handle many error cases
    ctx = spng_ctx_new(0);
    spng_set_png_file(ctx, f);
    spng_get_ihdr(ctx, &hdr);
    spng_decoded_image_size(ctx, SPNG_FMT_RGBA8, &size);
    out = memalloc(size); // alloc out
    spng_decode_image(ctx, out, size, SPNG_FMT_RGBA8, 0);

    spng_ctx_free(ctx);
    fclose(f);

    glGenTextures(1, &texid);
    glBindTexture(GL_TEXTURE_2D, texid);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, hdr.width, hdr.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, out);
    glGenerateMipmap(GL_TEXTURE_2D);
    memfree(out); // free out

    return 1;
}

#endif