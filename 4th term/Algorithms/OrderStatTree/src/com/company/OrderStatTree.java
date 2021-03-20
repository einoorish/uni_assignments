package com.company;

class OrderStatTree <K extends Comparable<K>, V> {

    protected enum Color {
        RED,
        BLACK
    };

    class Node {
        K key;
        V value;
        int size = 1;
        Node left = null, right = null, parent = null;
        Color color = Color.RED;

        Node(K key, V value) {
            this.key = key;
            this.value = value;
        }
    }

    private Node root = null;

    /*** Helper methods used for element insertion ***/

    private void recolor(Node node) {
        node.color = Color.RED;
        node.left.color = Color.BLACK;
        node.right.color = Color.BLACK;
    }

    private boolean isRed(Node node) {
        return node!=null && node.color == Color.RED;
    }

    private Node leftRotate(Node pivot) {
        Node current = pivot.right;

        //fixing size attribute
        int current_prev_size = current.size;
        current.size = pivot.size;
        pivot.size = current_prev_size;

        pivot.right = current.left;
        current.left = pivot;

        current.color = pivot.color;
        pivot.color = Color.RED;

        //fixing parent attribute
        current.parent=pivot.parent;
        pivot.parent = current;
        if(pivot.right!=null)
            pivot.right.parent = pivot;
        return current;
    }

    private Node rightRotate(Node pivot) {
        Node current = pivot.left;

        pivot.left = current.right;
        current.right = pivot;

        current.color = pivot.color;
        pivot.color = Color.RED;

        //fixing size attribute
        int current_prev_size = current.size - 1;
        current.size = pivot.size;
        pivot.size = current_prev_size;

        //fixing parent attribute
        current.parent=pivot.parent;
        pivot.parent = current;
        if(pivot.left!=null)
            pivot.left.parent = pivot;

        return current;
    }
    /******************************************/

    /*** Helper methods used for element removal ***/
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
        node.size--;
        node.left = removeMin(node.left);
        return node;
    }
    /******************************************/


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

    private Node insert(Node node, K key, V value) {
        if(node == null) {
            return new Node(key, value);
        }
        node.size++;

        if (key.compareTo(node.key) < 0) {
            node.left = insert(node.left, key, value);
            node.left.parent = node;
        } else if (key.compareTo(node.key) > 0) {
            node.right = insert(node.right, key, value);
            node.right.parent = node;
        } else
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

    private Node remove(Node node, K key) {
        if (node == null)
            return null;
        node.size--;

        if (key.compareTo(node.key) < 0) {
            node.left.size++;
            node.left = remove(node.left, key);
            return node;
        } else if (key.compareTo(node.key) > 0) {
            //node.right.size--;
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
            successor.size=node.size;

            node.left = node.right = null;

            return successor;
        }
    }

    /**Returns pointer to node containing the ith smallest key of the tree**/
    Node select(Node node, int i){
        int size = 0;
        if (node.left == null)
            size = 1;
        else
            size = (node.left).size + 1;

        if (i < size && node.left!=null)
            return select(node.left, i);
        else if (i > size && node.right!=null)
            return select(node.right, i - size);
        else
            return node;
    }

    int rank(Node node, K key){
        Node y = search(node, key);

        if(y.left==null)
            return 1;

        int rank = y.left.size + 1;

        while(y != root){
          if(y.parent.right != null && y == y.parent.right)
              rank += y.parent.left.size+1;

          y = y.parent;
        }
        return rank;
    }

    public void print(){
        String prefix = "";
        print(root, prefix);
    }

    private void print(Node node, String prefix) {
        if(node == null) return;

        System.out.println(prefix + " ↳ (" + node.key + ": " + node.value + ") - " + node.size);
        print(node.left, prefix + "   ");
        print(node.right, prefix + "   ");
    }

    public Node search(K key){
        return search(root, key);
    }

    /**Returns the ith smallest key of the tree**/
    public K select(int i) {
        Node node = select(root, i);
        return node.key;
    }

    /**Returns the rank of key in the linear order determined by an inorder walk through the tree**/
    public int rank(K key){
        return rank(root, key);
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
