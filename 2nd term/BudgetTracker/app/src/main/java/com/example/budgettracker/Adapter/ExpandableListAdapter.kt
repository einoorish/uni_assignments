package com.example.budgettracker.Adapter

import android.content.Context
import android.view.LayoutInflater
import android.view.View
import android.view.View.GONE
import android.view.View.VISIBLE
import android.view.ViewGroup
import android.widget.*
import com.example.budgettracker.Model.Account
import com.example.budgettracker.Model.AccountType
import com.example.budgettracker.R
import java.util.*


class ExpandableListAdapter(var context: Context, var expandableListView: ExpandableListView, var group: MutableList<String>,
                            var children: HashMap<String, List<Account?>>) : BaseExpandableListAdapter() {

    override fun getGroup(groupPosition: Int): String {
        return group[groupPosition]
    }

    override fun isChildSelectable(groupPosition: Int, childPosition: Int): Boolean {
        return true;
    }

    override fun hasStableIds(): Boolean {
        return false
    }

    override fun getGroupView(groupPosition: Int, isExpanded: Boolean, convertView: View?, parent: ViewGroup?): View {
        var convertView = convertView
        if(convertView == null){
            val inflater = context.getSystemService(Context.LAYOUT_INFLATER_SERVICE) as LayoutInflater
            convertView = inflater.inflate(R.layout.expandable_group,null)
        }

        val title = convertView?.findViewById<TextView>(R.id.listTitle)
        val balanceView = convertView?.findViewById<TextView>(R.id.listBalance)

        title?.text = getGroup(groupPosition)

        var balanceValue: Double = 0.0
        for(child in children[getGroup(groupPosition)]!!)
            if(child!=null)
                    balanceValue+=child.balance
        balanceView?.text = balanceValue.toString() + " UNITS"

        convertView?.setOnClickListener {
            if(expandableListView.isGroupExpanded(groupPosition))
                expandableListView.collapseGroup(groupPosition)
            else{
                expandableListView.expandGroup(groupPosition)
                expandableListView.smoothScrollToPositionFromTop(expandableListView.getCount()*2+1, 0, 500);
            }
        }
        return convertView!!
    }

    override fun getChildrenCount(groupPosition: Int): Int {
        return children[group[groupPosition]]!!.size
    }

    override fun getChild(groupPosition: Int, childPosition: Int): Account? {
        return children[group[groupPosition]]!![childPosition]
    }

    override fun getGroupId(groupPosition: Int): Long {
        return groupPosition.toLong()
    }

    override fun getChildView(groupPosition: Int, childPosition: Int, isLastChild: Boolean,
                              convertView: View?, parent: ViewGroup?): View {
        var convertView = convertView
        if(convertView == null){
            val inflater = context.getSystemService(Context.LAYOUT_INFLATER_SERVICE) as LayoutInflater
            convertView = inflater.inflate(R.layout.expandable_group_item,null)
        }

        if(childPosition == 0 && !isLastChild)
            convertView?.setBackgroundResource(R.drawable.rounded_top_background)
        else if(childPosition!=0)
            convertView?.setBackgroundResource(R.drawable.rectangle_background)


        val thisChild = getChild(groupPosition,childPosition);

        val title = convertView?.findViewById<TextView>(R.id.expandedListItem_title)
        val balance = convertView?.findViewById<TextView>(R.id.expandedListItem_balance)
        val type = convertView?.findViewById<ImageView>(R.id.expandedListItem_icon)

        if(thisChild != null){
            title?.text = thisChild.name

            if(thisChild.balance > 0){
                balance?.setTextColor(context.getResources().getColor(R.color.Green))
            }else
                balance?.setTextColor(context.getResources().getColor(R.color.Red))

            balance?.visibility = VISIBLE
            balance?.text = thisChild.balance.toString() + " " + thisChild.currency

            if(thisChild.type == AccountType.SAVINGS) type?.setBackgroundResource(R.drawable.savings_32)
            else type?.setBackgroundResource(R.drawable.card_32)

            title?.setOnClickListener {
                Toast.makeText(
                    context,
                    thisChild.name + getChildrenCount(groupPosition),
                    Toast.LENGTH_SHORT
                ).show()
            }
        } else {
            //TODO: inflate special layout
            balance?.visibility = GONE;
            convertView?.setBackgroundResource(R.drawable.rounded_bottom_background)
            title?.text = "Add"

            title?.setOnClickListener {
                Toast.makeText(context, "Add item", Toast.LENGTH_SHORT).show()

            }
        }

        return convertView!!
    }

    override fun getChildId(groupPosition: Int, childPosition: Int): Long {
        return childPosition.toLong()
    }

    override fun getGroupCount(): Int {
        return group.size
    }


}