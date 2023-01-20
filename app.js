var express = require('express');
var server = express();
const HTTP_PORT = 80;
const cors = require('cors');
const path = require('path');
server.use(express.json());
server.use(express.static('./esp32-app-casa/arquivos'));



const obejto = {
    PP: "ON",
    PG: "ON",
    IS: "ON",
    IC: "ON"
}

server.use((req, res, next) => {
	//Qual site tem permissão de realizar a conexão, no exemplo abaixo está o "*" indicando que qualquer site pode fazer a conexão
    res.header("Access-Control-Allow-Origin", "*");
	//Quais são os métodos que a conexão pode realizar na API
    res.header("Access-Control-Allow-Methods", 'GET,PUT,POST,DELETE');
    server.use(cors());
    next();
});

server.get('/teste',(req,res)=> {
  res.sendFile(path.resolve(__dirname, "./appcasaweb.html"))
  //res.sendFile(path.resolve(__dirname, './appcasaweb.html'))
});

server.get("/leitura", (req, res) => {

  console.log(obejto);
  return res.send(obejto);
})

server.get("/leitura/status", (req, res) => {
  let statusGeral = req.query;
  obejto.PP = statusGeral.PP;
  obejto.PG = statusGeral.PG;
  obejto.IS = statusGeral.IS;
  obejto.IC = statusGeral.IC;
  return res.send(obejto);
})


//esta função recebe a mensagem de envio do Esp32 e retorno que recebeu
server.post("/client", (req, res) => {

    //console.log(JSON.stringify(req.query));  {"portao":"OFF"}
  // console.log(req.query);
   // let nome = JSON.stringify(req.query);
   //console.log(nome.replace('{"portao":"OFF"}', "OFF"));
  // portao = nome.replace('{"portao":"OFF"}', "OFF");
return res.send(portao);
})

server.listen(HTTP_PORT, ()=> console.log(`HTTP server escutando na porta ${HTTP_PORT}`));
