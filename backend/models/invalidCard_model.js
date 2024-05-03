const db=require('../database.js');

const invalidcard={
    setInvalid(iC, updateData, callback){
        return db.query('UPDATE card SET cardValid=? WHERE idCard=?',
            [updateData.cardValid, iC], callback);
        },
    getCardInvalid(iC, callback){
        return db.query('SELECT cardValid FROM card WHERE idCard=?',
         [iC],callback);
    }
    
}



module.exports=invalidcard;