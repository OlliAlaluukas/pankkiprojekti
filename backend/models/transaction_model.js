const db = require('../database');

const transaction = {
  getAll: function(callback) {
    return db.query('select * from transaction', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from transaction where idAccount=?', [id], callback);
  },
  add: function(transaction, callback) {
    return db.query(
      'insert into transaction (idTransaction,idAccount,idCard,dateAndTime,transactionType,transactionAmount,participantAccount) values(?,?,?,?,?,?,?)',
      [transaction.idTransaction, transaction.idAccount, transaction.idCard, transaction.dateAndTime, transaction.transactionType, transaction.transactionAmount, transaction.participantAmount],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from transaction where idTransaction=?', [id], callback);
  },
  update: function(id, transaction, callback) {
    return db.query(
      'update transaction set idAccount=?,idCard=?, dateAndTime=?, transactionType=?, transactionAmount=?, participantAmount=? where idTransaction=?',
      [transaction.idTransaction, transaction.idAccount, transaction.idCard, transaction.dateAndTime, transaction.transactionType, transaction.transactionAmount, transaction.participantAmount, id],
      callback
    );
  }
};
module.exports = transaction;