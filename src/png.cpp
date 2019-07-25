#include "plugin.h"
#include "loop.h"
#include "../src/png.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>

void stdio_write_func(png_structp png, png_bytep data, png_size_t size)
{
	rawImage* rip=(rawImage*)png_get_io_ptr(png);
	rip->buf.insert(rip->buf.end(), data, data + size);
}
int raw2png(duk_context* ctx) {
	std::cout << "screen_cut!!!" << std::endl;
	duk_size_t size=0;
	if (duk_get_top(ctx) == 12) {
		for (size_t i = 2; i < 11; i++)
		{
			if (!duk_is_number(ctx, i)) {
				std::cout<<"raw2png:"<<i<<std::endl;
				return 0;
			}
		}
		duk_get_type(ctx, 0);
		if (duk_is_function(ctx, 11)) {
			if (duk_is_buffer_data(ctx, 0)) {
				rawImage r;
				r.width = duk_to_int(ctx, 2);
				r.height = duk_to_int(ctx, 3);
				r.title = (char*)duk_to_string(ctx, 1);
				r.data = (png_bytep)duk_require_buffer_data(ctx, 0, &size);
				r.bpp = duk_to_int(ctx, 4);
				r.rlen = duk_to_int(ctx, 5);
				r.glen = duk_to_int(ctx, 6);
				r.blen = duk_to_int(ctx, 7);
				r.ros = duk_to_int(ctx, 8);
				r.gos = duk_to_int(ctx, 9);
				r.bos = duk_to_int(ctx, 10);
				duk_dup(ctx, -1);
				if (raw2png(r, stdio_write_func)) {
					duk_push_int(ctx, 1);
					duk_push_undefined(ctx);
				}
				else {
					duk_push_int(ctx, 0);
					duk_push_external_buffer(ctx);
					duk_config_buffer(ctx, -1, r.buf.data(), r.buf.size());
				}
				duk_pcall(ctx,2);
				return 1;
			}
		}
	}
	return 0;
}

static const duk_function_list_entry my_module_funcs[] = {
	{ "raw2png", raw2png, DUK_VARARGS /*nargs*/ },
	{ NULL, NULL, 0 }
};
extern "C" int passoa_init(duk_context* ctx, boost::asio::io_service* io_) {
	loopSet(io_);
	duk_put_function_list(ctx, -1, my_module_funcs);
	std::cout << "Init Passoa Scut!!!" << std::endl;
	return 0;
}
extern "C" int passoa_exit() {
	//audioExit();
	return 0;
}
