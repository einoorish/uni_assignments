package com.company;

import java.lang.*;
import java.util.*;

class BplusTree<K extends Comparable<K>, V> {
    private int order;
    private InternalNode root;
    private LeafNode firstLeaf;

    BplusTree(int order) {
        this.order = order;
        this.root = null;
    }
    
    private class Record implements Comparable<Record>{
        K key;
        V value;
        
        Record(K key, V value) {
            this.key = key;
            this.value = value;
        }

        @Override
        public int compareTo(Record t1) {
            return this.key.compareTo(t1.key);
        }
    }

    /*~~~~~~~~~~~~~~~~ HELPER FUNCTIONS ~~~~~~~~~~~~~~~~*/

    private int linearSearch(K key, List<Record> sortedRecords) {
        Comparator<Record> comp = (o1, o2) -> {
            K a = o1.key;
            K b = o2.key;
            return a.compareTo(b);
        };

        for(int i = 0; i < sortedRecords.size(); i++){
            if(sortedRecords.get(i)!=null && sortedRecords.get(i).key == key){
                    return i;
            }

        }
        return -1;
    }

    private LeafNode findCurrLeafNode(K key) {
        List<K> keys = root.keys;
        int i;

        for (i = 0; i < root.degree - 1; i++) {
            if (key.compareTo(keys.get(i))<0) break;
        }

        Node childNode = root.childPointers.get(i);
        if (childNode instanceof BplusTree.LeafNode) {
            return (LeafNode)childNode;
        } else {
            return findCurrLeafNode((InternalNode) childNode, key);
        }
    }

    private LeafNode findCurrLeafNode(InternalNode node, K key) {
        List<K> keys = node.keys;
        int i;

        for (i = 0; i < node.degree - 1; i++) {
            if (key.compareTo(keys.get(i))<0) break;
        }

        Node childNode = node.childPointers.get(i);
        if (childNode instanceof BplusTree.LeafNode) {
            return (LeafNode)childNode;
        } else {
            return findCurrLeafNode((InternalNode) node.childPointers.get(i), key);
        }
    }

    private int findNodeIndex(List<Node> nodes, LeafNode targetNode) {
        for (int i = 0; i < nodes.size(); i++)
            if (nodes.get(i) == targetNode) return i;

        return -1;
    }

    private int getMidpoint() {
        return (int)Math.ceil((this.order+ 1) / 2.0) - 1;
    }

    private void handleDeficiency(InternalNode in) {
        InternalNode sibling;
        InternalNode parent = in.parent;

        if (this.root == in) {
            for (int i = 0; i < in.childPointers.size(); i++) {
                if (in.childPointers.get(i) != null) {
                    if (in.childPointers.get(i) instanceof BplusTree.InternalNode) {
                        this.root = (InternalNode) in.childPointers.get(i);
                        this.root.parent = null;
                    } else if (in.childPointers.get(i) instanceof BplusTree.LeafNode) {
                        this.root = null;
                    }
                }
            }
        }

        else if (in.leftSibling != null && in.leftSibling.isLendable()) {
            sibling = in.leftSibling;
        } else if (in.rightSibling != null && in.rightSibling.isLendable()) {
            sibling = in.rightSibling;

            K borrowedKey = sibling.keys.get(0);
            Node pointer = sibling.childPointers.get(0);

            in.keys.set(in.degree - 1, parent.keys.get(0));
            in.childPointers.set(in.degree, pointer);

            parent.keys.set(0, borrowedKey);

            sibling.removePointer(0);
            sibling.keys.sort(Comparator.naturalOrder());
            sibling.removePointer(0);
            shiftDown(in.childPointers, 1);
        }
        else if (in.rightSibling != null && in.rightSibling.isMergeable()) {
            sibling = in.rightSibling;

            sibling.keys.set(sibling.degree - 1, parent.keys.get(parent.degree - 2));
            sibling.keys.sort(Comparator.naturalOrder());
            parent.keys.set(parent.degree - 2, null);

            for (int i = 0; i < in.childPointers.size(); i++) {
                if (in.childPointers.get(i) != null) {
                    sibling.prependChildPointer(in.childPointers.get(i));
                    in.childPointers.get(i).parent = sibling;
                    in.removePointer(i);
                }
            }

            parent.removePointer(in);

            sibling.leftSibling = in.leftSibling;
        }

        if (parent != null && parent.isDeficient()) {
            handleDeficiency(parent);
        }
    }

    private int linearSearchForNull(List pointers) {
        for (int i = 0; i <  pointers.size(); i++) {
            if (pointers.get(i) == null) { return i; }
        }
        return -1;
    }


    private void shiftDown(List<Node> pointers, int amount) {
        List<Node> newPointers = new ArrayList<Node>(this.order + 1);
        for (int i = amount; i < pointers.size(); i++) {
            newPointers.set(i - amount, pointers.get(i));
        }
        pointers = newPointers;
    }



    private List<Node> splitChildPointers(InternalNode in, int split) {
        List<Node> pointers = in.childPointers;
        List<Node> halfPointers = new ArrayList<Node>(this.order + 1);

        // Copy half of the values into halfPointers while updating original keys
        for (int i = split + 1; i < pointers.size(); i++) {
            halfPointers.add(i - split - 1, pointers.get(i));
            in.removePointer(i);
        }

        return halfPointers;
    }

    private List<Record> splitRecords(LeafNode ln) {
        int midpoint = getMidpoint();

        List<Record> records = ln.records;
        List<Record> half = new ArrayList<>(this.order);

        for (int i = midpoint; i < records.size(); i++) {
            half.add(i - midpoint, records.get(i));
            ln.delete(i);
        }

        return half;
    }

    private void splitInternalNode(InternalNode in) {
        InternalNode parent = in.parent;

        int midpoint = getMidpoint();
        K newParentKey = in.keys.get(midpoint);
        List<K> halfKeys = splitKeys(in.keys, midpoint);
        List<Node> halfPointers = splitChildPointers(in, midpoint);

        in.degree = linearSearchForNull(in.childPointers);

        InternalNode sibling = new InternalNode(this.order, halfKeys, halfPointers);
        for (Node pointer : halfPointers) {
            if (pointer != null) { pointer.parent = sibling; }
        }

        sibling.rightSibling = in.rightSibling;
        if (sibling.rightSibling != null) {
            sibling.rightSibling.leftSibling = sibling;
        }
        in.rightSibling = sibling;
        sibling.leftSibling = in;

        if (parent == null) {

            List<K> keys = new ArrayList<K>(this.order);
            keys.add(0, newParentKey);
            InternalNode newRoot = new InternalNode(this.order, keys);
            newRoot.appendChild(in);
            newRoot.appendChild(sibling);
            this.root = newRoot;

            in.parent = newRoot;
            sibling.parent = newRoot;

        } else {

            parent.keys.set(parent.degree - 1, newParentKey);
            parent.keys.sort(Comparator.naturalOrder());

            int pointerIndex = parent.getNodeIndex(in) + 1;
            parent.insertChild(sibling, pointerIndex);
            sibling.parent = parent;
        }
    }

    private List<K> splitKeys(List<K> keys, int split) {
        List<K> halfKeys = new ArrayList<K>(order);

        keys.set(split, null);

        for (int i = split + 1; i < keys.size(); i++) {
            halfKeys.add(i - split - 1, keys.get(i));
            keys.set(i, null);
        }

        return halfKeys;
    }

    /*~~~~~~~~~~~~~~~~ DELETE, INSERT, SEARCH ~~~~~~~~~~~~~~~~*/

    public void delete(K key) {
        if (firstLeaf == null) {
            return;
        }
        LeafNode ln = (this.root == null) ? this.firstLeaf : findCurrLeafNode(root, key);
        int keyIndex = linearSearch(key, ln.records);

        if (keyIndex < 0) {
            System.err.println("Key not found.");
        } else {
            ln.delete(keyIndex);

            if (ln.isDeficient()) {
                LeafNode sibling;
                InternalNode parent = ln.parent;

                if (ln.leftSibling != null &&
                        ln.leftSibling.parent == ln.parent &&
                        ln.leftSibling.isLendable()) {

                    sibling = ln.leftSibling;
                    Record borrowedDP = sibling.records.get(sibling.numRecords - 1);

                    ln.insert(borrowedDP);
                    ln.records.sort(Comparator.naturalOrder());
                    sibling.delete(sibling.numRecords - 1);

                    int pointerIndex = findNodeIndex(parent.childPointers, ln);
                    if (!(borrowedDP.key.compareTo(parent.keys.get(pointerIndex - 1)) >= 0)) {
                        parent.keys.set(pointerIndex - 1, ln.records.get(0).key);
                    }

                } else if (ln.rightSibling != null &&
                        ln.rightSibling.parent == ln.parent &&
                        ln.rightSibling.isLendable()) {

                    sibling = ln.rightSibling;
                    Record borrowedDP = sibling.records.get(0);

                    ln.insert(borrowedDP);
                    sibling.delete(0);
                    sibling.records.sort(Comparator.naturalOrder());

                    int pointerIndex = findNodeIndex(parent.childPointers, ln);
                    if (!(borrowedDP.key.compareTo(parent.keys.get(pointerIndex)) < 0)) {
                        parent.keys.set(pointerIndex, sibling.records.get(0).key);
                    }
                }
                else if (ln.leftSibling != null &&
                        ln.leftSibling.parent == ln.parent &&
                        ln.leftSibling.isMergeable()) {

                    sibling = ln.leftSibling;
                    int pointerIndex = findNodeIndex(parent.childPointers, ln);

                    parent.removeKey(pointerIndex - 1);
                    parent.removePointer(ln);

                    sibling.rightSibling = ln.rightSibling;

                    if (parent.isDeficient())
                        handleDeficiency(parent);

                } else if (ln.rightSibling != null &&
                        ln.rightSibling.parent == ln.parent &&
                        ln.rightSibling.isMergeable()) {

                    sibling = ln.rightSibling;
                    int pointerIndex = findNodeIndex(parent.childPointers, ln);

                    parent.removeKey(pointerIndex);
                    parent.removePointer(pointerIndex);

                    sibling.leftSibling = ln.leftSibling;
                    if (sibling.leftSibling == null)
                        firstLeaf = sibling;

                    if (parent.isDeficient())
                        handleDeficiency(parent);
                }

            } else if (this.root == null && this.firstLeaf.numRecords == 0) {
                this.firstLeaf = null;
            } else {
                try {
                    ln.records.sort(Comparator.naturalOrder());
                }catch (NullPointerException e){
                    //size != capacity
                }
            }
        }
    }

    public void insert(K key, V value){
        if (firstLeaf == null) {
            firstLeaf = new LeafNode(this.order, new Record(key, value));
            return;
        }

        LeafNode ln = (root == null) ? firstLeaf : findCurrLeafNode(root, key);

        ln.insert(new Record(key, value));

        if(ln.isOverfull()) {
            List<Record> half = splitRecords(ln);

            if (ln.parent == null) {
                // Create internal node to serve as parent
                List<K> parentKeys = new ArrayList<>(order);
                parentKeys.add(0, half.get(0).key);
                InternalNode parent = new InternalNode(this.order, parentKeys);
                ln.parent = parent;
                parent.appendChild(ln);
            } else {
                // Add new key to parent for proper indexing
                K newParentKey = half.get(0).key;
                ln.parent.keys.add(ln.parent.degree - 1, newParentKey);
                ln.parent.keys.sort(Comparator.naturalOrder());
            }
            // Create new LeafNode that holds the other half
            LeafNode newLeafNode = new LeafNode(this.order, half, ln.parent);

            //Update parent
            int nodeIndex = ln.parent.getNodeIndex(ln) + 1;
            ln.parent.insertChild(newLeafNode, nodeIndex);

            //Update siblings
            newLeafNode.rightSibling = ln.rightSibling;
            if (newLeafNode.rightSibling != null)
                newLeafNode.rightSibling.leftSibling = newLeafNode;
            ln.rightSibling = newLeafNode;
            ln.rightSibling.numRecords = half.size();
            newLeafNode.leftSibling = ln;

            if (this.root == null) {
                this.root = ln.parent;
            } else {
                //repeat the process until no deficiencies are found up the tree
                InternalNode in = ln.parent;
                while (in != null) {
                    if (!in.isOverfull())
                        break;

                    splitInternalNode(in);
                    in = in.parent;
                }
            }
        }
    }

    public V search(K key) {
        if (firstLeaf == null) return null;

        LeafNode ln = (this.root == null) ? this.firstLeaf : findCurrLeafNode(root, key);

        int index = linearSearch(key, ln.records);
        if(index == -1) return null;

        return ln.records.get(index).value;
    }

    public ArrayList<V> search(K lowerBound, K upperBound) {
        ArrayList<V> values = new ArrayList<V>();

        LeafNode currNode = this.firstLeaf;
        while (currNode != null) {

            for (Record record : currNode.records) {
                if (record == null)
                    break;

                if (lowerBound.compareTo(record.key) <= 0 && record.key.compareTo(upperBound) <= 0) {
                    values.add(record.value);
                }
            }

            currNode = currNode.rightSibling;
        }
        return values;
    }

    class Node {
        InternalNode parent;
    }

    private class InternalNode extends Node {
        int maxDegree;
        int minDegree;
        int degree;
        InternalNode leftSibling;
        InternalNode rightSibling;
        List<K> keys;
        List<Node> childPointers;

        private void appendChild(Node child) {
            childPointers.add(child);
            this.degree++;
        }

        private int getNodeIndex(Node pointer) {
            for (int i = 0; i < childPointers.size(); i++)
                if (childPointers.get(i) == pointer) return i;
            return -1;
        }

        private void insertChild(Node pointer, int index) {
            for (int i = degree - 1; i >= index ;i--) {
                childPointers.set(i + 1, childPointers.get(i));
            }
            childPointers.add(index, pointer);
            degree++;
        }

        private boolean isDeficient() { return this.degree < this.minDegree; }

        private boolean isLendable() { return this.degree > this.minDegree; }

        private boolean isMergeable() { return this.degree == this.minDegree; }

        private boolean isOverfull() {
            return this.degree == maxDegree + 1;
        }

        private void prependChildPointer(Node pointer) {
            for (int i = degree - 1; i >= 0 ;i--) {
                childPointers.set(i + 1, childPointers.get(i));
            }
            childPointers.set(0, pointer);
            degree++;
        }

        private void removeKey(int index) { keys.set(index, null); }

        private void removePointer(int index) {
            childPointers.set(index, null);
            degree--;
        }

        private void removePointer(Node pointer) {
            for (int i = 0; i < childPointers.size(); i++)
                if (childPointers.get(i) == pointer) { childPointers.set(i, null); }
            this.degree--;
        }

        private InternalNode(int m, List<K> keys) {
            this.maxDegree = m;
            this.minDegree = (int)Math.ceil(m/2.0);
            this.degree = 0;
            this.keys = keys;
            this.childPointers = new ArrayList<Node>(this.maxDegree+1);
        }

        private InternalNode(int m, List<K> keys, List<Node> pointers) {
            this.maxDegree = m;
            this.minDegree = (int)Math.ceil(m/2.0);
            this.degree = linearSearchForNull(pointers);
            this.keys = keys;
            this.childPointers = pointers;
        }
    }

    public class LeafNode extends Node {
        int maxNumRecords;
        int minNumRecords;
        int numRecords;
        LeafNode leftSibling;
        LeafNode rightSibling;
        List<Record> records;

        public void delete(int index) {
            records.set(index, null);
            numRecords--;
        }

        public boolean isDeficient() { return numRecords < minNumRecords; }

        public boolean isOverfull() { return numRecords > maxNumRecords; }

        public boolean isLendable() { return numRecords > minNumRecords; }

        public boolean isMergeable() { return numRecords == minNumRecords; }

        public LeafNode(int m, Record dp) {
            this.maxNumRecords = m - 1;
            this.minNumRecords = (int)(Math.ceil(m/2) - 1);
            this.records = new ArrayList<Record>(m);
            this.numRecords = 0;
            this.insert(dp);
        }

        public LeafNode(int m, List<Record> records, InternalNode parent) {
            this.maxNumRecords = m - 1;
            this.minNumRecords = (int)(Math.ceil(m/2) - 1);
            this.records = records;
            this.numRecords = linearSearchForNull(records);
            this.parent = parent;
        }

        public void insert(Record record) {
            records.add(record);
            numRecords++;
            try{
                records.sort(Comparator.naturalOrder());
            }catch (NullPointerException e){
                //actual size < capacity
            }
        }
    }


    public static void main(String[] args) {
        BplusTree<Integer, String> tree = new BplusTree<>(3);
        tree.insert(5, "five");
        tree.insert(1, "one");
        tree.insert(2, "two");
        tree.insert(7, "seven");
        tree.insert(3, "three");
        tree.insert(5, "five");
        tree.insert(9, "nine");

        System.out.println(tree.search(9));
        System.out.println(tree.search(2));

        tree.delete(9);

        System.out.println(tree.search(9));
    }
}
