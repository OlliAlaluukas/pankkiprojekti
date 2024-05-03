const db=require('../database.js');

const customeraccount={
    getAllCustomerAccounts(callback){
        return db.query('SELECT * FROM customeraccount', callback)
    },
    getCustomerAccountByAccount(id, callback){
        return db.query("SELECT * FROM customeraccount WHERE idAccount=?",[id],callback);
    },
    getCustomerAccountByCustomer(id, callback){
        return db.query("SELECT * FROM customeraccount WHERE idCustomer=?",[id],callback);
    },
    addCustomerAccount(insertData, callback){
        return db.query('INSERT INTO customeraccount(idCustomer, idAccount) VALUES (?, ?)',[insertData.idCustomer,insertData.idAccount],callback);
    },
    updateCustomerAccount(updateData, id, callback){
        return db.query('UPDATE customeraccount SET idCustomer=?, idAccount=? WHERE idAccount=?',[updateData.idCard, updateData.idAccount, id], callback);
    },
    deleteCustomerAccount(id, callback){
        return db.query('DELETE FROM customeraccount WHERE idAccount=?',[id], callback);
    }
}

module.exports=customeraccount;