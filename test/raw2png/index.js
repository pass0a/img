const jpg=require("img");
const fs=require("fs");
buf=new Buffer(info.size);
var t1=new Date().getTime();
jpg.encode(buf,info,function(err,data){
	console.log("!!!!",new Date().getTime()-t1);
	fs.writeFileSync("test.jpg",data);
	console.log("!!!!",new Date().getTime()-t1);	
});


