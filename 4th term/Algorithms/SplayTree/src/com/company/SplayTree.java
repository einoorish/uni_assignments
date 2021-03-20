package com.company;

public class SplayTree <K extends Comparable<K>, V> {

    class Node {
        K key;
        V value;
        Node left = null, right = null;

        Node(K key, V value){
            this.key = key;
            this.value = value;
        }
    }

    Node root = null;

    private Node leftRotate(Node pivot) {
        try{
            Node current = pivot.right;
            pivot.right = current.left;
            current.left = pivot;
            return current;
        } catch (NullPointerException e) {
            return pivot;
        }
    }

    private Node rightRotate(Node pivot) {
        try{
            Node current = pivot.left;
            pivot.left = current.right;
            current.right = pivot;
            return current;
        } catch (NullPointerException e) {
            return pivot;
        }
    }

    private Node splay(Node root, K key) {
        // Base Case: key is root
        if (root == null || key.compareTo(root.key) == 0)
            return root;

        // Case1: Key lies in left subtree
        if (key.compareTo(root.key) < 0) {
            if (root.left == null) return root; // Key not found

            //Case 1.1: parent is a left child of key's grandparent
            // => two right rotations (RR, RR)
            if (key.compareTo(root.left.key) < 0) {
                root.left.left = splay(root.left.left, key);

                root = rightRotate(root);
            }

            //Case 1.2: parent is a right child of key's grandparent
            // => (LR, RR)
            else if (key.compareTo(root.left.key) > 0) {
                root.left.right = splay(root.left.right, key);

                if (root.left.right != null)
                    root.left = leftRotate(root.left);
            }

            return rightRotate(root);
        }
        // Case 2: Key lies in right subtree
        else  {
            if (root.right == null) return root; // Key not found

            //Case 2.2: parent is a right child of key's grandparent
            // => (RR, LR)
            if (key.compareTo(root.right.key) < 0) {
                root.right.left = splay(root.right.left, key);

                root.right = rightRotate(root.right);
            }
            //Case 2.2: parent is a right child of key's grandparent
            // => (LR, LR)
            else if(key.compareTo(root.right.key) > 0){
                root.right.right = splay(root.right.right, key);

                root = leftRotate(root);
            }

            return leftRotate(root);
        }
    }

    void print(Node root, String prefix) {
        if (root == null) return;

        System.out.println(prefix + " ↳ (" + root.key + ": " + root.value + ")");
        print(root.left, prefix + "   ");
        print(root.right, prefix + "   ");
    }

    private Node insert(Node root, Node node) {
        if (root == null)
            root = node;

        if (node.key.compareTo(root.key) < 0) {
            root.left = insert(root.left, node);
        } else if (node.key.compareTo(root.key) > 0) {
            root.right = insert(root.right, node);
        }

        return root;
    }

    /**
     * Search operation in Splay tree works like standard BST search, but it also splays (moves a node to the root).
     * If key is present in tree then, it is moved to root.
     * Else the last node accessed prior to reaching the NULL is splayed and becomes the new root.
     * **/
    public Node search(K key) {
        root = splay(root, key);
        return root;
    }

    public void print() {
        print(root,"");
    }

    public Node insert(K key, V value){
        Node node = new Node(key, value);
        root = insert(root, node);
        return root;
    }

}
