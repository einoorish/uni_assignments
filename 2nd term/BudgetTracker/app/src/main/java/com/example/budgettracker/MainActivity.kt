package com.example.budgettracker

import android.os.Bundle
import android.view.View
import android.widget.AdapterView
import androidx.appcompat.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_main.*
import me.ibrahimsn.lib.OnItemSelectedListener

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        //Item at index 1 (Expences) will be automatically selected as application opens
        if (savedInstanceState == null) {
            bottom_nav_bar.setActiveItem(1)

            val fragment = ExpencesFragment()
            supportFragmentManager.beginTransaction()
                    .replace(R.id.container, fragment, fragment.javaClass.simpleName)
                    .commit()
        }


        bottom_nav_bar.setOnItemSelectedListener(object : AdapterView.OnItemSelectedListener,
            OnItemSelectedListener {
            override fun onItemSelect(pos: Int) {
                when (pos) {
                    0 -> {
                        val fragment = BalanceFragment()
                        supportFragmentManager.beginTransaction()
                                .replace(R.id.container, fragment, fragment.javaClass.getSimpleName())
                                .commit()
                    }
                    1 -> {
                        val fragment = ExpencesFragment()
                        supportFragmentManager.beginTransaction()
                                .replace(R.id.container, fragment, fragment.javaClass.getSimpleName())
                                .commit()
                    }
                    2 -> {
                        val fragment = TransactionsFragment()
                        supportFragmentManager.beginTransaction()
                                .replace(R.id.container, fragment, fragment.javaClass.getSimpleName())
                                .commit()
                    }
                    3 -> {
                        val fragment = OverviewFragment()
                        supportFragmentManager.beginTransaction()
                                .replace(R.id.container, fragment, fragment.javaClass.getSimpleName())
                                .commit()
                    }
                }
            }

            override fun onNothingSelected(parent: AdapterView<*>?) {
                TODO("Not yet implemented")
            }

            override fun onItemSelected(
                parent: AdapterView<*>?,
                view: View?,
                position: Int,
                id: Long
            ) {
                TODO("Not yet implemented")
            }
        })
    }
}
