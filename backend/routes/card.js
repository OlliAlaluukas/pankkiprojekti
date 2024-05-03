const express = require('express');
const router = express.Router();
const card = require('../models/card_model');

router.get('/', function(request, response){
    card.getAllCards(function(err, result){
        if(err){
            response.json(err);
        }
        else{
            response.json(result);
        }
    })
})

router.get('/:iC',function(request, response){
    card.getOneCard(request.params.iC, function(err, result){
        if(err){
            response.json(err);
        }
        else{
            response.json(result[0]);
        }        
    })
});

router.post('/', function(request, response){
    card.addCard(request.body, function(err, result){
        if(err){
            response.json(err);
        }
        else{
            response.json(result.affectedRows);
        }
    })
});

router.put('/:iC', function(request, response){
    card.updateCard(request.params.iC, request.body, function(err, result){
        if(err){
            console.log(err);
            response.json(err);
        }
        else{
            response.json(result.affectedRows);
        }
    })
});

router.delete('/:iC', function(request, response){
    card.deleteCard(request.params.iC, function(err, result){
        if(err){
            console.log(err);
            response.json(err);
        }
        else{
            response.json(result.affectedRows);
        }
    });
});




module.exports=router;