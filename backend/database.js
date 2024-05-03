const mysql = require('mysql2');
const dotenv=require('dotenv');
dotenv.config();
const connection = mysql.createPool(process.env.sqlserver);

module.exports=connection;
