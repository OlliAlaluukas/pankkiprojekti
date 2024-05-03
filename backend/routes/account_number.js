const express = require('express');
const router = express.Router();
const card = require('../models/card_model');

router.get('/:iC',function(request, response){
    card.getAccountId(request.params.iC, function(err, result){
        if(err){
            response.json(err);
        }
        else{
            response.json(result);
        }        
    })
});

module.exports = router;