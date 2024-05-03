var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');


var indexRouter = require('./routes/index');

// var usersRouter = require('./routes/users');
var cardRouter = require('./routes/card');
const loginRouter=require('./routes/login.js');
const jwt=require('jsonwebtoken');
const dotenv=require('dotenv');
var customerRouter = require('./routes/customer');
var accountRouter = require('./routes/account.js');
var accountNumberRouter = require('./routes/account_number.js');
var proceduresRouter = require('./routes/procedures.js');
var transactionRouter = require('./routes/transaction.js');
var cardAccountRouter = require('./routes/cardaccount.js');
var customerAccountRouter = require('./routes/customeraccount.js');
var invalidcardRouter = require('./routes/invalidcard.js');
dotenv.config();

var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/login', loginRouter); // Ei suojattu
app.use('/invalidcard', invalidcardRouter);


app.use(authenticateToken);
//suojatut
app.use('/', indexRouter);
//app.use('/users', usersRouter);
app.use('/card', cardRouter);
app.use('/customer', customerRouter);
app.use('/account', accountRouter);
app.use('/procedures', proceduresRouter);
app.use('/accountNumber',accountNumberRouter);
app.use('/transaction',transactionRouter);
app.use('/cardaccount',cardAccountRouter);
app.use('/customeraccount',customerAccountRouter);


function authenticateToken(req, res, next) {
    const authHeader = req.headers['authorization']
    const token = authHeader && authHeader.split(' ')[1]
  
    console.log("token = "+token);
    if (token == null) return res.sendStatus(401)
  
    jwt.verify(token, process.env.MY_TOKEN, function(err, user) {
  
      if (err) return res.sendStatus(403)

      req.user = user
  
      next()
    })
  }


module.exports = app;
