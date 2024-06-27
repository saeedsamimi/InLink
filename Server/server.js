const WebSocket = require("ws");
const { pool } = require("./database/config.js");
const url = require("url");
const express = require("express");
const http = require("http");
const fs = require("fs");
const path = require("path");

const app = express();
const server = http.createServer(app);

const wsocket = new WebSocket.Server({ noServer: true });
const clients = new Map();

const getUserActiveChats = (ws, user_id) => {
  pool.query(
    "SELECT from_id,to_id FROM messages WHERE to_id = $1 or from_id = $1 GROUP BY (from_id,to_id)",
    [user_id],
    (err, res) => {
      if (err) {
        console.error("Error while loading chats: ", err);
        return;
      }
      const initChats = new Set();
      res.rows.forEach(function (row) {
        if (row.from_id === parseInt(user_id)) initChats.add(row.to_id);
        else initChats.add(row.from_id);
      });

      ws.send(
        JSON.stringify({
          type: "init",
          data: Array.from(initChats),
        })
      );
    }
  );
};

const getUserMessages = (ws, from_id, to_id) => {
  if (!to_id) {
    ws.close();
    return;
  }

  pool.query(
    "SELECT msg,time,from_id,picture FROM messages WHERE (to_id = $1 AND from_id = $2) or (to_id = $2 AND from_id = $1)",
    [from_id, to_id],
    (err, res) => {
      if (err) {
        console.error("Error while loading the messages: ", err);
        return;
      }
      const initMessages = res.rows.map((msg) => ({
        msg: msg.msg,
        time: msg.time,
        sender: msg.from_id,
        picture:  msg.picture
      }));
      ws.send(
        JSON.stringify({
          type: "init",
          data: initMessages,
        })
      );
    }
  );
};

const registerMessage = (ws, sender, receiver, msg,picture) => {
  if (!sender || !receiver || !msg) {
    console.log(
      "Error: some of the inputs in register message function is undefined, values: ",
      "\nsender",
      sender,
      "\nreceiver",
      receiver,
      "\nmsg",
      msg
    );
    return;
  }

  pool.query(
    "INSERT INTO messages (from_id,to_id,msg,picture) VALUES ($1,$2,$3,$4) RETURNING *",
    [sender,receiver,msg,picture],
    (err,res)=>{
      if(err){
        console.error("got an error from db: ",err);
        return;
      }
      const data = JSON.stringify({type: "registerMsg",data: res.rows[0]});
      ws.send(data);
      const wxClient = clients.get(receiver);
      if(wxClient && wxClient.readyState === WebSocket.OPEN)
        wxClient.send(data);
    }
  )
};

wsocket.on("connection", (ws, request) => {
  const paramaters = url.parse(request.url, true);
  const user_id = paramaters.query.user_id;

  if (!user_id) {
    ws.close();
    return;
  }

  clients.set(user_id, ws);
  console.log(`Client with user id: ${user_id} connected`);

  if (paramaters.pathname === "/chat") {
    getUserActiveChats(ws, user_id);
  } else if(paramaters.pathname === "/message"){
    const receiver = paramaters.query.to_id;
    getUserMessages(ws, user_id, receiver);
    ws.on('message',(msg)=>{
      const content = JSON.parse(msg);
      var picture = content.picture ? content.picture : null;
      registerMessage(ws,user_id,receiver,content.content,picture);
    });
  }

  ws.on("close", () => {
    clients.delete(user_id);
    console.log(`client by id ${user_id} disconnected!`);
  });
});

server.on("upgrade", (request, socket, head) => {
  const pathname = url.parse(request.url).pathname;

  if (pathname === "/chat" || pathname === "/message") {
    wsocket.handleUpgrade(request, socket, head, (ws) => {
      wsocket.emit("connection", ws, request);
    });
  } else {
    socket.destroy();
  }
});

server.listen(3000, () => {
  console.log("Web Socket is running over port 3000");
});
