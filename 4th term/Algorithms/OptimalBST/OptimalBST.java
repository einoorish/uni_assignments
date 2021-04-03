package com.company;

import java.text.DecimalFormat;

public class OptimalBST {

    private int[] keys;
    private double[] probs;
    private int numOfKeys;
    private int numColumns;
    private int numRows;
    private double[][] costTable;
    private int[][] rootTable;

    OptimalBST(int[] _keys, double[] probabilities) {
        keys = _keys;
        probs = probabilities;
        numOfKeys = probs.length;

        numColumns = numOfKeys + 1;
        numRows = numOfKeys + 2;

        costTable = new double[numRows][numColumns];
        rootTable = new int[numRows][numColumns];
    }

    void generateOptimalBST() {
        for (int i = 1; i < numColumns; i++) {
            costTable[i][i - 1] = 0;
            costTable[i][i] = probs[i-1];
            rootTable[i][i] = keys[i-1];
        }

        for (int i = 1; i < numOfKeys; i++) {
            for (int j = 1; j < (numOfKeys - i) + 1; j++) {
                int minKey = 0;
                double minCost = Float.MAX_VALUE;

                for (int k = j; k < j + i + 1; k++) {
                    double cost1 = costTable[j][k - 1];
                    double cost2 = costTable[k + 1][j + i];
                    if ((cost1 + cost2) < minCost) {
                        minCost = cost1 + cost2;
                        minKey = keys[k-1];
                    }
                }
                rootTable[j][j+i] = minKey;
                double sum = probs[j];
                for (int s = j + 1; s < j + i; s++) {
                    sum += probs[s];
                }
                costTable[j][j + i] = minCost + sum;
            }
        }
    }

    void printCostTable() {
        DecimalFormat df = new DecimalFormat("####0.0");
        System.out.print("\t-------------------  COST TABLE -------------------\n\t\t");

        for (int i = 0; i < numRows; i++) {
            if (i != 0)
                System.out.print("\t" +  i + "\t");

            for (int j = 0; j < numColumns; j++) {
                if (i != 0){
                    System.out.print("\t" + df.format(costTable[i][j]) + "\t");
                } else {
                    System.out.print("\t" + j + "\t");
                }
            }
            System.out.println("\n");
        }
    }

    void printRootTable() {
        System.out.print("\t-------------------  ROOT TABLE -------------------\n\t\t");

        for (int i = 0; i < numRows; i++) {
            if (i != 0)
                System.out.print("\t" +  i + "\t");

            for (int j = 0; j < numColumns; j++) {
                if (i != 0)
                    System.out.print("\t" + rootTable[i][j] + "\t");
                else
                    System.out.print("\t" + j + "\t");
            }
            System.out.println("\n");
        }
    }
}

