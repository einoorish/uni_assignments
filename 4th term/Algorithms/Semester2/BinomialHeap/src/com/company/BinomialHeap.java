package com.company;

class Node {
    int key;
    Node parent;
    Node sibling;
    Node child;
    int numOfChildren;

    Node(int key){
        this.key = key;
    }
}

public class BinomialHeap {


    private Node root;

    public void insert (Node node){
        BinomialHeap tempHeap = new BinomialHeap();
        tempHeap.root = node;

        root = this.merge(tempHeap).root;
    }

    private void pair(Node childNode, Node parentNode){
        childNode.parent = parentNode;
        childNode.sibling = parentNode.child;
        parentNode.child = childNode;
        parentNode.numOfChildren++;
    }

    private static Node mergeRoots(BinomialHeap h1, BinomialHeap h2){
        if(h1.root == null)
            return h2.root;
        if(h2.root == null)
            return h1.root;

        Node root;
        Node last;
        Node curr1 = h1.root;
        Node curr2 = h2.root;

        if (h1.root.numOfChildren <= h2.root.numOfChildren) {
            root = h1.root;
            curr1 = curr1.sibling;
        }
        else {
            root = h2.root;
            curr2 = curr2.sibling;
        }
        last = root;

        // Go through both root lists until reached the end of one of them
        while (curr1 != null && curr2 != null) {
            if (curr1.numOfChildren <= curr2.numOfChildren) {
                last.sibling = curr1;
                curr1 = curr1.sibling;
            } else {
                last.sibling = curr2;
                curr2 = curr2.sibling;
            }

            last = last.sibling;
        }

        // Merge remaining trees from other list
        if (curr1 != null)
            last.sibling = curr1;
        else
            last.sibling = curr2;

        h1.root = null;
        h2.root = null;

        return root;
    }

    public BinomialHeap merge(BinomialHeap anotherHeap){
        BinomialHeap result = new BinomialHeap();

        result.root = mergeRoots(this, anotherHeap); //merge root lists for both heaps sorted on degree of tree nodes.

        if (result.root == null)
            return result;

        Node prev = null;
        Node curr = result.root;
        Node next = curr.sibling;

        // Merge nodes with the same number of children
        while (next != null) {
            if (curr.numOfChildren != next.numOfChildren ||
                    (next.sibling != null && next.sibling.numOfChildren == curr.numOfChildren)) {
                // Skip
                prev = curr;
                curr = next;
            } else {
                // Combine trees with same degree
                if (curr.key < next.key) {
                    curr.sibling = next.sibling;
                    pair(next, curr);
                } else {
                    // Swap to preserve the order
                    if (prev == null)
                        result.root = next;
                    else
                        prev.sibling = next;

                    pair(curr, next);
                    curr = next;
                }
            }
            next = curr.sibling;
        }

        return result;
    }

    public int removeMin() {
        if (root == null)
            return -1;

        Node min = root;
        Node minPrev = null;
        Node curr = min.sibling;
        Node prev = min;

        // Find min in root list
        while (curr != null) {
            if (curr.key < min.key) {
                min = curr;
                minPrev = prev;
            }
            prev = curr;
            curr = curr.sibling;
        }

        // remove  min node from root list.
        if (min == root)
            root = min.sibling;
        else
            minPrev.sibling = min.sibling;

        // Add merge heap of min node children with existing tree.
        BinomialHeap temp = new BinomialHeap();

        Node minChild = min.child;
        while (minChild != null) {
            Node next = minChild.sibling;
            minChild.sibling = temp.root;
            temp.root = minChild;
            minChild = next;
        }
        root = this.merge(temp).root;

        return min.key;
    }

    public void displayHeap() {
        System.out.print("Heap : ");
        displayHeap(root);
        System.out.println("\n");
    }

    private void displayHeap(Node r) {
        if (r != null) {
            displayHeap(r.sibling);
            System.out.print(r.key + " ");
            displayHeap(r.child);
        }
    }

    public static void main(String[] args) {
        BinomialHeap heap = new BinomialHeap();

        for(int i=0; i<15; i++){
            heap.insert(new Node((int)Math.round(100*Math.random())));
        }

        heap.displayHeap();
        heap.removeMin();
        heap.displayHeap();
        heap.removeMin();
        heap.displayHeap();
    }
}
