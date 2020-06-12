package com.example.budgettracker

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.fragment.app.Fragment
import com.example.budgettracker.Adapter.ExpandableListAdapter
import com.example.budgettracker.Adapter.getData
import com.example.budgettracker.Model.Account
import kotlinx.android.synthetic.main.fragment_balance.*
import java.util.*

class BalanceFragment : Fragment() {

    override fun onActivityCreated(savedInstanceState: Bundle?) {
        super.onActivityCreated(savedInstanceState)

        (activity as AppCompatActivity).supportActionBar?.title = "Balance"

        val expandableListDetail : HashMap<String, List<Account?>> = getData()
        val expandableListTitle : MutableList<String> = expandableListDetail.keys.toMutableList()
        val expandableListAdapter =
            ExpandableListAdapter(
                this.context!!,
                expandableListView!!,
                expandableListTitle,
                expandableListDetail
            )

        expandableListView?.setAdapter(expandableListAdapter)

        expandableListView?.setOnGroupExpandListener {
            Toast.makeText(context,
                expandableListTitle[it] + " List Expanded.",
                Toast.LENGTH_SHORT).show();
        }
 
        expandableListView?.setOnGroupCollapseListener {
            Toast.makeText(context,
                expandableListTitle[it] + " List Collapsed.",
                Toast.LENGTH_SHORT).show();
        }

        expandableListView.expandGroup(0)

    }

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        return inflater.inflate(R.layout.fragment_balance, container, false)
    }

    companion object {
        @JvmStatic
        fun newInstance() =
            BalanceFragment().apply {
                arguments = Bundle().apply {
                }
            }
    }

}
