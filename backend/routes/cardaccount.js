const express = require('express');
const router = express.Router();
const cardaccount=require('../models/cardaccount_model.js');


router.get('/',function(request,response){
    cardaccount.getAllCardAccounts(function(err, result){
        if(err){
            console.log(err);
            response.json(err.errno);
        }
        else{
            console.log(result);
            response.json(result);
        }
        
    })
});

router.get('/account/:id',function(request,response){
    cardaccount.getCardAccountByAccount(request.params.id,function(err,result){
        if(err){
            console.log(err);
            response.json(err.errno);
        }
        else{
            console.log(result);
            response.json(result);
        }
        })
    });

router.get('/card/:id',function(request,response){
    cardaccount.getCardAccountByCard(request.params.id,function(err,result){
        if(err){
            console.log(err);
            response.json(err.errno);
        }
        else{
            console.log(result);
            response.json(result);
        }
        })
    });

router.post('/',function(request,response){
    cardaccount.addCardAccount(request.body,function(err,result){
        if(err){
            console.log(err);
            response.json(err.errno);
        }
        else{
            response.json(result);
        }
    });
});

router.put('/:id',function(request, response){
    cardaccount.updateCardAccount(request.body, request.params.id, function(err, result){
        if(err){
            console.log(err);
            response.json(err.errno);
        }
        else{
            response.json(result);
        }
    });
});

router.delete('/:id',function(request,response){
    cardaccount.deleteCardAccount(request.params.id, function(err, result){
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