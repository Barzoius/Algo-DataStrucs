#include <iostream>
#include <memory>
#include <vector>
#include <queue>

template<typename V>
class Tree {

private:
    int arity;

    struct Node {
    public:
        V value;
        int index;
        int level;
        std::vector<std::unique_ptr<Node>> children;

        Node(const V& val, int idx) : value(val), index(idx) {}
        friend class Tree<V>;
    };

    std::unique_ptr<Node> root;

public:
    explicit Tree(int a) : arity(a), root(nullptr) {}

    void createRootNode(V val) {
        root = std::make_unique<Node>(val, 0);
        root -> level = 0;
    }

    void insert(V val) {
        if (!root) {
            createRootNode(val);
            return;
        }

        std::queue<Node*> nodes;
        nodes.push(root.get());

        while (!nodes.empty()) {
            Node* current = nodes.front();
            nodes.pop();

            if (current->children.size() < arity) {
                int newIndex = current->index * arity + current->children.size() + 1;
                current->children.push_back(std::make_unique<Node>(val, newIndex));
                return;
            } else {
                for (auto& child : current->children) {
                    nodes.push(child.get());
                }
            }
        }
    }

    void printTree() {
        if (!root) return;

        std::queue<Node*> nodes;
        nodes.push(root.get()); 

        while (!nodes.empty()) {
            Node* current = nodes.front();
            nodes.pop();

            std::cout << "Node value: " << current->value << ", Index: " << current->index << "\n";
            for (auto& child : current->children) {
                nodes.push(child.get());
            }
        }
    }
};

int main() {
    Tree<int> tree(3); // Example with arity 3

    tree.insert(1); // Root
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);

    tree.printTree();

    return 0;
}
