const express = require('express');
const router = express.Router();
const invalidcard = require('../models/invalidCard_model.js');

router.get('/:iC',function(request, response){
    invalidcard.getCardInvalid(request.params.iC, function(err, result){
        if(err){
            response.json(err);
        }
        else{
            response.json(result[0]);
        }        
    })
});

router.put('/:iC', function(request, response){
    invalidcard.setInvalid(request.params.iC, request.body, function(err, result){
        if(err){
            console.log(err);
            response.json(err);
        }
        else{
            response.json(result.affectedRows);
        }
    })
});




module.exports=router;