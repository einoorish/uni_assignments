package com.example.budgettracker.Model

import java.util.*

class Transaction(
    var id:Int,
    var value: Double,
    var title: String,
    var date: Date,
    var category_id: Int,
    var account_id: Int
)