const db=require('../database.js');

const cardaccount={
    getAllCardAccounts(callback){
        return db.query('SELECT * FROM cardaccount', callback)
    },
    getCardAccountByAccount(id, callback){
        return db.query("SELECT * FROM cardaccount WHERE idAccount=?",[id],callback);
    },
    getCardAccountByCard(id, callback){
        return db.query("SELECT * FROM cardaccount WHERE idCard=?",[id],callback);
    },
    addCardAccount(insertData, callback){
        return db.query('INSERT INTO cardaccount(idCard, idAccount) VALUES (?, ?)',[insertData.idCard,insertData.idAccount],callback);
    },
    updateCardAccount(updateData, id, callback){
        return db.query('UPDATE cardaccount SET idCard=?, idAccount=? WHERE idAccount=?',[updateData.idCard, updateData.idAccount, id], callback);
    },
    deleteCardAccount(id, callback){
        return db.query('DELETE FROM cardaccount WHERE idAccount=?',[id], callback);
    }
}

module.exports=cardaccount;