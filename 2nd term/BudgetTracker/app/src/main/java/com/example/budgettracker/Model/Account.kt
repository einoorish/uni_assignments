package com.example.budgettracker.Model

class Account {

    var id : Int = 0
    var type: AccountType = AccountType.REGULAR
    var name: String = "Account"
    var currency: String = "UAH" //TODO: come up w/ efficient way to store and retrieve exchange rates
    var balance: Double = 0.0


    constructor(){}

    constructor(type: AccountType, name: String, currency: String, balance: Double){
        this.type = type
        this.name = name
        this.currency = currency
        this.balance = balance
    }

    constructor(Currency: String, Balance: Double, Name: String){
        this.name = Name
        this.currency = Currency
        this.balance = Balance
    }

}