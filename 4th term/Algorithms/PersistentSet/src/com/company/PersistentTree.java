package com.company;

import java.util.ArrayList;

public class PersistentTree<T extends Comparable> {
    private enum Color {BLACK, RED};

    private class Node<T> {
        private T element;
        private Node<T> left;
        private Node<T> right;
        private Color color;

        public Node(T element, Node<T> left, Node<T> right) {
            this.element = element;
            this.left = left;
            this.right = right;
            this.color = Color.RED;
        }

        public Node(T element, Node<T> left, Node<T> right, Color color) {
            this.element = element;
            this.left = left;
            this.right = right;
            this.color = color;
        }

        public boolean isRed(){
            return color==Color.RED;
        }

        public void setColor(Color color) {
            this.color = color;
        }

        public Node clone() {
            return new Node<T>(this.element, this.left, this.right, this.color);
        }
    }

    private Node<T> root;
    private Node<T> nil;
    private ArrayList<Node<T>> roots;

    public PersistentTree() {
        this.nil = new Node<T>(null, null, null);
        this.nil.left = this.nil;
        this.nil.right = this.nil;
        this.nil.setColor(Color.BLACK);

        this.root = this.nil;
        this.roots = new ArrayList<>();
    }

    public void insert(T element) {

        ArrayList<Node<T>> path = new ArrayList<>();

        // walk down tree
        Node<T> a = !this.root.equals(this.nil) ? this.root.clone() : this.nil;
        while (!a.equals(this.nil)) {
            path.add(a);

            if (element.compareTo(a.element) < 0) {
                if (!a.left.equals(this.nil)) {
                    a.left = a.left.clone();
                }
                a = a.left;
            }
            else {
                if (!a.right.equals(this.nil)) {
                    a.right = a.right.clone();
                }
                a = a.right;
            }
        }

        Node<T> newNode = new Node<T>(element, this.nil, this.nil);

        // empty tree -> new root
        if (path.size() == 0) {
            this.root = newNode;
        }
        else if (element.compareTo(path.get(path.size()-1).element) < 0) {
            path.get(path.size()-1).left = newNode;
            this.root = path.get(0);
        }
        else {
            path.get(path.size()-1).right = newNode;
            this.root = path.get(0);
        }

        path.add(newNode);

        // fix
        fix(path);
        this.roots.add(this.root);
    }

    private void fix(ArrayList<Node<T>> path) {

        Node<T> node = path.get(path.size()-1);
        Node<T> parent = getParent(node, path);
        Node<T> grandParent = getParent(parent, path);

        while (parent.isRed()) {

            if (parent.equals(grandParent.left)) {
                //case 1
                if (grandParent.right.isRed()) {
                    parent.setColor(Color.BLACK);
                    Node<T> uncle = grandParent.right.clone();
                    grandParent.right = uncle;
                    uncle.setColor(Color.BLACK);
                    grandParent.setColor(Color.RED);

                    node = grandParent;
                    parent = getParent(node, path);
                    grandParent = getParent(parent, path);
                }
                // case 2
                else if (node.equals(parent.right)) {
                    leftRotate(parent, grandParent);

                    // swap in path
                    path.add(path.indexOf(parent), path.remove(path.indexOf(node)));

                    node = parent;
                    parent = getParent(node, path);
                }
                // case 3
                else {
                    parent.setColor(Color.BLACK);
                    grandParent.setColor(Color.RED);
                    rightRotate(grandParent, getParent(grandParent, path));
                }

            }
            else {
                // case 1
                if (grandParent.left.isRed()) {
                    parent.setColor(Color.BLACK);
                    Node<T> uncle = grandParent.left.clone();
                    grandParent.left = uncle;
                    uncle.setColor(Color.BLACK);
                    grandParent.setColor(Color.RED);

                    node = grandParent;
                    parent = getParent(node, path);
                    grandParent = getParent(parent, path);
                }
                // case 2
                else if (node.equals(parent.left)) {
                    rightRotate(parent, grandParent);

                    path.add(path.indexOf(parent), path.remove(path.indexOf(node)));

                    node = parent;
                    parent = getParent(node, path);
                }
                // case 3
                else {
                    parent.setColor(Color.BLACK);
                    grandParent.setColor(Color.RED);
                    leftRotate(grandParent, getParent(grandParent, path));
                }
            }
        }

        root.setColor(Color.BLACK);
    }

    private Node<T> getParent(Node<T> node, ArrayList<Node<T>> path) {
        return path.indexOf(node)-1 > -1 ? path.get(path.indexOf(node)-1) : this.nil;
    }

    public void leftRotate(Node<T> node, Node<T> parent) {
        Node<T> right = node.right;
        if (!right.left.equals(this.nil)) {
            node.right = right.left; // clone???
        } else {
            node.right = this.nil;
        }

        if (node.equals(this.root)) {
            this.root = right;
        } else if (node.equals(parent.left)) {
            parent.left = right;
        } else {
            parent.right = right;
        }
        right.left = node;
    }

    public void rightRotate(Node<T> node, Node<T> parent) {
        Node<T> left = node.left;
        if (!left.right.equals(this.nil)) {
            node.left = left.right; // clone??
        } else {
            node.left = this.nil;
        }

        if (node.equals(this.root)) {
            this.root = left;
        } else if (node.equals(parent.left)) {
            parent.left = left;
        } else {
            parent.right = left;
        }
        left.right = node;
    }

    // misc

    public ArrayList<T> inOrder() {
        ArrayList<T> arrayList = new ArrayList<T>();
        inOrderRec(this.root, arrayList);
        return arrayList;
    }

    private void inOrderRec(Node<T> node, ArrayList<T> arrayList) {
        if (node == this.nil) {
            return;
        }
        inOrderRec(node.left, arrayList);
        arrayList.add(node.element);
        inOrderRec(node.right, arrayList);
    }

    public String print() {
        String print = this.printRec(this.root, "", "+", this.root);
        System.out.print(print);
        return print;
    }

    public String printHistory() {
        String print = "";
        for (int i = 0; i < this.roots.size(); i++) {
            print += "Tree " + (i + 1) + ":\n";
            print += this.printRec(this.roots.get(i), "", "+", this.roots.get(i));
            print += "\n";
        }
        System.out.print(print);
        return print;

    }
    private String printRec(Node<T> node, String padding, String nodeId, Node<T> root) {
        if (node == this.nil) {
            return "";
        }

        String print = "";

        print += this.printRec(node.right, padding + "  ", "R", root);

        print += padding + nodeId + ":" + node.element.toString() + "\n";

        print += this.printRec(node.left, padding + "  ", "L", root);
        return print;
    }

    public static void main(String[] args) {
        PersistentTree<Integer> tree = new PersistentTree<Integer>();
        tree.insert(5);
        tree.insert(6);
        tree.insert(4);
        tree.insert(7);
        tree.insert(3);
        tree.insert(2);
        tree.printHistory();
    }

}
