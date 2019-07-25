const jpg=require("img");
const fs=require("fs");
// png.encode("test.data",{width:800,height:480,title:"test",bpp:16,rlen:5,glen:6,blen:5,roffset:11,goffset:6,boffset:0},function(ev,data){
	// console.log(ev,data);
// });
var buf=fs.readFileSync("android1.raw");
var t1=new Date().getTime();
jpg.encode(buf,{"size":4915200,"width":960,"height":1280,"bpp":32,"rlen":8,"glen":8,"blen":8,"ros":16,"gos":8,"bos":0},function(err,data){
	console.log("!!!!",new Date().getTime()-t1);
	fs.writeFileSync("test.jpg",data);
	console.log("write end");
	console.log("!!!!",new Date().getTime()-t1);	
});


