const express = require("express")
const app = express()

const PORT = 8000

app.use(express.json());

const server = app.listen(PORT, function () {
    console.log("server running");
});

app.get("/", function (req, res) {
    console.log(req.body.request)
    res.sendFile(__dirname + "\\index.html");

});

const SocketServer = require("ws").Server;
const wss = new SocketServer({ server });

value = "0";
wss.on("connection", function (ws) {
    console.log("clint connected")
    ws.send(value);
    
    ws.on("message", function (msg) {
        value = msg + "";
        console.log(value);
        broadcast(value);
    });

    ws.on("close", function () {
        console.log("terminate");
    });
});

function broadcast(msg) {
    wss.clients.forEach(function (client) {
        if (client.readyState === client.OPEN) {
            client.send(msg);
            
        }
    });
}