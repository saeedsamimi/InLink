const {Pool} = require("pg");

const pool = new Pool({
  user: "postgres",
  host: "localhost",
  database: "InLink",
  password: "12345678",
  port: 8080,
});

module.exports = {pool}
