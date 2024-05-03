const express = require('express');
const router = express.Router();
const customeraccount=require('../models/customeraccount_model.js');


router.get('/',function(request,response){
    customeraccount.getAllCustomerAccounts(function(err, result){
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
    customeraccount.getCustomerAccountByAccount(request.params.id,function(err,result){
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

router.get('/customer/:id',function(request,response){
    customeraccount.getCustomerAccountByCustomer(request.params.id,function(err,result){
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
    customeraccount.addCustomerAccount(request.body,function(err,result){
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
    customeraccount.updateCustomerAccount(request.body, request.params.id, function(err, result){
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
    customeraccount.deleteCustomerAccount(request.params.id, function(err, result){
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