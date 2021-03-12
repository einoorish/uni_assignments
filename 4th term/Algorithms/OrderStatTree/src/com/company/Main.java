package com.company;

public class Main {

    public static void testRBTree(){

        final String[] author_names = {"RobertSingh", "AkkithamNamboodri", "MargaretAtwood", "JokhaAlharthi", "RichardPower", "NarendraModi","SusanNinan"};

        final String[] book_names = {"Politics of Opportunism", "Malayalam poetry", "The Testaments", "Celestial Bodies", "The Overstory", "The Braille edition of the book Exam Warriors", "Mind - Master"};

        RedBlackTree<String, String> tree = new RedBlackTree<>();
        for(int i = 0; i < 7; i++) {
            tree.insert(author_names[i], book_names[i]);
        }

        tree.print();

        System.out.println("\n\nRemoving JokhaAlharthi from tree: \n");

        tree.remove("JokhaAlharthi");
        tree.print();

        System.out.println("\n\nRemoving RichardPower from tree: \n");

        tree.remove("RichardPower");
        tree.print();

    }

    public static void main(String[] args) {
            testRBTree();
    }
}
