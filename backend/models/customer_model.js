const db=require('../database');

const customer={
    getAllCustomer(callback) {
        return db.query("SELECT * FROM customer", callback);
        
    },

    getOneCustomer(id, callback) {
        return db.query("SELECT * FROM customer WHERE idCustomer = ? ", [id], callback)
    },

    addCustomer(addCustomer, callback) {
        return db.query("INSERT INTO customer VALUES (?,?,?,?,?)",
    [addCustomer.idCustomer, addCustomer.firstName, addCustomer.lastName, addCustomer.streetAddress, addCustomer.phoneNumber], callback);
    },

    updateCustomer(u, updateData, callback) {
        return db.query("UPDATE customer SET firstName=?,lastName=?,streetAddress=?,phoneNumber=? WHERE idCustomer = ?",
        [updateData.firstName,updateData.lastName,updateData.streetAddress,updateData.phoneNumber, u ],callback);
    },

    deleteCustomer(u, callback) {
        db.query("DELETE FROM customer WHERE idCustomer = ?", [u],callback);
    }
}

module.exports=customer;