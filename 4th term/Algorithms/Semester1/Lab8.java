package com.company;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;

public class Main {

//---------------------------------------Наївний---------------------------------------//

    static int naive(String str, String template){
        for (int i = 0; i <= str.length() - template.length(); i++) {
            int j = 0;
            for (; j < template.length(); j++)
                if (str.charAt(i + j) != template.charAt(j))
                    break;

            if (j == template.length())
                return i;
        }
        return -1;
    }

//------------------------------------Rabin-Karp-------------------------------------//

    private static int RK_search(String str, String template){
    	final int primeNumber = 13;
    	int str_length = str.length();
        int template_length = template.length();

        //array for powers of primeNumber
    	long[] pows = new long[str_length];
    	Arrays.fill(pows, 1);
    	for(int i = 1; i < str_length; i++)
    	    pows[i] = pows[i-1]*primeNumber;


        long[] hash = new long[str_length];
        for(int i = 0; i<str_length; i++){
            hash[i] = (int)(str.charAt(i)-'a'+1)*pows[i];
            if(i!=0)
                hash[i] += hash[i-1];
        }

        //calculating hash sum
        long hash_sum = 0;
        for(int i = 0; i < template_length; ++i)
            hash_sum+=(template.charAt(i)-'a'+1)*pows[i];

        for (int i = 0; i + template_length - 1 < str.length(); ++i){
            long cur_hash = hash[i + template_length - 1];
            if (i!=0)  cur_hash -= hash[i - 1];
            //comparing hashes
            if (cur_hash == hash_sum * pows[i])
                return i;
        }

        return -1;
    }

//---------------------------------------КМП--------------------------------------//

    private static void computeKMPTable(String str, ArrayList<Integer> T) {
        int pos = 1; //current position in table T
        int cnd = 0; //index in str of the next character of the current candidate substring
        T.set(0,-1);

        while (pos < str.length()) {
            if (str.charAt(pos) == str.charAt(cnd)) {
                T.set(pos++,++cnd);
            }
            else {
                if (cnd > 0) {
                    cnd = T.get(cnd - 1);
                } else
                    T.set(pos++,0);
            }
        }
    }

    private static int KMP_search(String str, String template){
        int pos_in_str = 0, shift = 0;
        ArrayList<Integer> T = new ArrayList<Integer>(Collections.nCopies(str.length(), 0));
        computeKMPTable(template, T); //filling the table

        while(pos_in_str + shift < str.length()){
            if(template.charAt(shift) == str.charAt(pos_in_str+shift)){
                //success
                if(shift == template.length()-1)
                    return pos_in_str;
                shift++;
            } else {
                pos_in_str += shift-T.get(shift);
                if(T.get(shift)>-1)
                    shift=T.get(shift);
                else
                    shift=0;

            }
        }
        //pattern wasn't found
        return -1;
    }


//---------------------------------------Хорспул--------------------------------------//

    private static int Horspool(String source, String template) {
        int source_length = source.length();
        int template_length = template.length();

        //preprocessing the pattern
        HashMap<Character, Integer> offsetTable = new HashMap<Character, Integer>();
        for (int i = 0; i <= 255; i++)
            offsetTable.put((char) i, template_length);
        for (int i = 0; i < template_length - 1; i++)
            offsetTable.put(template.charAt(i), template_length - i - 1);

        //search
        int i = template_length - 1;
        int j = i;
        int k = i;
        while (j >= 0 && i <= source_length - 1) {
            j = template_length - 1;
            k = i;
            while (j >= 0 && source.charAt(k) == template.charAt(j)) {
                k--;
                j--;
            }
            i += offsetTable.get(source.charAt(i));
        }
        if (k >= source_length - template_length) {
            return -1;
        } else {
            return k + 1;
        }
    }

//---------------------------------------Боєр-Мур--------------------------------------//

    private static int ABC_SIZE = 256;

    //The max function is used to make sure that we get a positive shift.
    private static int max(int a, int b) { return Math.max(a, b); }

    private static void badCharHeuristic( String template, int[] badchar) {
        for (int i = 0; i < template.length(); i++)
            badchar[(int) template.charAt(i)] = i;
    }

    private static int Boyer_Moore(String source, String template) {
        int template_length = template.length();
        int source_length = source.length();

        int[] badchar = new int[ABC_SIZE];
        Arrays.fill(badchar, -1);
        // fill the actual value of last occurrence of a character
        badCharHeuristic(template, badchar);

        int shift = 0;  // s is shift of the pattern with respect to source
        while(shift <= (source_length - template_length)){
            int j = template_length-1;


        while(j >= 0 && template.charAt(j) == source.charAt(shift+j))
            j--;

            if (j < 0){
                return shift;
            }

            else
                //Shift the pattern so that the bad character in text aligns with
                //the last occurrence of it in pattern.
                shift += max(1, j - badchar[source.charAt(shift+j)]);
        }
        return -1;
    }

//--------------------------------------------------------------------------------//

    public static void main(String[] args) {
        String str1 = "THIS IS A TEST TEXT";
        String str2 = "TEXT";


        System.out.println(naive(str1, str2));
        System.out.println(KMP_search(str1, str2));
        System.out.println(Horspool(str1, str2));
        System.out.println(Boyer_Moore(str1, str2));
        System.out.println(RK_search(str1, str2));

    }
}
