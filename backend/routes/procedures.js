const express = require('express');
const router = express.Router();
const procedures=require('../models/procedures_model.js');

router.post('/siirto',function(request,response){
    console.log(request.body);
    procedures.creditTransfer(request.body,function(err,result){
        if(err){
            console.log(err);
            response.json(err.errno);
        }
        else{
            response.json(result);
        }
    });
});

router.post('/nosto',function(request,response){
    procedures.cashWithdrawal(request.body,function(err,result){
        if(err){
            console.log(err);
            response.json(err.errno);
        }
        else{
            response.json(result);
        }
    });
});




module.exports=router