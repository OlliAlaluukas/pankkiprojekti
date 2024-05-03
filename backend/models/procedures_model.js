const db=require('../database.js');

const procedures={
  
    creditTransfer(transferData, callback){
        return db.query("CALL credit_transfer(?,?,?)",[transferData.firstid,transferData.secondid,transferData.amount],callback);
    },

    cashWithdrawal(transferData, callback){
        return db.query("CALL cash_withdrawal(?,?)",[transferData.firstid,transferData.amount],callback);
    }
}

module.exports=procedures;

// nosto endpoint