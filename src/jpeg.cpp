#include "plugin.h"
#include <iostream>
#include "turbojpeg.h"

struct pa_plugin gp;
typedef struct {
    int width;
    int height;
    int bpp;
    int rof;
    int gof;
    int bof;
    int rlen;
    int glen;
    int blen;
} stInfo;

class imageCvt {
public:
    
    imageCvt(unsigned char* src,stInfo info) {
        err = 0;
        jpegBuf = NULL;
        tjInstance = NULL;
        jpegSize = 0;
        switch (info.bpp) {
        case 16:
            toRgb888(src,info.width,info.height,info.glen);
            format24(info.rof);
            break;
        case 24:
            buf = src;
            format24(info.rof);
            break;
        case 32:
            buf = src;
            format32(info.rof);
            break;
        }
        compress(info.width,info.height);
    }
    ~imageCvt() {
        tjDestroy(tjInstance);  tjInstance = NULL;
        tjFree(jpegBuf);  jpegBuf = NULL;
    }
    void format24(int rof) {
        if (rof) {
            fmt = TJPF_RGB;
        }
        else {
            fmt = TJPF_BGR;
        }
    }
    void format32(int rof) {
        switch (rof) {
       
        case 0:
            fmt = TJPF_RGBA;
            break;
        case 8:
            fmt = TJPF_ARGB;
            break;
        case 16:
            fmt = TJPF_BGRA;
            break;
        case 24:
            fmt = TJPF_ABGR;
            break;
        default:
            err = -3;
            break;
        }
    }
    void toRgb888(unsigned char* src, int width, int height,int gof) {
        uint16_t* ptr = (uint16_t*)src;
        buf = new unsigned char[width*height*3];
        if (gof == 6) {
            for (int i = 0; i < width*height; i++)
            {
                buf[i * 3] = ((ptr[i]) & 0xF800) >> 8;
                buf[i * 3+1] = ((ptr[i]) & 0x07E0) >> 3;
                buf[i * 3+2] = ((ptr[i]) & 0x001F) <<3;
            }
        }
    }
    void compress(int width,int height) {
        if ((tjInstance = tjInitCompress()) == NULL) {
            err = -1;
            return;
        }
        if (tjCompress2(tjInstance, buf, width, 0, height, fmt,
            &jpegBuf, &jpegSize, TJSAMP_444, 70, 0) < 0) {
            err = -2;
            std::cout << ">>>" << tjGetErrorStr() << std::endl;
            return;
        }
        
    }
    unsigned char* data() {
        return jpegBuf;
    }
    unsigned long size() {
        return jpegSize;
    }
    int error() {
        return err;
    }
private:
    unsigned char* buf;
    TJPF fmt;
    int err;
    tjhandle tjInstance;
    unsigned char *jpegBuf;
    unsigned long jpegSize;
};
int raw2jpeg(pa_context* ctx) {
    int len = 0;
    unsigned char* imgBuf=NULL;
    if (gp.get_top(ctx)!=11) {
        return 0;
    }
    imgBuf = (unsigned char *)gp.get_buffer_data(ctx, 0, &len);
    stInfo info;
    info.width = gp.get_int(ctx, 1);
    info.height = gp.get_int(ctx, 2);
    info.bpp = gp.get_int(ctx, 3);
    info.rlen = gp.get_int(ctx, 4);
    info.glen = gp.get_int(ctx, 5);
    info.blen = gp.get_int(ctx, 6);
    info.rof = gp.get_int(ctx, 7);
    info.gof = gp.get_int(ctx, 8);
    info.bof = gp.get_int(ctx, 9);
    imageCvt img(imgBuf,info);

    gp.dup(ctx, -1);
    gp.push_int(ctx, img.error());
    gp.push_external_buffer(ctx, img.data(), img.size());
    gp.call(ctx, 2);
    return 0;
}
static const pa_function_list_entry my_module_funcs[] = {
	{ "raw2jpeg", raw2jpeg, PA_VARARGS /*nargs*/ },
	{ NULL, NULL, 0 }
};
extern "C" int passoa_init(pa_plugin p) {
    gp = p;
    gp.put_function_list(p.ctx, -1, my_module_funcs);
    return 0;
}
extern "C" int passoa_exit() {
	//audioExit();
	return 0;
}
