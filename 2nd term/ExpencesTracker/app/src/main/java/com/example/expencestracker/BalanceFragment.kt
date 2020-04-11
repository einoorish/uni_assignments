package com.example.expencestracker

import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup

/**
 * A simple [Fragment] subclass.
 * Use the [BalanceFragment.newInstance] factory method to
 * create an instance of this fragment.
 */
class BalanceFragment : Fragment() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
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
