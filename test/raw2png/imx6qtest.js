const jpg=require("img");
const fs=require("fs");
// png.encode("test.data",,function(ev,data){
	// console.log(ev,data);
// });
var buf=fs.readFileSync("imx6q.raw");
var t1=new Date().getTime();
jpg.encode(buf,{width:800,height:480,title:"test",bpp:16,rlen:5,glen:6,blen:5,ros:11,gos:6,bos:0},function(err,data){
	console.log("!!!!",new Date().getTime()-t1);
	fs.writeFileSync("test.jpg",data);
	console.log("write end");
	console.log("!!!!",new Date().getTime()-t1);	
});


