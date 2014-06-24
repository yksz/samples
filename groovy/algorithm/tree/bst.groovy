class BinarySearchTree<E> {
    class Node<E> {
        E data
        Node left, right
    }

    Node root

    def search(E data) {
        def node = root
        while (node != null) {
            if (data == node.data) {
                return node
            } else if (data < node.data) {
                node = node.left
            } else {
                node = node.right
            }
        }
        return null
    }

    def insert(E data) {
        if (root == null) {
            root = new Node(data: data)
            return
        }
        def node = root
        while (true) {
            if (data < node.data) {
                if (node.left) {
                    node = node.left
                } else {
                    node.left = new Node(data: data)
                    break
                }
            } else {
                if (node.right) {
                    node = node.right
                } else {
                    node.right = new Node(data: data)
                    break
                }
            }
        }
    }

    def delete(E data) {
        if (root == null) {
            return null
        }
        def node = root
        def parent
        boolean isLeft
        while (node != null) {
            if (data == node.data) {
                if (node.left && node.right) {
                    node.data = deleteMin(node.right, node)
                } else if (node.left) {
                    if (isLeft)
                        parent.left = node.left
                    else
                        parent.right = node.left
                } else if (node.right) {
                    if (isLeft)
                        parent.left = node.right
                    else
                        parent.right = node.right
                } else {
                    if (isLeft)
                        parent.left = null
                    else
                        parent.right = null
                }
                return data
            } else if (data < node.data) {
                parent = node
                node = node.left
                isLeft = true
            } else {
                parent = node
                node = node.right
                isLeft = false
            }
        }
        return null
    }

    private def deleteMin(Node node, Node parent) {
        if (node.left == null) {
            parent.right = node.right
            return node.data
        }
        while (node.left) {
            parent = node
            node = node.left
        }
        parent.left = node.right
        return node.data
    }

    // 1: preorder
    // 2: in-order
    // 3: postorder
    def traverse(int order) {
        switch (order) {
            case 1:
                println "[preorder]"
                preorder(root, "")
                println ""
                break
            case 2:
                println "[inorder]"
                inorder(root, "")
                println ""
                break
            case 3:
                println "[postorder]"
                postorder(root, "")
                println ""
                break
        }
    }

    private def preorder(Node node, indent) {
        if (node == null) {
            return
        }
        indent += "  "
        println indent + node.data
        preorder(node.left, indent)
        preorder(node.right, indent)
    }

    private def inorder(Node node, indent) {
        if (node == null) {
            return
        }
        indent += "  "
        inorder(node.left, indent)
        println indent + node.data
        inorder(node.right, indent)
    }

    private def postorder(Node node, indent) {
        if (node == null) {
            return
        }
        indent += "  "
        postorder(node.left, indent)
        postorder(node.right, indent)
        println indent + node.data
    }
}

def tree = new BinarySearchTree<Integer>()
tree.insert(8)
tree.insert(3)
tree.insert(10)
tree.insert(1)
tree.insert(6)
tree.insert(14)
tree.insert(4)
tree.insert(7)
tree.insert(13)
tree.traverse(2)
println "delete: " + tree.delete(6)
tree.traverse(2)
println "delete: " + tree.delete(1)
tree.traverse(2)
println "delete: " + tree.delete(14)
tree.traverse(2)
println "delete: " + tree.delete(8)
tree.traverse(2)
