    int main() {
    
    link_type to_delete = position.node;
    link_type replace = to_delete;
    link_type xxx;
    if (left(replace) == NIL)
        xxx = right(replace);
    else
        if (right(replace) == NIL) 
            xxx = left(replace);
        else {
            replace = right(replace);
            while (left(replace) != NIL)
                replace = left(replace);
            xxx = right(replace);
        }
    if (replace != to_delete) { // relink replace in place of to_delete
        parent(left(to_delete)) = replace; 
        left(replace) = left(to_delete);
        if (replace != right(to_delete)) {
            parent(xxx) = parent(replace); // possibly xxx == NIL
            left(parent(replace)) = xxx;   // replace must be a left child
            right(replace) = right(to_delete);
            parent(right(to_delete)) = replace;
        } else
            parent(xxx) = replace;  // needed in case xxx == NIL
        if (root() == to_delete)
            root() = replace;
        else if (left(parent(to_delete)) == to_delete)
            left(parent(to_delete)) = replace;
        else 
            right(parent(to_delete)) = replace;
        parent(replace) = parent(to_delete);
        ::swap(color(replace), color(to_delete));
        replace = to_delete;
                       // replace points to node to be actually deleted
    } else {  // replace == to_delete
        parent(xxx) = parent(replace);   // possibly xxx == NIL
        if (root() == to_delete)
            root() = xxx;
        else 
            if (left(parent(to_delete)) == to_delete)
                left(parent(to_delete)) = xxx;
            else
                right(parent(to_delete)) = xxx;
        if (leftmost() == to_delete) 
            if (right(to_delete) == NIL)  // left(to_delete) must be NIL also
                leftmost() = parent(to_delete);
                // makes leftmost() == header if to_delete == root()
        else
            leftmost() = minimum(xxx);
        if (rightmost() == to_delete)  
            if (left(to_delete) == NIL) // right(to_delete) must be NIL also
                rightmost() = parent(to_delete);  
                // makes rightmost() == header if to_delete == root()
        else  // xxx == left(to_delete)
            rightmost() = maximum(xxx);
    }
    }