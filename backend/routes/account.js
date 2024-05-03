const express = require('express');
const router = express.Router();
const account=require('../models/account_model.js');

router.get('/',function(request,response){
    account.getAllAccounts(function(err, result){
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

router.get('/id/:id',function(request,response){
    account.getAccountById(request.params.id,function(err,result){
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

router.get('/owner/:owner',function(request,response){
    account.getAccountByOwner(request.params.owner,function(err,result){
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
    account.addAccount(request.body,function(err,result){
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
    account.updateAccount(request.body, request.params.id, function(err, result){
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
    account.deleteAccount(request.params.id, function(err, result){
        if(err){
            console.log(err);
            response.json(err.errno); 
        }
        else{
            response.json(result);
        }
    });
});

router.get('/balance/:id',function(request,response){
    account.getBalance(request.params.id,function(err,result){
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

module.exports=router