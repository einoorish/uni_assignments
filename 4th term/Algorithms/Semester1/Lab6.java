package com.company;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class Main {

    private static void computeTable(String W, ArrayList<Integer> T) {
        int pos = 1; //поточна позиція в T
        int cnd = 0; //базований на нулі індекс у W наступного символу в поточному підрядку кандидаті
        T.set(0,-1); //фіксоване значення для того, щоб алгоритм не зациклився після першого невдалого порівняння

        while (pos < W.length()) {
            //перший варіант: підрядок продовжується
            if (W.charAt(pos) == W.charAt(cnd)) {
                T.set(pos++,++cnd);
            }
            //другий випадок: не продовжується, але ми можемо відступити
            else {
                if (cnd > 0) {
                    cnd = T.get(cnd - 1);
                }
                //третій випадок: ми вичерпали всіх кандидатів.  Зауважимо cnd = 0
                else
                    T.set(pos++,0);
            }
        }
    }


    //S - текст пошуку, W - паттерн
    //повертає позицію, на якій знайдено повний збіг, або -1, якщо не знайдено збігів
    private static int kmp_search(String S, String W){
        int m = 0; //початок поточного збігу в S
        int i = 0; //позиція поточного символу в W)
        // зберігає кількість повернень, які ми маємо зробити після невдачного порівняння S[m + i] з W[i]
        ArrayList<Integer> T = new ArrayList<Integer>(Collections.nCopies(S.length(), 0));
        computeTable(W, T); //заповнення таблиці

        while(m+i < S.length()){
            if(W.charAt(i) == S.charAt(m+i)){
                //вдале завершення алгоритму
                if(i == W.length()-1)
                    return m;
                i++;
            } else {
                m += i-T.get(i);
                if(T.get(i)>-1)
                    i=T.get(i);
                else
                    i=0;
            }
        }
        // пошук завершився невдачею
        return -1;
    }

    public static void main(String[] args) {
        //String str1 = "ABC ABCDAB ABCDABCDABDE";
        //String str2 = "CDAB ABCDABCDABDEABC AB";

        Scanner scanner = new Scanner(System.in);

        System.out.println("String1: ");
        String str1 = scanner.nextLine();
        System.out.println("String1: ");
        String str2 = scanner.nextLine();

        if(str1.length()!=str2.length()) {
            System.out.println(false);
            return;
        }

        System.out.println(kmp_search(str1+str1,str2) != -1);
    }
}
