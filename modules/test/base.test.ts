import * as img from '../src/index';
const fs = require('fs');
var buf = fs.readFileSync('test.raw');
var info = img.screencapInfo(buf);
console.log(buf);
console.log(info.info);
console.log(info.data);
var t1 = new Date().getTime();
img.encode(info.data, info.info, function(err, data) {
	console.log('!!!!', new Date().getTime() - t1);
	fs.writeFileSync('test.jpg', data);
	console.log('!!!!', new Date().getTime() - t1);
});
