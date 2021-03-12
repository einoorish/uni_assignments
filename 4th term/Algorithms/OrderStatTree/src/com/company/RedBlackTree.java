package com.company;

import java.util.Iterator;

public class RedBlackTree <K extends Comparable<K>, V>  {

    protected enum Color {
        RED,
        BLACK
    };

    private class Node {
        K key;
        V value;
        Node left = null, right = null;
        Color color = Color.RED;

        Node(K key, V value) {
            this.key = key;
            this.value = value;
        }
    }

    private Node root = null;
    private int size = 0;

    private Node search(Node node, K key) {

        if (node == null)
            return null;

        if (key.compareTo(node.key) > 0)
            return search(node.right, key);
        else if (key.compareTo(node.key) < 0)
            return search(node.left, key);
        else
            return node;
    }

    private Node leftRotate(Node pivot) {
        Node current = pivot.right;

        pivot.right = current.left;
        current.left = pivot;

        current.color = pivot.color;
        pivot.color = Color.RED;

        return current;
    }

    private Node rightRotate(Node pivot) {
        Node current = pivot.left;

        pivot.left = current.right;
        current.right = pivot;

        current.color = pivot.color;
        pivot.color = Color.RED;

        return current;
    }

    private void recolor(Node node) {
        node.color = Color.RED;
        node.left.color = Color.BLACK;
        node.right.color = Color.BLACK;
    }

    private boolean isRed(Node node) {
        return node!=null && node.color == Color.RED;
    }

    private Node insert(Node node, K key, V value) {

        if (node == null) {
            size++;
            return new Node(key, value);
        }

        if (key.compareTo(node.key) < 0)
            node.left = insert(node.left, key, value);
        else if (key.compareTo(node.key) > 0)
            node.right = insert(node.right, key, value);
        else
            node.value = value;

        if (isRed(node.right) && !isRed(node.left)) {
            node = leftRotate(node);
        }
        if (isRed(node.left) && isRed(node.left.left)) {
            node = rightRotate(node);
        }
        if (isRed(node.left) && isRed(node.right)) {
            recolor(node);
        }

        return node;
    }

    private Node getMin(Node node) {
        if (node.left == null)
            return node;
        return getMin(node.left);
    }

    private Node removeMin(Node node) {

        if (node.left == null) {
            Node rightNode = node.right;
            node.right = null;
            return rightNode;
        }

        node.left = removeMin(node.left);
        return node;
    }

    private Node remove(Node node, K key) {

        if (node == null)
            return null;

        if (key.compareTo(node.key) < 0) {
            node.left = remove(node.left, key);
            return node;
        } else if (key.compareTo(node.key) > 0) {
            node.right = remove(node.right, key);
            return node;
        } else {

            if (node.left == null) {
                Node rightNode = node.right;
                node.right = null;
                return rightNode;
            }

            if (node.right == null) {
                Node leftNode = node.left;
                node.left = null;
                return leftNode;
            }

            Node successor = getMin(node.right);
            successor.right = removeMin(node.right);
            successor.left = node.left;

            node.left = node.right = null;

            size--;
            return successor;
        }
    }

    public void print(){
        String prefix = "";
        print(root, prefix);
    }

    private void print(Node node, String prefix) {
        if(node == null) return;

        System.out.println(prefix + " ↳ (" + node.key + ": " + node.value + ") - " + node.color);
        print(node.left , prefix + "   ");
        print(node.right , prefix + "   ");
    }

    public V get(K key) {
        Node node = search(key);
        return node == null ? null : node.value;
    }

    public void set(K key, V newValue) {
        Node node = search(key);
        if (node != null)
            node.value = newValue;
    }

    public int getSize() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public Node search(K key){
        return search(root, key);
    }

    public boolean contains(K key) {
        return search(root, key) != null;
    }

    public void insert(K key, V value) {
        root = insert(root, key, value);
        root.color = Color.BLACK;
    }

    public V remove(K key) {

        Node node = search(key);
        if (node != null) {
            root = remove(root, key);
            return node.value;
        }
        return null;
    }

}
