package com.company;

public class Main {

    public static void main(String[] args) {
        final String[] author_names = {"RobertSingh", "MargaretAtwood", "JokhaAlharthi", "AkkithamNamboodri", "RichardPower", "NarendraModi", "SusanNinan"};
        final String[] book_names = {"Politics of Opportunism", "The Testaments", "Celestial Bodies", "Malayalam poetry", "The Overstory", "The Braille edition of the book Exam Warriors", "Mind - Master"};

        SplayTree<String, String> tree = new SplayTree<>();
        for(int i = 0; i < 7; i++){
            tree.insert(author_names[i], book_names[i]);
        }
        tree.print();

        tree.search("RobertSingh");
        System.out.println("\nThe tree after searching for RobertSingh:\n");
        tree.print();

        tree.search("RichardPower");
        System.out.println("\nThe tree after searching for RichardPower:\n");
        tree.print();

        tree.search("RobertSingh");
        System.out.println("\nThe tree after searching for RobertSingh:\n");
        tree.print();
    }
}
