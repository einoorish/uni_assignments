
class Node {
    Node child;
    Node left;
    Node right;
    Node parent;

    int key;
    int value;
    int degree;
    boolean aChildWasRemoved;

    public Node(int data, int key) {
        right = this;
        left = this;
        this.value = data;
        this.key = key;
    }
}

public class FibonacciHeap {

    private Node min;
    private int nodeCount;

    public void decreaseKey(Node target, int key) {
        target.key = key;

        if (target.parent != null && target.key < target.parent.key) {
            // Restoring heap property
            cut(target);
            cascadingCut(target.parent);
        }

        if (target.key < min.key)
            min = target;
    }

    public void insert(Node node) {
        if (min != null) {
            node.left = min;
            node.right = min.right;
            min.right = node;
            node.right.left = node;

            if (node.key < min.key)
                min = node;
        } else {
            min = node;
        }

        nodeCount++;
    }

    public int removeMin() {
        Node temp = min;

        if (temp != null) {
            Node current = temp.child;
            Node tempRight;

            for(int i = temp.degree; i>0 ;i--) {
                tempRight = current.right;

                // Remove current from child list
                current.left.right = current.right;
                current.right.left = current.left;

                // Add current to root list of heap
                current.left = min;
                current.right = min.right;
                min.right = current;
                current.right.left = current;

                // Set parent[current] to null
                current.parent = null;
                current = tempRight;
            }

            // Remove temp from root list of heap
            temp.left.right = temp.right;
            temp.right.left = temp.left;

            if (temp == temp.right) {
                min = null;
            } else {
                min = temp.right;
                // Pair heaps if neccassary
                consolidate();
            }

            // Decrement size of heap
            nodeCount--;
        }

        return temp.value;
    }


    /** Cuts all nodes that that had their child removed and add them to root list
     * stops when met the first unmarked node */
    private void cascadingCut(Node node) {
        if (node.parent != null) {
            if (!node.aChildWasRemoved) {
                node.aChildWasRemoved = true;
            } else {
                // it's marked, cut it from parent
                cut(node);

                // cut the nodes above too
                cascadingCut(node.parent);
            }
        }
    }

    /** Pairs all nodes with the same degree. Used when removing min. */
    private void consolidate() {
        if(min == null)
            return;

        // golden ratio degrees limit
        final double phi = (1.0 + Math.sqrt(5.0)) / 2.0;
        int numOfDegrees = (int) Math.floor(Math.log(nodeCount) / Math.log(phi));
        Node[] degreeIndex = new Node[numOfDegrees+1];

        for (int i = 0; i < numOfDegrees; i++) {
            degreeIndex[i] = null;
        }

        int rootNodesCount = 0;
        Node curr = min;

        rootNodesCount++;
        curr = curr.right;

        while (curr != min) {
            rootNodesCount++;
            curr = curr.right;
        }

        while (rootNodesCount > 0) {
            int currDegree = curr.degree;
            Node next = curr.right;

            // Look for a node with the same degree
            while (degreeIndex[currDegree]!=null) {
                Node x = degreeIndex[currDegree];

                if (curr.key > x.key) {
                    Node temp = x;
                    x = curr;
                    curr = temp;
                }

                pair(x, curr); //pair nodes with same degree

                degreeIndex[currDegree]= null;
                currDegree++;
            }

            degreeIndex[currDegree] = curr;

            curr = next;
            rootNodesCount--;
        }

        // Reintialize tree from dIndex
        min = null;

        for (int i = 0; i < numOfDegrees; i++) {
            Node y = degreeIndex[i];
            if (y!= null) {
                if (min != null) {
                    // First remove node from root list.
                    y.left.right = y.right;
                    y.right.left = y.left;

                    // Add back to root list
                    y.left = min;
                    y.right = min.right;
                    min.right = y;
                    y.right.left = y;

                    if (y.key < min.key)
                        min = y;
                } else {
                    min = y;
                }
            }
        }
    }

    /** Cut the node and put it in root list. */
    private void cut(Node removed) {
        removed.left.right = removed.right;
        removed.right.left = removed.left;
        removed.parent.degree--;

        if (removed.parent.degree == 0)
            removed.parent.child = null;

        if (removed.parent.child == removed)
            removed.parent.child = removed.right;

        // adding node to root list
        removed.left = min;
        removed.right = min.right;
        min.right = removed;

        removed.right.left = removed;
        removed.parent = null;
        removed.aChildWasRemoved = false;
    }

    private void pair(Node childNode, Node parentNode) {
        // Remove child from root list
        childNode.left.right = childNode.right;
        childNode.right.left = childNode.left;

        childNode.parent = parentNode;

        if (parentNode.child == null) {
            parentNode.child = childNode;
            childNode.right = childNode;
            childNode.left = childNode;
        } else {
            childNode.left = parentNode.child;
            childNode.right = parentNode.child.right;
            parentNode.child.right = childNode;
            childNode.right.left = childNode;
        }

        // increase degree[great] and mark as false as it is in
        // root list.
        parentNode.degree++;
        childNode.aChildWasRemoved = false;
    }

    public static void main(String[] args){
        FibonacciHeap b = new FibonacciHeap();
        Node[] t;
        t = new Node[10];
        System.out.println("Inserted: ");
        for(int i = 0; i < 10; i++){
            t[i] = new Node(i, 10 + (int)Math.round(30*Math.random()));
            b.insert(t[i]);

            System.out.println(t[i].value + ": " + t[i].key);
        }
        System.out.println("Decreased key for 3 and 9");
        b.decreaseKey(t[3],3);
        b.decreaseKey(t[9],9);

        System.out.println("Removing min:");
        while( b.min!=null){
            int x = b.removeMin();
            System.out.println(t[x].value + ": " + t[x].key);
        }
    }

}

