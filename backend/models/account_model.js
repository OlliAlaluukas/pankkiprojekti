const db=require('../database.js');

const account={
    getAllAccounts(callback){
        return db.query("SELECT * FROM account",callback);
    },
    getAccountById(id, callback){
        return db.query("SELECT * FROM account WHERE idAccount=?",[id],callback);
    },
    getAccountByOwner(owner, callback){
        return db.query("SELECT * FROM account WHERE accountOwner=?",[owner],callback);
    },
    addAccount(insertData, callback){
        return db.query('INSERT INTO account(idAccount,balance,creditLimit,accountOwner) VALUES (?, ?, ?, ?)',[insertData.idAccount,insertData.balance,insertData.creditLimit,insertData.accountOwner],callback);
    },
    updateAccount(updateData, id, callback){
        return db.query('UPDATE account SET idAccount=?, balance=?, creditLimit=?, accountOwner=? WHERE idAccount=?',[updateData.idAccount, updateData.balance, updateData.creditLimit, updateData.accountOwner, id], callback);
    },
    deleteAccount(id, callback){
        return db.query('DELETE FROM account WHERE idAccount=?',[id], callback);
    },
    getBalance(id, callback){
        return db.query("SELECT balance FROM account WHERE idAccount=?",[id],callback);
    }
}

module.exports=account;