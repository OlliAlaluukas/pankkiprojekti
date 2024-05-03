const express = require('express');
const router = express.Router();
const card = require('../models/card_model.js');
const bcrypt = require('bcryptjs');
const dotenv=require('dotenv');
dotenv.config();
const jwt=require('jsonwebtoken');

router.post('/', function(request, response){
    console.log(process.env.MY_TOKEN);
    card.login(request.body.idCard, function(err, result){
        if (request.body.idCard && request.body.cardPin){
            if (err){
                response.json(err);
            }
            else{
                if (result.length > 0){
                    const hashedPIN = result[0].cardPin;
                    console.log(hashedPIN);
                    bcrypt.compare(request.body.cardPin, hashedPIN, function(err, compareResult){
                        if(compareResult){
                            console.log("Kirjautuminen ok");
                            const token = generateAccessToken({ idCard: request.body.idCard});
                            response.send(token);
                        }
                        else{
                            console.log("Väärä salasana");
                            response.send(compareResult);
                        }
                    })
                }
                else{
                    console.log("Korttia ei ole tietokannassa");
                    response.send(false);
                }
            }
        }
        else{
            console.log("Tunnus tai PIN puuttuu");
            response.send(false);
        }
    });
});

function generateAccessToken(idCard) {
    dotenv.config();
    return jwt.sign(idCard, process.env.MY_TOKEN, { expiresIn: '1000s' });
  };


module.exports = router;