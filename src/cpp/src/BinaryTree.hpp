#ifndef OOPPROJECT_RANGEBINARYTREE_HPP
#define OOPPROJECT_RANGEBINARYTREE_HPP

#include "ArrayList.hpp"

template <typename B, typename A>
class BinaryNode{
public:
    B tag;
    ArrayList<A> value;
    BinaryNode<B, A>* left;
    BinaryNode<B, A>* right;


    BinaryNode(B const& tag, A const& value){
        this->tag = tag;
        this->value.append(value);
        left = right = nullptr;
    }

    ~BinaryNode(){
        delete left;
        delete right;
    }

    static BinaryNode<B, A>* instance(B const& tag, A const&  value){
        return new BinaryNode(tag, value);
    }


    void populate(B const& ntag, A const& nvalue){

        if(tag == ntag){
            value.append(nvalue);
        }else if(tag > ntag){
            if(left == nullptr){
                left = BinaryNode::instance(ntag, nvalue);
            }
            else left->populate(ntag, nvalue);
        }else{
            if(right == nullptr){
                right = BinaryNode::instance(ntag, nvalue);
            }
            else right->populate(ntag, nvalue);
        }
    }

    BinaryNode<B, A>* firstMatch(bool predicate(B)){
        if(predicate(tag)) return this;
        if(left != nullptr){
            BinaryNode<B, A>* res = left->firstMatch(predicate);
            if(res != nullptr) return nullptr;
        }
        if(right != nullptr){
            BinaryNode<B, A>* res = right->firstMatch(predicate);
            if(res != nullptr) return nullptr;
        }
        return nullptr;
    }

    unique_ptr<ArrayList<A>> allInRange(B const& lower, B const& upper){
        unique_ptr<ArrayList<A>> range = make_unique<ArrayList<A>>();

        if(tag >= lower && tag <= upper){
            range->appendAll(value);
            if(tag != upper && right != nullptr) range->appendAll(*right->allInRange(lower, upper));
            if(tag != lower && left != nullptr) range->appendAll(*left->allInRange(lower, upper));
        }

        if(tag > upper){
            if(left!=nullptr) range->appendAll(*left->allInRange(lower, upper));
        }else if(tag < lower){
            if(right!=nullptr) range->appendAll(*right->allInRange(lower, upper));
        }

        return range;
    }
};

template <typename B, typename A>
class RangeBinaryTree{
private:
    BinaryNode<B, A>* root = nullptr;

    void free(){
        delete root;
    }

public:

    ~RangeBinaryTree(){
        free();
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    /**
     * This frees the original head so be careful
     */
    void setHead(BinaryNode<B, A> newHead){
        free();
        root = newHead;
    }

    const BinaryNode<B, A>* viewHead() const {
        return root;
    }

    BinaryNode<B, A>* getHead(){
        return root;
    }

    const BinaryNode<B, A>* findFirst(bool predicate(B)){
        return root->firstMatch(predicate);
    }

};

#endif //OOPPROJECT_RANGEBINARYTREE_HPP
