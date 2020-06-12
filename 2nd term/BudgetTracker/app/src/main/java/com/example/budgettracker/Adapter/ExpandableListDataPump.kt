package com.example.budgettracker.Adapter

import android.util.Log
import android.widget.ExpandableListView
import com.example.budgettracker.Model.Account
import com.example.budgettracker.Model.AccountType
import com.google.firebase.database.*
import kotlinx.android.synthetic.main.fragment_balance.*
import java.util.*
import kotlin.collections.ArrayList

fun fetchDataFromDB(ref : DatabaseReference, type : AccountType): MutableList<Account?> {
    val list: MutableList<Account?> = ArrayList()

    val eventListener: ValueEventListener = object : ValueEventListener {
        override fun onDataChange(dataSnapshot: DataSnapshot) {
            for (ds in dataSnapshot.children) {

                var acc = ds.getValue(Account::class.java)
                acc?.type = type
                list.add(acc)
            }
            list.add(null)
        }
        override fun onCancelled(databaseError: DatabaseError) {}
    }
    ref.addListenerForSingleValueEvent(eventListener)

    return list
}

public fun getData(): HashMap<String, List<Account?>>{
    val rootRef = FirebaseDatabase.getInstance().reference.child("user").child("Accounts")

    val expandableListDetail = HashMap<String, List<Account?>>()

    expandableListDetail["REGULAR"] = fetchDataFromDB(rootRef.child("REGULAR"), AccountType.REGULAR)
    expandableListDetail["DEBT"] = fetchDataFromDB(rootRef.child("DEBT"), AccountType.DEBT)
    expandableListDetail["SAVINGS"] = fetchDataFromDB(rootRef.child("SAVINGS"), AccountType.SAVINGS)

    //TODO:notify adapter when all data is fetched

    return expandableListDetail
}

