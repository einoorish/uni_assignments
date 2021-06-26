package com.company;

public class Main {

    public static void main(String[] args) {

        double probs[] = {0.1, 0.2, 0.3, 0.5, 0.4};
        int keys[] = {1, 2, 3, 4, 5};

        OptimalBST optimalBST = new OptimalBST(keys, probs);

        optimalBST.generateOptimalBST();
        optimalBST.printCostTable();
        optimalBST.printRootTable();
    }
}
