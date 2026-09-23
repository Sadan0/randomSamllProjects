const http=require("http"),fs=require("fs"),path=require("path");
function calculate(s){const discount=s>=10000?s*.10:0,tax=(s-discount)*.18;return {subtotal:s,discount,tax,total:s-discount+tax}}
http.createServer((req,res)=>{const u=new URL(req.url,"http://localhost:5000");
if(u.pathname==="/api/calculate"){const s=Number(u.searchParams.get("subtotal")||0);res.writeHead(200,{"Content-Type":"application/json"});return res.end(JSON.stringify(calculate(s)))}
let f=path.join(__dirname,u.pathname==="/"?"index.html":u.pathname);if(!fs.existsSync(f))return res.writeHead(404).end();res.writeHead(200,{"Content-Type":u.pathname.endsWith(".css")?"text/css":"text/html"});res.end(fs.readFileSync(f));}).listen(5000,()=>console.log("Open http://localhost:5000"));
