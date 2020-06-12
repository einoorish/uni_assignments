package com.example.budgettracker.Adapter

import android.os.AsyncTask
import okhttp3.*
import java.io.IOException
import kotlin.coroutines.coroutineContext

open class CurrencyConverter (val from:String, val to:String, val balance:String ): AsyncTask<Void, Void, String>() {

    //TODO: improve handling background tasks

    override fun doInBackground(vararg params: Void?): String? {

        val client = OkHttpClient()

        var result : String = ""

        val request: Request = Request.Builder()
            .url("https://currency-converter5.p.rapidapi.com/currency/convert?format=json&from=$from&to=$to&amount=$balance")
            .get()
            .addHeader("x-rapidapi-host", "currency-converter5.p.rapidapi.com")
            .addHeader("x-rapidapi-key", "76c1607843mshbc4b3a596c038ddp16b433jsned57400b49be")
            .build()

        client.newCall(request).enqueue(object : Callback {
            override fun onFailure(call: Call, e: IOException) {
                e.printStackTrace()
            }

            override fun onResponse(call: Call, response: Response) {
                response.use {
                    if (!response.isSuccessful) throw IOException("Unexpected code $response")

                    // JSONObject obj = new JSONObject(response.body.string())
                    result = it.body!!.string()

                }
            }
        })
        return result
    }


}