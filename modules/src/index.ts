// if ('win32' == process.platform) {
	// process.env.Path = process.env.Path + ';' + __dirname;
// } else {
	// process.env.LD_LIBRARY_PATH = process.env.LD_LIBRARY_PATH + ';' + __dirname;
// }
const inst = require('./img.passoa');

interface Options {
	title?: string;
	width?: number;
	height?: number;
	bpp?: number;
	rlen?: number;
	glen?: number;
	blen?: number;
	ros?: number;
	gos?: number;
	bos?: number;
}
interface ImgInfo {
	info: Options;
	data: Buffer;
}
enum format {
	PIXEL_FORMAT_RGBA_8888 = 1, // 4x8-bit RGBA
	PIXEL_FORMAT_RGBX_8888 = 2, // 4x8-bit RGB0
	PIXEL_FORMAT_RGB_888 = 3, // 3x8-bit RGB
	PIXEL_FORMAT_RGB_565 = 4, // 16-bit RGB
	PIXEL_FORMAT_BGRA_8888 = 5, // 4x8-bit BGRA
	PIXEL_FORMAT_RGBA_5551 = 6, // 16-bit ARGB
	PIXEL_FORMAT_RGBA_4444 = 7, // 16-bit ARGB
	PIXEL_FORMAT_A_8 = 8 // 8-bit A
}
export function encode(src: Buffer, opt: Options, fn: (err: number, data: Buffer) => void) {
	return inst.raw2jpeg(
		src,
		opt.width,
		opt.height,
		opt.bpp,
		opt.rlen,
		opt.glen,
		opt.blen,
		opt.ros,
		opt.gos,
		opt.bos,
		fn
	);
}
export function screencapInfo(data: Buffer) {
	var info: Options = {};
	var idx = 0;
	info.width = data[idx++] + (data[idx++] << 8) + (data[idx++] << 16) + (data[idx++] << 24);
	info.height = data[idx++] + (data[idx++] << 8) + (data[idx++] << 16) + (data[idx++] << 24);
	var bpp = data[idx++] + (data[idx++] << 8) + (data[idx++] << 16) + (data[idx++] << 24);
	switch (bpp) {
		case format.PIXEL_FORMAT_RGBA_8888:
		case format.PIXEL_FORMAT_RGBX_8888:
			info.bpp = 32;
			info.rlen = info.glen = info.blen = 8;
			info.bos = 16;
			info.gos = 8;
			info.ros = 0;
			break;
		case format.PIXEL_FORMAT_RGB_888:
			info.bpp = 24;
			info.rlen = info.glen = info.blen = 8;
			info.bos = 16;
			info.gos = 8;
			info.ros = 0;
			break;
		case format.PIXEL_FORMAT_RGB_565:
			info.bpp = 16;
			info.rlen = 5;
			info.glen = 6;
			info.blen = 5;
			info.bos = 11;
			info.gos = 5;
			info.ros = 0;
			break;
		default:
			console.log('unsupported format:' + bpp);
			break;
	}
	let result: ImgInfo = { info: info, data: data.subarray(idx) };
	return result;
}
