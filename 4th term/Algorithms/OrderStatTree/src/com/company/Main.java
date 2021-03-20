package com.company;

public class Main {

    static void demoOSTree(){
        final String[] author_names = {"RobertSingh", "AkkithamNamboodri", "MargaretAtwood", "JokhaAlharthi", "RichardPower", "NarendraModi","SusanNinan"};
        final String[] book_names = {"Politics of Opportunism", "Malayalam poetry", "The Testaments", "Celestial Bodies", "The Overstory", "The Braille edition of the book Exam Warriors", "Mind - Master"};

        OrderStatTree<String, String> tree = new OrderStatTree<>();
        for(int i = 0; i < 7; i++){
            tree.insert(author_names[i], book_names[i]);
        }
        tree.print();

        System.out.println("\n2nd smallest element in the tree: " + tree.select(2));
        System.out.println("1nd smallest element in the tree: " + tree.select(1));
        System.out.println("4nd smallest element in the tree: " + tree.select(4));

        System.out.println("\nRank of RobertSingh: " + tree.rank("RobertSingh"));
        System.out.println("Rank of MargaretAtwood: " + tree.rank("MargaretAtwood"));

        System.out.println("\n\nRemoving JokhaAlharthi from tree: \n");
        tree.remove("JokhaAlharthi");
        tree.print();

        System.out.println("\n\nRemoving RichardPower from tree: \n");
        tree.remove("RichardPower");
        tree.print();
    }


    static void demoOSTree1(){
        final int[] author_names = {1, 2, 3, 4, 5, 6, 7};
        final String[] book_names = {"Politics of Opportunism", "Malayalam poetry", "The Testaments", "Celestial Bodies", "The Overstory", "The Braille edition of the book Exam Warriors", "Mind - Master"};

        OrderStatTree<Integer, String> tree = new OrderStatTree<>();
        for(int i = 0; i < 7; i++){
            tree.insert(author_names[i], book_names[i]);
        }
        tree.print();

        System.out.println("\n2nd smallest element in the tree: " + tree.select(2));
        System.out.println("1nd smallest element in the tree: " + tree.select(1));
        System.out.println("4nd smallest element in the tree: " + tree.select(4));

        System.out.println("\nRank of 2: " + tree.rank(2));
        System.out.println("Rank of 1: " + tree.rank(1));
        System.out.println("Rank of 4: " + tree.rank(4));

        System.out.println("\n\nRemoving 4 from tree: \n");
        tree.remove(4);
        tree.print();

        System.out.println("\n\nRemoving 1 from tree: \n");
        tree.remove(1);
        tree.print();
    }


    public static void main(String[] args) {
        demoOSTree();
    }
}
